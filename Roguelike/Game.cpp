#include "stdafx.h"
#include "Game.h"
using namespace std;

/* Sets the command window states.                                                               */
bool Game::init()
{
	/*  This bunch of code deals with setting the console state.  */ 
	// Set the font size and family.
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 25;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	if (SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi) == 0)
		return false;

	// Stop the cursor from blinking.
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	if (SetConsoleCursorInfo(out, &cursorInfo) == 0)
		return false;
	
	// Name the window.
	if (SetConsoleTitle(L"BENEATH") == 0)
		return false;

	mCurrentLevel = 0;

	return true;
}

/* Loads all data from binary files.                                                             */
bool Game::loadLevel()
{
	if (!newLevel(++mCurrentLevel))
		return false;

	system("cls");
	return true;
}

bool Game::newLevel(const int levelNumber)
{
	bool validLoading = true;
	cout << "Loading resources...";
	string level = std::to_string(levelNumber);

	Loader loader(Loader::MAP);
	if (!loader.load("binaries/map" + level + ".bin", mNakedMap))
		validLoading = false;
	if (!loader.setType(Loader::DOOR).load("binaries/doors" + level + ".bin", mDoorList))
		validLoading = false;
	if (!loader.setType(Loader::ITEM).load("binaries/items" + level + ".bin", mItemList))
		validLoading = false;
	return validLoading;
}

void Game::resetLevel()
{
	mNakedMap.clear();
	mDoorList.clear();
	mItemList.clear();

	mPlayer.newLevel(1, 1);
}

/* The game loop - calls the three main Game methods until an exit condition is detected.        */
void Game::run()
{
	if (TheMenu::Instance()->run(mBuffer))
	{
		mCurrentState = STATE_GAME;
		characterChoice();
		draw();
		while (mIsPlaying)
		{
			getInput();
			update();
			draw();
		}
	}
}

/* A big switch/case nestled within a while statement. This while loop decides whether the input //
/* demonstrates the need for a break and a call to the update and draw methods.                  */
void Game::getInput()
{
	bool validInput = false;
	while (!validInput)					// validInput is set to true when the update() or draw() methods require
										// calling. Examples of when this is not the case include an invalid input
										// (moving into a wall, opening a door which is not there) or inputs which 
										// do not require a change to the draw state.
	{
		int value = _getch();
		switch (value)
		{
		case ESCAPE:
			if (mCurrentState == STATE_GAME_MENU)
			{
				mCurrentState = STATE_END;
				validInput = true;
				break;
			}
			if (mCurrentState == STATE_GAME)
			{
				mCurrentState = STATE_GAME_MENU;
				validInput = true;
				break;
			}
			break;
		case CHANGE_SCOPE:
			switch (mCurrentScope)
			{
			case SCOPE_ACTION:
				mCurrentScope = SCOPE_ATTACK;
				break;
			case SCOPE_ATTACK:
				mCurrentScope = SCOPE_END_TURN;
				break;
			case SCOPE_END_TURN:
				mCurrentScope = SCOPE_ACTION;
				break;
			}
			validInput = true;
			break;
		case ACCEPT:
			if (mCurrentState == STATE_GAME_MENU)
			{
				mCurrentState = STATE_GAME;
				validInput = true;
				break;
			}
			else if (mCurrentState == STATE_GAME)
			{
				if (mUpdateDialogue != "")
				{
					mUpdateDialogue = "";
					validInput = true;
					break;
				}
				if (mCurrentScope == SCOPE_END_TURN)
				{
					mBuffer.clear();
					mBuffer.drawDialogue("Ending turn... Press any one key to continue...", 2);
					mBuffer.print();
					_getch();

					mPlayer.reset();
					mCurrentScope = SCOPE_ACTION;
				}
				validInput = true;
				break;
			}
			break;
		case MOVE_NORTH:
			validInput = mPlayer.move(0, -1, getMap());
			break;
		case MOVE_SOUTH:
			validInput = mPlayer.move(0, 1, getMap());
			break;
		case MOVE_WEST:
			validInput = mPlayer.move(-1, 0, getMap());
			break;
		case MOVE_EAST:
			validInput = mPlayer.move(1, 0, getMap());
			break;
		case MOVE_NORTH_WEST:
			validInput = mPlayer.move(-1, -1, getMap());
			break;
		case MOVE_SOUTH_EAST:
			validInput = mPlayer.move(1, 1, getMap());
			break;
		case MOVE_NORTH_EAST:
			validInput = mPlayer.move(1, -1, getMap());
			break;
		case MOVE_SOUTH_WEST:
			validInput = mPlayer.move(-1, 1, getMap());
			break;
		case OPEN:
			for (auto &door : mDoorList)
			{
				if (door.nextTo(mPlayer.getPosX(), mPlayer.getPosY()))
				{
					if (mPlayer.getActionPoints() > 0)
					{
						door.OpenClose();
						mPlayer.takeAction();
						validInput = true;
						break;
					}
				}
			}
			break;
		case HELP:
			{
				int inputQuery = _getch();
				switch (inputQuery)
				{
				case '/':
					mUpdateDialogue = "/: An open door.";
					break;
				case '+':
					mUpdateDialogue = "+: A closed door.";
					break;
				case '#':
					mUpdateDialogue = "#: A stretch of wall.";
					break;
				case '.':
					mUpdateDialogue = ".: The floor.";
					break;
				case '@':
					mUpdateDialogue = "@: You.";
					break;
				case '0':
					mUpdateDialogue = "0: Level exit.";
					break;
				default:
					mUpdateDialogue = "Not a valid key.";
					break;
				}
			}
			validInput = true;
			break;
		case INVENTORY:
			mPlayer.inventoryMenu(mBuffer);
			validInput = true;
			break;
		}
	}
}

/* The game prints by updating a buffer with the various map draw states and object positions and //
/* then printing that. This method deals with updating this buffer and a number of interactions   //
/* in the game world (picking up items, for example).                                             */
void Game::update()
{
	// Deal with the player standing on an item. 
	for (int x = 0; x != mItemList.size(); ++x)
	{
		if ((mPlayer.getPosX() == mItemList[x]->getPosX()) && (mPlayer.getPosY() == mItemList[x]->getPosY()))
		{
			mPlayer.addItem(mItemList[x]);
			mUpdateDialogue = "You have picked up: " + mItemList[x]->getName();
			mItemList[x] = nullptr;
			mItemList.erase(remove(mItemList.begin(), mItemList.end(), nullptr), mItemList.end());
			
			break;
		}
	}

	if (mCurrentState == STATE_END)
		quit();
	if (mPlayer.turnEnd)
	{
		if (mCurrentLevel == 2)
		{
			mCurrentState = STATE_END;
			mBuffer.clear();
			mBuffer.drawDialogue("You have won!");
			mBuffer.print();
		}
		else{
			mBuffer.clear();
			mBuffer.drawDialogue("Now you head... beneath!", 2);
			mBuffer.print();
			_getch();
			resetLevel();
			loadLevel();
		}
	}
		
}

/*  Prints the buffer, and any additional information, to the screen.                             */
void Game::draw()
{
	if (mCurrentState == STATE_GAME)
	{
		mBuffer.clear();
		updateBuffer();
		mBuffer.print();
	}
	if (mCurrentState == STATE_GAME_MENU)
		runGameMenu();
}

/*  The map is stored in its own variable as just the floor and walls. This method returns the    //
/*  same map, with items, doors and the player added on. It is needed to update the buffer, as    //
/*  well as for other calculations.                                                               */
vector<string> Game::getMap()
{
	vector<string> returnValue = mNakedMap;

	for (auto doors : mDoorList)
		returnValue[doors.getYPos()][doors.getXPos()] = (doors.isOpen()) ? '/' : '+';
	for (auto items : mItemList)
		returnValue[items->getPosY()][items->getPosX()] = items->getChar();
	returnValue[mPlayer.getPosY()][mPlayer.getPosX()] = '@';

	return returnValue;
}

vector<string> Game::getHiddenMap()
{
	// Load the naked map with all the updated objects printed on top.
	vector<string> updateMap = getMap();

	/* Now we deal with getting the visible map: hiding the map behind doors and (TODO) implementing//
	/* a line of sight.                                                                             */
	for (auto door : mDoorList)
	{
		if (door.isVertical() && !door.isOpen())
		{
			if (mPlayer.getPosX() < door.getXPos())
			{
				for (auto &s : updateMap)						// Hide the map right of the door.
				for (int x = 0; x < s.length(); ++x)
				if (x > door.getXPos())
					s[x] = ' ';
			}
			else {
				for (auto &s : updateMap)						// Hide the map left of the door.
				for (int x = 0; x < s.length(); ++x)
				if (x < door.getXPos())
					s[x] = ' ';
			}
		}
		else if (!door.isVertical() && !door.isOpen()) {
			if (mPlayer.getPosY() < door.getYPos())
			{
				for (int x = 0; x < updateMap.size(); ++x)	// Hide the map south of the door.
				if (x > door.getYPos())
				for (auto &c : updateMap[x])
					c = ' ';
			}
			else {
				for (int x = 0; x < updateMap.size(); ++x)	// Hide the map north of the door.
				if (x < door.getYPos())
				for (auto &c : updateMap[x])
					c = ' ';
			}
		}
	}

	return updateMap;
}

vector<string> Game::getMenuBar()
{
	// Now we construct the menu bar.
	vector<string> menuBar;

	switch (mCurrentScope)
	{
	case SCOPE_ACTION:
		menuBar.push_back(" |   *ACTION*   |    ATTACK    |    END TURN    |");
		menuBar.push_back(" -              --------------------------------");
		menuBar.push_back(" | [o]pen       |");
		menuBar.push_back(" ----------------");
		break;
	case SCOPE_ATTACK:
		menuBar.push_back(" |    ACTION    |   *ATTACK*   |    END TURN    |");
		menuBar.push_back(" -----------------------------------------------");
		break;
	case SCOPE_END_TURN:
		menuBar.push_back(" |    ACTION    |    ATTACK    |   *END TURN*   |");
		menuBar.push_back(" -----------------------------------------------");
		break;
	}

	return menuBar;
}

/*  First creates a visible map, based on the player's position, from the map returned by getMap().//
/*  This is then converted into a string containing the valid  formatting characters, appended any //
/*  update messages, and returned.                                                                 */
bool Game::updateBuffer()
{
	mBuffer.drawLine(" ------------------*BENEATH*--------------------", 0);
	mBuffer.drawLine("                Caves: Level " + std::to_string(mCurrentLevel), 1);
	mBuffer.drawLine(" -----------------------------------------------", 2);

	auto map = getHiddenMap();
	for (auto &s : map)
	{
		s.erase(remove(s.begin(), s.end(), '\n'), s.end());
		s.erase(remove(s.begin(), s.end(), '\r'), s.end());
	}
	for (int x = 0; x < map.size(); ++x)
		mBuffer.drawLine(map[x], x+3, 5);

	mBuffer.drawLine(" -----------------------------------------------", 11);

	auto menu = getMenuBar();
	for (int x = 0; x < menu.size(); ++x)
		mBuffer.drawLine(menu[x], x+12);	

	mBuffer.drawLine("Movement: " + to_string(mPlayer.getMovementPoints()), 3, 50);
	mBuffer.drawLine("Action: " + to_string(mPlayer.getActionPoints()), 4, 50);
	mBuffer.drawLine("Health: " + to_string(mPlayer.getHealth()), 5, 50);

	if (mUpdateDialogue != "")
		mBuffer.drawDialogue(mUpdateDialogue);
	return true;
}

void Game::characterChoice()
{
	bool choosing = true;
	int choice = 1;
	while (choosing)
	{
		mBuffer.clear();
		int lineNumber = 1;
		mBuffer.drawLine("One member of Herr. Zimmer's team survived the crash.", lineNumber++, 1);
		mBuffer.drawLine("Choose your character.", lineNumber++, 1);

		lineNumber = 5;
		mBuffer.drawLine("Ingrid Hoffman", lineNumber++, 8);
		mBuffer.drawLine("Horst Weber", lineNumber++, 8);
		mBuffer.drawLine("Wolfgang Beutel", lineNumber++, 8);
		mBuffer.drawLine("Ilse Hahn", lineNumber++, 8);

		lineNumber = 10;
		mBuffer.drawLine("                                       ___", lineNumber++, 20);
		mBuffer.drawLine("                                      /  /]", lineNumber++, 20);
		mBuffer.drawLine("                                     /  / ]", lineNumber++, 20);
		mBuffer.drawLine("                 )           _____,.-\" /__]", lineNumber++, 20);
		mBuffer.drawLine("                         ,-\"             _>", lineNumber++, 20);
		mBuffer.drawLine("                  (     _/           ,.-\"`", lineNumber++, 20);
		mBuffer.drawLine("                 )     / |     _,.-\"`", lineNumber++, 20);
		mBuffer.drawLine("      0          (    /. /    |", lineNumber++, 20);
		mBuffer.drawLine("     /|\\_         )  ,  /`  ./", lineNumber++, 20);
		mBuffer.drawLine("    / |          (   \\_/   //  _", lineNumber++, 20);
		mBuffer.drawLine("     / \\          )  /    //==(_)", lineNumber++, 20);
		mBuffer.drawLine("    /   \\         _,~'#   (/.", lineNumber++, 20);
		mBuffer.drawLine("--------------------------------------#--#--------------------", lineNumber++, 1);

		if (choice == 1)
		{
			mBuffer.drawLine("A talented scientist, easy to scare.", 10, 5);
			mBuffer.drawLine("<----", 5, 30);
		}
		if (choice == 2)
		{
			mBuffer.drawLine("A weapons expert, wearing only a vest top.", 10, 5);
			mBuffer.drawLine("<----", 6, 30);
		}
		if (choice == 3)
		{
			mBuffer.drawLine("A military man, terrified of rats.", 10, 5);
			mBuffer.drawLine("<----", 7, 30);
		}
		if (choice == 4)
		{
			mBuffer.drawLine("An seasoned archaeologist, too old for this s**t.", 10, 5);
			mBuffer.drawLine("<----", 8, 30);
		}
		mBuffer.print();

		char input = _getch();
		switch (input)
		{
		case MOVE_NORTH:
			(choice == 1) ? choice = 1 : choice--;
			break;
		case MOVE_SOUTH:
			(choice == 4) ? choice = 4 : choice++;
			break;
		case ACCEPT:
			if (choice == 1)
			{
				// Assign character attributes.	
			}
			if (choice == 2)
			{
				// Assign character attributes.
			}
			if (choice == 3)
			{
				// Assign character attributes.
			}
			if (choice == 4)
			{
				// Assign character attributes.
			}

			mBuffer.clear();
			lineNumber = 1;
			mBuffer.drawLine("Night is coming in, and you head into a nearby cave. Perhaps", lineNumber++, 1);
			mBuffer.drawLine("this may even be the one mentioned in Zimmer's dossier. You", lineNumber++, 1);
			mBuffer.drawLine("feel that you may very well soon find out. For now, however,", lineNumber++, 1);
			mBuffer.drawLine("you are glad to have found some shelter.", lineNumber++, 1);
			lineNumber = 10;
			mBuffer.drawLine("                                       ___", lineNumber++, 20);
			mBuffer.drawLine("                                      /  /]", lineNumber++, 20);
			mBuffer.drawLine("                                     /  / ]", lineNumber++, 20);
			mBuffer.drawLine("                 )           _____,.-\" /__]", lineNumber++, 20);
			mBuffer.drawLine("                         ,-\"             _>", lineNumber++, 20);
			mBuffer.drawLine("                  (     _/           ,.-\"`", lineNumber++, 20);
			mBuffer.drawLine("                 )     / |     _,.-\"`", lineNumber++, 20);
			mBuffer.drawLine("    \\ 0 /        (    /. /    |", lineNumber++, 20);
			mBuffer.drawLine("     \\|/           )  ,  /`  ./", lineNumber++, 20);
			mBuffer.drawLine("      |          (   \\_/   //  _", lineNumber++, 20);
			mBuffer.drawLine("     / \\          )  /    //==(_)", lineNumber++, 20);
			mBuffer.drawLine("    /   \\         _,~'#   (/.", lineNumber++, 20);
			mBuffer.drawLine("--------------------------------------#--#--------------------", lineNumber++, 1);
			mBuffer.print();
			_getch();

			choosing = false;
			break;
		}
	}
}

void Game::runGameMenu()
{
	mBuffer.clear();

	mBuffer.drawLine(" -----------------------------------------------", 0);
	mBuffer.drawLine("                     BENEATH", 1);
	mBuffer.drawLine(" -----------------------------------------------", 2);
	mBuffer.drawLine(" Welcome to the game menu. Press space to play,", 3);
	mBuffer.drawLine(" or escape to exit.", 4);
	mBuffer.print();
}
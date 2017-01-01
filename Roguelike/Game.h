#pragma once
#include "stdafx.h"
#include "Menu.h"
#include "Player.h"
#include "Door.h"
#include "Loader.h"
#include "Buffer.h"

class Game
{
	/*   The public methods are limited to the initialization routine, in order to check for // 
	/*   failure conditions and end the program, and the run method.                         */
public:
	enum InputTypes {						// This enum allows for easy changing to which key press means what. The hex values correspond
		// to ASCII characters.
		CHANGE_SCOPE = 0x09,
		ESCAPE = 0x1B,
		ACCEPT = 0x20,
		HELP = 0x2f,
		MOVE_SOUTH_WEST = 0x31,
		MOVE_SOUTH = 0x32,
		MOVE_SOUTH_EAST = 0x33,
		MOVE_WEST = 0x34,
		MOVE_EAST = 0x36,
		MOVE_NORTH_WEST = 0x37,
		MOVE_NORTH = 0x38,
		MOVE_NORTH_EAST = 0x39,
		DESTROY = 0x44,
		DROP = 0x64,
		INVENTORY = 0x69,
		OPEN = 0x6f
	};
	enum MenuScope  { SCOPE_ACTION, SCOPE_ATTACK, SCOPE_END_TURN };
	enum GameState	{ STATE_BEGIN, STATE_GAME, STATE_GAME_MENU, STATE_ITEM_MENU, STATE_END };

	bool				init();             // Sets the command window states
											// -------------------------
	bool				loadLevel();				// Loads all data from binary files.
											// -------------------------
	void				run();				// The game loop - calls the three main Game methods
											// until an exit condition is detected.
											// -------------------------
	inline void			quit();

	/*   As the key functionality is encapsulated within class methods, the Game class'      //
	/*   methods simply deal with keeping the code within the three main methods, getInput(),//
	/*   update() and draw(), clean. These three methods, the core of the program, are each  //
	/*   called in turn from the main game loop and cover getting input from the player,     //
	/*   game logic, updating objects and their properties, and displaying the board at each //
	/*   appropriate juncture.			                                                     */
private:
	void				getInput();			// A big switch/case nestled within a while statement.
											// This while loop decides whether the input indicates the need
											// for a break and a call to the update and draw methods. The input
											// is checked alongside the enum InputTypes defined below.
											// -------------------------
	void				update();			// The game prints by updating a buffer with the various map draw 
											// states and object positions and then printing that. The update 
											// method deals with updating this buffer and a number of interactions
											// in the game world (picking up items, for example).
											// -------------------------
	void				draw();				// Prints the buffer, and any additional information, to the screen.
											// -------------------------

	void				characterChoice();
	void				runGameMenu();

	bool				newLevel(const int levelNumber);
	void				resetLevel();

	/*  The rest of Game's methods deal with printing. Some of these are quite large to keep  //
	/*  the number of methods down within the Game class.                                     */
	std::vector<std::string>    getMap();			// The map is stored in its own variable as just the floor and walls. 
													// This method returns the same map, with items, doors and the player 
													// added on. It is needed to update the buffer, as well as for other calculations.
													// -------------------------
	std::vector<std::string>	getHiddenMap();
	std::vector<std::string>	getMenuBar();
	bool						updateBuffer();				// First creates a visible map, based on the player's position, from the map
													// returned by getMap(). This is then converted into a string containing the valid 
													// formatting characters, appended any update messages, and returned.
													// ------------------------

private:
	bool						mIsPlaying = true;
	int							mCurrentLevel = 0;

	/*  The main game objects. mPlayer has its position initialized in the top left corner;     //
	/*  mNakedMap is the map only as floors and walls; mDoorList and mItemList are assigned to  //
	/*  in the init() method.                                                                   */
	Player						mPlayer = { 1, 1 };
	std::vector<std::string>    mNakedMap;
	std::vector<Door>			mDoorList;
	std::vector<Item*>			mItemList;

	Buffer						mBuffer;
	std::string					mUpdateDialogue;

	MenuScope					mCurrentScope = SCOPE_ACTION;
	GameState					mCurrentState = STATE_BEGIN;
};

void Game::quit()
{
	mIsPlaying = false;
}
// This file is part of Descent.
//
// Descent is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Descent is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Descent.  If not, see <http://www.gnu.org/licenses/>.
//
// Alex Sigston
// admin@thestuffcupboard.com
// 2015-04-15

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "game.h"

/* CONSTRUCTOR */
Game::Game(Screen screen): m_isPlaying(true), m_currentLevel(0), m_currentScope(SCOPE_ACTION), 
    m_currentState(STATE_BEGIN), m_player(), m_screen(screen), m_loader(), m_map(),
    m_nakedMap(), m_doorList(), m_itemList(), m_updateDialogue() { }


/* calls a new level and loads the major text assets */
bool Game::setup() 
{ 
    bool bval = newLevel();
    if (!m_loader.loadAssets("binaries/_files.bin"))
        bval = false;
    return bval;
}


/* Loads data from binary files. */
bool Game::newLevel()
{
    bool validLoading = true;
    m_screen.draw("Loading resources...");

    std::string level = std::to_string(++m_currentLevel);
    for (auto item : m_itemList)
        delete item;
    m_itemList.clear(); m_nakedMap.clear(); m_doorList.clear();
    if (!m_loader.loadMap("binaries/map" + level + ".bin", m_nakedMap))
        validLoading = false;
    if (!m_loader.loadDoors("binaries/doors" + level + ".bin", m_doorList))
        validLoading = false;
    if (!m_loader.loadItems("binaries/items" + level + ".bin", m_itemList))
        validLoading = false;
    return validLoading;
}


/* calls the three main methods until an exit condition is detected. */
void Game::run()
{
    // runIntro returns false if the players chooses to exit the game.
    if (runIntro())
    {
        m_currentState = STATE_GAME;
        characterChoice();
        update();
        draw();
        while (m_isPlaying)
        {
            getInput();
            update();
            draw();
        }
    }
}


/* A big switch/case nestled within a while statement. */
void Game::getInput()
{
    // get the latest populated map for condition testing
    std::vector<std::string> map = m_nakedMap;
    populateMap(map);

    /* validInput keeps the execution inside the input stage */
    /* until something worth updating or drawing happens.    */
    bool validInput = false;
    while (!validInput) 
    {
        int value = m_screen.getInput();    
        switch (value) 
        {
        /**********************/
        /* MOVEMENT CONDITIONS*/
        /**********************/
        case MOVE_NORTH:
            validInput = m_player.move(0, -1, map);
            break;
        case MOVE_SOUTH:
            validInput = m_player.move(0, 1, map);
            break;
        case MOVE_WEST:
            validInput = m_player.move(-1, 0, map);
            break;
        case MOVE_EAST:
            validInput = m_player.move(1, 0, map);
            break;
        case MOVE_NORTH_WEST:
            validInput = m_player.move(-1, -1, map);
            break;
        case MOVE_SOUTH_EAST:
            validInput = m_player.move(1, 1, map);
            break;
        case MOVE_NORTH_EAST:
            validInput = m_player.move(1, -1, map);
            break;
        case MOVE_SOUTH_WEST:
            validInput = m_player.move(-1, 1, map);
            break;
        /*******************/
        /* IN GAME CHOICES */
        /*******************/
        case ACCEPT:
            if (m_currentState == STATE_GAME_MENU) 
            {
                m_currentState = STATE_GAME;
                validInput = true;
                break;
            }
            else if (m_currentState == STATE_GAME) 
            {
                if (m_updateDialogue != "") 
                {
                    m_updateDialogue = "";
                    validInput = true;
                    break;
                }
                if (m_currentScope == SCOPE_END_TURN) 
                {
                    m_screen.draw("Ending turn... Press any key to continue...");
                    m_screen.pause();
                    m_player.newTurn();
                }
                validInput = true;
                break;
            }
            break;
        case OPEN:
            if (m_currentState == STATE_GAME)
            {
                for (auto &door : m_doorList) 
                {
                    if (door.nextTo(m_player.getX(), m_player.getY())) 
                    {
                        if (m_player.getActionPoints() > 0) 
                        {
                            door.openClose();
                            m_player.takeAction();
                            validInput = true;
                            break;
                        }
                    }
                }
            }
            break;
        case HELP:
            if (m_currentState == STATE_GAME)
            {
                int inputQuery = m_screen.getInput();
                switch (inputQuery) 
                {
                case '/':
                    m_updateDialogue = "/: An open door.";
                    break;
                case '+':
                    m_updateDialogue = "+: A closed door.";
                    break;
                case '#':
                    m_updateDialogue = "#: A stretch of wall.";
                    break;
                case '.':
                    m_updateDialogue = ".: The floor.";
                    break;
                case '@':
                    m_updateDialogue = "@: You.";
                    break;
                case '0':
                    m_updateDialogue = "0: Level exit.";
                    break;
                default:
                    m_updateDialogue = "Not a valid key.";
                    break;
                }
                validInput = true;
            }
            break;
        /****************/
        /* MENU OPTIONS */
        /****************/
        case INVENTORY:
            inventoryMenu();
            validInput = true;
            break;
        case ESCAPE:
            if (m_currentState == STATE_GAME_MENU) 
            {
                m_currentState = STATE_END;
                validInput = true;
            }
            else if (m_currentState == STATE_GAME) 
            {
                m_currentState = STATE_GAME_MENU;
                validInput = true;
            }
            break;
        case CHANGE_SCOPE:
            if (m_currentState == STATE_GAME)
            {
                switch (m_currentScope) 
                {
                case SCOPE_ACTION:
                    m_currentScope = SCOPE_ATTACK;
                    break;
                case SCOPE_ATTACK:
                    m_currentScope = SCOPE_END_TURN;
                    break;
                case SCOPE_END_TURN:
                    m_currentScope = SCOPE_ACTION;
                    break;
                }
                validInput = true;
            }
            break;
        }
    }
}


/* Does a whole load of checking and stuff. See inside for deets */
void Game::update()
{
    /* Deal with the player standing on an item */
    for (unsigned x = 0; x != m_itemList.size(); ++x)
    {
        if ((m_player.getX() == m_itemList[x]->getX()) && (m_player.getY() == m_itemList[x]->getY()))
        {
            m_player.inventory.addItem(m_itemList[x]);
            m_updateDialogue = "You have picked up: " + m_itemList[x]->getName();
            m_itemList[x] = nullptr;
            m_itemList.erase(std::remove(m_itemList.begin(), m_itemList.end(), nullptr), m_itemList.end());
            break;
        }
    }

    /* state and level changes */
    if (m_nakedMap[m_player.getY()][m_player.getX()] == '0')
    {
        if (m_currentLevel == 2)
        {
            m_currentState = STATE_END;
            m_screen.draw("You have won!");
            m_screen.pause();
        }
        else
        {
            m_screen.draw("Now you head... beneath!");
            m_screen.pause();
            m_player.newLevel(1, 1);
            newLevel();
        }
    }
    if (m_currentState == STATE_END)
        quit();

    /* update the empty map object with all the relevant bits */
    m_map = m_nakedMap;
    updateAssets(m_map);
}


/*  Prints the buffer, and any additional information, to the screen */
void Game::draw()
{
    if (m_currentState == STATE_GAME)
    {
        if (m_updateDialogue == "")
        {
            std::vector<std::string> temp = {   
                std::string(" ------------------*BENEATH*--------------------"),                     
                std::string("                Caves: Level " + std::to_string(m_currentLevel)),
                std::string(" -----------------------------------------------") 
                };
            m_screen.draw(m_map, &temp);
        }
        else
            m_screen.draw(m_updateDialogue);
    }
    if (m_currentState == STATE_GAME_MENU)
        m_screen.draw(*m_loader.getFile("main_menu"));
}


/* */
void Game::updateAssets(std::vector<std::string> &map)
{
    populateMap(map);

    /* hide the relevant bits */
    for (auto door : m_doorList)
    {
        if (door.isVertical() && !door.isOpen())
        {
            if (m_player.getX() < door.getX())
            {
                for (auto &s : map)                       // Hide the map right of the door.
                for (unsigned x = 0; x < s.length(); ++x)
                if (x > door.getX())
                    s[x] = ' ';
            }
            else {
                for (auto &s : map)                       // Hide the map left of the door.
                for (unsigned x = 0; x < s.length(); ++x)
                if (x < door.getX())
                    s[x] = ' ';
            }
        }
        else if (!door.isVertical() && !door.isOpen()) {
            if (m_player.getY() < door.getY())
            {
                for (unsigned x = 0; x < map.size(); ++x) // Hide the map south of the door.
                if (x > door.getY())
                for (auto &c : map[x])
                    c = ' ';
            }
            else {
                for (unsigned x = 0; x < map.size(); ++x) // Hide the map north of the door.
                if (x < door.getY())
                for (auto &c : map[x])
                    c = ' ';
            }
        }
    }

    /* add the menu */
    map.push_back(" -----------------------------------------------");
    switch (m_currentScope)
    {
    case SCOPE_ACTION:
        map.push_back(" |   *ACTION*   |    ATTACK    |    END TURN    |");
        map.push_back(" -              --------------------------------");
        map.push_back(" | [o]pen       |");
        map.push_back(" ----------------");
        break;
    case SCOPE_ATTACK:
        map.push_back(" |    ACTION    |   *ATTACK*   |    END TURN    |");
        map.push_back(" -----------------------------------------------");
        map.push_back("");
        map.push_back("");
        break;
    case SCOPE_END_TURN:
        map.push_back(" |    ACTION    |    ATTACK    |   *END TURN*   |");
        map.push_back(" -----------------------------------------------");
        map.push_back("");
        map.push_back("");
        break;
    }
}


/*  Combines the door and item list with the naked map to get the printable one */
void Game::populateMap(std::vector<std::string> &buffer)
{
    for (auto doors : m_doorList)
        buffer[doors.getY()][doors.getX()] = (doors.isOpen()) ? '/' : '+';
    for (auto items : m_itemList)
        buffer[items->getY()][items->getX()] = items->getChar();
    buffer[m_player.getY()][m_player.getX()] = '@';
}


/* the player's inventory menu: it returns false if it wants to be called again */
void Game::inventoryMenu()
{
    unsigned itemFocus = 1;
    std::vector<std::string> vecTemp;
    while(true)
    {
        vecTemp.erase(vecTemp.begin(), vecTemp.end());
        vecTemp.push_back("-----------------------------------------------");
        vecTemp.push_back("                   INVENTORY");
        vecTemp.push_back("-----------------------------------------------");
        if (m_player.inventory.getSize() < 1)
            vecTemp.push_back("No items!");
        else
        {
            for (auto s : m_player.inventory.getNames())
                vecTemp.push_back(s);
        }
        vecTemp[2+itemFocus] = vecTemp[2+itemFocus] + "  <------";    
        m_screen.draw(vecTemp);

        //  Gets user input and updates accordingly.
        char value = getch();
        switch (value)
        {
        case ESCAPE:
            return;
        case INVENTORY:
        {
            bool isExit = false;
            vecTemp.erase(vecTemp.begin(), vecTemp.end());
            while (!isExit)
            {
                vecTemp.erase(vecTemp.begin(), vecTemp.end());
                vecTemp.push_back("-----------------------------------------------");
                vecTemp.push_back("                  BODY STATS");
                vecTemp.push_back("-----------------------------------------------");
                vecTemp.push_back("Health: " + std::to_string(m_player.getHealth()));
                vecTemp.push_back("Fear: " + std::to_string(m_player.getFear()));
                m_screen.draw(vecTemp);

                //  Gets user input and updates accordingly.
                char value = getch();
                switch (value)
                {
                case INVENTORY:
                    isExit = true;
                    break;
                case ESCAPE:
                    return;
                }
            }
            break;
        }
        case DESTROY:
            m_player.inventory.deleteItem(m_player.inventory.getItem(itemFocus-1));
            itemFocus = 1;
            break;
        case MOVE_SOUTH:
            if (itemFocus < m_player.inventory.getSize())
                itemFocus++;
            break;
        case MOVE_NORTH:
            if (itemFocus > 1)
                itemFocus--;
            break;
        }
    }
}


/* parses the intro files at prints them */
bool Game::runIntro() 
{
    int menuChoice = 1;
    std::vector<std::string> temp = *m_loader.getFile("intro_0");
    while (true)
    {
        temp = *m_loader.getFile("intro_0");
        if (menuChoice == 1)
            temp[3] = "         @@@@@@@@@@->START<-@@@@@@@@@@";
        else if (menuChoice == 2)
            temp[4] = "         @@@@@@@->QUICK START<-@@@@@@@";
        else if (menuChoice == 3)
            temp[5] = "         @@@@@@@@->EXIT GAME<-@@@@@@@@";
        m_screen.draw(temp);

        char input = m_screen.getInput();
        switch (input)
        {
        case Game::MOVE_SOUTH:
            (menuChoice == 3) ? menuChoice = 3 : menuChoice++;
            break;
        case Game::MOVE_NORTH:
            (menuChoice == 1) ? menuChoice = 1 : menuChoice--;
            break;
        case Game::ACCEPT:
            if (menuChoice == 3)
                return false;
            if (menuChoice == 1 || menuChoice == 2)
            {
                if (menuChoice == 1)
                {
                    m_screen.draw(*m_loader.getFile("intro_1"));
                    m_screen.pause();
                    m_screen.draw(*m_loader.getFile("intro_2"));
                    m_screen.pause();
                    m_screen.draw(*m_loader.getFile("intro_3"));
                    m_screen.pause();
                    m_screen.draw(*m_loader.getFile("intro_4"));
                    m_screen.pause();
                    m_screen.draw(*m_loader.getFile("intro_5"));
                    m_screen.pause();
                    m_screen.draw(*m_loader.getFile("intro_6"));
                    m_screen.pause();
                    m_screen.draw(*m_loader.getFile("intro_7"));
                    m_screen.pause();
                    m_screen.draw("");
                    m_screen.pause();
                }
                return true;
            }
            break;
        case Game::ESCAPE:
            return false;
            break;
        }
    }
}


/* part of the opening menu */
void Game::characterChoice()
{
    bool choosing = true;
    int choice = 1;

    /* we want a copy as we'll be changing things */
    std::vector<std::string> vtemp = *m_loader.getFile("char_choice1");
    while (choosing)
    {
        if (choice == 1)
        {
            vtemp[10].assign("     A talented scientist, easy to scare.");
            vtemp[4].assign(vtemp[4] + " <----");
        }
        if (choice == 2)
        {
            vtemp[10].assign("A weapons expert, wearing only a vest top.");
            vtemp[5].assign(vtemp[5] + " <----");
        }
        if (choice == 3)
        {
            vtemp[10].assign("A military man, terrified of rats.");
            vtemp[6].assign(vtemp[6] + " <----");
        }
        if (choice == 4)
        {
            vtemp[10].assign("An seasoned archaeologist, too old for this s**t.");
            vtemp[7].assign(vtemp[7] + " <----");
        }
        m_screen.draw(vtemp);
        vtemp = *m_loader.getFile("char_choice1");

        char input = m_screen.getInput();
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

            // choosing is done, print the next screen and exit
            // to the actual game.
            vtemp = *m_loader.getFile("char_choice2");
            m_screen.draw(vtemp);
            m_screen.pause();
            choosing = false;
            break;
        }
    }
}

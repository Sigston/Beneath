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

#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <vector>
#include "utilities/loader.h"
#include "utilities/screen.h"
#include "player.h"
#include "door.h"
#include "item.h"

class Game
{
 public:
    /* ENUMS AND CONSTANTS */
    enum InputTypes 
    {   
        CHANGE_SCOPE = 0x09,        // enum allows flexibility
        ESCAPE = 0x1B,              // in deciding which key is
        ACCEPT = 0x20,              // is what - the values are
        HELP = 0x2f,                // ASCII value.
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
    enum GameState  { STATE_BEGIN, STATE_GAME, STATE_GAME_MENU, STATE_END };

    /* CONSTRUCTORS AND DESTRUCTORS */
    Game(Screen screen);
    
    /* PUBLIC METHODS: CALLED FROM MAIN() */
    bool setup();
    void run();
    void quit();

 private:
    /* PRIVATE METHODS: CALLED FROM RUN() */
    void getInput();
    void update();
    void draw();

    /* PRIVATE METHODS: CALLED FROM UPDATE() */
    void updateAssets(std::vector<std::string> &map);
    void populateMap(std::vector<std::string> &buffer);

    /* PRIVATE METHODS: LEVEL ACCESS */
    bool newLevel();

    /* PRIVATE METHODS: MENU OPTIONS */
    void inventoryMenu();
    bool runIntro();
    void characterChoice();

 private:
    /* CONTROL VARIABLES */
    bool m_isPlaying;
    int m_currentLevel;
    MenuScope m_currentScope;
    GameState m_currentState;

    /* OTHER GAME VARIABLES */
    Player m_player;
    Screen m_screen;
    Loader m_loader;

    /* PRINTABLE VARIABLES */
    std::vector<std::string> m_map;
    std::vector<std::string> m_nakedMap;
    std::vector<Door> m_doorList;
    std::vector<Item*> m_itemList;
    std::string m_updateDialogue;
};

/* INLINE FUNCTION DEFINITIONS */
inline void Game::quit() { m_isPlaying = false; }

#endif  // _GAME_H_

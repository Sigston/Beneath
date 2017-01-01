// This file is part of **Descent**
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

#include "game.h"
#include "utilities/screen.h"

int main()
{
    /* establish the screen and pass it into the game */
    Screen screen; 
    screen.initialize();
    Game game(screen);

    /* check for errors loading resources, and run game */
    if (!game.setup())
    {
        screen.draw("FAIL: game assets failed to load");
        screen.pause();
        screen.quit();
        exit(EXIT_FAILURE);
    }
    else
        game.run();     
    screen.quit();
    exit(EXIT_SUCCESS);
}

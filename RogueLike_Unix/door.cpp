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

#include "door.h"

/* Takes an X and Y coordinate and returns true if they are next to the door object */
bool Door::nextTo(const unsigned x, const unsigned y)
{
    if (m_isVertical)
    {
        if (((x == m_x - 1) || (x == m_x + 1)) && (y == m_y))
            return true;
        else
            return false;
    }
    else 
    {
        if (((y == m_y - 1) || (y == m_y + 1)) && (x == m_x))
            return true;
        else
            return false;
    }
}

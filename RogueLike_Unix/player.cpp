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

#include <vector>
#include <string>
#include "player.h"

/* CONSTRUCTOR */
Player::Player(): inventory(), m_x(1), m_y(1), m_maxHealth(100), 
    m_maxMovement(10), m_maxAction(3), m_minFear(20), 
    m_health(m_maxHealth), m_movementPts(m_maxMovement), 
    m_actionPts(m_maxAction), m_fear(m_minFear)
{ }


// takes a change to x and y coordinates along with a map to test this 
// movement within. If successful, the method returns true and updates
bool Player::move(const unsigned changeX, const unsigned changeY, 
    const std::vector<std::string> &mapCase)
{
    // check for impenetrable obstacles
    if (mapCase[m_y + changeY][m_x + changeX] == '+' ||
        mapCase[m_y + changeY][m_x + changeX] == '#')
        return false;
    else
    {
        if (m_movementPts == 0)
            return false;
        else
        {
            m_x += changeX;
            m_y += changeY;
            m_movementPts--;
            return true;
        }
    }
}


/* decrements the action count */
Player& Player::takeAction()
{
    m_actionPts--;
    return *this;
}


/* reset is called at the end of each turn */
void Player::newTurn()
{
    m_movementPts = m_maxMovement;
    m_actionPts = m_maxAction;
}


/* called at the start of a new level */
void Player::newLevel(int posX, int posY)
{
    newTurn();
    m_x = posX;
    m_y = posY;
}

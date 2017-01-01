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

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <vector>
#include <string>
#include "item.h"
#include "inventory.h"

class Player
{
 public:
    /* CONSTRUCTOR(S) */
    Player();

    /* PUBLIC VARIABLES */
    Inventory inventory;

    /* PUBLIC METHODS: */
    bool move(const unsigned changeX, const unsigned changeY, 
        const std::vector<std::string> &mapCase);
    Player& takeAction();
    void newTurn();
    void newLevel(int x, int y);

    /* PUBLIC METHODS: TRIVIAL GETTERS */
    unsigned getX();
    unsigned getY();
    unsigned getHealth();
    unsigned getFear();
    unsigned getMovementPoints();
    unsigned getActionPoints();

 private:
    /* PRIVATE MEMBERS */
    unsigned m_x;
    unsigned m_y;
    unsigned m_maxHealth;
    unsigned m_maxMovement;
    unsigned m_maxAction;
    unsigned m_minFear;
    unsigned m_health;
    unsigned m_movementPts;
    unsigned m_actionPts;
    unsigned m_fear;
};

inline unsigned Player::getX() { return m_x; }
inline unsigned Player::getY() { return m_y; }
inline unsigned Player::getHealth() { return m_health; }
inline unsigned Player::getFear() { return m_fear; }
inline unsigned Player::getMovementPoints() { return m_movementPts; }
inline unsigned Player::getActionPoints() { return m_actionPts; }

#endif  // _PLAYER_H_

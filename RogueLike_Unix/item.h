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

#ifndef _ITEM_H_
#define _ITEM_H_
#include <string>

class Item
{
public:
    /* CONSTRUCTORS AND OPERATOR OVERLOADS */
    Item(const char printValue, unsigned x, unsigned y, 
        const std::string &name);
    Item& operator=(const Item &element);
    bool operator==(const Item &element);

    /* PUBLIC METHODS: GETTERS */
    unsigned getX();
    unsigned getY();
    char getChar();
    int getIndex();
    std::string getName();

private:
    /* PRIVATE MEMBERS */
    char m_printValue;
    unsigned m_x;
    unsigned m_y;
    std::string m_itemName;
};

/* INLINE DEFINITIONS */
inline unsigned Item::getX() { return m_x; }
inline unsigned Item::getY() { return m_y; }
inline char Item::getChar() { return m_printValue; }
inline std::string Item::getName() { return m_itemName; }

#endif  // _ITEM_H_

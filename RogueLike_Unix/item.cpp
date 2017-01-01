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
#include "item.h"

/* CONSTRUCTOR */
Item::Item(const char printValue, const unsigned posX, 
    const unsigned posY, const std::string &name): 
    m_printValue(printValue), m_x(posX), m_y(posY), 
    m_itemName(name)
{ }


/* ASSIGNMENT: pretty bog standard */
Item& Item::operator=(const Item &element)
{
    if (this == &element)
        return *this;
    m_printValue = element.m_printValue;
    m_x = element.m_x;
    m_y = element.m_y;
    m_itemName = element.m_itemName;
    return *this;
}


/* COMPARISON: also pretty standard */
bool Item::operator==(const Item &element)
{
    if (m_printValue == element.m_printValue && m_x == element.m_x 
        && m_y == element.m_y && m_itemName == element.m_itemName)
        return true;
    else
        return false;
}

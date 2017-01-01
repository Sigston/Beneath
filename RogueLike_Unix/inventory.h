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

#ifndef _INVENTORY_H_
#define _INVENTORY_H_
#include <vector>
#include "item.h"

/*  The class simplifies access to a vector of item pointers */
class Inventory
{
public:
    /* CONSTRUCTOR(S) */
    Inventory(): m_inventory() { }

    /* PUBLIC METHODS: GENERAL */
    void addItem(Item *const item);
    bool deleteItem(const Item *const item);

    /* PUBLIC METHODS: GETTERS */
    unsigned getSize();
    Item* getItem(const int index);
    std::vector<std::string> getNames();
    bool isEmpty();

private:
    /* PRIVATE MEMBERS */
    std::vector<Item*>  m_inventory;
};

inline unsigned Inventory::getSize() { return m_inventory.size(); }
inline Item* Inventory::getItem(const int index) { return (!m_inventory.empty()) ? m_inventory[index] : nullptr; }
inline bool Inventory::isEmpty() { return m_inventory.empty(); }
inline void Inventory::addItem(Item *const item) { m_inventory.push_back(item); }

#endif  // _INVENTORY_H_
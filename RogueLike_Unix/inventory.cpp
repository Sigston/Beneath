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

#include <algorithm>
#include "inventory.h"
#include "item.h"

/* To delete items, the vector is checked for a corresponding item and, when		//
 * found, the pointer is set to null. The vector is then cleansed of nullptr using  //
 * the erase:remove idiom. The method returns false if that item cannot be found.	*/
bool Inventory::deleteItem(const Item *const item)
{
	for (unsigned x = 0; x != m_inventory.size(); ++x)
	{
		if (m_inventory[x] == item)
		{
			delete m_inventory[x];
			m_inventory[x] = nullptr;
			m_inventory.erase(std::remove(m_inventory.begin(), 
				m_inventory.end(), nullptr), m_inventory.end());
			return true;
		}
	}
	return true;
}


/* returns all the inventory item's names in a vector */
std::vector<std::string> Inventory::getNames()
{
	std::vector<std::string> temp;
	for (auto item : m_inventory)
		temp.push_back(item->getName());
	return temp;
}

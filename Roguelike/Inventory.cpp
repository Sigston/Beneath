#include "stdafx.h"
#include "Inventory.h"

void Inventory::addItem(Item *item)
{
	mInventory.push_back(item);
}

/* To delete items, the vector is checked for a corresponding item and, when		//
/* found, the pointer is set to null. The vector is then cleansed of nullptr using  //
/* the erase:remove idiom. The method returns false if that item cannot be found.	*/
bool Inventory::deleteItem(const Item *item)
{
	for (int x = 0; x != mInventory.size(); ++x)
		if (mInventory[x] == item)
		{
			delete mInventory[x];
			mInventory[x] = nullptr;
			mInventory.erase(std::remove(mInventory.begin(), mInventory.end(), nullptr), mInventory.end());
			return true;
		}

	return true;
}

int Inventory::getSize()
{
	return mInventory.size();
}

Item* Inventory::getItem(int index)
{
	if (!mInventory.empty())
		return mInventory[index];
}

bool Inventory::isEmpty()
{
	return mInventory.empty();
}
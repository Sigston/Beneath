#pragma once
#include "stdafx.h"
#include "Item.h"

/*	The class simplifies access to a vector of item pointers representing an inventory.	*/
class Inventory
{
public:
	/*	The real logic is in the add and delete item methods. As the inventory is stored	//
	/* as a vector of pointers to items, to add an item we just push_back() a pointer to	//
	/* a new object. To delete, the vector is checked for a corresponding item and, when	//
	/* found, the pointer is set to null. The vector is then cleansed of nullptr using		//
	/* the erase:remove idiom.																*/
	void			addItem(Item *item);
	bool			deleteItem(const Item *item);

	int				getSize();
	Item*			getItem(int index);
	bool			isEmpty();

private:
	vector<Item* const>	mInventory;
};


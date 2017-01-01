#include "stdafx.h"
#include "Item.h"

Item::Item(const char printValue, unsigned posX, unsigned posY, const string name)
: mPrintValue(printValue)
, mX(posX)
, mY(posY)
, itemName(name)
{
}

int Item::getPosX()
{
	return mX;
}

int Item::getPosY()
{
	return mY;
}

char Item::getChar()
{
	return mPrintValue;
}

string Item::getName()
{
	return itemName;
}

Item& Item::operator=(const Item &element)
{
	Item item(element.mPrintValue, element.mX, element.mY, element.itemName);
	return item;
}

bool Item::operator==(const Item &element)
{
	if (mPrintValue == element.mPrintValue && mX == element.mX && mY == element.mY && itemName == element.itemName)
		return true;
	else
		return false;
}
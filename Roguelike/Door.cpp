#include "stdafx.h"
#include "Door.h"

/* Takes an X and Y coordinate and returns true if they are next to the door object. The logic	//
/* differs depending on the orientation of the door.											*/
bool Door::nextTo(const unsigned posX, const unsigned posY)
{
	if (mIsVertical)
	{
		if (((posX == mX - 1) || (posX == mX + 1)) && (posY == mY))
			return true;
		else
			return false;
	}
	else {
		if (((posY == mY - 1) || (posY == mY + 1)) && (posX == mX))
			return true;
		else
			return false;
	}
}

bool Door::isOpen()
{
	return mIsOpen;
}
bool Door::isVertical()
{
	return mIsVertical;
}
int Door::getXPos()
{
	return mX;
}
int Door::getYPos()
{
	return mY;
}

void Door::OpenClose()
{
	mIsOpen = !mIsOpen;
}
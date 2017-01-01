#pragma once
#include "stdafx.h"

/* This class is really just an encapsulation of a load of data types. The only logic it does is	// 
/* in the nextTo() method.																			*/
class Door
{
public:
	Door(const unsigned posX, const unsigned posY) : mIsOpen(false), mIsVertical(false), mX(posX), mY(posY) { };
	Door(const bool isOpen, const bool isVertical, const unsigned posX, const unsigned posY)
		: mIsOpen(isOpen), mIsVertical(isVertical), mX(posX), mY(posY) { };

	bool				nextTo(const unsigned posX, const unsigned posY);	// Takes an X and Y coordinate and returns true
																			// if they are next to the door object. The logic
																			// differs depending on the orientation of the door.

	/* Get methods: */
	bool				isOpen();
	bool				isVertical();
	int 				getXPos();
	int 				getYPos();

	/* Set methods: */
	void				OpenClose();
	
	
private:
	bool				mIsOpen;
	bool				mIsVertical;

	unsigned			mX;
	unsigned			mY;
};


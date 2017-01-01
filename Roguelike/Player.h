#pragma once
#include "stdafx.h"
#include "Buffer.h"
#include "Item.h"
#include "Inventory.h"

class Player
{
public:
	/* The player class only handles movement. The constructor initializes x and y position and the three methods	//
	/* deal with setting and getting these private objects. TODO: add interface for inventory functions.			*/
	Player(const unsigned setPosX, const unsigned setPosY);

	unsigned		getPosX();
	unsigned		getPosY();
	int				getHealth();
	int				getMovementPoints();
	int				getActionPoints();
	Player&			takeAction();

	bool			move(const unsigned changeX, const unsigned changeY, const vector<string> mapCase);		// The move method takes a change to the x and y coordinates along 
																							// with a map to test this movement within. If successful, the method
																							// returns true and updates this->posX and posY.
	void			reset();
	void			newLevel(int posX, int posY);

	void			inventoryMenu(Buffer &buffer);
	bool            healthMenu(Buffer &buffer);
	void			addItem(Item *item);

	bool			turnEnd;

private:
	unsigned		posX;
	unsigned		posY;

	int				mMaxHealth;
	int				mMaxMovement;
	int				mMaxAction;
	int				mMinFear;

	int				mHealth;
	int				mMovementPoints;
	int				mActionPoints;
	int				mFear;

	Inventory		mInventory;

	enum InputTypes {						// This enum allows for easy changing to which key press means what. The hex values correspond
		// to ASCII characters.
		ESCAPE = 0x1B,
		HELP = 0x2f,
		MOVE_SOUTH_WEST = 0x31,
		MOVE_SOUTH = 0x32,
		MOVE_SOUTH_EAST = 0x33,
		MOVE_WEST = 0x34,
		MOVE_EAST = 0x36,
		MOVE_NORTH_WEST = 0x37,
		MOVE_NORTH = 0x38,
		MOVE_NORTH_EAST = 0x39,
		DESTROY = 0x44,
		INVENTORY = 0x69,
		OPEN = 0x6f
	};
};


#include "stdafx.h"
#include "Player.h"
using namespace std;

Player::Player(const unsigned setPosX, const unsigned setPosY)
: posX(setPosX)
, posY(setPosY)
, mMaxAction(3)
, mMaxHealth(100)
, mMaxMovement(10)
, mMinFear(20)
{
	mMovementPoints = mMaxMovement;
	mActionPoints = mMaxAction;
	mHealth = mMaxHealth;
	mFear = mMinFear;
}

unsigned Player::getPosX()
{
	return posX;
}
unsigned Player::getPosY()
{
	return posY;
}
int Player::getHealth()
{
	return mHealth;
}
int Player::getMovementPoints()
{
	return mMovementPoints;
}
int Player::getActionPoints()
{
	return mActionPoints;
}

/* The move method takes a change to the x and y coordinates along with a map to test this  //
/* movement within. If successful, the method returns true and updates this->posX and posY	*/
bool Player::move(const unsigned changeX, const unsigned changeY, const vector<string> mapCase)
{
	if (mapCase[posY + changeY][posX + changeX] == '+' ||
		mapCase[posY + changeY][posX + changeX] == '#')
		return false;
	else
	{
		if (mMovementPoints <= 0)
			return false;
		else
		{
			posX += changeX;
			posY += changeY;
			mMovementPoints--;
			if (mapCase[posY][posX] == '0')
				turnEnd = true;
			return true;
		}
	}
}

void Player::addItem(Item *item)
{
	mInventory.addItem(item);
}

void Player::inventoryMenu(Buffer &buffer)
{
	int itemFocus = 1;
	bool isExit = false;

	while (!isExit)
	{
		buffer.clear();
		int lineNumber = 0;
		buffer.drawLine(" -----------------------------------------------", lineNumber++);
		buffer.drawLine("                    INVENTORY", lineNumber++);
		buffer.drawLine(" -----------------------------------------------", lineNumber++);

		if (mInventory.isEmpty())
			buffer.drawLine("No items!", lineNumber++, 1);
		else {
			for (int x = 0; x != mInventory.getSize(); ++x)
			{
				Item *p_temp = mInventory.getItem(x);
				buffer.drawLine(p_temp->getName(), x + lineNumber, 1);
			}
			buffer.drawLine("<------", itemFocus - 1 + lineNumber++, 20);
		}		
		buffer.print();

		//	Gets user input and updates accordingly.
		char value = _getch();
		switch (value)
		{
		case ESCAPE:
			isExit = true;
			break;
		case INVENTORY:
			if (healthMenu(buffer))
				break;
			else
				isExit = true;
			break;
		case DESTROY:
			mInventory.deleteItem(mInventory.getItem(itemFocus - 1));
			itemFocus = 1;
			break;
		case MOVE_SOUTH:
			if (itemFocus < mInventory.getSize())
				itemFocus++;
			break;
		case MOVE_NORTH:
			if (itemFocus > 1)
				itemFocus--;
			break;
		}		
	}
}

bool Player::healthMenu(Buffer &buffer)
{
	bool isExit = false;

	while (!isExit)
	{
		buffer.clear();
		int lineNumber = 0;
		buffer.drawLine(" -----------------------------------------------", lineNumber++);
		buffer.drawLine("                   BODY STATS", lineNumber++);
		buffer.drawLine(" -----------------------------------------------", lineNumber++);

		buffer.drawLine("Health: " + std::to_string(mHealth), lineNumber++, 1);
		buffer.drawLine("Fear: " + std::to_string(mFear), lineNumber++, 1);
		
		buffer.print();

		//	Gets user input and updates accordingly.
		char value = _getch();
		switch (value)
		{
		case INVENTORY:
			return true;
			break;
		case ESCAPE:
			return false;
			break;
		}
	}
}

Player& Player::takeAction()
{
	mActionPoints--;
	return *this;
}

void Player::reset()
{
	mMovementPoints = mMaxMovement;
	mActionPoints = mMaxAction;
}

void Player::newLevel(int posX, int posY)
{
	Player::reset();
	this->posX = posX;
	this->posY = posY;

	turnEnd = false;
}
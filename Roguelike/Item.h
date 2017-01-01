#pragma once
#include "stdafx.h"
using namespace std;

class Item
{
public:
	Item(const char printValue, unsigned posX, unsigned posY, const string name);
	Item& operator=(const Item &element);
	bool operator==(const Item &element);

	int				getPosX();
	int				getPosY();
	char			getChar();
	int				getIndex();
	string			getName();

private:
	const char		mPrintValue;
	unsigned		mX;
	unsigned		mY;
	string			itemName;
	
};


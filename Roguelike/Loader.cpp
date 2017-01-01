#include "stdafx.h"
#include "Loader.h"
using namespace std;

bool Loader::load(const string &fileName, vector<string> &dst)
{
	if (mCurrentType == MAP)
		if (loadMap(fileName, dst))
			return true;

	return false;
}

bool Loader::load(const string &fileName, vector<Item*> &dst)
{
	if (mCurrentType == ITEM)
		if (loadItems(fileName, dst))
			return true;

	return false;
}

bool Loader::load(const string &fileName, vector<Door> &dst)
{
	if (mCurrentType == DOOR)
	if (loadDoors(fileName, dst))
		return true;

	return false;
}

bool Loader::loadMap(const string &fileName, vector<string> &dst)
{
	string temp;
	bool returnValue;

	//	Read the map, line by line.
	mReadFile.open(fileName, ios::in | ios::binary);
	if (mReadFile.good())
	{
		while (getline(mReadFile, temp))
			dst.push_back(temp);
		returnValue = true;
	} else { returnValue = false; }

	mReadFile.close();
	return returnValue;
}

bool Loader::loadItems(const std::string &fileName, vector<Item*> &dst)
{
	string temp;

	mReadFile.open(fileName, ios::in | ios::binary);
	if (mReadFile.good())
	{
		while (getline(mReadFile, temp))
		{
			char itemToken = ' ';
			unsigned posX = 0;
			unsigned posY = 0;
			string name;

			istringstream stream(temp);
			string temp2;
			while (stream >> temp2)
			{
				if (temp2 == "PRINTVALUE:")
				{
					stream >> temp2;
					itemToken = temp2[0];
					continue;
				}
				else if (temp2 == "POSX:")
				{
					stream >> temp2;
					posX = atoi(temp2.c_str());
					continue;
				}
				else if (temp2 == "POSY:")
				{
					stream >> temp2;
					posY = atoi(temp2.c_str());
					continue;
				}
				else if (temp2 == "NAME:")
					stream >> name;
			}

			Item *ptr = new Item(itemToken, posX, posY, name);
			dst.push_back(ptr);
		}
	} else { mReadFile.close(); return false; }
	mReadFile.close();
	return true;
}

bool Loader::loadDoors(const std::string &fileName, vector<Door> &dst)
{
	string temp;

	mReadFile.open(fileName, ios::in | ios::binary);
	if (mReadFile.good())
	{
		while (getline(mReadFile, temp))
		{
			bool isOpen = false;
			bool isVertical = false;
			unsigned posX = 0;
			unsigned posY = 0;

			istringstream stream(temp);
			string temp2;
			while (stream >> temp2)
			{
				if (temp2 == "OPEN:")
				{
					stream >> temp2;
					if (temp2 == "false")
						isOpen = false;
					else
						isOpen = true;
					continue;
				}
				else if (temp2 == "VERTICAL:")
				{
					stream >> temp2;
					if (temp2 == "false")
						isVertical = false;
					else
						isVertical = true;
					continue;
				}
				else if (temp2 == "POSX:")
				{
					stream >> temp2;
					posX = atoi(temp2.c_str());
					continue;
				}
				else if (temp2 == "POSY:")
				{
					stream >> temp2;
					posY = atoi(temp2.c_str());
					continue;
				}
			}
			dst.push_back({ isOpen, isVertical, posX, posY });
		}
	} else { mReadFile.close(); return false; }
	mReadFile.close();
	return true;
}

Loader& Loader::setType(Loader::FileTypes fileType)
{
	mCurrentType = fileType;
	return *this;
}

Loader::FileTypes Loader::getType()
{
	return mCurrentType;
}
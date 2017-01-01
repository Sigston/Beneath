#pragma once
#include "stdafx.h"
#include "Door.h"
#include "Item.h"

class Loader
{
public:
	enum FileTypes { MAP, DOOR, ITEM };

	Loader(FileTypes loadType): mCurrentType(loadType) { }
	Loader() : Loader(MAP) { }

	bool			load(const std::string &, std::vector<std::string> &);
	bool			load(const std::string &, std::vector<Item*> &);
	bool			load(const std::string &, std::vector<Door> &);

	FileTypes		getType();
	Loader&			setType(FileTypes);

private:
	bool			loadMap(const std::string &, std::vector<std::string> &);
	bool			loadItems(const std::string &, std::vector<Item*> &);
	bool			loadDoors(const std::string &, std::vector<Door> &);

	ifstream		mReadFile;
	FileTypes		mCurrentType;
};
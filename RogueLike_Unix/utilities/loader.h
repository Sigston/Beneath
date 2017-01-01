// This file is part of Descent.
//
// Descent is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Descent is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Descent.  If not, see <http://www.gnu.org/licenses/>.
//
// Alex Sigston
// admin@thestuffcupboard.com
// 2015-04-15

#ifndef _LOADER_H_
#define _LOADER_H_
#include <map>
#include <string>
#include <vector>
#include "../door.h"
#include "../item.h"

// The loader class has two sets of public functions. The first set takes 
// a filename and a reference to an object, filling that object with the special 
// data read from the file. The second set deal with the private m_fileMap variable.
class Loader
{
public:
    /* CONSTRUCTOR */
    Loader(): m_fileMap() { }

    /* PUBLIC METHODS: OBJECT LOADERS */
    bool loadMap(const std::string &filename, std::vector<std::string> &dst);
    bool loadItems(const std::string &filename, std::vector<Item*> &dst);
    bool loadDoors(const std::string &filename, std::vector<Door> &dst);

    /* PUBLIC METHODS: FILE LOADERS */
    bool loadAssets(const std::string &specialFile);
    std::vector<std::string>* getFile(const std::string &fileID);
    bool deleteFile(const std::string &fileID);

private:
    /* PRIVATE METHODS */
    std::vector<std::string>* loadFile(const std::string &filename);

    /* PRIVATE MEMBERS */
    std::map<std::string, std::vector<std::string>* > m_fileMap;
};

/* INLINE DEFINITIONS */
inline std::vector<std::string>* Loader::getFile(const std::string &fileID)
    { return (m_fileMap.find(fileID) != m_fileMap.end()) ? m_fileMap[fileID] : nullptr; }

#endif // _LOADER_H_

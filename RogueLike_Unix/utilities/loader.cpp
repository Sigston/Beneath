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

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "../door.h"
#include "../item.h"
#include "loader.h"

/* load the map with the specified file */
bool Loader::loadMap(const std::string &filename, std::vector<std::string> &dst)
{
    std::ifstream filestream(filename, std::ios::in | std::ios::binary);
    if (filestream.good())
    {
        std::string temp;
        while (getline(filestream, temp))
            dst.push_back(temp);
        filestream.close();
        return true;
    } else { filestream.close(); return false; }
}


/* load the vector of items with the specified file */
bool Loader::loadItems(const std::string &filename, std::vector<Item*> &dst)
{
    std::ifstream filestream(filename, std::ios::in | std::ios::binary);
    if (filestream.good())
    {
        std::string sentence, word, itemName;
        char itemToken(' ');
        unsigned posX(0), posY(0);
        while (getline(filestream, sentence))
        {
            std::istringstream stream(sentence);
            while (stream >> word)
            {
                if (word == "PRINTVALUE:")
                    stream >> itemToken;
                else if (word == "POSX:")
                    stream >> posX;
                else if (word == "POSY:")
                    stream >> posY;
                else if (word == "NAME:")
                    stream >> itemName;
            }
            Item *ptr = new Item(itemToken, posX, posY, itemName);
            dst.push_back(ptr);
        }
        filestream.close();
        return true;
    } else { filestream.close(); return false; }
}


/* load the vector of doors with the specified file */
bool Loader::loadDoors(const std::string &filename, std::vector<Door> &dst)
{
    std::ifstream filestream(filename, std::ios::in | std::ios::binary);
    if (filestream.good())
    {
        std::string sentence, word;
        bool isOpen(false), isVertical(false);
        unsigned posX(0), posY(0);
        while (getline(filestream, sentence))
        {         
            std::istringstream stream(sentence);
            while (stream >> word)
            {
                if (word == "OPEN:")
                {
                    stream >> word;
                    if (word == "false")
                        isOpen = false;
                    else
                        isOpen = true;
                }
                else if (word == "VERTICAL:")
                {
                    stream >> word;
                    if (word == "false")
                        isVertical = false;
                    else
                        isVertical = true;
                }
                else if (word == "POSX:")
                    stream >> posX;
                else if (word == "POSY:")
                    stream >> posY;
            }
            dst.push_back({ isOpen, isVertical, posX, posY });
        }
        filestream.close();
        return true;
    } else { filestream.close(); return false; }
}


/* load binary files into m_fileMap */
bool Loader::loadAssets(const std::string &specialFile)
{
    std::ifstream stream(specialFile, std::ios::in | std::ios::binary);
    if (stream.good())
    {
        std::string temp, fileID, filename;
        while (getline(stream, temp))
        {
            std::istringstream sstream(temp);
            sstream >> fileID >> filename;
            m_fileMap[fileID] = loadFile(filename);
        }
        stream.close();
        return true;
    } else { stream.close(); return false; }
}


/* returns true if the file was found, false if not */
bool Loader::deleteFile(const std::string &fileID)
{
    if (m_fileMap.find(fileID) != m_fileMap.end())
    {
        delete m_fileMap[fileID];
        m_fileMap.erase(fileID);
        return true;
    } else { return false; }
}


/* the private function called by loadAssets() */
std::vector<std::string>* Loader::loadFile(const std::string &filename)
{
    std::ifstream stream(filename);
    if (stream.good())
    {
        std::vector<std::string> *fileptr = new std::vector<std::string>();
        std::string temp;
        while (getline(stream, temp))
            fileptr->push_back(temp);
        stream.close();
        return fileptr;
    } else { stream.close(); return nullptr; }
}

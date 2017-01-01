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

#include <ncurses.h>
#include <vector>
#include <string>
#include <algorithm>
#include "screen.h"

/* creates the initial ncurses environment */
bool Screen::initialize()
{
    // init screen, remove echo, cursor and delay 
    // on the escape key
    initscr();
    keypad(stdscr, TRUE);
    raw();
    noecho();
    if (getenv("ESCDELAY") == NULL)
        ESCDELAY = 25;
    if (curs_set(0) == ERR)
    {
        draw("FAIL: try changing terminals");
        pause();
        return false;
    }
    return true;
}


/* takes a vector of strings and optional header and prints it all on screen */
void Screen::draw(const std::vector<std::string> &vs, const std::vector<std::string> *const optionalHeader)
{
    //
    // 1) Get the limits of the window and the limits on the input.
    //
    clear();
    unsigned maxY(0), maxX(0), tallestY(vs.size()), widestX(0);
    getmaxyx(stdscr, maxY, maxX);
    for (auto s : vs)
    {
        if (s.size() > widestX)
            widestX = s.size();
    }
    if (optionalHeader != nullptr)
    {
        tallestY += optionalHeader->size();
        for (auto s : *optionalHeader)
        {
            if (s.size() > widestX)
                widestX = s.size();
        }
    }

    //
    // 2) Check if the input is larger than the window.
    //
    if (tallestY > maxY || widestX > maxX)
    {
        std::string mesg = "Resize your terminal window, dummy!";
        mvprintw(maxY/2, (maxX-mesg.size())/2, "%s", mesg.c_str());
        refresh();
    }
    else
    {
        //
        // 3) Do some funky maths to get the appropriate
        //    x and y offsets.
        //
        int xOffset = (maxX-widestX)/2;
        int yOffset = (maxY-tallestY)/2;
        if (optionalHeader != nullptr)
        {
            for (auto s : *optionalHeader)
            {
                mvprintw(yOffset++, xOffset, s.c_str());
            }
        }

        //
        // 4) Print.
        //
        for (unsigned x = 0; x < vs.size(); ++x)
            mvprintw(x+yOffset, xOffset, vs[x].c_str());
        refresh();
    }
}


/* this version of draw is simpler, just taking one string; it prints with an additional box */
void Screen::draw(const std::string &s) 
{
    clear();
    int row, col;
    getmaxyx(stdscr, row, col);
    mvprintw(row/2-1, (col-s.size())/2, std::string(s.size(), '-').c_str());
    mvprintw(row/2, (col-s.size())/2, "%s", s.c_str());
    mvprintw(row/2+1, (col-s.size())/2, std::string(s.size(), '-').c_str());
    refresh();
}
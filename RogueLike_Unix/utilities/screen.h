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

#ifndef _SCREEN_H_
#define _SCREEN_H_
#include <ncurses.h>
#include <string>
#include <vector>

class Screen
{
public:
	/* CONSTRUCTOR(S) */
	Screen() = default;

	/* PUBLIC METHODS: SETUP AND SHUTDOWN */
	bool initialize();
	void quit();

	/* PUBLIC METHODS: MAIN METHODS */
	void draw(const std::vector<std::string> &vs, 
		const std::vector<std::string> *const optionalHeader = nullptr);
	void draw(const std::string &s);
	int getInput();
	void pause();
};

/* INLINE DEFINITIONS */
inline void Screen::pause() { getch(); }
inline int Screen::getInput() { return getch(); }
inline void Screen::quit() { clear(); endwin(); }

#endif // _SCREEN_H_

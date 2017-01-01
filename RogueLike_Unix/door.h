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

#ifndef _DOOR_H_
#define _DOOR_H_

class Door
{
public:
    /* CONSTRUCTOR(S) */
    Door(const bool isOpen, const bool isVertical, const unsigned x, const unsigned y)
        : m_isOpen(isOpen), m_isVertical(isVertical), m_x(x), m_y(y) { };

    /* PUBLIC METHODS: GENERAL */
    bool nextTo(const unsigned x, const unsigned y);

    /* PUBLIC METHODS: GETTERS */
    bool isOpen();
    bool isVertical();
    unsigned getX();
    unsigned getY();

    /* PUBLIC METHODS: SETTERS */
    void openClose();
private:
    /* PRIVATE MEMBERS */
    bool m_isOpen;
    bool m_isVertical;
    unsigned m_x;
    unsigned m_y;
};

/* INLINE DEFINITIONS */
inline bool Door::isOpen() { return m_isOpen; }
inline bool Door::isVertical() { return m_isVertical; }
inline unsigned Door::getX() { return m_x; }
inline unsigned Door::getY() { return m_y; }
inline void Door::openClose() { m_isOpen = !m_isOpen; }

#endif  // _DOOR_H_

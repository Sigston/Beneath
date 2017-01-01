# This file is part of Descent.
#
# Descent is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Descent is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Descent.  If not, see <http://www.gnu.org/licenses/>.
#
# Alex Sigston
# admin@thestuffcupboard.com
# 2015-04-15

CC=g++
CFLAGS=-c -std=c++11 -Wall -Wextra -Wpedantic -Weffc++ -g
SOURCES=main.cpp door.cpp game.cpp inventory.cpp item.cpp player.cpp utilities/loader.cpp utilities/screen.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=roguelike
LIB=-lncurses

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIB)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o utilities/*.o roguelike

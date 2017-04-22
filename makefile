	# krusgen - a Kruskal's algorithm maze generator
	# Copyright (C) 2017 Miłosz Ryguła <miloszrygula@interia.pl>

	# This file is part of krusgen.

	# Krusgen is free software: you can redistribute it and/or modify
	# it under the terms of the GNU General Public License as published by
	# the Free Software Foundation, either version 3 of the License, or
	# (at your option) any later version.

 	# Krusgen is distributed in the hope that it will be useful,
	# but WITHOUT ANY WARRANTY; without even the implied warranty of
	# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	# GNU General Public License for more details.

	# You should have received a copy of the GNU General Public License
	# along with this program.  If not, see <http://www.gnu.org/licenses/>.

	# This is makefile for krusgen - a Kruskal's algorithm maze generator

all: libobos/lib/libobos.a
	gcc -o krusgen src/krusgen.c src/maze.c -lobos -Wall -Ilibobos/include -Llibobos/lib

libobos/lib/libobos.a:
	cd libobos && make all

clean:
	cd libobos && make clean
	rm krusgen

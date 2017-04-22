
/*
	krusgen - a Kruskal's algorithm maze generator
	Copyright (C) 2017 Miłosz Ryguła <miloszrygula@interia.pl>

	This file is part of krusgen.

	Krusgen is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Krusgen is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAZE_H
#define MAZE_H
#include <inttypes.h>

struct
{
	unsigned int width, height;
	uint16_t **walls;
	uint32_t **maze, wallcnt;
}maze;

extern uint8_t mazeInit( );
extern void mazeGrid( );
extern void mazeFlood( uint16_t x, uint16_t y, uint32_t old, uint32_t val );
extern void mazeGen( );
extern int wallsList( );
extern void mazeDraw( FILE *f );
extern void mazeBmp( FILE *f, uint32_t colwall, uint32_t colair );

#endif

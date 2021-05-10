
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

#ifndef KRUSGEN_H
#define KRUSGEN_H
#include <inttypes.h>

#define FLAG_BMP ( 1 << 0 )
#define FLAG_TXT ( 1 << 1 )
#define FLAG_FRAME ( 1 << 2 )
#define FLAG_X ( 1 << 3 )
#define FLAG_Y ( 1 << 4 )
#define FLAG_WALL ( 1 << 5 )
#define FLAG_AIR ( 1 << 6 )
#define FLAG_SEED ( 1 << 7 )
#define FLAG_WALLCHAR ( 1 << 8 )
#define FLAG_AIRCHAR ( 1 << 9 )


extern uint16_t flags;

#endif

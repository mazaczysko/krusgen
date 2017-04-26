
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

#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <obos/obos.h>
#include "krusgen.h"

struct
{
	unsigned int width, height;
	uint16_t **walls;
	uint32_t **maze, wallcnt;
}maze;

uint8_t mazeInit( )
{
	uint16_t i;
	if ( ( maze.maze = (uint32_t**) calloc( maze.width, sizeof( uint32_t* ) ) ) == NULL ) return 1;
	for ( i = 0; i < maze.width; i++ )
		if ( ( maze.maze[i] = (uint32_t*) calloc( maze.height, sizeof( uint32_t ) ) ) == NULL )
		{
			free( maze.maze );
			return 1;
		}
	return 0;
}

void mazeGrid( )
{
	uint16_t i, j, k = 1;
	for( j = 0; j< maze.height; j++ )
	{
		if( j % 2 == !!( flags & FLAG_FRAME ) )
		{
			for( i = 0; i < maze.width; i++)
			{
				if( i % 2 == !!( flags && FLAG_FRAME ) )
					maze.maze[i][j] = k++;
			}
		}
	}

	if( flags & FLAG_FRAME )
	{
		for( i = 0; i < maze.height; i++ )
						maze.maze[0][i] = 0;

		for ( i = 0; i < maze.width; i++ )
						maze.maze[i][0] = 0;

		for( i = 0; i < maze.height; i++ )
						maze.maze[maze.width - 1][i] = 0;

		for( i = 0; i < maze.width ; i++ )
						maze.maze[i][maze.height - 1] = 0;
	}
}

void mazeFlood( uint16_t x, uint16_t y, uint32_t old, uint32_t val )
{
	if( x >= maze.width || y >= maze.height || x < 0 || y <0 ) return;
	if( maze.maze[x][y] != old) return;

	maze.maze[x][y] = val;

	mazeFlood( x-1, y, old, val);
	mazeFlood( x+1, y, old, val);
	mazeFlood( x, y-1, old, val);
	mazeFlood( x, y+1, old, val);

}

void mazeGen( )
{
	srand( time( NULL ) );
	while( maze.wallcnt )
	{
		unsigned int r = rand( ) % maze.wallcnt, w = 0, h = 0;
		w = maze.walls[r][0];
		h = maze.walls[r][1];
		maze.walls[r][0] = maze.walls[maze.wallcnt - 1][0];
		maze.walls[r][1] = maze.walls[maze.wallcnt - 1][1];
		maze.wallcnt--;
			if( w > 0 && w < maze.width - 1 && maze.maze[w+1][h] != 0 && maze.maze[w-1][h] != 0&& maze.maze[w+1][h] != maze.maze[w-1][h] )
			{
				maze.maze[w][h] = maze.maze[w+1][h];
				mazeFlood( w-1, h, maze.maze[w-1][h], maze.maze[w+1][h]);
			}
			if( h > 0 && h < maze.height - 1 && maze.maze[w][h+1] != 0 && maze.maze[w][h-1] !=0 && maze.maze[w][h+1] != maze.maze[w][h-1] )
			{
				maze.maze[w][h] = maze.maze[w][h+1];
				mazeFlood( w, h-1, maze.maze[w][h-1], maze.maze[w][h+1]);
			}
		}
}
int wallsList( )
{
	uint32_t i, j, c = 0;
	for( i = 0; i < maze.width; i++ )
	{
		for( j = 0; j < maze.height; j++)
		{
			if( maze.maze[i][j] == 0 )
			{
				c++;
			}
		}
	}
	maze.wallcnt = c;
	if ( ( maze.walls = (uint16_t**) calloc(c, sizeof( uint16_t* ) ) ) == NULL ) return 1;
		for ( i = 0; i < c; i++ )
		if ( ( maze.walls[i] = (uint16_t*) calloc( 2, sizeof( uint16_t ) ) ) == NULL )
		{
			free( maze.walls );
			return 1;
		}
	c = 0;
		for( i = 0; i < maze.width; i++ )
		{
			for( j = 0; j < maze.height; j++)
			{
				if( maze.maze[i][j] == 0 )
				{
					maze.walls[c][0] = i;
					maze.walls[c][1] = j;
					c++;
				}
			}
		}
	return 0;
}

void mazeDraw( FILE *f )
{
	uint16_t i, j;
	for( i = 0; i < maze.height; i++ )
	{
		for( j = 0; j < maze.width; j++ )
			if ( maze.maze[j][i] )
			{
				fprintf(f, " ");
			}
			else
			{
				fprintf(f, "#");
			}
		fprintf(f, "\n");
	}

}

void mazeBmp( FILE *f, uint32_t colwall, uint32_t colair )
{
	uint16_t i, j;
	BMP2 bmp;
	bmpInit( &bmp, maze.width, maze.height );
	for( i = 0; i < maze.width; i++ )
	{
		for( j = 0; j < maze.height; j++ )
			if ( maze.maze[i][j] )
			{
				bmp.imageData[i][j].colnum = colair;
			}
			else
			{
				bmp.imageData[i][j].colnum = colwall;
			}
	}
	bmpWrite( &bmp, f );
	bmpFree( &bmp );
}

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

struct
{
	uint16_t width, height, **walls;
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
		if( j % 2 )
		{
			for( i = 0; i < maze.width; i++)
			{
				if( i % 2)
					maze.maze[i][j] = k++;
			}
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
	printf("\nWalls count:%d\n",c);
	return 0;
}

void mazeDraw( )
{
	uint16_t i, j;
	for( i = 0; i < maze.height; i++ )
	{
		for( j = 0; j < maze.width; j++ )
			if ( maze.maze[j][i] )
			{
				printf(" ");
			}
			else
			{
				printf("#");
			}
		printf("\n");
	}

}

int main( )
{
	maze.width = 32;
	maze.height = 32;

	mazeInit( );
	mazeGrid( );
	mazeDraw( );
	wallsList( );
	return 0;
}

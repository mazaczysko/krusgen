#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

struct
{
	uint16_t width, height;
	uint32_t **maze;
}maze;

uint8_t mazeInit( )
{
	uint16_t i;
	if ( ( maze.maze = (uint32_t**) malloc( maze.width * sizeof( uint32_t* ) ) ) == NULL ) return 1;
	for ( i = 0; i < maze.width; i++ )
		if ( ( maze.maze[i] = (uint32_t*) malloc( maze.height * sizeof( uint32_t ) ) ) == NULL )
		{
			free( maze.maze );
			return 1;
		}
	return 0;
}

void mazeGrid( )
{

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
	return 0;
}

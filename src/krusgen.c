#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

#define KRUSGEN_VERSION "v0.5"

#define FLAG_BMP ( 1 << 0 )
#define FLAG_TXT ( 1 << 1 )
uint16_t flags = 0;

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
		if( j % 2 == 0  )
		{
			for( i = 0; i < maze.width; i++)
			{
				if( i % 2 == 0 )
					maze.maze[i][j] = k++;
			}
		}
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
				bmp.imageData[i][j].colnum = colwall;
			}
			else
			{
				bmp.imageData[i][j].colnum = colair;
			}
	}
	bmpWrite( &bmp, f );
	bmpFree( &bmp );
}

int main( int argc, char **argv )
{
	int i, badarg;
	uint32_t colwall = 0xFFFFFF, colair = 0x000000;
	FILE *outfile = stdout;
	maze.width = 31;
	maze.height = 31;
	for( i = 1; i < argc; i++)
	{
		badarg = 1;
		if( !strcmp( argv[i], "-x" ) )
		{
			if( i + 1 >= argc || !sscanf( argv[++i], "%d", &maze.width ) )
			{
				fprintf(stderr, "%s: bad value for %s\n", argv[0], argv[i]);
				return 1;
			}
			badarg = 0;
		}

		if( !strcmp( argv[i], "-y" ) )
		{
			if( i + 1 >= argc || !sscanf( argv[++i], "%d", &maze.height) )
			{
				fprintf(stderr, "%s: bad value for %s\n", argv[0], argv[i]);
				return 1;
			}
			badarg = 0;
		}

		if( !strcmp( argv[i], "-h" ) || !strcmp( argv[i], "--help" ) )
		{
			printf(	"%s " KRUSGEN_VERSION " - maze generator\n" \
					"Usage: %s [OPTIONS]\n\n" \
					"Supported options:\n" \
					"\t-h, --help - show help\n" \
					"\t-x [odd number] - define map width\n" \
					"\t-y [odd number] - define map height\n" \
					"\t-t, --txt [file name.txt] - export maze to .txt file\n" \
					"\n-b, --bmp [file name.bmp] - export maze to .bmp file\n"
					, argv[0], argv[0] );
			badarg = 0;
			return 0;
		}


		if( !strcmp( argv[i], "--txt" ) || !strcmp( argv[i], "-t" ) )
		{
			if( i + 1 >= argc )
			{
				fprintf(stderr, "%s: missing value for '%s'\n", argv[0], argv[i] );
				return 1;
			}
			outfile = fopen(argv[++i], "w");
			if( outfile == NULL )
			{
				fprintf(stderr, "%s: cannot open file\n", argv[0] );
			}
			flags |= FLAG_TXT;
			badarg = 0;
		}

		if( !strcmp( argv[i], "--bmp" ) || !strcmp( argv[i], "-b" ) )
		{
			if( i + 1 >= argc )
			{
				fprintf(stderr, "%s: missing value for '%s'\n", argv[0], argv[i] );
				return 1;
			}
			outfile = fopen(argv[++i], "w");
			if( outfile == NULL )
			{
				fprintf(stderr, "%s: cannot open file\n", argv[0] );
			}
			flags |= FLAG_BMP;
			badarg = 0;
		}

		if( !strcmp( argv[i], "--air" ) || !strcmp( argv[i], "-a" ) )
		{
			if( i + 1 >= argc )
			{
				fprintf(stderr, "%s: missing value for '%s'\n", argv[0], argv[i] );
				return 1;
			}
			if( sscanf( argv[++i], "%06x", &colair ) != 1)
			{
				fprintf( stderr, "%s: bad value '%s'\n", argv[0], argv[i] );
				return 1;
			}
			badarg = 0;
		}

		if( !strcmp( argv[i], "--wall" ) || !strcmp( argv[i], "-w" ) )
		{
			if( i + 1 >= argc )
			{
				fprintf(stderr, "%s: missing value for '%s'\n", argv[0], argv[i] );
				return 1;
			}
			if( sscanf( argv[++i], "%06x", &colwall ) != 1)
			{
				fprintf( stderr, "%s: bad value '%s'\n", argv[0], argv[i] );
				return 1;
			}
			badarg = 0;
		}

		if (badarg)
		{
			fprintf(stderr, "%s: bad argument '%s'\n", argv[0], argv[i]);
			return 1;
		}
	}
	if( maze.width % 2 == 0 || maze.height % 2 == 0 )
	{
		fprintf( stderr, "%s: dimensions must be odd!\n", argv[0]);
		return 1;
	}
	mazeInit( );
	mazeGrid( );
	wallsList( );
	mazeGen( );
	if( flags & FLAG_BMP && flags & FLAG_TXT )
	{
		fprintf( stderr, "%s: cannot export to .bmp and .txt files at once\n", argv[0]);
	}
	if( flags & FLAG_BMP )
		mazeBmp( outfile, colwall, colair );
	else
		mazeDraw( outfile );
	fclose( outfile );
	return 0;
}

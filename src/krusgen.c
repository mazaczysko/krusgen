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
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <obos/obos.h>
#include "maze.h"
#include "krusgen.h"

#define KRUSGEN_VERSION "v1.3"

uint16_t flags = 0;

int main( int argc, char **argv )
{
	int i, badarg;
	char wallchr = '#', airchr = ' ';
	char * outputfilename = NULL;
	uint32_t colwall = 0xFFFFFF, colair = 0x000000;
	FILE *outfile = stdout;
	maze.width = 31;
	maze.height = 31;
	struct timeval tv;
	gettimeofday( &tv, NULL );
	unsigned long long int seed = tv.tv_sec * 1000000 + tv.tv_usec;

	for( i = 1; i < argc; i++)
	{
		badarg = 1;
		if( !strcmp( argv[i], "-x" ) )
		{
			if( i + 1 >= argc )
			{
				fprintf(stderr, "%s: missing value for '%s'\n", argv[0], argv[i]);
				return 1;
			}
			if( !sscanf( argv[++i], "%d", &maze.width ) )
			{
				fprintf(stderr, "%s: bad value for '%s'\n", argv[0], argv[i-1]);
				return 1;
			}

			if( maze.width <= 0 || maze.width % 2 == 0 )
			{
				fprintf( stderr, "%s: bad value for '%s': dimensions must be odd and positive!\n", argv[0], argv[i-1]);
				badarg = 1;
				return 1;
			}
			badarg = 0;
		}

		if( !strcmp( argv[i], "-y" ) )
		{
			if( i + 1 >= argc )
			{
				fprintf(stderr, "%s: missing value for '%s'\n", argv[0], argv[i]);
				return 1;
			}
			if( !sscanf( argv[++i], "%d", &maze.height ) )
			{
				fprintf(stderr, "%s: bad value for '%s'\n", argv[0], argv[i-1]);
				return 1;
			}

			if( maze.height <= 0 || maze.height % 2 == 0 )
			{
				fprintf( stderr, "%s: bad value for '%s': dimensions must be odd and positive!\n", argv[0], argv[i-1]);
				badarg = 1;
				return 1;
			}
			badarg = 0;
		}

		if( !strcmp( argv[i], "-h" ) || !strcmp( argv[i], "--help" ) )
		{
			printf(	"%s " KRUSGEN_VERSION " - Kruskal's algorithm maze generator\n" \
					"Usage: %s [OPTIONS]\n\n" \
					"Supported options:\n" \
					"\t-h, --help - show help\n" \
					"\t-v, --version - show Krusgen's version\n" \
					"\t-x [positive, odd number] - define map width\n" \
					"\t-y [positive, odd number] - define map height\n" \
					"\t-f, --frame - add borders to maze\n" \
					"\t-s, --seed [seed] - define seed to generate maze\n" \
					"\t-v, --version - displays krusgen version\n" \
					"\t-t, --txt [file name] - export maze to txt file\n" \
					"\t-b, --bmp [file name] - export maze to bmp file\n" \
					"\t-w, --wall [hexadecimal] - define wall color in bmp\n" \
					"\t-a, --air [hexadecimal] - define air color in bmp\n" \
					"\t-W, --wallchar [character] - define wall character\n" \
					"\t-A, --airchar [character] - define air character\n"
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
			outputfilename = argv[++i];
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
			outputfilename = argv[++i];
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

		if( !strcmp( argv[i], "-f" ) || !strcmp( argv[i], "--frame" ) )
		{
			flags |= FLAG_FRAME;
			badarg = 0;
		}

		if( !strcmp( argv[i], "--seed" ) || !strcmp( argv[i], "-s" ) )
		{
			if( i + 1 >= argc )
			{
				fprintf(stderr, "%s: missing value for '%s'\n", argv[0], argv[i] );
				return 1;
			}

			if( sscanf( argv[++i], "%llu", &seed ) != 1)
			{
				fprintf( stderr, "%s: bad value '%s'\n", argv[0], argv[i] );
				return 1;
			}
			badarg = 0;
		}

		if( !strcmp( argv[i], "-v") || !strcmp( argv[i], "--version" ) )
			{
				printf("%s " KRUSGEN_VERSION "\n", argv[0] );
				badarg = 0;
				return 0;
			}

		if( !strcmp( argv[i], "--wallchar" ) || !strcmp( argv[i], "-W" ) )
		{
			if( i + 1 >= argc )
			{
				fprintf(stderr, "%s: missing value for '%s'\n", argv[0], argv[i] );
				return 1;
			}
			wallchr = argv[++i][0];
			badarg = 0;
		}

		if( !strcmp( argv[i], "--airchar" ) || !strcmp( argv[i], "-A" ) )
		{
			if( i + 1 >= argc )
			{
				fprintf(stderr, "%s: missing value for '%s'\n", argv[0], argv[i] );
				return 1;
			}
			airchr =  argv[++i][0];
			badarg = 0;
		}

		if (badarg)
		{
			fprintf(stderr, "%s: bad argument '%s'\n", argv[0], argv[i]);
			return 1;
		}
	}

	if( flags & FLAG_BMP && flags & FLAG_TXT )
	{
		fprintf( stderr, "%s: cannot export to .bmp and .txt files at once!\n", argv[0]);
		return 1;
	}

	if( outputfilename != NULL)
	{
		outfile = fopen( outputfilename, "w");

		if( outfile == NULL )
		{
			fprintf(stderr, "%s: cannot open file!\n", argv[0] );
			return 1;
		}
	}

	if( mazeInit( ) == 1 )
	{
		fprintf( stderr, "%s: memory allocation error!\n", argv[0]);
		return 1;
	}

	mazeGrid( );
	
	if( wallsList( ) == 1 )
	{
		fprintf( stderr, "%s: memory allocation error!\n", argv[0]);
		free( maze.maze );
		return 1;
	}

	srand( seed );
	mazeGen( );


	if( flags & FLAG_BMP )
		mazeBmp( outfile, colwall, colair );
	else
		mazeDraw( outfile, wallchr, airchr );

	fclose( outfile );
	free(maze.maze);
	free(maze.walls);
	return 0;
}

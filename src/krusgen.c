#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <obos.h>
#include "maze.h"

#define KRUSGEN_VERSION "v0.5"

#define FLAG_BMP ( 1 << 0 )
#define FLAG_TXT ( 1 << 1 )
uint16_t flags = 0;

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
					"\t-t, --txt [file name] - export maze to txt file\n" \
					"\t-b, --bmp [file name] - export maze to bmp file\n" \
					"\t-w, --wall [hexadecimal] - define wall color in bmp\n" \
					"\t-a, --air [hexadecimal] - define air color in bmp\n"
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

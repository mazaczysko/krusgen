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

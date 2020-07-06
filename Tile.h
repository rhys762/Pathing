#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

/*
 *	The grid will be broken into a bunch of tiles, which know: thier coods, thier state
 *
 */

enum class TileState
{
	free,//can be walked on
	blocked,//cannot
	walked//is walked on
};

struct Tile
{
	TileState state = TileState::free;//determines the color on the gui and used for pathing
	SDL_Rect outline, inner;//rects for the outline and inner
};

//draw the tile to the renderer
void tdraw(const Tile & t, SDL_Renderer * rend);

Tile tile_fac(int xpos, int ypos, int width);//factory function for creating a tile

#endif

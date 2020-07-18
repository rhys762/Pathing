#include "Tile.h"

//draw the tile to the renderer
void tdraw(const Tile & t, SDL_Renderer * rend)
{
	//draw the black outline
	
	SDL_SetRenderDrawColor(rend, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(rend, &t.outline);
	
	//draw the coloured inner
	switch(t.state)
	{
		case TileState::free: 
			SDL_SetRenderDrawColor(rend, 0xC0, 0xC0, 0xC0, 0xFF);//silver
			break;
		case TileState::blocked:
			SDL_SetRenderDrawColor(rend, 0x69, 0x69, 0x69, 0xFF);//grey
			break;
		case TileState::walked:
			SDL_SetRenderDrawColor(rend, 0x33, 0x33, 0xFF, 0xFF);//blue
			break;
		case TileState::origin:
			SDL_SetRenderDrawColor(rend, 0xFF, 0xA5, 0x00, 0xFF);//orange
			break;
		case TileState::checked:
			SDL_SetRenderDrawColor(rend, 0x9A, 0xCD, 0x32, 0xFF);//green
			break;
	}

	SDL_RenderFillRect(rend, &t.inner);
}

Tile tile_fac(int row, int col, int width)//factory function for creating a tile
{
	Tile t;

	//set the outline
	t.outline.x = row*width;
	t.outline.y = col*width;
	t.outline.w = t.outline.h = width;

	//set the inner
	t.inner.x = t.outline.x+1;
	t.inner.y = t.outline.y+1;
	t.inner.w = t.inner.h = width-2;

	t.r = row;
	t.c = col;

	return t;
}

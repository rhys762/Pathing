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
	}

	SDL_RenderFillRect(rend, &t.inner);
}

Tile tile_fac(int xpos, int ypos, int width)//factory function for creating a tile
{
	Tile t;

	//set the outline
	t.outline.x = xpos;
	t.outline.y = ypos;
	t.outline.w = t.outline.h = width;

	//set the inner
	t.inner.x = xpos+1;
	t.inner.y = ypos+1;
	t.inner.w = t.inner.h = width-2;

	return t;
}

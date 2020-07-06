#include "TileGrid.h"
		
void TileGrid::clear_states()//return the states to initial values
{

}

void TileGrid::path()//path from source to target	
{

}

TileGrid::TileGrid(int r, int c, int w)//init
:grid{new Tile [r*c]}, rows{r}, columns{c}, width{w}
{
	for(int i = 0; i < r; i++)
	{
		for(int j = 0; j < c; j++)
		{
			grid[i*columns + j] = tile_fac(i*width, j*width, w); 
		}
	}

	grid[source_r*columns + source_c].state = TileState::walked;
}
		
void TileGrid::draw(SDL_Renderer * renderer)//draw the grid to renderer
{
	for(int i = 0; i < (rows*columns); i++)
	{
		tdraw(grid[i], renderer);
	}
}

void TileGrid::click(int x, int y)//click on an x,y
{
	int r = x/width;
	int c = y/width;

	//early exit
	if(r == source_r && c == source_c)
	{
		return;
	}

	Tile & t = grid[r*columns + c];

	if(t.state == TileState::free || t.state == TileState::walked)
	{
		t.state = TileState::blocked;
	}
	else if(t.state == TileState::blocked)
	{
		t.state = TileState::free;
	}
}

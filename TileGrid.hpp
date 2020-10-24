#ifndef TILEGRID_H
#define TILEGRID_H

#include "Tile.hpp"
#include <SDL2/SDL.h>

class TileGrid
{
	private:
		Tile * grid = nullptr;
		int rows, columns, width;
		int source_r = 0, source_c = 0;//source to path from
		int target_r, target_c;//target to path to

		void set_walked_states_free();//return the states to initial values
		void path();//path from source to target	
	public:
		TileGrid(int r, int c, int w);//init

		int get_rows();
		int get_columns();

		Tile * operator[](int index);//return a pointer to the tile at index

		void draw(SDL_Renderer * renderer);//draw the grid to renderer
		void click(int x, int y);//click on an x,y
};

#endif

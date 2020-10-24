#include <vector>
#include <cmath>
#include <iostream>

#include "TileGrid.hpp"
#include "AStar.hpp"
#include "AStarBoiler.hpp"

void TileGrid::set_walked_states_free()//set walked states to free AND set origin nodes to the correct state
{
	for(int i = 0; i < rows*columns; i++)
	{
		if(grid[i].state != TileState::origin && grid[i].state != TileState::blocked)
		{
			grid[i].state = TileState::free;
		}
	}

	grid[0].state = TileState::origin;
	grid[rows*columns-1].state = TileState::origin;
}

void TileGrid::path()//path from source to target	
{
	Tile * start = &grid[0];//start is top left
	Tile * goal = &grid[rows*columns-1];//end is bottom right

	//this instantiates some thing from astar boiler, which was big enough to be in a different file

	//returns neighbours
	NFunctor nf = {this};
	//heuristic for estimating distance to goal node
	HFunctor hf = {goal};

	//edge cost also defined in boiler
	auto path = AStar(start, goal, hf, edge_cost, nf);

	if(path.size())
	{
		path.erase(path.begin());//remove the end node (its goal, like the last pointer will always be goal on succesful path)
		for(auto t : path)
		{
			t->state = TileState::walked;
		}
	}
}

TileGrid::TileGrid(int r, int c, int w)//init
:grid{new Tile [r*c]}, rows{r}, columns{c}, width{w}
{
	for(int i = 0; i < r; i++)
	{
		for(int j = 0; j < c; j++)
		{
			grid[i*columns + j] = tile_fac(i, j, w); 
		}
	}

	set_walked_states_free();
	path();
}

int TileGrid::get_rows()
{
	return rows;
}

int TileGrid::get_columns()
{
	return columns;
}

Tile * TileGrid::operator[](int index)//return a pointer to the tile at index
{
	return grid + index;
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

	//clear whats in the grid
	set_walked_states_free();

	//the target tile who's 'walkability' is toggled
	Tile & t = grid[r*columns + c];

	if(t.state != TileState::origin && t.state != TileState::blocked)
	{
		t.state = TileState::blocked;
	}
	else if(t.state == TileState::blocked)
	{
		t.state = TileState::free;
	}

	path();//repath
}

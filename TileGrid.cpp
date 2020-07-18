#include <vector>
#include <cmath>
#include <iostream>

#include "TileGrid.h"
#include "AStar.h"

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

	//this is going to be some boilerplate for the general a star func
	//its larger than it should be	
	//this needs to return a container with the neighbours to the param tile
	struct NFunctor 
	{
		TileGrid * tg = nullptr;

		std::vector<Tile*> operator()(Tile * tile)
		{
			if(tile->state != TileState::origin)
			{
				tile->state = TileState::checked;
			}
			std::vector<Tile*> neighbors;
			int r, c;
			int rows = tg->get_rows(), columns = tg->get_columns();

			//std::cout << "checking for neighbors of " << tile->r << ", " << tile->c << std::endl;
			//push pointers to the neighboring tiles to neighbors
			for(int i = -1; i < 2; i++)
			{
				for(int j = -1; j < 2; j++)
				{
					//i = j = 0 equates to the param tile, dont want to be neighbor to ourself
					if(!i && !j)
					{
						continue;
					}
					
					r = tile->r + i;
					c = tile->c + j;

					//if the rc is valid, push the tile
					if(r >= 0 && r < rows && c >= 0 && c < columns)
					{
						Tile * n = tg->operator[](r*columns + c);
						if(n->state != TileState::blocked)
						{	
							neighbors.push_back(n);
						}
					}

				}
			}

			return neighbors;
		}
	};

	//this needs to estimate the distance to goal
	struct HFunctor
	{
		Tile * goal = nullptr;

		double operator()(Tile * tile)
		{
			double x_dist = goal->r - tile->r;
			double y_dist = goal->c - tile->c;
			return sqrt(x_dist*x_dist + y_dist*y_dist);
		}
	};

	auto edge_cost = [](Tile * a, Tile * b)
	{
		if(a->r == b->r || a->c == b->c)
		{
			return 1.0;
		}	
		else
		{	
			return 1.7;//root 2
		}
	};

	NFunctor nf = {this};
	HFunctor hf = {goal};

	auto path = AStar(start, goal, hf, edge_cost, nf);

	if(path.size())
	{
		path.erase(path.begin());//remove the end node
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
	//std::cout << "CLICK REGISTERED" << std::endl;

	int r = x/width;
	int c = y/width;

	set_walked_states_free();

	Tile & t = grid[r*columns + c];

	if(t.state != TileState::origin && t.state != TileState::blocked)
	{
		t.state = TileState::blocked;
	}
	else if(t.state == TileState::blocked)
	{
		t.state = TileState::free;
	}
	path();
}

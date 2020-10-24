#ifndef ASTARTBOILER_HPP
#define ASTARTBOILER_HPP

//boiler plate for getting templated astar to work

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

//cost of moving from a to b
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

#endif

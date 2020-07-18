/*
 *	Rhys Trueman || 4/7/2020
 *	Building a portfolio so i can hopefilly get a job one day
 *	Starting off small
 *	Demonstrates the templated astar algo on an interactive grid
 */

#include <iostream>
#include <SDL2/SDL.h>

#include "Window.h"
#include "TileGrid.h"

int main()
{
	int window_width = 600;
	int window_height = 600;

	int box_width = 50;
	int box_rows = window_height/box_width;
	int box_columns = window_width/box_width;

	Window win ("Pathing Demo: Click a box!", window_width, window_height);

	SDL_SetRenderDrawColor(win.rend(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(win.rend());

	TileGrid grid (box_rows, box_columns, box_width);

	grid.draw(win.rend());

	SDL_RenderPresent(win.rend());

	//event loop:
	SDL_Event e;
	bool running = true;
	int mouse_x, mouse_y;

	while(running)
	{
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&mouse_x, &mouse_y);
					grid.click(mouse_x, mouse_y);
					grid.draw(win.rend());
					SDL_RenderPresent(win.rend());
					break;
				default:
					break;
			}
		}
	}

	return 0;
}

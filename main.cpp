/*
 *	Rhys Trueman || 4/7/2020
 *	Building a portfolio so i can hopefilly get a job one day
 *	Starting off small
 *	Demonstrates the templated astar algo on an interactive grid
 */

#include <iostream>
#include <SDL2/SDL.h>

#include "Window.hpp"
#include "TileGrid.hpp"

int main()
{
	const int window_width = 600;
	const int window_height = 600;

	const int box_width = 50;
	const int box_rows = window_height/box_width;
	const int box_columns = window_width/box_width;

	bool running = true;

	Window win ("Pathing Demo: Click a box!", window_width, window_height, &running);

	SDL_SetRenderDrawColor(win.renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(win.renderer());

	TileGrid grid (box_rows, box_columns, box_width);

	grid.draw(win.renderer());

	SDL_RenderPresent(win.renderer());

	//event loop:
	SDL_Event e;
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
					grid.draw(win.renderer());
					SDL_RenderPresent(win.renderer());
					break;
				default:
					break;
			}
		}
	}

	return 0;
}

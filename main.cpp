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
	//const variables
	const int window_width = 600;
	const int window_height = 600;

	const int box_width = 50;
	const int box_rows = window_height/box_width;
	const int box_columns = window_width/box_width;

	//running is true when the main loop should continue, set by window creation
	bool running;

	//create a window
	Window win ("Pathing Demo: Click a box!", window_width, window_height, &running);

	//clears the window, in hindsight this isnt necessary? TODO check later
	SDL_SetRenderDrawColor(win.renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(win.renderer());

	//the grid of tile to path over
	TileGrid grid (box_rows, box_columns, box_width);

	//draws grid to screen
	grid.draw(win.renderer());

	SDL_RenderPresent(win.renderer());

	//event loop:
	SDL_Event e;
	int mouse_x, mouse_y;

	//main loop
	while(running)
	{
		//event loop
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_QUIT://exit
					running = false;
					break;
				case SDL_MOUSEBUTTONDOWN://mouse click, causes a repath and redraw
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

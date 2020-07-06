#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

/*
 *	Rhys Trueman || 4/7/2020
 *	Wrapper for an sdl window and renderer pair
 */

class Window
{
	private:
		SDL_Window * window = nullptr;
		SDL_Renderer * renderer = nullptr;
	public:
		Window(const char * title, int w, int h);//constr, calls sdl init
		SDL_Renderer * rend();//get the renderer
};

#endif

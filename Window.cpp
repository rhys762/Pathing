#include "Window.h"

Window::Window(const char * title, int w, int h)//constr, calls sdl init
{
	SDL_Init(SDL_INIT_EVERYTHING);//init sdl

	//create window
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);

	//create renderer
	renderer = SDL_CreateRenderer(window, -1, 0);

}

SDL_Renderer * Window::rend()//get the renderer
{
	return renderer;
}

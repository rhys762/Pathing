#ifndef WINDOW_HPP
#define WINDOW_HPP

/*
 *	Rhys Trueman || 16/8/2020
 *
 *	SDL window and wrapper pair
 *	calls sdl init in its constructor, and sdl quit on its destruction
 */

#include <SDL2/SDL.h>

class Window
{
	public:
		//structors 
		Window(const char * title, int width, int height, bool * success, int windowFlags=0, int renderFlags=SDL_RENDERER_ACCELERATED);
		~Window();
	
		//returns a pointer to the windows renderer
		SDL_Renderer * renderer();
		//creates an additional texture with the same format as the window
		SDL_Texture * createTexture(int access, int width, int height);
	private:
		SDL_Window * mWindow;
		SDL_Renderer * mRenderer;

		int mWidth;
		int mHeight;
};

#endif

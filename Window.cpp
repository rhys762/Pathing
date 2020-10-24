#include "Window.hpp"
#include <iostream>//error output

//structors 
Window::Window(const char * title, int width, int height, bool * success, int windowFlags, int renderFlags)
:mWindow{nullptr}, mRenderer{nullptr}, mWidth{width}, mHeight{height}
{
	*success = false;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Could not init sdl: " << SDL_GetError() << std::endl;
	}
	else
	{

		mWindow = SDL_CreateWindow(title,
			       SDL_WINDOWPOS_UNDEFINED,	
			       SDL_WINDOWPOS_UNDEFINED,	
			       mWidth,
			       mHeight,
			       windowFlags);

		if(mWindow == nullptr)
		{
			std::cout << "could not create window: " << SDL_GetError() << std::endl;
		}
		else
		{
			int rendererMagicNumber = -1;//something to do with driver
			mRenderer = SDL_CreateRenderer(mWindow,
					rendererMagicNumber,
					renderFlags);

			if(mRenderer == nullptr)
			{
				std::cout << "Couldnt create renderer: " << SDL_GetError() << std::endl;
			}
			else
			{
				*success = true;
			}
		}
	}
}

Window::~Window()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}
		
//returns a pointer to the windows renderer
SDL_Renderer * Window::renderer()
{
	return mRenderer;
}
		
//creates an additional texture with the same format as the window
SDL_Texture * Window::createTexture(int access, int width, int height)
{
	//first need to grab the format from the window texture
	auto pixelFormat = SDL_GetWindowPixelFormat(mWindow);

	if(pixelFormat == SDL_PIXELFORMAT_UNKNOWN)
	{
		std::cout << "Window Error: createTexture: couldn't retreive pixel format" << std::endl;
		return nullptr;
	}

	SDL_Texture * newTexture = SDL_CreateTexture(mRenderer, pixelFormat, access, width, height);

	if(newTexture == nullptr)
	{
		std::cout << "Window Error: createTexture: couldn't create new texture" << std::endl;
	}

	return newTexture;
}

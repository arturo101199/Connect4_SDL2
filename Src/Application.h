#pragma once
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Application
{
public:
	Application();
	~Application();

	static const int APPLICATION_WIDTH = 640;
	static const int APPLICATION_HEIGHT = 550;

	//The window we'll be rendering to
	static SDL_Window* gWindow;

	//The window renderer
	static SDL_Renderer* gRenderer;

	static bool isWellInitialized;

private:
	static bool init();
	static void close();
};


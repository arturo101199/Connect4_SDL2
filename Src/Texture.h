#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_TTF.h>
#include "Application.h"

class Texture
{
public:

	Texture();

	~Texture();

	bool LoadFromFile(std::string path);

	//Creates image from font string
	bool LoadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font);


	void Render(int x, int y, SDL_Rect* clip);

	int GetWidth();
	int GetHeight();

private:

	void free();

	SDL_Texture* mTexture;

	SDL_Renderer* gRenderer;

	int mWidth;
	int mHeight;
};
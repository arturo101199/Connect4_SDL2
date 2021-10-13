#pragma once
#include <SDL.h>

class Button
{
public:
	void SetRect(const SDL_Rect& rect);
	bool IsPressed();
private:
	SDL_Rect rect;
};
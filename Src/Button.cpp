#include "Button.h"

void Button::SetRect(const SDL_Rect& rect)
{
	this->rect = rect;
}

bool Button::IsPressed()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	if (mouseX >= rect.x && mouseX <= rect.x + rect.w)
	{
		if (mouseY >= rect.y && mouseY <= rect.y + rect.h)
			return true;
	}
	return false;
}

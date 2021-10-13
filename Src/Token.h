#pragma once
#include "Texture.h"

enum class TokenType {EMPTY, RED, YELLOW};
class Token 
{
public:
	static constexpr int TOKEN_WIDTH = 91;
	static constexpr int TOKEN_HEIGHT = 91;

	Token(int xPos, int yPos, Texture* texture, SDL_Rect* tokenClips);

	void Render();
	TokenType GetTokenType();
	void SetTokenType(TokenType type);

private:
	int xPos;
	int yPos;
	Texture* texture;
	SDL_Rect* tokenClips;
	TokenType tokenType;
};

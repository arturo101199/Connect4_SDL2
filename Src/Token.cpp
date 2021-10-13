#include "Token.h"

Token::Token(int xPos, int yPos, Texture* texture, SDL_Rect* tokenClips)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->texture = texture;
	this->tokenClips = tokenClips;
	tokenType = TokenType::EMPTY;
}

void Token::Render()
{
	SDL_Rect* clip;
	switch (tokenType)
	{
	case TokenType::EMPTY:
		clip = &tokenClips[0];
		break;
	case TokenType::RED:
		clip = &tokenClips[1];
		break;
	default:
		clip = &tokenClips[2];
		break;
	}
	texture->Render(xPos, yPos, clip);
}

TokenType Token::GetTokenType() 
{
	return tokenType;
}

void Token::SetTokenType(TokenType type) 
{
	tokenType = type;
}
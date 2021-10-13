#pragma once
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Texture.h"
#include "Token.h"
#include "Button.h"
#include "Application.h"

class Game
{
public:
	Game();
	~Game();
	bool IsWellInitialized();
	bool IsGameEnded();
	bool IsGameRestarted();
	void Update();
private:
	static constexpr int ROWS = 6;
	static constexpr int COLS = 7;

	static constexpr float XOFFSET = (Application::APPLICATION_WIDTH - Token::TOKEN_WIDTH * COLS) / 2;
	static constexpr float YOFFSET = (Application::APPLICATION_HEIGHT - Token::TOKEN_HEIGHT * ROWS) / 2;


	bool loadMedia();

	void close();

	void initializeBoard();

	void createRestartButton();

	void handleEvents();

	void tryToPlaceAToken();

	void placeToken(int row, int col);

	void getBoardCoordsFromMouse(int& row, int& col);

	bool isValidMove(int row, int col);

	bool isHorizontalWin(int row, int col, TokenType player);

	bool isVerticalWin(int row, int col, TokenType player);

	bool isDescendingDiagonalWin(int row, int col, TokenType player);

	bool isAscendingDiagonalWin(int row, int col, TokenType player);

	bool isWin(int row, int col, TokenType player);

	void render();

	void renderWinText();

	TTF_Font* gFont = NULL;

	//Scene sprites
	SDL_Rect gTokenClips[3];
	Texture gTokensSpriteSheetTexture;

	Texture textBackground;
	Texture player1WinsTextTexture;
	Texture player2WinsTextTexture;
	Texture restartTextTexture;

	std::vector<std::vector<Token>> board;

	TokenType playerColors[2];
	int turn;

	Button restartButton;

	bool isWellInitialized;
	bool quit;
	bool endGame;
	bool isRestart;

	SDL_Event e;

};


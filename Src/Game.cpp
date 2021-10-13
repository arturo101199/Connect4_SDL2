#include "Game.h"

Game::Game()
{
    isWellInitialized = loadMedia();
    initializeBoard();
	createRestartButton();
	endGame = false;
	quit = false;
	isRestart = false;
}

Game::~Game()
{
	close();
}

bool Game::IsWellInitialized()
{
	return isWellInitialized;
}

bool Game::IsGameEnded()
{
	return quit;

}
bool Game::IsGameRestarted()
{
	return isRestart;
}

void Game::Update()
{
	handleEvents();
	render();
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if (!gTokensSpriteSheetTexture.LoadFromFile("media/Tokens.png"))
	{
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}
	else
	{
		//Set left sprite
		gTokenClips[0].x = 0;
		gTokenClips[0].y = 0;
		gTokenClips[0].w = 91;
		gTokenClips[0].h = 91;

		//Set center sprite
		gTokenClips[1].x = 91;
		gTokenClips[1].y = 0;
		gTokenClips[1].w = 91;
		gTokenClips[1].h = 91;

		//Set right sprite
		gTokenClips[2].x = 182;
		gTokenClips[2].y = 0;
		gTokenClips[2].w = 91;
		gTokenClips[2].h = 91;

	}

	if (!textBackground.LoadFromFile("media/TextBackground.png"))
	{
		printf("Failed to load TextBackground texture!\n");
		success = false;
	}

	gFont = TTF_OpenFont("media/Ephesis-Regular.ttf", 80);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 0, 0 };
		if (!player1WinsTextTexture.LoadFromRenderedText("Player 1 wins", textColor, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}

		textColor = { 255, 255, 0 };
		if (!player2WinsTextTexture.LoadFromRenderedText("Player 2 wins", textColor, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
		textColor = { 255, 255, 255 };
		if (!restartTextTexture.LoadFromRenderedText("Restart", textColor, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}

void Game::close()
{

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;
}

void Game::initializeBoard()
{
	for (int row = 0; row < ROWS; row++)
	{
		std::vector<Token> v;
		for (int col = 0; col < COLS; col++)
		{
			v.push_back(Token(XOFFSET + col * Token::TOKEN_WIDTH, YOFFSET + row * Token::TOKEN_HEIGHT, &gTokensSpriteSheetTexture, &gTokenClips[0]));
		}
		board.push_back(v);
	}

	playerColors[0] = TokenType::RED;
	playerColors[1] = TokenType::YELLOW;
	turn = 0;
}

void Game::createRestartButton()
{
	SDL_Rect rect{ Application::APPLICATION_WIDTH / 2 - 200 / 2, Application::APPLICATION_HEIGHT / 2 + 110 / 2, 200, 100 };
	restartButton.SetRect(rect);
}

void Game::handleEvents()
{
	while (SDL_PollEvent(&e) != 0)
	{
		bool isApplicationClosed = (e.type == SDL_QUIT);
		if (isApplicationClosed) quit = true;

		bool isMouseButtonDown = (e.type == SDL_MOUSEBUTTONDOWN);
		if (!endGame && isMouseButtonDown) tryToPlaceAToken();
		else if (endGame && isMouseButtonDown) 
		{
			if (restartButton.IsPressed()) isRestart = true;
		}

	}
}

void Game::tryToPlaceAToken()
{
	int row, col;
	getBoardCoordsFromMouse(row, col);

	if (isValidMove(row, col)) placeToken(row, col);
}

void Game::getBoardCoordsFromMouse(int& row, int& col)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	row = (mouseY / Token::TOKEN_HEIGHT);
	if (row >= ROWS) row = ROWS - 1;
	col = (mouseX / Token::TOKEN_WIDTH);
	if (col >= COLS) col = COLS - 1;
}

bool Game::isValidMove(int row, int col)
{
	//Look if there is no token there
	if (board[row][col].GetTokenType() != TokenType::EMPTY) return false;
	//Look if it is the last row
	if (row == ROWS - 1) return true;
	//Look if there is a token below
	if (board[++row][col].GetTokenType() != TokenType::EMPTY) return true;
	return false;
}

void Game::placeToken(int row, int col)
{
	board[row][col].SetTokenType(playerColors[turn]);
	if (isWin(row, col, playerColors[turn]))
	{
		endGame = true;
		return;
	}

	turn == 0 ? turn = 1 : turn = 0;
}



bool Game::isHorizontalWin(int row, int col, TokenType player)
{
	int currentCol = col + 1;
	int tokensCounter = 1;
	while (currentCol < COLS && board[row][currentCol].GetTokenType() == player)
	{
		++tokensCounter;
		++currentCol;
	}
	currentCol = col - 1;
	while (currentCol >= 0 && board[row][currentCol].GetTokenType() == player)
	{
		++tokensCounter;
		--currentCol;
	}
	if (tokensCounter >= 4) return true;
	return false;
}

bool Game::isVerticalWin(int row, int col, TokenType player)
{
	int tokensCounter = 1;
	int currentRow = row + 1;

	while (currentRow < ROWS && board[currentRow][col].GetTokenType() == player)
	{
		++tokensCounter;
		++currentRow;
	}
	currentRow = row - 1;
	while (currentRow >= 0 && board[currentRow][col].GetTokenType() == player)
	{
		++tokensCounter;
		--currentRow;
	}
	if (tokensCounter >= 4) return true;
	return false;
}

bool Game::isDescendingDiagonalWin(int row, int col, TokenType player)
{
	int tokensCounter = 1;
	int currentRow = row + 1;
	int currentCol = col + 1;

	while (currentRow < ROWS && currentCol < COLS && board[currentRow][currentCol].GetTokenType() == player)
	{
		++tokensCounter;
		++currentRow;
		++currentCol;
	}

	currentRow = row - 1;
	currentCol = col - 1;

	while (currentRow >= 0 && currentCol >= 0 && board[currentRow][currentCol].GetTokenType() == player)
	{
		++tokensCounter;
		--currentRow;
		--currentCol;
	}
	if (tokensCounter >= 4) return true;
	return false;
}

bool Game::isAscendingDiagonalWin(int row, int col, TokenType player)
{
	int tokensCounter = 1;
	int currentRow = row + 1;
	int currentCol = col - 1;

	while (currentRow < ROWS && currentCol >= 0 && board[currentRow][currentCol].GetTokenType() == player)
	{
		++tokensCounter;
		++currentRow;
		--currentCol;
	}

	currentRow = row - 1;
	currentCol = col + 1;

	while (currentRow >= 0 && currentCol < COLS && board[currentRow][currentCol].GetTokenType() == player)
	{
		++tokensCounter;
		--currentRow;
		++currentCol;
	}
	if (tokensCounter >= 4) return true;
	return false;
}

bool Game::isWin(int row, int col, TokenType player)
{
	if (isHorizontalWin(row, col, player)) return true;
	if (isVerticalWin(row, col, player)) return true;
	if (isDescendingDiagonalWin(row, col, player)) return true;
	if (isAscendingDiagonalWin(row, col, player)) return true;

	return false;
}

void Game::render()
{
	//Clear screen
	SDL_SetRenderDrawColor(Application::gRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderClear(Application::gRenderer);

	//Update screen
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			board[i][j].Render();
		}
	}

	if (endGame) renderWinText();

	SDL_RenderPresent(Application::gRenderer);
}

void Game::renderWinText()
{
	SDL_Rect clip;
	clip.x = 0;
	clip.y = 0;
	clip.w = 400;
	clip.h = 100;
	textBackground.Render(Application::APPLICATION_WIDTH / 2 - clip.w / 2, Application::APPLICATION_HEIGHT / 2 - clip.h / 2, &clip);
	if (turn == 0)
		player1WinsTextTexture.Render(Application::APPLICATION_WIDTH / 2 - clip.w / 2, Application::APPLICATION_HEIGHT / 2 - clip.h / 2, &clip);
	else
		player2WinsTextTexture.Render(Application::APPLICATION_WIDTH / 2 - clip.w / 2, Application::APPLICATION_HEIGHT / 2 - clip.h / 2, &clip);

	clip.w = 200;
	textBackground.Render(Application::APPLICATION_WIDTH / 2 - clip.w / 2, Application::APPLICATION_HEIGHT / 2 + clip.h / 2 + 10, &clip);
	restartTextTexture.Render(Application::APPLICATION_WIDTH / 2 - clip.w / 2, Application::APPLICATION_HEIGHT / 2 + clip.h / 2 + 10, &clip);
}

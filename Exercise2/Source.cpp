//Libreria grafica utilizada: SDL 2.0 (coloqué la .dll en la carpeta del ejecutable sino generaba error al ejecutar)

//Configurar en el proyecto las rutas de biblioteca y encabezado para poder compilar con SDL

#include "SDL.h"
#undef main
#include <iostream>

#define KING_W 0
#define QUEEN_W 1
#define BISHOP_W 2
#define TOWER_W 3
#define KNIGHT_W 4
#define PAWN_W 5
#define KING_B 6
#define QUEEN_B 7
#define BISHOP_B 8
#define TOWER_B 9
#define KNIGHT_B 10
#define PAWN_B 11


SDL_Renderer* renderer;
SDL_Window* window;

bool isRunning;
void handleEvents();
void render();
void initWindow();
void clearWindow();
void drawChessBoard(char* initPosition);
void drawBackground(SDL_Surface* backgroundSurface);
void loadImages();
void drawImage(SDL_Surface* src, SDL_Surface* dest, int x, int y);

int WIDTH = 512;
int HEIGHT = 512;

//Chess surface references
SDL_Surface* chessboardSurface = NULL;
SDL_Surface* chessPieces[12];


int main() {

	char boardPosition[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

	initWindow();

	loadImages();

	while (isRunning) {
		handleEvents();
		drawBackground(chessboardSurface);
		drawChessBoard(boardPosition);

		SDL_UpdateWindowSurface(window);
	}

	clearWindow();

	return 0;
}

//SDL initialization
void initWindow() {

	int flags = 0;
	flags = SDL_WINDOW_ALLOW_HIGHDPI;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized!\n";

		window = SDL_CreateWindow("Chess Board", 
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			WIDTH, HEIGHT, flags);
		if (window) {
			std::cout << "Window Created!\n";
			SDL_SetWindowMinimumSize(window, 100, 100);
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 121, 121, 121, 255);
			std::cout << "Renderer created!\n";
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			isRunning = true;
		}

	}

}

//Free window and renderer memory
void clearWindow() {

	for (int i = 0; i < 12;i++) {
		SDL_FreeSurface(chessPieces[i]);
	}
	SDL_FreeSurface(chessboardSurface);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);	 
	SDL_Quit();

}

//handles any events that SDL noticed.
void handleEvents() {
	//the only event we'll check is the  SDL_QUIT event.
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

//Render function called every frame
void render() {
	SDL_SetRenderDrawColor(renderer, 121, 121, 121, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

}

//load all chess images
void loadImages() {

	chessboardSurface = SDL_LoadBMP("chessboard.bmp");
	if (chessboardSurface == NULL) {
		std::cout << "SDL could not load image. Error: " << SDL_GetError() << std::endl;
	}

	chessPieces[KING_W] = SDL_LoadBMP("KING_W.bmp");
	chessPieces[QUEEN_W] = SDL_LoadBMP("QUEEN_W.bmp");
	chessPieces[BISHOP_W] = SDL_LoadBMP("BISHOP_W.bmp");
	chessPieces[TOWER_W] = SDL_LoadBMP("TOWER_W.bmp");
	chessPieces[KNIGHT_W] = SDL_LoadBMP("KNIGHT_W.bmp");
	chessPieces[PAWN_W] = SDL_LoadBMP("PAWN_W.bmp");
	chessPieces[KING_B] = SDL_LoadBMP("KING_B.bmp");
	chessPieces[QUEEN_B] = SDL_LoadBMP("QUEEN_B.bmp");
	chessPieces[BISHOP_B] = SDL_LoadBMP("BISHOP_B.bmp");
	chessPieces[TOWER_B] = SDL_LoadBMP("TOWER_B.bmp");
	chessPieces[KNIGHT_B] = SDL_LoadBMP("KNIGHT_B.bmp");
	chessPieces[PAWN_B] = SDL_LoadBMP("PAWN_B.bmp");

	for (int i = 0; i < 12;i++) {
		if (chessPieces[i] == NULL) {
			std::cout << "SDL could not chess piece image #" << i << std::endl;
		}
	}


}

//Drawing each chess piece based on pixel position and piece character
void drawChessPiece(int x, int y, char piece) {

	//white pieces
	if (isupper(piece)) {

		if (piece == 'P') {
			drawImage(
				chessPieces[PAWN_W],
				chessboardSurface,
				x,
				y);
		}
		else if (piece == 'R') {
			drawImage(
				chessPieces[TOWER_W],
				chessboardSurface,
				x,
				y);
		}
		else if (piece == 'B') {
			drawImage(
				chessPieces[BISHOP_W],
				chessboardSurface,
				x,
				y);
		}
		else if (piece == 'N') {
			drawImage(
				chessPieces[KNIGHT_W],
				chessboardSurface,
				x,
				y);
		}
		else if (piece == 'Q') {
			drawImage(
				chessPieces[QUEEN_W],
				chessboardSurface,
				x,
				y);
		}
		else if (piece == 'K') {
			drawImage(
				chessPieces[KING_W],
				chessboardSurface,
				x,
				y);
		}


	}
	//black pieces
	else {

		if (piece == 'p') {
			drawImage(
				chessPieces[PAWN_B],
				chessboardSurface,
				x,
				y);
		}
		else if (piece == 'r') {
			drawImage(
				chessPieces[TOWER_B],
				chessboardSurface,
				x,
				y);
		}
		else if (piece == 'b') {
			drawImage(
				chessPieces[BISHOP_B],
				chessboardSurface,
				x,
				y);
		}
		else if (piece == 'n') {
			drawImage(
				chessPieces[KNIGHT_B],
				chessboardSurface,
				x,
				y);
		}
		else if (piece == 'q') {
			drawImage(
				chessPieces[QUEEN_B],
				chessboardSurface,
				x,
				y);
		}
		else if (piece == 'k') {
			drawImage(
				chessPieces[KING_B],
				chessboardSurface,
				x,
				y);
		}

	}

}


//Drawing chessboard based on character sequence
void drawChessBoard(char* initPosition) {
	
	int x = 0;
	int y = 0;

	for (int i = 0; i <= (int)strlen(initPosition);i++) {

		char c = initPosition[i];

		//std::cout << c << std::endl;
		
		if (c >= '1' && c <= '8') 
		{
			x += c - '0';
		}else if (c == '/') 
		{
			x = 0;
			y++;
		}
		else
		{

			drawChessPiece(x*WIDTH/8, y*WIDTH/8, c);
			x++;
			
		}

	}


	return;

}


//Drawing one image using surface references and position
void drawImage(SDL_Surface* src, SDL_Surface* dest, int x, int y) {

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;

	SDL_BlitSurface(src, NULL, dest, &rect);

}

//Drawing chessboard background
void drawBackground(SDL_Surface* chessBackground) {

	SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
	drawImage(chessBackground, windowSurface, 0, 0);

}
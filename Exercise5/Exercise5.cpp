// Exercise5.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
// Consideracion: en caso se quiera forzar el calculo de laberintos con soluciones mas largas,
// se puede modificar la macro MINIMUM_SIZE_PATH

#include <iostream>
#include <cstdlib>
#include <ctime>       /* time */
#include <utility>
#include <vector>

#define START_POINT_X 1
#define START_POINT_Y 1

#define MOVE_RIGHT 0
#define MOVE_UP 1
#define MOVE_LEFT 2
#define MOVE_DOWN 3

#define MINIMUM_MAZE_PATH 3 //Distancia minima para poder considerar una solucion como valida. Con valores mas grandes, la ejecucion tomara mas tiempo

//Print the maze found
void printMaze(char** maze,int n) {

	for (int i = 0; i < n; i++) {

		for (int j = 0; j < n; j++) {

			printf("%c ", maze[i][j]);

		}
		printf("\n");

	}

}

//Get the random value of a maze cell (either 'X' or ' ')
char GetRandomCell() {

	int a = rand() % 2;
	return a == 0 ? ' ' : 'X';
}

//Set a maze with random values. Border walls are always set.
void randomizeMaze(int n, char** maze) {

	for (int i = 0; i < n; i++) {

		for (int j = 0; j < n; j++) {

			if (i == 0) {
				maze[i][j] = 'X'; //top wall
			}else if (i == n - 1) {
				maze[i][j] = 'X'; //bottom wall
			}else if (j == 0) {
				maze[i][j] = 'X'; //left wall
			}
			else if (j == n-1) {
				maze[i][j] = 'X'; //right wall
			}
			else {
				maze[i][j] = GetRandomCell();
			}

		}

	}

}

//Return new point (X,Y) based on the move chosen
void GetNewPosition(int movement, int& newPosX, int& newPosY) {

	switch (movement) {

	case MOVE_LEFT:
		newPosX = newPosX - 1;
		break;
	case MOVE_RIGHT:
		newPosX = newPosX + 1;
		break;
	case MOVE_UP:
		newPosY = newPosY - 1;
		break;
	case MOVE_DOWN:
		newPosY = newPosY + 1;
		break;

	default:
		break;
	}

}


//Check if a new position is valid based on maze limits and empty cells
bool IsValidPosition(int n, char** maze, int newPosX, int newPosY) {

	if (newPosX < 0) {
		return false;
	}

	if (newPosY < 0) {
		return false;

	}

	if (newPosX >= n) {
		return false;
	}

	if (newPosY >= n) {
		return false;
	}

	if (maze[newPosY][newPosX] == ' ') {
		return true;
	}
	else
		return false;
}


//Recursively look for new paths based on the maze movements and if a dead end is found, maxDistance is compared
void MazeMovement(int& maxDistance, int& maxX, int& maxY, int distance, int posX, int posY, int n, char** maze, std::vector<std::pair<int, int>>& deadEnds) {


	for (int move = MOVE_RIGHT ;move <= MOVE_DOWN;move++) {

		int newPosX = posX;
		int newPosY = posY;
		GetNewPosition(move, newPosX, newPosY);

		if (IsValidPosition(n,maze,newPosX, newPosY)) {

			distance++;
			maze[newPosY][newPosX] = '-';
			MazeMovement(maxDistance, maxX, maxY, distance, newPosX, newPosY, n, maze, deadEnds);
			distance--;
		}

	}

	//Dead end: No more moves available (backtrack and evaluate maximum)
	maze[posY][posX] = ' ';

	if (maxDistance < distance) {
		maxDistance = distance;
		maxX = posX;
		maxY = posY;
	}

	deadEnds.push_back(std::make_pair(posX, posY));

}

//Use the dead ends array to check if there are multiple ways toward the solution found (posX, posY)
bool CheckMultiplePathsToSolution(int posX, int posY, std::vector<std::pair<int, int>> deadEnds) {
	
	int numTimes = 0;
	for (std::pair<int,int> pair : deadEnds) {

		if (pair.first == posX && pair.second == posY) {
			numTimes++;
		}

//		printf("Solution found: (%d,%d)\n", pair.first,pair.second);


	}

//	printf("NumTimes solution found: %d\n", numTimes);

	if (numTimes == 1) {
		return false;
	}
	else {
		return true;
	}


}

//Check for the largest path in the MAZE received, if the proper requirements are met (read createMaze2D comment)
//If found, maxDistance, maxPosX and maxPosY values are returned
bool LargestMazePathFound(int n, char** maze, int& maxDistance, int& maxPosX, int& maxPosY) {

	bool repeteadedSolutions = false;
	std::vector<std::pair<int, int>> deadEnds;
	maze[START_POINT_Y][START_POINT_X] = '-'; //Default start position

	MazeMovement(maxDistance, maxPosX, maxPosY, 0, START_POINT_X, START_POINT_Y, n, maze, deadEnds);

	if (maxDistance >= MINIMUM_MAZE_PATH && !CheckMultiplePathsToSolution(maxPosX, maxPosY, deadEnds)){
		return true;
	}
	else {
		return false;
	}


}

//Continuous creation of randomized mazes until the following requirements are met:
// - There are no multiple ways towards the solution
// - Minimum distance should be MINIMUM_MAZE_PATH (to discard solutions that are too short)
void createMaze2D(int n) {

	bool keepRandomizing = true;
	char** maze = new char*[n];
	for (int i = 0; i < n; ++i)
		maze[i] = new char[n];

	int maxDistance, maxPosX, maxPosY;

	while (keepRandomizing) {

		randomizeMaze(n, maze);

		maxDistance = 0;
		maxPosX = START_POINT_X;
		maxPosY = START_POINT_Y;

		if (LargestMazePathFound(n, maze,maxDistance,maxPosX,maxPosY)) {
			keepRandomizing = false;
		}

	}

	//Set 'A' and 'B' characters in the maze
	maze[START_POINT_Y][START_POINT_X] = 'A'; //Default start position
	maze[maxPosY][maxPosX] = 'B'; //Using the solution point found

	printMaze(maze, n);
	//printf("\n Distancia max: %d. Punto final (%d, %d)", maxDistance, maxPosX, maxPosY);

	for (int i = 0; i < n; ++i)
		delete[] maze[i];
	delete[] maze;
}

int main()
{
   
	int n = 11;
	srand((unsigned int)time(NULL));
	createMaze2D(n);


}



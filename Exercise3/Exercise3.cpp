// Soluciones posibles de MICHI

// Exercise3.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <iomanip>
#include <fstream>

void listAllTicTacToeGames(char* filename);
void printSolution(int n, char* solution, char winner, std::ofstream& file);
bool isSolutionValid(char* solution, char& winner);

int main()
{
	char filename[] = "resultado.txt";

	listAllTicTacToeGames(filename);

}

//New position is only valid if it's not already in the solutionArray
bool isNewPositionValid(int newPosition, char* solution) {

	for (int i = 0; i < 9; i++) {
		if (solution[i] == newPosition + '0') {
			//printf("character %c already exists in solutionArray at index %d (%c)\n", newPosition + '0', i, solution[i]);
			return false;
		}
	}
	return true;

}


//Calculate all solutions in an index of the solution array. Each index represents a different player movement (X 0 X 0 X 0 ..)
void searchSolution(int index, char* solution, int& numSolutions, std::ofstream& file) {

	//If we're at the last index, we stop
	if (index == 9) {
		return;
	}

	//Iterate through all possible movements for current index (1 to 9)
	for (int i = 1; i <= 9; i++) {

		char winner;

		if (isNewPositionValid(i, solution)) {

			solution[index] = i + '0';

			if (isSolutionValid(solution, winner)) {

				(numSolutions)++;
				printSolution(numSolutions, solution, winner, file);

				//return;

			}
			else {

				searchSolution(index + 1, solution, numSolutions, file);

			}

			solution[index] = '0'; //rollback solution
		}

	}


}


//Start searching for solutions from the first movement (index 0)
void listAllTicTacToeGames(char* filename)
{

	std::ofstream myfile;
	char solution[10] = { '0','0','0','0','0','0','0','0','0' }; //Array used to find solutions
	int numSolutions = 0; //Number of solutions found

	myfile.open(filename);
	myfile << "  N    X 0 X 0 X 0 X 0 X Win" << std::endl;
	
	searchSolution(0, solution, numSolutions, myfile);  //Start at 0

	myfile.close();

}

//Get numbered position (in ASCII) from board coordinates (ex: (0,0) = 1 , (0,1) = 2 , etc..)
char GetPositionNumber(int x, int y) {
	return x * 3 + y + 1 + '0';
}

//Analyze solution array and indicate if solution is valid or not. If it's valid, winner character is set (X/0/E)
bool isSolutionValid(char* solution, char& winner) {

	char board[3][3];

	//A board is built and filled with current solution
	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			board[i][j] = ' ';

			for (int p = 0;p < 9;p++) {
				//if current board position is inside solution array
				if (solution[p] != '0' &&  GetPositionNumber(i, j) == solution[p]) {
					char player = (p % 2 == 0) ? 'X' : '0';
					board[i][j] = player;
				}

			}

		}

	}


	//Checking solution
	bool isBoardFull = true;

	for (int i = 0; i < 3; i++) {

		//Row win
		if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
			winner = board[i][0];
			//printf("Row %d win\n", i + 1);
			return true;
		}

		//Column win
		if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
			winner = board[0][i];
			//printf("Column %d win\n",i+1);
			return true;
		}

		//Check if board is full of character moves
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') {
				isBoardFull = false;
				break;
			}
		}

	}

	//Diagonal 1 win
	if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
		winner = board[0][0];
		//printf("diagonal 1\n");
		return true;
	}

	//Diagonal 2 win
	if (board[2][0] != ' ' && board[2][0] == board[1][1] && board[1][1] == board[0][2]) {
		winner = board[2][0];
		//printf("diagonal 2\n");
		return true;
	}

	//Check if there is a draw
	if (isBoardFull) {
		winner = 'E';
		//printf("draw\n");
		return true;
	}

	//All other cases: game is not finished yet / solution invalid
	return false;

}


//Print solution format
void printSolution(int n, char* solution, char winner, std::ofstream& file) {
	file << std::setfill('0') << std::setw(6) << n << " ";
	for (int i = 0; i < 9;i++) {
		file << solution[i] << " ";
	}

	file << winner << std::endl;
}

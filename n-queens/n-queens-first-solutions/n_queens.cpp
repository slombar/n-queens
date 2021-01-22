// n_queens.cpp : Defines the entry point for the application.
//

#include "n_queens.h"

using namespace std;

#define N 8
int solutions = 0;

int findLastQueen(int board[], int n) {
	//set i to the last index in board
	int lastIndex = n - 1;

	while (board[lastIndex] == 0 && lastIndex > 0) {
		lastIndex--;
	}
	//return the last queens index
	return lastIndex;
}

bool isLegalPosition(int board[],int index, int n) {

	for (int row = 0; row < index; row++) {
			//if the column we are in has another queen in it
			if (board[index] == board[row]) {
				return false;
			}
			
			//the diagonal of the queen has another queen in it
			else if (abs(row - index) == abs(board[row]-board[index])) {
				return false;
		}
	}
	return true;
}

/*@param index, the index of the last queen on the board
*/
int* successor(int board[], int index, int n) {

	if (!isLegalPosition(board, index, n)) {
		//if we are at the last column
		if (board[index] == n) {
			//remove queen
			board[index] = 0;
			//if the next index is also in last position
			if (board[index - 1] == n) {
				board[index - 1] = 0;
				board[index - 2] += 1;
			}
			else {
				board[index - 1] += 1;
			}
		}
		//if not legal and not in last row
		else {
			board[index] += 1;
		}
	}
	else {

		//if we have reached the last row and we're valid 
		if (index == n - 1) {
			//we have a solution! now we backtrack
			//if we are in the last column
			if (board[index] == n) {
				//remove queen
				board[index] = 0;
				//if the next index is also in last column
				if (board[index - 1] == n) {
					board[index - 1] = 0;
					board[index - 2] += 1;
				}
				else {
					board[index - 1] += 1;
				}
			}
			//if not legal and not in last row
			else {
				board[index] += 1;
			}
		}
		else {
			// add new queen to board
			board[index + 1] += 1;
		}
		
	}

	return board;
}

void printSolution(int board[], int n) {
	cout << "Solution for " << n << "queens: " << endl;
	cout << "{";
	for (int i = 0; i < n; i++) {
		cout << board[i] << ",";
	}
	cout << "}" << endl;
}

int* nextLegalPosition(int board[], int n) {

	//the index of the last queen
	int index = findLastQueen(board, n);
	int* successorBoard = board;
	successorBoard = successor(board, index, n);
	
	if (isLegalPosition(successorBoard, index, n)) {
		return successorBoard;
	}
	else {
		nextLegalPosition(successorBoard, n);
	}

	return board;
}


void firstSolutions() {
	
	int board[100] = { 0 };
	int* solutionBoard;
	board[0] = 1;
	solutionBoard = board;

	for (int n = 4; n < 41;) {

		solutionBoard = nextLegalPosition(solutionBoard, n);

		//if we reach the last queen
		if (isLegalPosition(solutionBoard, n - 1, n) && findLastQueen(solutionBoard, n) == n - 1) {
			cout << "The first solution for n = " << n << " is ";
			printSolution(solutionBoard, n);
			n++;
			int i = 0;
			//reset all the numbers that are non-zero
			while (solutionBoard[i] != 0) {
				solutionBoard[i] = 0;
				i++;
			}
			solutionBoard[0] = 1;
		}
	}
}

int main(){
	cout << "Generating all solutions for " << N <<"x"<< N <<" board:"<< endl;

	firstSolutions();
	return 0;
}

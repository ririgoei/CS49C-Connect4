#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <conio.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define BOARD_ROWS 8
#define BOARD_COLS 8

void printBoard(char *board);
int takeTurn(char *board, int player, const char*);
int checkWin(char *board);
int checkFour(char *board, int, int, int, int);
int horizontalCheck(char *board);
int verticalCheck(char *board);
int diagonalCheck(char *board);

int main(int argc, char *argv[]) {
	
	const char *PIECES = "XO";
	char board[BOARD_ROWS *BOARD_COLS];
	memset(board, ' ', BOARD_ROWS * BOARD_COLS);

	int turn, done = 0;

	for (turn = 0; turn < BOARD_ROWS * BOARD_COLS && !done; turn++) {
		printBoard(board);
		while (!takeTurn(board, turn % 2, PIECES)) {
			printBoard(board);
			puts("**Column full!**\n");
		}
		done = checkWin(board);
	}
	printBoard(board);

	if (turn == BOARD_ROWS * BOARD_COLS && !done) {
		puts("It's a tie!");
	}
	else {
		turn--;
		printf("Player %d (%c) wins!\n", turn % 2 + 1, PIECES[turn % 2]);
	}

	return 0;

}
void printBoard(char *board) {
	int row, col;
	

	puts("\n    ****Connect Four****\n");
	puts("  1   2   3   4   5   6   7   8\n");
	for (row = 0; row < BOARD_ROWS; row++) {
		for (col = 0; col < BOARD_COLS; col++) {
			if ('X' == board[BOARD_COLS * row + col])
			{
				
				printf(ANSI_COLOR_RED "| %c " , board[BOARD_COLS * row + col]);
			}
			else
			{
				printf("| %c ", board[BOARD_COLS * row + col]);
			}
			
		}
		puts("|");
		puts("--------------------------------");

	}
	

}
int takeTurn(char *board, int player, const char *PIECES) {
	int row, col = 0;
	printf("Player %d (%c):\nEnter number coordinate: ", player + 1, PIECES[player]);

	while (1) {
		if (1 != scanf_s("%d", &col) || col < 1 || col > 8) {
			while (getchar() != '\n');
			puts("Number out of bounds! Try again.");
		}
		else {
			break;
		}
	}
	col--;

	for (row = BOARD_ROWS - 1; row >= 0; row--) {
		if (board[BOARD_COLS * row + col] == ' ') {
			board[BOARD_COLS * row + col] = PIECES[player];
			return 1;
		}
	}
	return 0;

}
int checkWin(char *board) {
	return (horizontalCheck(board) || verticalCheck(board) || diagonalCheck(board));

}
int checkFour(char *board, int a, int b, int c, int d) {
	return (board[a] == board[b] && board[b] == board[c] && board[c] == board[d] && board[a] != ' ');

}
int horizontalCheck(char *board) {
	int row, col, idx;
	const int WIDTH = 1;

	for (row = 0; row < BOARD_ROWS; row++) {
		for (col = 0; col < BOARD_COLS - 3; col++) {
			idx = BOARD_COLS * row + col;
			if (checkFour(board, idx, idx + WIDTH, idx + WIDTH * 2, idx + WIDTH * 3)) {
				return 1;
			}
		}
	}
	return 0;

}
int verticalCheck(char *board) {
	int row, col, idx;
	const int HEIGHT = 8;

	for (row = 0; row < BOARD_ROWS - 3; row++) {
		for (col = 0; col < BOARD_COLS; col++) {
			idx = BOARD_COLS * row + col;
			if (checkFour(board, idx, idx + HEIGHT, idx + HEIGHT * 2, idx + HEIGHT * 3)) {
				return 1;
			}
		}
	}
	return 0;

}
int diagonalCheck(char *board) {
	int row, col, idx, count = 0;
	const int DIAG_RGT = 8, DIAG_LFT = 8;

	for (row = 0; row < BOARD_ROWS - 3; row++) {
		for (col = 0; col < BOARD_COLS; col++) {
			idx = BOARD_COLS * row + col;
			if (count <= 3 && checkFour(board, idx, idx + DIAG_LFT, idx + DIAG_LFT * 2, idx + DIAG_LFT * 3) || count >= 3 && checkFour(board, idx, idx + DIAG_RGT, idx + DIAG_RGT * 2, idx + DIAG_RGT * 3)) {
				return 1;
			}
			count++;
		}
		count = 0;
	}
	return 0;

}
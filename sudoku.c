#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Prints sudoku to terminal */
void print_sudoku(int sudoku[9][9]) {
	printf("The Sudoku contains:\n\n");
	for (int x = 0; x < 9; x++){
		for (int y = 0; y < 9; y++)
			printf("%d  ", sudoku[x][y]);
		printf("\n");
	}
}

/* Returns the beginning index for a 3x3 square */
int getSquareIndex(int n) {
    if (n <= 2)
        return 0;
    else if (n <= 5)
        return 3;
    return 6;
}

/* Returns 1 if value n at position x, y, in sudoku array is invalid. */
int check_position(int x, int y, int n, int sudoku[9][9]){

	/* Check if values in column and row */
	for (int i = 0; i < 9; i++) {
		if (sudoku[x][i] == n || sudoku[i][y] == n)
			return 1;
	}

	/* Now check local square */
	int xp, yp;
	xp = getSquareIndex(x);
	yp = getSquareIndex(y);

	for (int j = xp; j < xp + 3; j++){
		for (int k = yp; k < yp + 3; k++){
			if (sudoku[j][k] == n)
				return 1;
		}
	}

	return 0;
}


/* Main recursive algorithim. */
int recursive_solve(int sudoku[9][9], int x, int y){

	/* If this square is empty */
	if (sudoku[x][y] == 0){
		for (int num = 1; num <= 9; num++){
			if (check_position(x, y, num, sudoku) == 0){
				sudoku[x][y] = num;
				if (x == 8 && y == 8)
					return 1;

				if (x < 8 && recursive_solve(sudoku, x + 1, y))
					return 1;

				else if (x == 8 && recursive_solve(sudoku, 0, y + 1))
					return 1;
			}
		}
		sudoku[x][y] = 0;
		return 0;
	}

	/* If this square is already a number, skip it. */
	if (sudoku[x][y] != 0){
		if (x == 8 && y == 8)
			return 1;

		if (x < 8)
			return recursive_solve(sudoku, x + 1, y);

		return recursive_solve(sudoku, 0, y + 1);
	}
}

/* Checks if input is a valid sudoku, then solves  */
void solve_sudoku(int sudoku[9][9], int depth) {
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (sudoku[i][j] != 0 && check_position(i, j, sudoku[i][j], sudoku) == 0)
				return;
		}
	}
	recursive_solve(sudoku, 0, 0);
}

int main(){

	/* Example Sudoku input. Edit this nested array to solve a sudoku. */
	/* Zeroes are empty spaces. */

	int sudoku[9][9] = {
		{ 0,0,0,0,0,0,2,0,0 },
		{ 0,8,0,0,0,7,0,9,0 },
		{ 6,0,2,0,0,0,5,0,0 },
		{ 0,7,0,0,6,0,0,0,0 },
		{ 0,0,0,9,0,1,0,0,0 },
		{ 0,0,0,0,2,0,0,4,0 },
		{ 0,0,5,0,0,0,6,0,3 },
		{ 0,9,0,4,0,0,0,7,0 },
		{ 0,0,6,0,0,0,0,0,0 }
	};

	printf("\nOriginal sudoku is:\n\n");
	print_sudoku(sudoku);
 	solve_sudoku(sudoku, 0);
	printf("\n\nSolved sudoku is:\n\n");
	print_sudoku(sudoku);
	printf("\n");
}

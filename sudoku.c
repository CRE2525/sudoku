#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void print_sudoku(int sudoku[9][9]){
	printf("The Sudoku contains:\n");
	for (int x = 0; x < 9; x++){
  			for (int y = 0; y < 9; y++){
				printf("%d  ", sudoku[x][y]);
    			}
    			printf("\n");
  		}
}


int check_position(int x, int y, int num, int sudoku[9][9]){
	
	int i, j, k;
	
	for(i = 0; i < 9; i++){
		if(sudoku[x][i] == num){
			return 1;
		}
		if(sudoku[i][y] == num){
			return 1;
		}
	}

	if(x <= 2){
		x = 0;
	} else if(x <= 5){
		x = 3;
	} else {
		x = 6;
	}

	if(y <= 2){
		y = 0;
	} else if(y <= 5){
		y = 3;
	} else {
		y = 6;
	}

	for(j = x; j < x + 3; j++){
		for(k = y; k < y + 3; k++){
			if(sudoku[j][k] == num){
				return 1;
			}
		}
	}
	return 0;
}


int epic_solver(int sudoku[9][9], int x, int y){

	int num = 1;
	if(sudoku[x][y] == 0){
		for(num = 1; num <= 9; num++){
			if(check_position(x, y, num, sudoku) == 0){

				sudoku[x][y] = num;

				if(x == 8 && y == 8){
					return 1;
				}

				if(x < 8){
					if(epic_solver(sudoku, x + 1, y) == 1){
						return 1;
					}

				} else if(x == 8){
					if(epic_solver(sudoku, 0, y + 1) == 1){
						return 1;
					}
				}
			}
		}
		sudoku[x][y] = 0;
		return 0;
	}

	if(sudoku[x][y] != 0){

		if((x == 8) && (y == 8)){
			return 1;
		}

		if(x < 8){
			if(epic_solver(sudoku, x + 1, y) == 1){
				return 1;
		} else {
				return 0;
			}
		} else if(x == 8){
			if(epic_solver(sudoku, 0, y + 1) == 1){
				return 1;
		} else {
				return 0;
			}
		}
	}
	return 0;
}


void solve_sudoku(int sudoku[9][9], int depth)
{
	int i = 0;
	int j = 0;
	int q = 0;

	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			if((sudoku[i][j] != 0) && (check_position(i, j, sudoku[i][j], sudoku) == 0)){
				q = 1;
			}
		}
	}

	if(q == 0){
		epic_solver(sudoku, 0, 0);
	}
}

int main(){

	int Sudoku[9][9]={
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

	printf("Input puzzle is:\n");
  	print_sudoku(Sudoku);
 	solve_sudoku(Sudoku, 0);
  	printf("Solution is:\n");
  	print_sudoku(Sudoku);
}

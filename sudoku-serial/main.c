#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"
#include <string.h>
#include <time.h>


//returns a 2D array from a file containing the Sudoku in space separated format (empty cells are 0)
int ** readInput(char *filename){
	FILE *infile;
	infile = fopen(filename, "r");
	int i, j;
	char dummyline[SIZE+1];
	char dummy;
	int value;
	int **sudokuGrid = (int**)malloc(sizeof(int*)*SIZE);
	for (i=0;i<SIZE;i++){
		sudokuGrid[i] = (int*)malloc(sizeof(int)*SIZE);
		for (j=0;j<SIZE;j++)
			sudokuGrid[i][j] = 0;
	}

	for (i = 0; i < SIZE; i++){
		for (j = 0; j < SIZE; j++){
			/* Checking if number of rows is less than SIZE */
			if (feof(infile)){
				if (i != SIZE){
					printf("The input puzzle has less number of rows than %d. Exiting.\n", SIZE);
					exit(-1);
				}
        		}

        		fscanf(infile, "%d", &value);
        		if(value >= 0 && value <= SIZE)
				sudokuGrid[i][j] = value;
			else{
				printf("The input puzzle is not a grid of numbers (0 <= n <= %d) of size %dx%d. Exiting.\n", SIZE, SIZE, SIZE);
				exit(-1);
			}
		}
		fscanf(infile, "%c", &dummy); /* To remove stray \0 at the end of each line */

		/* Checking if row has more elements than SIZE */
		if (j > SIZE){
			printf("Row %d has more number of elements than %d. Exiting.\n", i+1, SIZE);
			exit(-1);
		}
	}
	return sudokuGrid;
}


/*checks if solution is a valid solution to original 
i.e. all originally filled cells match, and that solution is a valid grid*/
int isValid(int **original, int **solution){
	int valuesSeen[SIZE],i,j,k;

	//check all rows
	for (i=0;i<SIZE;i++){
		for (k=0;k<SIZE;k++) valuesSeen[k] = 0;
		for (j=0;j<SIZE;j++){
			if (solution[i][j]==0) return 0;
			if ((original[i][j])&&(solution[i][j] != original[i][j])) return 0;
			int v = solution[i][j];
			if (valuesSeen[v-1]==1){
				return 0;
			}
			valuesSeen[v-1] = 1;
		}
	}

	//check all columns
	for (i=0;i<SIZE;i++){
		for (k=0;k<SIZE;k++) valuesSeen[k] = 0;
		for (j=0;j<SIZE;j++){
			int v = solution[j][i];
			if (valuesSeen[v-1]==1){
				return 0;
			}
			valuesSeen[v-1] = 1;
		}
	}

	//check all minigrids
	//check all rows
	for (i=0;i<SIZE;i=i+MINIGRIDSIZE){
		for (j=0;j<SIZE;j=j+MINIGRIDSIZE){
			for (k=0;k<SIZE;k++) valuesSeen[k] = 0;
			int r,c;
			for (r=i;r<i+MINIGRIDSIZE;r++)
				for (c=j;c<j+MINIGRIDSIZE;c++){
					int v = solution[r][c];
					if (valuesSeen[v-1]==1) {
						return 0;
					}
					valuesSeen[v-1] = 1;
				}
		}
	}
	return 1;
}

int main(int argc, char *argv[]){
	int **originalGrid = readInput(argv[1]);
	int **gridToSolve = readInput(argv[1]);
	int i,j;
	printf("************************INPUT GRID***********************\n");
	for (i=0;i<SIZE;i++){
		for (j=0;j<SIZE;j++){
			printf("%d ",originalGrid[i][j]);
		}
		printf("\n");
	}
	double time_spent = 0.0;
    	clock_t end,begin= clock();
	int **outputGrid = solveSudoku(originalGrid);
	end = clock();
	printf("\n************************OUTPUT GRID***********************\n");
	for (i=0;i<SIZE;i++){
		for (j=0;j<SIZE;j++)
			printf("%d ",outputGrid[i][j]);
		printf("\n");
	}
	if (isValid(originalGrid,outputGrid)){
		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
		printf("\nSOLUTION FOUND\nTIME = %lf\n",time_spent);
	}
	else{
		printf("\nNO SOLUTION FOUND\nTIME =%lf\n",time_spent);
	}
}

// Project 1: Minesweepers part B
// Netta Adani. ID: 
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>       
#include <stdbool.h>    
#include <math.h>
#define ROWS 22
#define COLS 22

void initPlayerBoard(char board[][COLS], int logRowSize, int logColSize);
void initBoard0(char board_0[][COLS], int logRowSize, int logColSize, int bombNum);
void rendom_bomb(char board_0[][COLS], int bombNum);
void printBoard(char board[][COLS], int rowNum, int colNum);
void updateBoard(char srcBoard[][COLS], char destBoard[][COLS], int i, int j);
void open_j_amuont_of_sells(int j, char board_0[][COLS], char players_board[][COLS], int logRowSize, int logColSize);
bool win(char board_0[][COLS], char players_board[][COLS], int row, int col, int bombNum);
void floodfill(char board_0[][COLS], char players_board[][COLS], int logRowSize, int logColSize, int i, int j);
void gameMeneger(int logRowSize, int logColSize);

//**********************************************************************************************************************

void main()
{
	int n;
	printf("\n  Welcome to Minesweepers!\n\n");
	printf("  Please choose one of the following options and enter it's number: \n\n  1 - for size 8X8 \n\n  2 - for size 12X12 \n\n  3 - for size  15X15 \n\n  4 - for custom size \n\n  0 - Exit\n\n");
	scanf("%d", &n);
	printf("\n");

	// <><><><><><><><><><><><><><><><><>< check if input is valid ><><><><><><><><><><><><><><><><><><><><><><> //
	if (n < 0 || n>4)
	{
		printf("Invalid choise!\n\n");

		printf("\n  Welcome to Minesweepers!\n\n");
		printf("  Please choose one of the following options and enter it's number: \n\n  1 - for size 8X8 \n\n  2 - for size 12X12 \n\n  3 - for size  15X15 \n\n  4 - for custom size \n\n  0 - Exit\n\n");
		scanf("%d", &n);
		printf("\n");
	}

	// <><><><><><><><><><><><><><><><><><><><><><><><   Exit   ><><><><><><><><><><><><><><><><><><><><><><><><> //
	else if (n == 0)
		printf("good bye!\n");

	// <><><><><><><><><><><><><><><><><><><><><><><><   8X8   ><><><><><><><><><><><><><><><><><><><><><><><><> //
	else if (n == 1)
	{
		int logRowSize = 8;
		int logColSize = 8;
		gameMeneger(logRowSize, logColSize);
	}

	// <><><><><><><><><><><><><><><><><><><><><><><><   12X12   ><><><><><><><><><><><><><><><><><><><><><><><> //
	else if (n == 2)
	{
		int logRowSize = 12;
		int logColSize = 12;
		gameMeneger(logRowSize, logColSize);
	}

	// <><><><><><><><><><><><><><><><><><><><><><><><   15X15   ><><><><><><><><><><><><><><><><><><><><><><><> //
	else if (n == 3)
	{
		int logRowSize = 15;
		int logColSize = 15;
		gameMeneger(logRowSize, logColSize);
	}

	// <><><><><><><><><><><><><><><><><><><><><><   free choice of board size   ><><><><><><><><><><><><><><><><><><><><><> //
	else if (n == 4)
	{
		int logRowSize, logColSize;

		printf("Plaese enter the size of the board (Line<=22 and Cols <= 22): ");
		scanf("%d%d", &logRowSize, &logColSize);
		printf("\n");

		if (logRowSize < 1 || logColSize < 1 || logRowSize >= 23 || logColSize >= 23)
		{
			printf("Please enter a valid choice! \n");
			printf("Plaese enter the size of the board(Line <= 22 and Cols <= 22) : ");
			scanf("%d%d", &logRowSize, &logColSize);
			printf("\n");
		}

		gameMeneger(logRowSize, logColSize);
	}
}


void initPlayerBoard(char board[][COLS], int logRowSize, int logColSize)
{
	for (int i = 0; i < logRowSize; i++)
		for (int j = 0; j < logColSize; j++)
			board[i][j] = 'x';
}
void initBoard0(char board_0[][COLS], int logRowSize, int logColSize, int bombNum)
{

	rendom_bomb(board_0, bombNum);  // Random placement of bombs on the board has been sat
	char counter;
	for (int i = 0; i < logRowSize; i++)
	{
		for (int j = 0; j < logColSize; j++)
		{
			counter = '0';
			if (board_0[i][j] == ('*')) // this is a bomb
			{
				continue;
			}
			else // The tests are within the limits of the board
			{

				if ((i - 1 >= 0) && (j - 1 >= 0) && (board_0[i - 1][j - 1] == ('*'))) // up & left
					counter++;

				if ((i - 1 >= 0) && (board_0[i - 1][j] == ('*'))) // up
					counter++;

				if ((i - 1 >= 0) && (j + 1 < logColSize) && (board_0[i - 1][j + 1] == ('*'))) // up & right
					counter++;

				if ((j - 1 >= 0) && (board_0[i][j - 1] == ('*'))) // left
					counter++;

				if ((j + 1 < logColSize) && (board_0[i][j + 1] == ('*'))) // right
					counter++;

				if ((i + 1 < logRowSize) && (j - 1 >= 0) && (board_0[i + 1][j - 1] == ('*'))) // down & left
					counter++;

				if ((i + 1 < logRowSize) && (board_0[i + 1][j] == ('*')))// down
					counter++;

				if ((i + 1 < logRowSize) && (j + 1 < logColSize) && (board_0[i + 1][j + 1] == ('*'))) // down & right
					counter++;
			}
			if (counter == '0') // there is no bomb in the area of this sell - put space in this sell
				board_0[i][j] = ' ';
			else                // Placing a number according to the number of bombs in the sell area
				board_0[i][j] = counter;
		}
	}
}
void rendom_bomb(char board_0[][COLS], int bombNum)
{
	// this fanction does random placement of bombs on the board
	int i, row, col;

	srand(time(NULL));

	for (i = 0; i < bombNum; )
	{
		row = rand() % bombNum; // random row
		col = rand() % bombNum; // random colum

		if (board_0[row][col] != '*')
		{
			board_0[row][col] = '*'; // * bomb *
			i++;
		}
	}
}

void printBoard(char board[][COLS], int rowNum, int colNum)
{
	char value;
	int row, col, i;
	// print mine line 0-(size-1) cols
	printf("     ");
	for (int i = 0; i < colNum; i++)
		printf("%4d", i);
	printf("\n");

	//print a line
	printf("   ");
	for (i = 0; i < (colNum * 4.5); i++)
		printf("%c", '_');
	printf("\n");

	// print x's table
	for (row = 0; row < rowNum; row++)
	{
		printf("   ");
		printf("%2d%2c", row, '|');
		for (col = 0; col < colNum; col++)
		{
			value = board[row][col];
			printf("%2c%2c", value, '|');
		}
		printf("\n");
	}

	//print a line
	printf("   ");
	for (int i = 0; i < (colNum * 4.5); i++)
		printf("%c", '_');

	printf("\n");
}
void updateBoard(char srcBoard[][COLS], char destBoard[][COLS], int i, int j)
{
	destBoard[i][j] = srcBoard[i][j];
}
void open_j_amuont_of_sells(int j, char board_0[][COLS], char players_board[][COLS], int logRowSize, int logColSize)
{
	int counter = 0;

	for (int row = 0; row < logRowSize; row++)
	{
		for (int col = 0; col < logColSize; col++)
		{
			if (board_0[row][col] != '*') // skip bombs
			{
				if (players_board[row][col] == 'x')
				{
					if (counter == j) // j amuout of sells was opened
						break;

					//else - coninue until j amuout of sells will open
					updateBoard(board_0, players_board, row, col);
					counter++;
				}
			}
		}
	}
}
bool win(char board_0[][COLS], char players_board[][COLS], int row, int col, int bombNum) {
	int i, j, count = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (players_board[i][j] == 'x' || players_board[i][j] == 'F') // this sell didn't open yet
				count++;
		}
	}

	if (count == bombNum) // The amount of X is equal to the number of bombs
		return true;
	else
		return false;
}

void floodfill(char board_0[][COLS], char players_board[][COLS], int logRowSize, int logColSize, int i, int j)
{
	if (board_0[i][j] == ' ')
	{
		board_0[i][j] = '0';

		if (i < logRowSize - 1 && j > 0)
			floodfill(board_0, players_board, logRowSize, logColSize, i + 1, j - 1);
		if (i < logRowSize - 1)
			floodfill(board_0, players_board, logRowSize, logColSize, i + 1, j);
		if (i < logRowSize - 1 && j < logColSize - 1)
			floodfill(board_0, players_board, logRowSize, logColSize, i + 1, j + 1);


		if (j < logColSize - 1)
			floodfill(board_0, players_board, logRowSize, logColSize, i, j + 1);
		if (j > 0)
			floodfill(board_0, players_board, logRowSize, logColSize, i, j - 1);


		if (j > 0 && i > 0)
			floodfill(board_0, players_board, logRowSize, logColSize, i - 1, j - 1);
		if (i > 0)
			floodfill(board_0, players_board, logRowSize, logColSize, i - 1, j);
		if (i > 0 && j < logColSize - 1)
			floodfill(board_0, players_board, logRowSize, logColSize, i - 1, j + 1);
	}

	updateBoard(board_0, players_board, i, j);
	// put space where there is 0
	for (int i = 0; i < logRowSize; i++)
		for (int j = 0; j < logColSize; j++)
			if (players_board[i][j] == '0')
				players_board[i][j] = ' ';

}
void gameMeneger(int logRowSize, int logColSize)
{
	bool end = false;
	int x = logRowSize * logColSize;
	int bombNum = (int)sqrt(x);
	int i, j;
	char flag;
	char board_0[ROWS][COLS];                 // the uncoverd board
	char players_board[ROWS][COLS];           // the covered board - this is the board the player see

	initBoard0(board_0, logRowSize, logColSize, bombNum);      // init board 0 - put a bomb, number or space
	initPlayerBoard(players_board, logRowSize, logColSize);    // init players bora with x's

	printBoard(players_board, logRowSize, logColSize);

	while (end != true)
	{
		printf("Please enter your move, row and colum: ");
		scanf("%d%d %c", &i, &j, &flag);
		printf("\n");

		// ******************************************* chack if the input is valid   ******************************************
		if (flag != 102 && flag != 70 && flag != 111 && flag != 79)
		{
			printf("Invalid choice!! \n\n");
			continue;
		}

		// the player choose f for flag
		else if (flag == 70 || flag == 102)
		{
			players_board[i][j] = 'F';
			printBoard(players_board, logRowSize, logColSize);
			continue;
		}

		// the player choose o for open
		else if (flag == 111 || flag == 79)
		{
			//  ************* shortcut *************************************************************************
			if ((i == -1) && (j > 0))
			{
				open_j_amuont_of_sells(j, board_0, players_board, logRowSize, logColSize);
				printBoard(players_board, logRowSize, logColSize);
				// ********** chack for win ********************************************************************
				if (win(board_0, players_board, logRowSize, logColSize, bombNum) == true)
				{
					printf("\n You won!! congragulation! CHAMPION! \n\n");
					updateBoard(board_0, players_board, i, j);
					printBoard(players_board, logRowSize, logColSize);
					printf("\nHope you have enjoyed playing!!!!! \n");
					end = true;
				}
			}
			// *************** chack if the input is valid *****************************************************
			else if (i < -1 || i >= logRowSize || j < 0 || j >= logColSize)
			{
				printf("Please enter a valid choice! \n\n");
				continue;
			}
			// *************** chack if this row and col already have been chosen  *****************************
			else if (players_board[i][j] != 'x' && players_board[i][j] != 'F' && players_board[i][j] != 'f')
			{
				printf("You already played this move, please enter a valid choice! \n\n");
				printBoard(players_board, logRowSize, logColSize);
				continue;
			}

			// 4. ************ chack if hit a bomb *************************************************************
			else if (board_0[i][j] == '*')
			{
				updateBoard(board_0, players_board, i, j);
				printf("\n\nYou've hit a bomb! Game over! \n\n");
				printBoard(board_0, logRowSize, logColSize);
				printf("\nHope you have enjoyed playing!!!!! \n");
				end = true;
			}

			// 5. ************ chack if hit a space ************************************************************
			else if (board_0[i][j] == ' ')
			{
				floodfill(board_0, players_board, logRowSize, logColSize, i, j);
				for (int i = 0; i < logRowSize; i++)
					for (int j = 0; j < logColSize; j++)
						if (board_0[i][j] == '0')
							board_0[i][j] = ' ';
				printBoard(players_board, logRowSize, logColSize);

			}

			// 6. ************ not a bomb - num or space *******************************************************
			else
			{
				updateBoard(board_0, players_board, i, j);
				printBoard(players_board, logRowSize, logColSize);
				// chack for win ****************************************************************************
				if (win(board_0, players_board, logRowSize, logColSize, bombNum) == true)
				{
					printf("\n You won!! congragulation! CHAMPION! \n\n");
					updateBoard(board_0, players_board, i, j);
					printBoard(players_board, logRowSize, logColSize);
					printf("\nHope you have enjoyed playing!!!!! \n");
					end = true;
				}
				continue;
			}
		}
	}
}

// Project 1: Minesweepers part A
// Netta Adani. ID: 206960338
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>      // printf, scanf, NULL
#include <stdlib.h>     // srand, rand 
#include <time.h>       // time 
#include <stdbool.h>    // bool
#define SIZE 8

void rendom_bomb(char board_0[][SIZE]);
void printBoard(char board[][SIZE], int rowNum, int colNum, int size);
void updateBoard(char srcBoard[][SIZE], char destBoard[][SIZE], int i, int j);
void initBoard0(char board_0[][SIZE]);
void initPlayerBoard(char board[][SIZE]);
void open_j_amuont_of_sells(int j, char board_0[][SIZE], char players_board[][SIZE]);
bool win(char board_0[][SIZE], char players_board[][SIZE], int row, int col);
void game(char board_0[][SIZE], char players_board[][SIZE]);

void main()
{
	char board_0[SIZE][SIZE];                 // the uncoverd board
	char players_board[SIZE][SIZE];           // the covered board - this is the board the player see
	game(board_0, players_board);
}



void initPlayerBoard(char board[][SIZE])
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = 'x';
}
void rendom_bomb(char board_0[][SIZE])
{
	// this fanction does random placement of bombs on the board
	int i, row, col;
	srand(time(NULL));

	for (i = 0; i < SIZE; )
	{
		row = rand() % SIZE; // random row
		col = rand() % SIZE; // random colum

		if (board_0[row][col] != '*')
		{
			board_0[row][col] = '*'; // * bomb *
			i++;
		}
	}
}
void initBoard0(char board_0[][SIZE])
{
	rendom_bomb(board_0);  // Random placement of bombs on the board has been sat
	char counter;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
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

				if ((i - 1 >= 0) && (j + 1 < SIZE) && (board_0[i - 1][j + 1] == ('*'))) // up & right
					counter++;

				if ((j - 1 >= 0) && (board_0[i][j - 1] == ('*'))) // left
					counter++;

				if ((j + 1 < SIZE) && (board_0[i][j + 1] == ('*'))) // right
					counter++;

				if ((i + 1 < SIZE) && (j - 1 >= 0) && (board_0[i + 1][j - 1] == ('*'))) // down & left
					counter++;

				if ((i + 1 < SIZE) && (board_0[i + 1][j] == ('*')))// down
					counter++;

				if ((i + 1 < SIZE) && (j + 1 < SIZE) && (board_0[i + 1][j + 1] == ('*'))) // down & right
					counter++;
			}
			if (counter == '0') // there is no bomb in the area of this sell - put space in this sell
				board_0[i][j] = ' ';
			else                // Placing a number according to the number of bombs in the sell area
				board_0[i][j] = counter;
		}
	}
}
void printBoard(char board[][SIZE], int rowNum, int colNum, int size)
{
	char value;
	int row, col, i;
	// print mine line 0-(size-1) cols
	printf("     ");
	for (int i = 0; i < size; i++)
		printf("%4d", i);
	printf("\n");

	//print a line
	printf("   ");
	for (i = 0; i < (size * 4.5); i++)
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
	for (int i = 0; i < (size * 4.5); i++)
		printf("%c", '_');

	printf("\n");
}
void updateBoard(char srcBoard[][SIZE], char destBoard[][SIZE], int i, int j)
{
	destBoard[i][j] = srcBoard[i][j];
}
void open_j_amuont_of_sells(int j, char board_0[][SIZE], char players_board[][SIZE])
{
	int counter = 0;

	for (int row = 0; row < SIZE; row++)
	{
		for (int col = 0; col < SIZE; col++)
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
bool win(char board_0[][SIZE], char players_board[][SIZE], int row, int col)
{
	int i, j, count = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (players_board[i][j] == 'x') // this sell didn't open yet
				count++;
		}
	}

	if (count == 8) // The amount of X is equal to the number of bombs: 8
		return true;
}
void game(char board_0[][SIZE], char players_board[][SIZE])
{
	int i, j, n;
	bool end = false;

	initBoard0(board_0);                      // init board 0 - put a bomb, number or space
	initPlayerBoard(players_board);           // init players bora with x's

	while (end != true)
	{
		printf("\nWelcome to Minesweepers!\n\n");
		printf("Please choose one of the following options and enter it's number: \n\n1 - for size 8X8 \n\n2 - for size 12X12 \n\n3 - for size  15X15 \n\n4 - for custom size \n\n0 - Exit\n\n");
		scanf("%d", &n);
		printf("\n");

		// **** check if input is valid *******************************************************************
		if (n < 0 || n>4)
		{
			printf("Invalid choise!\n\n");
			continue;
		}

		if (n == 0) // Exit *******************************************************************************
		{
			printf("good bye!\n");
			break;
		}

		if (n == 1) // 8X8 **********************************************************************************
		{
			printBoard(players_board, SIZE, SIZE, SIZE);
			while (n == 1)
			{
				printf("Plese enter your move, row and colum: ");
				scanf("%d%d", &i, &j);
				printf("\n");

				// 1. shortcut ******************************************************************************
				if ((i == -1) && (j > 0))
				{
					open_j_amuont_of_sells(j, board_0, players_board);
					printBoard(players_board, SIZE, SIZE, SIZE);
					// chack for win ****************************************************************************
					if (win(board_0, players_board, SIZE, SIZE) == true)
					{
						printf(" You won!! congragulation! CHAMPION! \n\n");
						updateBoard(board_0, players_board, i, j);
						printBoard(players_board, SIZE, SIZE, SIZE);
						end = true;
					}
				}
				// 2. chack if the input is valid ***********************************************************
				else if ((i < 0 || i >= SIZE) || (j < 0 || j >= SIZE))
				{
					printf("Please enter a valid choice! \n\n");
					continue;
				}
				// 3. chack if this row and col already have been chosen ************************************
				else if (players_board[i][j] != 'x')
				{
					printf("Invalid move, please enter a valid choice! \n\n");
					printBoard(players_board, SIZE, SIZE, SIZE);
					continue;
				}
				// 4. chack if hit a bomb *******************************************************************
				else if (board_0[i][j] == '*')
				{
					updateBoard(board_0, players_board, SIZE, SIZE);
					printBoard(players_board, SIZE, SIZE, SIZE);
					printf("\n\nYou've hit a bomb! Game over! \n\n");
					printBoard(board_0, SIZE, SIZE, SIZE);
					end = true;
				}
				// 4. not a bomb - num or space *************************************************************
				else
				{
					updateBoard(board_0, players_board, i, j);
					printBoard(players_board, SIZE, SIZE, SIZE);
					// chack for win ****************************************************************************
					if (win(board_0, players_board, SIZE, SIZE) == true)
					{
						printf(" You won!! congragulation! CHAMPION! \n\n");
						updateBoard(board_0, players_board, i, j);
						printBoard(players_board, SIZE, SIZE, SIZE);
						end = true;
					}
					continue;
				}
			}
		}

		if (n == 2)       // 12X12
		{
			printf("To be continue...\n\n");
			continue;
		}

		if (n == 3)       // 15X15
		{
			printf("To be continue...\n\n");
			continue;
		}

		if (n == 4)       // free choice
		{
			printf("To be continue...\n\n");
			continue;
		}
	}
}
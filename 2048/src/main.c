#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

// Define

#define MAX 4

// Key

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

// Map

int Map[4][4];

// Global

int i, j, k;
int cnt, action = 1;
int score;

// Fuction

void Menu_Print();
void Game_Init();
void Rand_Block();
void Print();
int Power(int num);
void Get_Key();
void Move_Block_Up();
void Move_Block_Down();
void Move_Block_Left();
void Move_Block_Right();
void Check();
void Game_Win();
void Game_Lose();

int main() {
	Game_Init();
	Rand_Block();
	while (1) {
		if (action) {
			Rand_Block();
		}
		Print();
		Get_Key();
		Print();
		Check();
	}
}

void Menu_Print() {
	char choose;

	system("cls");
	system("mode con: lines=7 cols=90");
	printf("+---------------------------------------------------------------------------------------+\n");
	printf("|                                         2048                                          |\n");
	printf("+---------------------------------------------------------------------------------------+\n");
	printf("|                                 Start, press 's' key.                                 |\n");
	printf("+---------------------------------------------------------------------------------------+\n");

	choose = getch();

	switch (choose) {
	case 's': return;
	default: exit(0);
	}
}

void Game_Init() {
	cnt = 0;
	score = 0;
	action = 1;
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			Map[i][j] = 0;
		}
	}
	Menu_Print();
}

int Power(int num) {
	if (!num)
		return cnt + 1;
	num /= 2;
	++cnt;
	return Power(num);
}

void Print() {
	system("cls");
	system("mode con: lines=15 cols=30");
	printf("+===========================+\n");
	for (i = 0; i < MAX; ++i) {
		printf("|                           |\n|");
		for (j = 0; j < MAX; ++j, cnt = 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Power(Map[i][j]));
			printf(" %4d ", Map[i][j]);
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("   |\n|                           |\n");
	}
	printf("+===========================+\nscore = %d", score);
}

void Rand_Block() {
	int block = 0;
	int per = 0;
	srand(time(NULL));
	per = rand() % 10;
	do
	{
		block = rand() % (MAX * MAX);
	} while (Map[block / MAX][block % MAX]);
	if (per > 2) {
		Map[block / MAX][block % MAX] = 2;
	}
	else
	{
		Map[block / MAX][block % MAX] = 4;
	}
}

void Get_Key() {
	char Key = 0;
	action = 0;

	Key = getch();

	switch (Key) {
	case UP: Move_Block_Up(); break;
	case DOWN: Move_Block_Down(); break;
	case LEFT: Move_Block_Left(); break;
	case RIGHT: Move_Block_Right();
	}
	for (i = 0; i < MAX; ++i) {
		for (j = 0; j < MAX; ++j) {
			if (Map[i][j] % 2) {
				--Map[i][j];
			}
		}
	}
}

void Move_Block_Up() {
	for (i = 1; i < MAX; ++i) {
		for (j = 0; j < MAX; ++j) {
			for (k = i; k > 0; --k) {
				if (!Map[k][j]) {
					break;
				}
				else {	// 1
					if (Map[k][j] % 2) {
						break;
					}
					if (Map[k - 1][j]) {	// 1
						if (Map[k - 1][j] == Map[k][j]) {
							Map[k - 1][j] = Map[k - 1][j] * 2 + 1;
							score += Map[k][j] * 2;
							Map[k][j] = 0;
							++action;
						}
						else {
							break;
						}
					}
					else {	// 0
						Map[k - 1][j] = Map[k][j];
						Map[k][j] = 0;
						++action;
					}
				}
			}
		}
	}
}

void Move_Block_Down() {
	for (i = MAX - 2; i >= 0; --i) {
		for (j = 0; j < MAX; ++j) {
			for (k = i; k < MAX - 1; ++k) {
				if (!Map[k][j]) {
					break;
				}
				else {	// 1
					if (Map[k][j] % 2) {
						break;
					}
					if (Map[k + 1][j]) {
						if (Map[k + 1][j] == Map[k][j]) {
							Map[k + 1][j] = Map[k + 1][j] * 2 + 1;
							score += Map[k][j] * 2;
							Map[k][j] = 0;
							++action;
						}
						else {
							break;
						}
					}
					else {
						Map[k + 1][j] = Map[k][j];
						Map[k][j] = 0;
						++action;
					}
				}
			}
		}
	}
}

void Move_Block_Left() {
	for (i = 0; i < MAX; ++i) {
		for (j = 1; j < MAX; ++j) {
			for (k = j; k > 0; --k) {
				if (!Map[i][k]) {
					break;
				}
				else {	// 1
					if (Map[i][k] % 2) {
						break;
					}
					if (Map[i][k - 1]) {
						if (Map[i][k - 1] == Map[i][k]) {
							Map[i][k - 1] = Map[i][k - 1] * 2 + 1;
							score += Map[i][k] * 2;
							Map[i][k] = 0;
							++action;
						}
						else {
							break;
						}
					}
					else {
						Map[i][k - 1] = Map[i][k];
						Map[i][k] = 0;
						++action;
					}
				}
			}
		}
	}
}

void Move_Block_Right() {
	for (i = 0; i < MAX; ++i) {
		for (j = MAX - 2; j >= 0; --j) {
			for (k = j; k < MAX - 1; ++k) {
				if (!Map[i][k]) {
					break;
				}
				else {	// 1
					if (Map[i][k] % 2) {
						break;
					}
					if (Map[i][k + 1]) {
						if (Map[i][k + 1] == Map[i][k]) {
							Map[i][k + 1] = Map[i][k + 1] * 2 + 1;
							score += Map[i][k] * 2;
							Map[i][k] = 0;
							++action;
						}
						else {
							break;
						}
					}
					else {
						Map[i][k + 1] = Map[i][k];
						Map[i][k] = 0;
						++action;
					}
				}
			}
		}
	}
}

void Check() {
	int count = 0;
	for (int i = 0; i < MAX; ++i) {
		for(int j = 0; j < MAX; ++j)	{
			if (Map[i][j] == 2048) {
				Game_Win();
			}
			if (Map[i][j]) {
				++count;
			}
		}
	}

	if (count == MAX * MAX && !action) {
		getch();
		Game_Lose();
	}
}

void Game_Win() {
	char choose;

	system("cls");
	system("mode con: lines=7 cols=90");
	printf("+---------------------------------------------------------------------------------------+\n");
	printf("|                                 You win!                                              |\n");
	printf("|                               Restart, press 'r' key.                                 |\n");
	printf("|                               Quit, press any key.                                    |\n");
	printf("+---------------------------------------------------------------------------------------+\n");

	choose = getch();

	switch (choose) {
	case 'r': Game_Init(); break;
	default: exit(0);
	}
}

void Game_Lose() {
	char choose;

	system("cls");
	system("mode con: lines=7 cols=90");
	printf("+---------------------------------------------------------------------------------------+\n");
	printf("|                                 Oops, You lose.                                       |\n");
	printf("|                               Restart, press 'r' key.                                 |\n");
	printf("|                               Quit, press any key.                                    |\n");
	printf("+---------------------------------------------------------------------------------------+\n");

	choose = getch();

	switch (choose) {
	case 'r': Game_Init(); break;
	default: exit(0);
	}
}
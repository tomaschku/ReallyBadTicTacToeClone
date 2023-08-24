#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>

struct Struct_Player {
public:
	Struct_Player() {
		srand((unsigned)time(NULL));
		pisX = false;
	};

	bool isX() { return pisX ? true : false; };
	char getChar() {
		if (pisX) {
			return 'X';
		}
		else {
			return 'O';
		};
	};

	void swap() { pisX = !pisX; };
	void randomize() {
		pisX = rand() % 2;
	};

private:
	bool pisX;
};

Struct_Player Player;
bool WantToPlay = true;
char Field[3][3];
bool FieldSetable[3][3];

void print_field() {
	printf("%c|%c|%c\n", Field[0][0], Field[0][1], Field[0][2]);
	printf("-----\n");
	printf("%c|%c|%c\n", Field[1][0], Field[1][1], Field[1][2]);
	printf("-----\n");
	printf("%c|%c|%c\n", Field[2][0], Field[2][1], Field[2][2]);
};

void check() {
	bool Xwon = false;
	bool Owon = false;

	//X
	for (int row = 0; row < 3; row++) {//row-test
		if (Field[row][0] == 'X' && Field[row][1] == 'X' && Field[row][2] == 'X') { Xwon = true; };
	};
	for (int colummn = 0; colummn < 3; colummn++) {//colummn-test
		if (Field[0][colummn] == 'X' && Field[1][colummn] == 'X' && Field[2][colummn] == 'X') { Xwon = true; };
	};
	//left top to right bottom
	if (Field[0][0] == 'X' && Field[1][1] == 'X' && Field[2][2] == 'X') { Xwon = true; };
	//right top to left bottom
	if (Field[0][2] == 'X' && Field[1][1] == 'X' && Field[2][0] == 'X') { Xwon = true; };
	//O
	for (int row = 0; row < 3; row++) {//row-test
		if (Field[row][0] == 'O' && Field[row][1] == 'O' && Field[row][2] == 'O') { Owon = true; };
	};
	for (int colummn = 0; colummn < 3; colummn++) {//colummn-test
		if (Field[0][colummn] == 'O' && Field[1][colummn] == 'O' && Field[2][colummn] == 'O') { Owon = true; };
	};
	//left top to right bottom
	if (Field[0][0] == 'O' && Field[1][1] == 'O' && Field[2][2] == 'O') { Owon = true; };
	//right top to left bottom
	if (Field[0][2] == 'O' && Field[1][1] == 'O' && Field[2][0] == 'O') { Owon = true; };

	
	if (Xwon && Owon) {
		WantToPlay = false;
		system("cls");
		printf("Nobody has won!");
		system("pause > nul");
	};
	if (Xwon) {
		WantToPlay = false;
		system("cls");
		print_field();
		printf("X has won!");
		system("pause > nul");
	}
	else if (Owon) {
		WantToPlay = false;
		system("cls");
		print_field();
		printf("O has won!");
		system("pause > nul");
	};
};

int main() {
	char user_in[2];
	
	while (true) {
		user_in[0] = '1';
		user_in[1] = '1';
		for (int a = 0; a < 3; a++) {
			for (int b = 0; b < 3; b++) {
				Field[a][b] = '-';
				FieldSetable[a][b] = true;
			};
		};
		Player.randomize();
		
		WantToPlay = true;
		
		while (WantToPlay) {
		ERR:
			system("cls");
			print_field();
			printf("%c is now playing!", Player.getChar());
			printf("\nEnter a number from 1 to 3 for the row: ");
			user_in[1] = _getch();
			printf("\r                                            \rAnd a second number for the column: %cx", user_in[1]);
			user_in[0] = _getch();

			if ((int)user_in[0] < 49 || (int)user_in[0] > 51) {
				printf("\nERROR: WRONG FIRST INPUT (%i~%c)", user_in[0], user_in[0]);
				system("pause > nul");
				goto ERR;
			} else if ((int)user_in[1] < 49 || (int)user_in[1] > 51) {
				printf("\nERROR: WRONG SECOND INPUT (%i~%c)", user_in[1], user_in[1]);
				system("pause > nul");
			};

			if (FieldSetable[user_in[1] - '0' - 1][user_in[0] - '0' - 1]) {
				Field[user_in[1] - '0' - 1][user_in[0] - '0' - 1] = Player.getChar();
				FieldSetable[user_in[1] - '0' - 1][user_in[0] - '0' - 1] = false;
			}
			else {
				printf("\nInput field already filled!");
				system("pause > nul");
				goto ERR;
			};

			check();

			Player.swap();
		};
	};
};
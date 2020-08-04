// ����������� ������. ������� � 2.
// �������. ��������, ����������� ������� ������ �� ��������� � �������� �����, ������������ ������ ��������.

#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <windows.graphics.h>
//----------------------------------------------------���������-------------------------------------
#define ESC 27
#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
//------------------------------------------------------����----------------------------------------
#define MENU_SIZE 3
char menu[MENU_SIZE][10] = { "NEW GAME","OPTIONS","EXIT" };
#define MENU_X 100
#define MENU_Y 20
#define MENU_NEW_GAME 0
#define MENU_OPTIONS 1
#define MENU_EXIT 2
//---------------------------------------------------------�����------------------------------------
#define HERO_WIDTH 7
#define HERO_HEIGHT 7
#define HERO_ACTION_COUNT 2
#define HERO_SPRITES_COUNT 2
//--------------------------------------------------------�����-------------------------------------
#define BORDER_UPPER 2
#define BORDER_DOWN 62
#define BORDER_LEFT 5
#define BORDER_RIGHT 215

#define HORISON_WALL_1 14
#define HORISON_WALL_2 26
#define HORISON_WALL_3 38
#define HORISON_WALL_4 50
#define HORISON_WALL_5 52

#define ENEM_UP 3
#define ENEM_DOWN 4
#define ENEM_LEFT 1
#define ENEM_RIGHT 2

//---------------------------------------------------------------------------------------------------
enum colors_enum
{
	Black = 0,
	Grey = FOREGROUND_INTENSITY,
	LightGrey = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Blue = FOREGROUND_BLUE,
	Green = FOREGROUND_GREEN,
	Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
	Red = FOREGROUND_RED,
	Purple = FOREGROUND_RED | FOREGROUND_BLUE,
	LightBlue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	LightGreen = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	LightCyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	LightRed = FOREGROUND_RED | FOREGROUND_INTENSITY,
	LightPurple = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Orange = FOREGROUND_RED | FOREGROUND_GREEN,
	Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
};
HANDLE hStdOut; // ��������� ����������� �������
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(hStdOut, c);
}
void cursorHide()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = FALSE;

	SetConsoleCursorInfo(hStdOut, &cursorInfo);
}
void setcolor(WORD attr)
{
	SetConsoleTextAttribute(hStdOut, attr);
}

int PacManLR[HERO_ACTION_COUNT][HERO_SPRITES_COUNT][HERO_HEIGHT][HERO_WIDTH] =
{
	0,0,5,5,5,0,0,
	0,5,5,5,5,5,0,
	5,5,5,5,0,5,5,
	5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,
	0,5,5,5,5,5,0,
	0,0,5,5,5,0,0,// �������� �
				  // �����
	0,0,5,5,5,0,0,// "0" �������
	0,5,5,0,5,5,0,
	5,5,5,5,5,0,0,
	5,5,5,5,0,0,0,
	5,5,5,5,5,0,0,
	0,5,5,5,5,5,0,
	0,0,5,5,5,0,0,

	//-----------------------------------

	0,0,5,5,5,0,0,
	0,5,5,5,5,5,0,
	5,5,0,5,5,5,5,
	5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,
	0,5,5,5,5,5,0,
	0,0,5,5,5,0,0,// �������� �
				  // ����
	0,0,5,5,5,0,0,// "1" �������
	0,5,5,0,5,5,0,
	0,0,5,5,5,5,5,
	0,0,0,5,5,5,5,
	0,0,5,5,5,5,5,
	0,5,5,5,5,5,0,
	0,0,5,5,5,0,0,
};
int PacManUD[HERO_ACTION_COUNT][HERO_SPRITES_COUNT][HERO_HEIGHT][HERO_WIDTH] =
{
	0,0,5,5,5,0,0,
	0,5,5,5,5,5,0,
	5,5,5,5,0,5,5,
	5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,
	0,5,5,5,5,5,0,
	0,0,5,5,5,0,0,// �������� 
				  // �����
	0,0,0,0,0,0,0,// "0" �������
	0,5,0,0,0,5,0,
	5,5,5,0,5,5,5,
	5,5,5,5,5,0,5,
	5,5,5,5,5,5,0,
	0,5,5,5,5,5,0,
	0,0,5,5,5,0,0,

	//-----------------------------------

	0,0,5,5,5,0,0,
	0,5,5,5,5,5,0,
	5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,
	5,5,5,5,0,5,5,
	0,5,5,5,5,5,0,
	0,0,5,5,5,0,0,// �������� 
				  // ����
	0,0,5,5,5,0,0,// "1" �������
	0,5,5,5,5,5,0,
	5,5,5,5,5,5,5,
	5,5,5,5,5,0,5,
	5,5,5,0,5,5,5,
	0,5,0,0,0,5,0,
	0,0,0,0,0,0,0,
};

int Enemy[HERO_HEIGHT][HERO_WIDTH] =
{
	0,0,5,5,5,0,0,
	0,5,5,5,5,5,0,
	0,5,0,5,0,5,0,
	0,5,5,5,5,5,0,
	0,5,5,5,5,5,0,
	0,5,5,5,5,5,0,
	0,5,0,5,0,5,0,
};

long X_POS_PM = 107;//---------�������
long Y_POS_PM = 54;//---------�������

long X_POS_ENEMY = 150; //--------�������
long Y_POS_ENEMY = 5; //--------�����

void DrawPacManLR(int direction, int mouth, int x, int y);// ��������� ������� ��� �������� ������ � �����.
void PacManRunRight(int x, int y, int hero_step);// ������ �������� ������.
void PacManRunLeft(int x, int y, int hero_step);// ������ �������� �����.

void DrawPacManUD(int direction, int mouth, int x, int y);// ��������� ������� ��� �������� ����� � ����.
void PacManRunUp(int x, int y, int hero_step);// ������ �������� �����.
void PacManRunDown(int x, int y, int hero_step);// ������ �������� ����.

void ErasePacMan(int x, int y);// ������� ���������.

void DrawGameArea();// ��������� ������ �����.
void DrawAreaFilling();// ��������� ���������� ���� �����.
void DrawAreaPrise();// ���������� ����� �������.

void DrawEnemy(int x, int y); // ��������� �����.
void EnemyRunRight(int x, int y, int enemy_step); // �������� ������. 
void EnemyRunLeft(int x, int y, int enemy_step); // �������� �����.
void EnemyRunUp(int x, int y, int enemy_step); // �������� �����.
void EnemyRunDown(int x, int y, int enemy_step); // �������� ����.
void EraseEnemy(int x, int y); // ������� �����.

void game();
void showMenu(int pos);

//------------------------------------------------------------------------------------------------------------------------��������� ��������� �����/������-------------------
void DrawPacManLR(int direction, int mouth, int x, int y)
{
	int i, j;
	setcolor(Orange);
	for (i = 0; i < HERO_HEIGHT; i++)
	{
		for (j = 0; j < HERO_WIDTH; j++)
		{
			if (PacManLR[direction][mouth][i][j] == 5)
			{
				gotoxy(x + j, y + i);
				printf("#");
			}
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------�������� ������------------------------------------
void PacManRunRight(int x, int y, int hero_step)
{
	int direction_R = 0;
	static int mouthContr = 0;//���
	static int mouthPos;

	ErasePacMan(x - hero_step, y + 1);

	if (mouthContr % 15 <= 7) // �������� ����������/���������� ���
	{
		mouthPos = 1;
	}
	else if (mouthContr % 15 >= 7)
	{
		mouthPos = 0;
	}
	DrawPacManLR(direction_R, mouthPos, X_POS_PM, Y_POS_PM);
	mouthContr++;
}
//------------------------------------------------------------------------------------------------------------------------�������� �����-------------------------------------
void PacManRunLeft(int x, int y, int hero_step)
{
	int direction_L = 1;
	static int mouthContr = 0;//���
	static int mouthPos;

	ErasePacMan(x + hero_step, y + 1);

	if (mouthContr % 15 <= 7) // �������� ����������/���������� ���.
	{
		mouthPos = 1;
	}
	else if (mouthContr % 15 >= 7)
	{
		mouthPos = 0;
	}

	DrawPacManLR(direction_L, mouthPos, X_POS_PM, Y_POS_PM);
	mouthContr++;
}

//------------------------------------------------------------------------------------------------------------------------��������� ��������� �����/����---------------------
void DrawPacManUD(int direction, int mouth, int x, int y)
{
	int i, j;
	setcolor(Orange);
	for (i = 0; i < HERO_HEIGHT; i++)
	{
		for (j = 0; j < HERO_WIDTH; j++)
		{
			if (PacManUD[direction][mouth][i][j] == 5)
			{
				gotoxy(x + j, y + i);
				printf("#");
			}
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------�������� �����-------------------------------------
void PacManRunUp(int x, int y, int hero_step)
{
	int direction_U = 0;
	static int mouthContr = 0;//���
	static int mouthPos;

	ErasePacMan(x + 1, y + hero_step);

	if (mouthContr % 15 <= 7) // �������� ����������/���������� ���
	{
		mouthPos = 1;
	}
	else if (mouthContr % 15 >= 7)
	{
		mouthPos = 0;
	}

	DrawPacManUD(direction_U, mouthPos, X_POS_PM, Y_POS_PM);
	mouthContr++;
}
//------------------------------------------------------------------------------------------------------------------------�������� ����--------------------------------------
void PacManRunDown(int x, int y, int hero_step)
{
	int direction_D = 1;
	static int mouthContr = 0;//���
	static int mouthPos;

	ErasePacMan(x + 1, y - hero_step);

	if (mouthContr % 15 <= 7) // �������� ����������/���������� ���
	{
		mouthPos = 1;
	}
	else if (mouthContr % 15 >= 7)
	{
		mouthPos = 0;
	}

	DrawPacManUD(direction_D, mouthPos, X_POS_PM, Y_POS_PM);
	mouthContr++;
}

//------------------------------------------------------------------------------------------------------------------------�������� ���������---------------------------------
void ErasePacMan(int x, int y)
{
	int i, j;

	for (i = 0; i <= 7; i++)
	{
		for (j = 0; j <= 7; j++)
		{
			gotoxy((x - 1) + j, (y - 1) + i);//�������� ������� ��� ���
			printf(" ");
		}
	}
}


//------------------------------------------------------------------------------------------------------------------------������� �����--------------------------------------
void DrawGameArea()
{
	int u, l, r, d;

	SetConsoleTextAttribute(hStdOut, (WORD)((Grey << 4) | Grey));

	for (u = BORDER_LEFT; u < BORDER_RIGHT; u++)// ������� �������
	{
		gotoxy(u, BORDER_UPPER);

		printf("=");
	}

	for (d = BORDER_LEFT; d < BORDER_RIGHT; d++)// ������ �������
	{
		gotoxy(d, BORDER_DOWN);

		printf("=");
	}

	for (l = BORDER_UPPER; l < BORDER_DOWN; l++)// ����� �������
	{
		gotoxy(BORDER_LEFT, l);

		printf("=");
	}

	for (r = BORDER_UPPER; r <= BORDER_DOWN; r++) //������ �������
	{
		gotoxy(BORDER_RIGHT, r);

		printf("=");
	}
}
//------------------------------------------------------------------------------------------------------------------------����� ������ �����---------------------------------
void DrawAreaFilling()
{
	int h1, h2, h3, h4;


	SetConsoleTextAttribute(hStdOut, (WORD)((Blue << 4) | Blue));

	for (h1 = BORDER_LEFT + 17; h1 < BORDER_RIGHT - 17; h1++)// ���������� �������������� ����� 1
	{
		gotoxy(h1, HORISON_WALL_1);

		printf("=");
	}

	for (h2 = BORDER_LEFT + 17; h2 < BORDER_RIGHT - 17; h2++)// ���������� �������������� ����� 2
	{
		gotoxy(h2, HORISON_WALL_2);

		printf("=");

	}

	for (h3 = BORDER_LEFT + 17; h3 < BORDER_RIGHT - 17; h3++)// ���������� �������������� ����� 3
	{
		gotoxy(h3, HORISON_WALL_3);

		printf("=");
	}

	for (h4 = BORDER_LEFT + 17; h4 < BORDER_RIGHT - 17; h4++)// ���������� �������������� ����� 4
	{
		gotoxy(h4, HORISON_WALL_4);

		printf("=");

	}
}
//------------------------------------------------------------------------------------------------------------------------������� ������-------------------------------------
void DrawAreaPrise()
{
	int prise;

	SetConsoleTextAttribute(hStdOut, (WORD)((Black << 4) | Yellow));

	for (prise = BORDER_LEFT + 8; prise < BORDER_RIGHT - 8; prise += 4)// ���������� �������������� ����� 4
	{
		gotoxy(prise, HORISON_WALL_1 - 6);

		printf("@");
	}

	for (prise = BORDER_LEFT + 8; prise < BORDER_RIGHT - 8; prise += 4)// ���������� �������������� ����� 4
	{
		gotoxy(prise, HORISON_WALL_2 - 6);

		printf("@");
	}

	for (prise = BORDER_LEFT + 8; prise < BORDER_RIGHT - 8; prise += 4)// ���������� �������������� ����� 4
	{
		gotoxy(prise, HORISON_WALL_3 - 6);

		printf("@");
	}

	for (prise = BORDER_LEFT + 8; prise < BORDER_RIGHT - 8; prise += 4)// ���������� �������������� ����� 4
	{
		gotoxy(prise, HORISON_WALL_4 - 6);

		printf("@");
	}

	for (prise = BORDER_LEFT + 8; prise < BORDER_RIGHT - 8; prise += 4)// ���������� �������������� ����� 4
	{
		gotoxy(prise, HORISON_WALL_4 + 6);

		printf("@");
	}

	for (prise = BORDER_UPPER + 8; prise < BORDER_DOWN - 6; prise += 2)// ���������� �������������� ����� 4
	{
		gotoxy(BORDER_LEFT + 8, prise);

		printf("@");
	}

	for (prise = BORDER_UPPER + 6; prise < BORDER_DOWN - 4; prise += 2)// ���������� �������������� ����� 4
	{
		gotoxy(BORDER_RIGHT - 6, prise);

		printf("@");
	}
}


//------------------------------------------------------------------------------------------------------------------------��������� �����------------------------------------
void DrawEnemy(int x, int y)
{
	int i, j;
	setcolor(Red);
	for (i = 0; i < HERO_HEIGHT; i++)
	{
		for (j = 0; j < HERO_WIDTH; j++)
		{
			if (Enemy[i][j] == 5)
			{
				gotoxy(x + j, y + i);
				printf("#");
			}
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------�������� ������------------------------------------
void EnemyRunRight(int x, int y, int enemy_step)
{
	EraseEnemy(x - enemy_step, y + 1);
	DrawEnemy(X_POS_ENEMY, Y_POS_ENEMY);
}
//------------------------------------------------------------------------------------------------------------------------�������� �����-------------------------------------
void EnemyRunLeft(int x, int y, int enemy_step)
{
	EraseEnemy(x + enemy_step, y + 1);
	DrawEnemy(X_POS_ENEMY, Y_POS_ENEMY);
}
//------------------------------------------------------------------------------------------------------------------------�������� �����-------------------------------------
void EnemyRunUp(int x, int y, int enemy_step)
{
	EraseEnemy(x + 1, y + enemy_step);
	DrawEnemy(X_POS_ENEMY, Y_POS_ENEMY);
}
//------------------------------------------------------------------------------------------------------------------------�������� ����--------------------------------------
void EnemyRunDown(int x, int y, int enemy_step)
{
	EraseEnemy(x + 1, y - enemy_step);
	DrawEnemy(X_POS_ENEMY, Y_POS_ENEMY);
}

//------------------------------------------------------------------------------------------------------------------------������� �����--------------------------------------
void EraseEnemy(int x, int y)
{
	int i, j;

	for (i = 0; i <= 8; i++)
	{
		for (j = 0; j <= 7; j++)
		{
			gotoxy((x - 1) + (j + 1), (y - 1) + i);//�������� ������� ��� ���
			printf(" ");
		}
	}
}

void showMenu(int pos)
{
	int i;

	for (i = 0; i < MENU_SIZE; i++)
	{
		gotoxy(MENU_X, MENU_Y + i);

		if (i == pos)
		{
			setcolor(LightGreen);
		}
		else
		{
			setcolor(White);
		}

		printf("%s", menu[i]);
	}
}

void game()
{
	srand(time(NULL));
	int isExit = 0;
	char stick = 0;
	int enemStep = 1, help = 0;
	DWORD ticks;

	DrawEnemy(X_POS_ENEMY, Y_POS_ENEMY);
	DrawPacManLR(0, 0, X_POS_PM, Y_POS_PM);

	while (isExit == 0 && (X_POS_ENEMY != X_POS_PM || (Y_POS_PM - Y_POS_ENEMY) >= 3 && (Y_POS_PM - Y_POS_ENEMY) >= -3 || ((Y_POS_ENEMY - Y_POS_PM) >= 3 && (Y_POS_ENEMY - Y_POS_PM) >= -3))) // ������� ���������
	{
		if (X_POS_ENEMY == (BORDER_LEFT + 3) && (Y_POS_ENEMY == (HORISON_WALL_1 - 9)))
		{
			help = 1 + rand() % 2;

			switch (help)
			{
			case 1: enemStep = ENEM_DOWN;
				break;

			case 2: enemStep = ENEM_DOWN;
				break;
			}
		}

		if (X_POS_ENEMY == (BORDER_LEFT + 3) && (Y_POS_ENEMY == (HORISON_WALL_2 - 9)))
		{
			help = 1 + rand() % 3;

			switch (help)
			{
			case 1: enemStep = ENEM_RIGHT;
				break;

			case 2: enemStep = ENEM_UP;
				break;

			case 3: enemStep = ENEM_DOWN;
				break;
			}
		}

		if (X_POS_ENEMY == (BORDER_LEFT + 3) && (Y_POS_ENEMY == (HORISON_WALL_3 - 9)))
		{
			help = 1 + rand() % 3;

			switch (help)
			{
			case 1: enemStep = ENEM_RIGHT;
				break;

			case 2: enemStep = ENEM_UP;
				break;

			case 3: enemStep = ENEM_DOWN;
				break;
			}
		}

		if (X_POS_ENEMY == (BORDER_LEFT + 3) && (Y_POS_ENEMY == (HORISON_WALL_4 - 9)))
		{
			help = 1 + rand() % 3;

			switch (help)
			{
			case 1: enemStep = ENEM_RIGHT;
				break;

			case 2: enemStep = ENEM_UP;
				break;

			case 3: enemStep = ENEM_DOWN;
				break;
			}
		}

		if (X_POS_ENEMY == (BORDER_LEFT + 3) && (Y_POS_ENEMY == (HORISON_WALL_5 + 1)))
		{
			help = 1 + rand() % 2;

			switch (help)
			{
			case 1: enemStep = ENEM_RIGHT;
				break;

			case 2: enemStep = ENEM_UP;
				break;
			}
		}

		//------------------------------------------------------------������ �������---------------------------------------

		if (X_POS_ENEMY == (BORDER_RIGHT - 8) && (Y_POS_ENEMY == (HORISON_WALL_1 - 9)))
		{
			help = 1 + rand() % 2;

			switch (help)
			{
			case 1: enemStep = ENEM_LEFT;
				break;

			case 2: enemStep = ENEM_DOWN;
				break;
			}
		}

		if (X_POS_ENEMY == (BORDER_RIGHT - 8) && (Y_POS_ENEMY == (HORISON_WALL_2 - 9)))
		{
			help = 1 + rand() % 3;

			switch (help)
			{
			case 1: enemStep = ENEM_LEFT;
				break;

			case 2: enemStep = ENEM_UP;
				break;

			case 3: enemStep = ENEM_DOWN;
				break;
			}
		}

		if (X_POS_ENEMY == (BORDER_RIGHT - 8) && (Y_POS_ENEMY == (HORISON_WALL_3 - 9)))
		{
			help = 1 + rand() % 3;

			switch (help)
			{
			case 1: enemStep = ENEM_LEFT;
				break;

			case 2: enemStep = ENEM_UP;
				break;

			case 3: enemStep = ENEM_DOWN;
				break;
			}
		}

		if (X_POS_ENEMY == (BORDER_RIGHT - 8) && (Y_POS_ENEMY == (HORISON_WALL_4 - 9)))
		{
			help = 1 + rand() % 3;

			switch (help)
			{
			case 1: enemStep = ENEM_LEFT;
				break;

			case 2: enemStep = ENEM_UP;
				break;

			case 3: enemStep = ENEM_DOWN;
				break;
			}
		}

		if (X_POS_ENEMY == (BORDER_RIGHT - 8) && (Y_POS_ENEMY == (HORISON_WALL_5 + 1)))
		{
			help = 1 + rand() % 2;

			switch (help)
			{
			case 1: enemStep = ENEM_LEFT;
				break;

			case 2: enemStep = ENEM_UP;
				break;


			}
		}

		switch (enemStep)
		{
		case ENEM_LEFT://�����
			if ((X_POS_ENEMY > (BORDER_LEFT + 3) && (Y_POS_ENEMY < (HORISON_WALL_1 - 8))     // ������� ������ ���������� ����.
				|| X_POS_ENEMY > (BORDER_LEFT + 3) && (Y_POS_ENEMY > (HORISON_WALL_1 + 1)))

				&& (X_POS_ENEMY > (BORDER_LEFT + 3) && (Y_POS_ENEMY < (HORISON_WALL_2 - 8))
					|| X_POS_ENEMY > (BORDER_LEFT + 3) && (Y_POS_ENEMY > (HORISON_WALL_2 + 1)))

				&& (X_POS_ENEMY > (BORDER_LEFT + 3) && (Y_POS_ENEMY < (HORISON_WALL_3 - 8))
					|| X_POS_ENEMY > (BORDER_LEFT + 3) && (Y_POS_ENEMY > (HORISON_WALL_3 + 1)))

				&& (X_POS_ENEMY > (BORDER_LEFT + 3) && (Y_POS_ENEMY < (HORISON_WALL_4 - 8))
					|| X_POS_ENEMY > (BORDER_LEFT + 3) && (Y_POS_ENEMY > (HORISON_WALL_4 + 1))))
			{
				EraseEnemy(X_POS_ENEMY, Y_POS_ENEMY);
				DrawEnemy(X_POS_ENEMY, Y_POS_ENEMY);
				X_POS_ENEMY--;
			}
			break;

		case ENEM_RIGHT://������
			if ((X_POS_ENEMY < (BORDER_RIGHT - 8) && (Y_POS_ENEMY < (HORISON_WALL_1 - 8))     // ������� ������ ���������� ����.
				|| X_POS_ENEMY < (BORDER_RIGHT - 8) && (Y_POS_ENEMY > (HORISON_WALL_1 + 1)))

				&& (X_POS_ENEMY < (BORDER_RIGHT - 8) && (Y_POS_ENEMY < (HORISON_WALL_2 - 8))
					|| X_POS_ENEMY < (BORDER_RIGHT - 8) && (Y_POS_ENEMY > (HORISON_WALL_2 + 1)))

				&& (X_POS_ENEMY < (BORDER_RIGHT - 8) && (Y_POS_ENEMY < (HORISON_WALL_3 - 8))
					|| X_POS_ENEMY < (BORDER_RIGHT - 8) && (Y_POS_ENEMY > (HORISON_WALL_3 + 1)))

				&& (X_POS_ENEMY < (BORDER_RIGHT - 8) && (Y_POS_ENEMY < (HORISON_WALL_4 - 8))
					|| X_POS_ENEMY < (BORDER_RIGHT - 8) && (Y_POS_ENEMY > (HORISON_WALL_4 + 1))))

			{
				EraseEnemy(X_POS_ENEMY, Y_POS_ENEMY);
				DrawEnemy(X_POS_ENEMY, Y_POS_ENEMY);
				X_POS_ENEMY++;
			}
			break;

		case ENEM_UP://�����
			if (Y_POS_ENEMY > (BORDER_UPPER + 3) && (X_POS_ENEMY < (BORDER_LEFT + 10))        // ������� ��� ��������� ����� �������������� �����
				|| (Y_POS_ENEMY > (BORDER_UPPER + 3) && (X_POS_ENEMY > (BORDER_RIGHT - 15))))
			{
				EraseEnemy(X_POS_ENEMY, Y_POS_ENEMY);
				DrawEnemy(X_POS_ENEMY, Y_POS_ENEMY);
				Y_POS_ENEMY--;
			}
			break;

		case ENEM_DOWN://����
			if (Y_POS_ENEMY < (BORDER_DOWN - 8) && (X_POS_ENEMY < (BORDER_LEFT + 10))         // ������� ��� ��������� ����� �������������� �����
				|| (Y_POS_ENEMY < (BORDER_DOWN - 8) && (X_POS_ENEMY > (BORDER_RIGHT - 15))))
			{
				EraseEnemy(X_POS_ENEMY, Y_POS_ENEMY);
				DrawEnemy(X_POS_ENEMY, Y_POS_ENEMY);
				Y_POS_ENEMY++;
			}
			break;
		}


		ticks = GetTickCount();
		while (GetTickCount() - ticks < 20)//������������ ���������� ���������� �����
		{
			if (_kbhit())   // ��������� ��������
			{
				stick = _getch();

				switch (stick)
				{
				case LEFT:
					if ((X_POS_PM > (BORDER_LEFT + 3) && (Y_POS_PM < (HORISON_WALL_1 - 8))     // ������� ������ ���������� ����.
						|| X_POS_PM > (BORDER_LEFT + 3) && (Y_POS_PM > (HORISON_WALL_1 + 1)))

						&& (X_POS_PM > (BORDER_LEFT + 3) && (Y_POS_PM < (HORISON_WALL_2 - 8))
							|| X_POS_PM > (BORDER_LEFT + 3) && (Y_POS_PM > (HORISON_WALL_2 + 1)))

						&& (X_POS_PM > (BORDER_LEFT + 3) && (Y_POS_PM < (HORISON_WALL_3 - 8))
							|| X_POS_PM > (BORDER_LEFT + 3) && (Y_POS_PM > (HORISON_WALL_3 + 1)))

						&& (X_POS_PM > (BORDER_LEFT + 3) && (Y_POS_PM < (HORISON_WALL_4 - 8))
							|| X_POS_PM > (BORDER_LEFT + 3) && (Y_POS_PM > (HORISON_WALL_4 + 1))))
					{
						ErasePacMan(X_POS_PM, Y_POS_PM);
						PacManRunLeft(X_POS_PM, Y_POS_PM, 1);
						X_POS_PM--;
					}
					break;

				case RIGHT:
					if ((X_POS_PM < (BORDER_RIGHT - 8) && (Y_POS_PM < (HORISON_WALL_1 - 8))     // ������� ������ ���������� ����.
						|| X_POS_PM < (BORDER_RIGHT - 8) && (Y_POS_PM > (HORISON_WALL_1 + 1)))

						&& (X_POS_PM < (BORDER_RIGHT - 8) && (Y_POS_PM < (HORISON_WALL_2 - 8))
							|| X_POS_PM < (BORDER_RIGHT - 8) && (Y_POS_PM > (HORISON_WALL_2 + 1)))

						&& (X_POS_PM < (BORDER_RIGHT - 8) && (Y_POS_PM < (HORISON_WALL_3 - 8))
							|| X_POS_PM < (BORDER_RIGHT - 8) && (Y_POS_PM > (HORISON_WALL_3 + 1)))

						&& (X_POS_PM < (BORDER_RIGHT - 8) && (Y_POS_PM < (HORISON_WALL_4 - 8))
							|| X_POS_PM < (BORDER_RIGHT - 8) && (Y_POS_PM > (HORISON_WALL_4 + 1))))

					{
						ErasePacMan(X_POS_PM, Y_POS_PM);
						PacManRunRight(X_POS_PM, Y_POS_PM, 1);
						X_POS_PM++;
					}
					break;

				case UP:
					if (Y_POS_PM > (BORDER_UPPER + 3) && (X_POS_PM < (BORDER_LEFT + 10))        // ������� ��� ��������� ����� �������������� �����
						|| (Y_POS_PM > (BORDER_UPPER + 3) && (X_POS_PM > (BORDER_RIGHT - 15))))
					{
						ErasePacMan(X_POS_PM, Y_POS_PM);
						PacManRunUp(X_POS_PM, Y_POS_PM, 1);
						Y_POS_PM--;
					}
					break;

				case DOWN:
					if (Y_POS_PM < (BORDER_DOWN - 8) && (X_POS_PM < (BORDER_LEFT + 8))         // ������� ��� ��������� ����� �������������� �����
						|| (Y_POS_PM < (BORDER_DOWN - 8) && (X_POS_PM > (BORDER_RIGHT - 15))))
					{
						ErasePacMan(X_POS_PM, Y_POS_PM);
						PacManRunDown(X_POS_PM, Y_POS_PM, 1);
						Y_POS_PM++;
					}
					break;

				case ESC:
					isExit = 1;
					break;
				}
			}
		}
	}
}
void options()
{

}

void main()
{
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cursorHide();

	system("mode con cols=220 lines=65");

	int pos = 0;
	int isExit = 0;
	char ch;

	while (!isExit)
	{
		showMenu(pos);
		ch = _getch();

		switch (ch)
		{
		case ESC:isExit = 1; break;
		case UP:
			if (pos > 0)
			{
				pos--;
			}
			break;
		case DOWN:
			if (pos < MENU_SIZE - 1)
			{
				pos++;
			}
			break;
		case ENTER:
			switch (pos)
			{
			case MENU_NEW_GAME: system("cls"); DrawGameArea(); DrawAreaFilling(); DrawAreaPrise(); game(); system("cls"); break;
			case MENU_OPTIONS: options(); break;
			case MENU_EXIT: isExit = 1; break;
			}
			break;
		}
	}
	_getch();
	setcolor(White);
}
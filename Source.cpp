#include <windows.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>

#pragma warning(disable : 4996)

using namespace std;

#define KEY_ARROW_UP 72
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75
enum direction { RIGHT, LEFT, UP, DOWN };

int x = 9;
int y = 9;
int e = 0;
int ship = 0;
int user = 0;
int esc = 0;


SHORT xx = 1, yy = 0;
int a[14][14];
int n = 24;
int score = 1;
DWORD cWrittenChars = 0;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

struct Pos {
	int x, y;
};

struct Player {
	char* name;
	int scor;
};

Player pl[100];
int pln = 0;

void Setup();
void Table();
Pos Cursor();
void Enter(SHORT x, SHORT y);

void OkrasLogoVirus(char map[][57]);
void CursorVisible();
void printStuff(int x, int y);
void ConsoleWindow();
void OkrasMenu(string vibor, int color);
void funcBeckShip(char map[][19], int button1, int a, int b);
void LogoVirus();
void fViborVirus(int count);

void OkrasField(char map[][19], int color1, int color2, int color3, int color4, int color5, int color6, int x);
void OkrasAutorAndInstr(char map[][70], int color, int str);
void changFont();
void menuBeckShip(string ship);
void moveField(char map[][19], int but);
void mapAutor();
void mapInstr();
void drawingShips(char map[][19], int but);
void eliminationSticking(char map[][19]);
void winn(int numWin);
void outlineAroundShipInsaid(char map2[][19], int ship, int numShip);
void outlineAroundShip(char map1[][19], char map2[][19], int ship);

void main() {
	ConsoleWindow();

menuGameAgain:

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	CursorVisible();
	changFont();

	int viborVirus = 0;
	int buttonVirus1 = 0;
	int buttonVirus2 = 0;

	LogoVirus();

	do
	{
		if (buttonVirus2 == 80 || viborVirus == 0) {
			if (viborVirus < 4 && viborVirus != 0) {
				++viborVirus;
			}
			else {
				viborVirus = 1;
			}

			fViborVirus(viborVirus); // Покраска выбранного меню
			buttonVirus1 = _getch(); // считывание нажатия клавиши

			if (buttonVirus1 == 13) {
				printStuff(0, 12);
				break;
			}
			else if (buttonVirus1 == 27) {
				system("cls");
				x = 21;
				y = 9;
				ship = 0;
				user = 0;
				esc = 0;
				goto menuGameAgain;
			}
			else if (buttonVirus1 != 224) {
				viborVirus = 0;
				printStuff(0, 12);
				continue;
			}

			buttonVirus2 = _getch(); // считывание нажатия клавиши

			if (buttonVirus2 == 77 || buttonVirus2 == 75) {
				viborVirus = 0;
				printStuff(0, 12);
				continue;
			}
			printStuff(0, 12);
		}
		else if (buttonVirus2 == 72) {
			if (viborVirus <= 4 && viborVirus > 1) {
				--viborVirus;
			}
			else {
				viborVirus = 4;
			}

			fViborVirus(viborVirus); // Покраска выбранного меню
			buttonVirus1 = _getch(); // считывание нажатия клавиши

			if (buttonVirus1 == 13) {
				printStuff(0, 12);
				break;
			}
			else if (buttonVirus1 == 27) {
				system("cls");
				x = 21;
				y = 9;
				ship = 0;
				user = 0;
				esc = 0;
				goto menuGameAgain;
			}
			else if (buttonVirus1 != 224) {
				viborVirus = 0;
				printStuff(0, 12);
				continue;
			}

			buttonVirus2 = _getch(); // считывание нажатия клавиши

			if (buttonVirus2 == 77 || buttonVirus2 == 75) {
				viborVirus = 0;
				printStuff(0, 12);
				continue;
			}
			printStuff(0, 12);
		}
	} while (true);

	system("cls");

	if (viborVirus == 1)
	{
		xx = 1;
		yy = 0;
		Setup();
		Table();
		while (n > 0) {
			Pos p = Cursor();
			Enter(p.x, p.y);
			n--;
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(hStdOut, { 0, 14 });
			cout << "Очки: " << score << endl;
			cout << "Залишок ходів: " << n << " " << endl;
		}

		cout << endl;
		cout << "Введіть своє ім'я" << endl;
		char* name = new char[5];
		cin >> name;

		FILE* fp = fopen("Текст.txt", "a");

		fprintf(fp, "%s %d\n", name, score);
		fclose(fp);

		n = 24;
		score = 1;
		cWrittenChars = 0;
		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		pln = 0;
		system("cls");
		goto menuGameAgain;
	}
	else if (viborVirus == 2) {
		do {
			system("cls");
			LogoVirus();
			mapInstr();

			int butt = _getch();

			if (butt == 27) {
				esc = 1;
			}
		} while (esc == 0);

		if (esc == 1) {
			system("cls");
			x = 9;
			y = 9;
			ship = 0;
			user = 0;
			esc = 0;
			goto menuGameAgain;
		}
	}
	else if (viborVirus == 3) {
		system("cls");
		int butt;

		LogoVirus();

		do {
			mapAutor();

			if (_kbhit()) {
				butt = _getch();
				if (butt == 27) {
					break;
				}
			}
		} while (true);

		system("cls");
		x = 9;
		y = 9;
		ship = 0;
		user = 0;
		esc = 0;
		goto menuGameAgain;
	}
}

void Setup() {
	srand(time(0));
	system("CLS");

	for (int i = 1; i <= 14; i++) {
		for (int j = 1; j <= 14; j++) {
			if ((i == 1) && (j == 1)) {
				SetConsoleTextAttribute(hStdOut, 15);
				a[i - 1][j - 1] = 15;
			}
			else {
				int k = (((rand() % 6) + 1) * 16) + 15;
				HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hStdOut, k);
				a[i - 1][j - 1] = k;
			}
			cout << "   ";
		}
		cout << endl;
	}
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 15);
	cout << "Score: " << score << endl;
	cout << n << endl;
}

void Table() {
	FILE* fp = fopen("Текст.txt", "r");
	char* name = new char[5];
	int scor = 0;
	int k = 0;
	while (!feof(fp)) {
		if (k == 1) {
			pl[pln].scor = scor;
			pl[pln].name = new char[strlen(name) + 1];
			strcpy(pl[pln].name, name);
			pln++;
		}
		fscanf(fp, "%s %d", name, &scor);
		k = 1;
	}
	int temp1;
	char* temp2;
	for (int i = 0; i < pln - 1; i++) {
		for (int j = 0; j < pln - i - 1; j++) {
			if (pl[j].scor < pl[j + 1].scor) {
				// меняем элементы местами
				temp1 = pl[j].scor;
				pl[j].scor = pl[j + 1].scor;
				pl[j + 1].scor = temp1;
				temp2 = pl[j].name;
				pl[j].name = pl[j + 1].name;
				pl[j + 1].name = temp2;
			}
		}
	}

	for (short i = 0; i < 10; i++) {
		SetConsoleCursorPosition(hStdOut, { 50, i });
		printf("%-8s - %d", pl[i].name, pl[i].scor);
	}
}

Pos Cursor() {
	int k = 0, x1, y1;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	FillConsoleOutputCharacter(hStdOut, (TCHAR)'X', 1, { xx, yy }, &cWrittenChars);
	int iKey = 67;
	while (k == 0)
	{
		k = 0;
		iKey = 67;
		while ((iKey != 13))
		{
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			if (_kbhit())
			{
				iKey = _getch();
				switch (iKey)
				{
				case KEY_ARROW_UP:
					if (yy != 0) {
						FillConsoleOutputCharacter(hStdOut, (TCHAR)'X', 1, { xx, yy - 1 }, &cWrittenChars);
						FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', 1, { xx, yy }, &cWrittenChars);
						yy--;
					}
					break;

				case KEY_ARROW_DOWN:
					if (yy != 13) {
						FillConsoleOutputCharacter(hStdOut, (TCHAR)'X', 1, { xx, yy + 1 }, &cWrittenChars);
						FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', 1, { xx, yy }, &cWrittenChars);
						yy++;
					}
					break;

				case KEY_ARROW_LEFT:
					if (xx != 1) {
						FillConsoleOutputCharacter(hStdOut, (TCHAR)'X', 1, { xx - 3, yy }, &cWrittenChars);
						FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', 1, { xx, yy }, &cWrittenChars);
						xx -= 3;
					}
					break;

				case KEY_ARROW_RIGHT:
					if (xx != 40) {
						FillConsoleOutputCharacter(hStdOut, (TCHAR)'X', 1, { xx + 3, yy }, &cWrittenChars);
						FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', 1, { xx, yy }, &cWrittenChars);
						xx += 3;
					}
					break;
				}
			}
		}
		if (a[yy][(xx - 1) / 3] != 15) {
			if (a[yy - 1][(xx - 1) / 3] == 15)
			{
				k = 1;
			}
			else {
				if (a[yy + 1][(xx - 1) / 3] == 15)
				{
					k = 1;
				}
				else {
					if (a[yy][((xx - 1) / 3) - 1] == 15)
					{
						k = 1;
					}
					else {
						if (a[yy][((xx - 1) / 3) + 1] == 15)
						{
							k = 1;
						}
					}
				}
			}
		}
	}
	Pos p;
	p.x = xx;
	p.y = yy;
	FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', 1, { xx, yy }, &cWrittenChars);
	return p;
}

void Enter(SHORT x, SHORT y) {
	DWORD cWrittenChars = 0;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	FillConsoleOutputAttribute(hStdOut, 15, 3, { x - 1, y }, &cWrittenChars);
	score++;
	int k = a[y][(x - 1) / 3];
	a[y][(x - 1) / 3] = 15;
	if (k == a[y - 1][(x - 1) / 3])
	{
		Enter(x, y - 1);
	}
	if (k == a[y + 1][(x - 1) / 3])
	{
		Enter(x, y + 1);
	}
	if (k == a[y][((x - 1) / 3) - 1])
	{
		Enter(x - 3, y);
	}
	if (k == a[y][((x - 1) / 3) + 1])
	{
		Enter(x + 3, y);
	}
}

void ConsoleWindow() { // Размер окна консоли и его отображение
	HWND window_header = GetConsoleWindow();
	SetWindowPos(window_header, HWND_TOP, 100, 100, 600, 600, NULL);
}

void CursorVisible() {// Скрыть видимость курсора
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// Получение дескриптора устройства стандартного вывода
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hConsole, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &structCursorInfo);
}

void changFont() { // Смена шрифта  + размер шрифта
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 16;                   // Width of each character in the font
	cfi.dwFontSize.Y = 16;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Lucida Console"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void OkrasLogoVirus(char map[][57]) {// цвет логотипа
	HANDLE consoleOutput;
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < 12; i++) {
		SetConsoleTextAttribute(consoleOutput, 12); //Перед строкой для выделения текста цветом 
		cout << "\t" << map[i] << endl;
		SetConsoleTextAttribute(consoleOutput, 15); //Возвращаем назад цвет
	}
}

inline void LogoVirus() { // Логотип морского боя
	char mapLogo[56][57] = {
		"  8888888888888888888888888888888888888888888888888888",
		"  8888888888888888888888888888888888888888888888888888",
		"         $$  $$  $$$$$$  $$$$$   $$  $$   $$$$         ",
		"         $$  $$    $$    $$  $$  $$  $$  $$            ",
		"         $$  $$    $$    $$$$$   $$  $$   $$$$         ",
		"          $$$$     $$    $$  $$  $$  $$      $$        ",
		"           $$    $$$$$$  $$  $$   $$$$    $$$$			",
		"  8888888888888888888888888888888888888888888888888888",
		"  8888888888888888888888888888888888888888888888888888",
	};
	OkrasLogoVirus(mapLogo);
}

void OkrasMenu(string vibor, int color) {  // Окрашивание меню
	HANDLE consoleOutput;
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(consoleOutput, color); //Перед строкой для выделения текста цветом
	cout << vibor;
	SetConsoleTextAttribute(consoleOutput, 15); //Возвращаем назад цвет
}

void fViborVirus(int count) { // Передвижение по меню Морской бой
	string oneVibor = " 1. ГРАТИ ";
	string twoVibor = " 2. ПРАВИЛА ";
	string threeVibor = " 3. АВТОР ";
	string fourVibor = " 4. ВИХІД ";

	int a1 = 12;
	int a2 = 12;
	int a3 = 12;
	int a4 = 12;

	if (count == 1)
		a1 = 15;
	else if (count == 2)
		a2 = 15;
	else if (count == 3)
		a3 = 15;
	else if (count == 4)
		a4 = 15;

	cout << endl; cout << endl;
	cout << "\t\t\t\t"; OkrasMenu(oneVibor, a1); cout << endl; cout << endl;
	cout << "\t\t\t\t"; OkrasMenu(twoVibor, a2); cout << endl; cout << endl;
	cout << "\t\t\t\t"; OkrasMenu(threeVibor, a3); cout << endl; cout << endl;
	cout << "\t\t\t\t"; OkrasMenu(fourVibor, a4); cout << endl; cout << endl;
}

void printStuff(int x, int y) {
	// Sleep(95);
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(hd, cd);
}

void OkrasAutorAndInstr(char map[][70], int color, int str) {// Окрашивание пункта Автор
	HANDLE consoleOutput;
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < str; i++) {
		for (int j = 0; j < 70; j++) {
			SetConsoleTextAttribute(consoleOutput, color); //Перед строкой для выделения текста цветом
			cout << map[i][j];
			SetConsoleTextAttribute(consoleOutput, 15); //Возвращаем назад цвет
		}
		cout << endl;
		Sleep(10);
	}
}

void mapInstr() {// Функция меню описания
	char map[18][70]
	{
	"                                     ПРАВИЛА ГРИ",
	"        ",
	"        ",
	"        Мета гри заразити, тобто зафарбувати в чорне,",
	"        як умога більше клітинок за 24 ходи",
	"        ",
	"        Зафарбовувати можна лише сусідні ",
	"        до уже зафарбованих клітинок,",
	"        при цьому зафарбовується весь блок",
	"        з суміжних однокольорових клітинок",
	"        ",
	"        Щоб зафарбувати клітинку наведіть на неї курсор",
	"        за допомогою клавіш-стрілок та натисніть Enter",
	"        ",
	"        Після завершення гри введіть своє ім'я,",
	"        воно буде внесено в таблицю рекордів",
	"        ",
	"        Гарної гри!",
	};
	printStuff(0, 12);
	OkrasAutorAndInstr(map, 6, 18);
}

void mapAutor() {// Функция отображения автора
	char map[70][70] = {
"	  ##  ## ##  ## #####  ##  ##    ### ##  ##  ##  ##",
"	  ## ##   ## ## ##  ## ##  ##   # ## ## #  # ## ##",
"	  ####     #### ###### ## ###  #  ## ##### # ####",
"	  ## ##      ## ##     ### ## ##  ## ## #  # ## ##",
"	  ##  ##   ###  ##     ##  ## ##  ## ##  ##  ##  ##",
"	",
"			   #####   ####  ##   ##  ####  ##  ##",
"			   ##  ## ##  ## ### ### ##  ## ##  ##",
"			   ###### ##  ## ## # ## ###### ######",
"			   ##     ##  ## ##   ## ##  ## ##  ##",
"			   ##      ####  ##   ## ##  ## ##  ##",
	};
	printStuff(0, 15);
	OkrasAutorAndInstr(map, 12, 11);
	printStuff(0, 15);
	OkrasAutorAndInstr(map, 6, 11);
	printStuff(0, 15);
	OkrasAutorAndInstr(map, 14, 11);
	printStuff(0, 15);
	OkrasAutorAndInstr(map, 10, 11);
	printStuff(0, 15);
	OkrasAutorAndInstr(map, 11, 11);
	printStuff(0, 15);
	OkrasAutorAndInstr(map, 9, 11);
	printStuff(0, 15);
	OkrasAutorAndInstr(map, 13, 11);
	printStuff(0, 15);
}

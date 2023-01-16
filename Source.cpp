#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include<fstream>

using namespace std;
int n = 18, m = 12;//player index
int i = 18, j = 7;//enemy index
int lives = 3, score = 0;
bool flag = true;
int speed = 500;
void player(char arr[][20]);
void menu(char arr[][20]);

void addscore()//function for highscores
{
	ifstream input;
	input.open("text.txt");
	int s_arr[10], update = 0;
	while (!input.eof())
	{
		for (int I = 0; I < 10; I++)
		{
			input >> s_arr[I];
		}
	}
	input.close();
	for (int k = 0; k < 10; k++)
	{
		cout << s_arr[k] << endl;
	}
	for (int m = 0; m < 10; m++)
	{
		if (score > s_arr[m])
		{
			s_arr[m] = score;
			break;
		}
	}
	cout << endl;
	
	ofstream output;
	output.open("text.txt");
	for (int j = 0; j < 10; j++)
	{
		output << s_arr[j] << endl;
	}
	output.close();
}

void cursor()
{

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);

}

void display(char arr[][20])//function to display the arr on console
{
	cursor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
	cout << "\t\t score = " << score << "\tLives: " << lives << endl;
	for (int i = 0; i < 20; i++)
	{
		cout << "\t\t";
		for (int j = 0; j < 20; j++)
		{
			cout << " " << arr[i][j] << " ";
		}
		cout << endl;
	}
	system("color 6");//it is at the end so that when ever the color chanages to red when life is deducted it will go back to orange 
}

void board(char arr[][20])
{
	//background
	for (int i = 0; i < 20; i++)//first initialize with a dot
	{
		for (int j = 0; j < 20; j++)
		{
			arr[i][j] = '.';
		}
	}
	for (int i = 0; i < 20; i++) //outside border
	{
		arr[i][0] = '*';
		arr[i][19] = '*';
		arr[0][i] = '*';
		arr[19][i] = '*';
	}
	for (int i = 2; i < 18; i++)//2nd border
	{
		arr[i][2] = '*';
		arr[i][17] = '*';
		arr[2][i] = '*';
		arr[17][i] = '*';
	}
	for (int i = 4; i < 16; i++)//3rd border
	{
		arr[i][4] = '*';
		arr[i][15] = '*';
		arr[4][i] = '*';
		arr[15][i] = '*';
	}
	for (int i = 6; i < 14; i++)//forth border
	{
		arr[i][6] = '*';
		arr[i][13] = '*';
		arr[6][i] = '*';
		arr[13][i] = '*';
	}

	for (int i = 8; i <= 11; i++)//removing the part where there is blank
	{
		for (int j = 0; j < 20; j++)
		{
			arr[i][j] = ' ';
			arr[j][i] = ' ';
		}
	}
	for (int i = 8; i <= 11; i++)//adding the inside box
	{
		arr[i][7] = '*';
		arr[i][12] = '*';
		arr[8][i] = '*';
		arr[11][i] = '*';
	}
	//making dots as score 
	//it should be with one index left blank and dot on the next
	for (int i = 1; i < 19; i += 2)//for first path
	{
		arr[i][1] = ' ';
		arr[i][18] = ' ';
		arr[1][i] = ' ';
		arr[18][i] = ' ';
	}
	for (int i = 3; i < 17; i += 2)//2nd path
	{
		arr[i][3] = ' ';
		arr[i][16] = ' ';
		arr[3][i] = ' ';
		arr[16][i] = ' ';
	}
	for (int i = 5; i < 15; i += 2)//3rd path
	{
		arr[i][5] = ' ';
		arr[i][14] = ' ';
		arr[5][i] = ' ';
		arr[14][i] = ' ';
	}
	//central box
	for (int i = 8; i < 12; i++)
	{
		arr[i][7] = ' ';
	}
	for (int i = 8; i < 12; i++)
	{
		arr[i][12] = ' ';
	}
	for (int i = 9; i < 11; i++)
	{
		arr[i][8] = '*';
	}
	for (int i = 9; i < 11; i++)
	{
		arr[i][8] = '*';
	}
	for (int i = 9; i < 11; i++)
	{
		arr[i][11] = '*';
	}

}

//these will be called for each input (w a s d) form imput function
void up(char arr[][20])//w 
{
	if (n - 1 > 0) {
		if (arr[n - 1][m] != '*') {
			n--;
			arr[n + 1][m] = ' ';
		}
		if (arr[n][m] == '.') {//score counter
			score++;
		}
	}
}
void down(char arr[][20])//s
{
	if (n + 1 < 19) {
		if (arr[n + 1][m] != '*') {
			n++;
			arr[n - 1][m] = ' ';
		}
		if (arr[n][m] == '.') {//score counter
			score++;
		}
	}
}
void left(char arr[][20])//a
{
	if (m - 1 > 0) {
		if (arr[n][m - 1] != '*') {
			m--;
			arr[n][m + 1] = ' ';
		}
		if (arr[n][m] == '.') {//score counter
			score++;
		}
	}
}
void right(char arr[][20])//d
{
	if (m + 1 < 19) {
		if (arr[n][m + 1] != '*') {
			m++;
			arr[n][m - 1] = ' ';
		}

		if (arr[n][m] == '.') {//score counter
			score++;
		}
	}
}


//these are for enemy
void oppdown(char arr[][20])
{
	char temp = ' ';


	if (arr[i + 1][j] != '*')
	{
		temp = arr[i + 1][j];
		if (temp == '@')
		{
			system("color 4");
			lives--;
			temp = ' ';
		}
		i++;
		arr[i - 1][j] = temp;

		arr[i][j] = '$';//enemy
		player(arr);
	}

}
void oppright(char arr[][20])
{
	char temp = ' ';
	if (arr[i][j + 1] != '*')
	{
		temp = arr[i][j + 1];
		if (temp == '@')
		{
			system("color 4");
			lives--;
			temp = ' ';
		}
		j++;
		arr[i][j - 1] = temp;

		arr[i][j] = '$';//enemy
		player(arr);
	}

}
void oppup(char arr[][20])
{
	char temp = ' ';

	if (arr[i - 1][j] != '*')
	{
		temp = arr[i - 1][j];
		if (temp == '@')
		{
			system("color 4");
			lives--;
			temp = ' ';
		}
		i--;
		arr[i + 1][j] = temp;

		arr[i][j] = '$';//enemy
		player(arr);
	}
}
void oppleft(char arr[][20])
{
	char temp = ' ';


	if (arr[i][j - 1] != '*')//a
	{

		temp = arr[i][j - 1];
		if (temp == '@')
		{
			system("color 4");
			lives--;
			temp = ' ';
		}
		j--;
		arr[i][j + 1] = temp;

		arr[i][j] = '$';//enemy
		player(arr);
	}

}


void oppmovement1(char arr[][20])
{
	if (lives == 0)//if game over output color will be red and game over will be printed on the screen
	{
		system("cls");
		system("color 4");
		cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tGAME OVER!123\n\n\n\n";
		Sleep(1000);
		flag = false;
		return;
	}
	while (i != 18 && j == 18)
	{
		oppdown(arr);
	}
	while (j != 1 && i != 1)
	{
		oppleft(arr);
	}

	while (i != 1)
	{
		oppup(arr);
	}
	while (j != 18)
	{
		oppright(arr);
	}
	Sleep(speed);
}
void oppmovement2(char arr[][20])
{
	while (i != 18 && j == 18)
	{
		oppdown(arr);
	}
	while (j != 1 && i != 1)
	{
		oppleft(arr);
	}

	while (i != 1)
	{
		oppup(arr);
	}
	while (j != 18)
	{
		oppright(arr);
	}
}



void input(char arr[][20])//this function will be uesd to take inputs from the user
{
	char input = _getch();

	if (input == 's') {//dowm
		
		down(arr);
	}
	else if (input == 'a') {//left
		
		left(arr);
	}
	else if (input == 'w') {//up
		
		up(arr);
	}
	else if (input == 'd') {//rigth
		
		right(arr);
	}
	else if (input == 'p') //game will be paused whenever p is pessed 
	{
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tGame Paused\n\n\n\n";
		Sleep(1000);
		menu(arr);
	}
}
void player(char arr[][20])
{
	static int l = 1;
	arr[n][m] = '@';//player

	while (lives > 0 && l < 5)
	{//while alive

		if (n > 9) {//lower half
			if ((arr[n][m + 1] == ' ' || arr[n][m + 1] == '.' || arr[n][m + 1] == '$') && (arr[n][m - 1] == ' ' || arr[n][m - 1] == '.') && arr[n + 1][m] == '*' && arr[n - 1][m] == '*' || (n == 14 && m == 5) || (n == 16 && m == 3) || (n == 18 && m == 1)) {//if its in a path
				m++;
				if (arr[n][m] == '.') {//score counter
					score++;
				}
				else if (arr[n][m] == '$') {//meet opponent
					lives--;
					system("color 4");
				}
				arr[n][m] = '@';
				arr[n][m - 1] = ' ';
				display(arr);
			}
		}
		else // upperhalf
		{
			if ((arr[n][m + 1] == ' ' || arr[n][m + 1] == '.') && (arr[n][m - 1] == ' ' || arr[n][m - 1] == '.' || arr[n][m - 1] == '$') && arr[n + 1][m] == '*' && arr[n - 1][m] == '*' || (n == 1 && m == 18) || (n == 3 && m == 16) || (n == 5 && m == 14)) {
				m--;
				if (arr[n][m] == '.') {//score counter
					score++;
				}
				else if (arr[n][m] == '$') {//meet opponent
					lives--;
					system("color 4");
				}
				arr[n][m] = '@';
				arr[n][m + 1] = ' ';
				display(arr);
			}
		}
		if (m > 13) {//rigth half
			if (arr[n][m - 1] == '*' && (arr[n][m + 1] == '*' || arr[n][m + 1] == ' ') && (arr[n - 1][m] == ' ' || arr[n - 1][m] == '.' || arr[n - 1][m] == '$') && (arr[n + 1][m] == ' ' || arr[n + 1][m] == '.') || (n == 16 && m == 16) /*|| n == 18 && m == 18*/ || (n == 14 && m == 14))
			{
				for (int l = 0; l < 2; l++) {
					n--;
					if (arr[n][m] == '.') {//score counter
						score++;
					}
					else if (arr[n][m] == '$') {//meet opponent
						lives--;
						system("color 4");
					}
					arr[n][m] = '@';
					if (arr[n + 1][m] != '*') {
						arr[n + 1][m] = ' ';
					}
					display(arr);
				}
			}
			else if (n == 18 && m == 18 || arr[n - 1][m] == '$')//for bottom-rigth corner
			{
				n--;
				if (arr[n][m] == '.') {//score counter
					score++;
				}
				else if (arr[n][m] == '$') {//meet opponent
					lives--;
					system("color 4");
				}
				arr[n][m] = '@';
				if (arr[n + 1][m] != '*') {
					arr[n + 1][m] = ' ';
				}
				display(arr);
			}
		}
		else if (m < 7)//left half
		{
			for (int l = 0; l < 2; l++) 
			{
				if ((arr[n][m + 1] == '*' || arr[n][m + 1] == ' ') && arr[n][m - 1] == '*' && (arr[n + 1][m] == ' ' || arr[n + 1][m] == '.' || arr[n + 1][m] == '$') && (arr[n - 1][m] == ' ' || arr[n - 1][m] == '.') || (n == 1 && m == 1) || (m == 3 && n == 3) || (n == 5 && m == 5))
				{
					n++;
					if (arr[n][m] == '.')//score counter
					{
						score++;
					}
					else if (arr[n][m] == '$') //meet opponent
					{
						lives--;
						system("color 4");
					}
					arr[n][m] = '@';
					if (arr[n - 1][m] != '*') {
						arr[n - 1][m] = ' ';
					}
					display(arr);
				}
			}
		}
		if (arr[n + 1][m] == ' ' && arr[n - 1][m] == ' ' || n == 11 || n == 8 || n == 0 || m == 0 || (n >= 7 && n <= 12 && m >= 7 && m <= 12)) 
		{
			input(arr);
		}
		if (score == 50) {//total score is 50 thus win at 50 score
			system("cls");
			system("color 2");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tWINNER!!!\n\n\n";
			Sleep(1000);
			l++;
			if (l > 4) {
				system("color 5");
				cout << "\t\t\tCongratulations you have completed the game have a cupcake\n\n\n\n\n";
				system("pause");
				break;
			}
			system("cls");
			system("color 3");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tlevel " << l << "\n\n\n\n";
			Sleep(1000);
			board(arr);
			i = 18; j = 7; n = 18; m = 12;
			score = 0;
			speed -= 125;
			arr[i][j] = '$';//enemy
			arr[n][m] = '@';//player
			display(arr);
			player(arr);
			flag = false;
			break;
		}
		arr[n][m] = '@';//player
		display(arr); 
		if (j == 3 && i <= 16 && i >= 3 || (i == 3 && (j >= 3 && j <= 16)) || (j == 16 && (i >= 3 && i <= 16)))
		{
			oppmovement2(arr);
		}
		else
		{
			oppmovement1(arr);
		}
		if (lives == 0)//if game over output color will be red and game over will be printed on the screen
		{
			system("cls");
			system("color 4");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tGAME OVER!\n\n\n\n";
			Sleep(1000);
			flag = false;
			break;
		}
	}
}

void menu(char arr[][20])
{
	system("cls");
	system("color a");//green
	cout << "====================================================DODGE EM================================================== \n         ============================================MENU===============================================" << endl;
	cout << " 1) start New Game" << endl;
	cout << " 2) See Highscore" << endl;
	cout << " 3) continue game\n";
	cout << " 4) Help" << endl;
	cout << " 5) Exit" << endl;
	char option;
	option=_getch();
	if (option == '1')
	{
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tLevel 1\n\n\n\n";
		Sleep(1000);
		board(arr);
		i = 18; j = 7; n = 18; m = 12;
		arr[i][j] = '$';//enemy
		arr[n][m] = '@';//player
		system("color 6");
		display(arr);
		player(arr);

	}
	else if (option == '2')
	{
		system("cls");
		/*for (int i = 0; i < 10; i++)
		{
			cout << scores[i] << endl;;
		}*/
		addscore();
		system("pause");
		menu(arr);
	}
	else if (option == '4')
	{
		system("cls");
		system("color b");
		cout << "Moves:-\n";
		cout << "w = up\ns = down\na = left\nd = rigth\np = pause\n\n";
		cout << "For further help contact us at:\nwww.atari.com/dodge.em\n" << endl;
		system("pause");
		menu(arr);
	}
	else if (option == '3')
	{
		player(arr);
	}
	else if (option == '5')
	{
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tPORGRAM EXIIED\n\n\n\n\n\n\n" << endl;
	}
	else
	{
		menu(arr);
	}
}

int main()
{
	char arr[20][20];
	board(arr);
	system("color c");//redish
	cout << "----------Dodge-em----------\n\n";
	cout << "Developers:-\n";
	cout << "Muhamamd Usman Anwar\nUmer Rashid\nMuhammad Sarmad\n\n";
	cout << "----------------------------\n\n";
	cout << "w = up\ns = down\na = left\nd = rigth\n\n";
	system("pause");
	menu(arr);
	return 0;
}
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>/*
#include <string>*/
using namespace std;
const char enemy = 20, player = 2, wall = 178;
bool flag = true;
int n = 1, m = 1, score = 0;
int i = 18, j = 48;
void movement(char arr[][50]);
void menu(char arr[][50]);
//void addscore()
//{
//	string str;
//	ofstream store; ifstream fin;
//	store.open("Scores.txt");
//	fin.open("Scores.txt");
//	if (store.is_open() && fin.is_open())
//	{
//		while (!fin.eof())
//		{
//			fin >> str;
//		}
//		if (stoi(str) < score)
//		{
//			store << "Score = " << score << endl;
//		}
//	}
//	fin.close();
//	store.close();
//}
//void displayscore()
//{
//	ifstream fin;
//	string str;
//	fin.open("Scores.txt");
//	while (!fin.eof())
//	{
//		getline(fin, str);
//		cout << str << endl;
//	}
//	fin.close();
//}

void cursor()
{

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);

}
void display(char arr[][50])//function to display the arr on console
{
	cursor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
	cout << "\t\tScore = " << score << endl;
	for (int i = 0; i < 20; i++)
	{
		cout << "\t\t";
		for (int j = 0; j < 50; j++)
		{
			cout << arr[i][j];
		}
		cout << endl;
	}
	system("color 6");//it is at the end so that when ever the color chanages to red when life is deducted it will go back to orange 
}
void board(char arr[][50])
{
	for (int i = 0; i < 20; i++)//first initialize with a dot
	{
		for (int j = 0; j < 50; j++)
		{
			arr[i][j] = '.';
		}
	}
	for (int i = 0; i < 50; i++) //outside border
	{
		arr[0][i] = wall;
		arr[19][i] = wall;
	}
	for (int i = 0; i < 20; i++)
	{
		arr[i][0] = wall;
		arr[i][49] = wall;
	}
}
void up(char arr[][50])//w 
{
	if (n - 1 > 0 && arr[n - 1][m] != wall) {
		if (arr[n - 1][m] != '*')
		{
			n--;
			arr[n + 1][m] = ' ';
		}
		if (arr[n][m] == '.') {//score counter
			score++;
		}
	}
}
void down(char arr[][50])//s
{
	if (n + 1 < 49 && arr[n + 1][m] != wall)
	{
		if (arr[n + 1][m] != '*')
		{
			n++;
			arr[n - 1][m] = ' ';
		}
		if (arr[n][m] == '.')//score counter 
		{
			score++;
		}
	}
	arr[n][m] = player;
}
void left(char arr[][50])//a
{
	if (m - 1 > 0 && arr[n][m - 1] != wall) {
		if (arr[n][m - 1] != '*')
		{
			m--;
			arr[n][m + 1] = ' ';
		}
		if (arr[n][m] == '.') {//score counter
			score++;
		}
	}
}
void right(char arr[][50])//d
{
	if (m + 1 < 49 && arr[n][m + 1] != wall) {
		if (arr[n][m + 1] != '*')
		{
			m++;
			arr[n][m - 1] = ' ';
		}
		if (arr[n][m] == '.') {//score counter
			score++;
		}
	}
}
void opp(char arr[][50], int& i, int& j)
{
	if (i > n && arr[i - 1][j] != wall)
	{
		if (arr[i - 1][j] == ' ')
		{
			i--;
			arr[i + 1][j] = ' ';
		}
		else if (arr[i - 1][j] == '.')
		{
			i--;
			arr[i + 1][j] = '.';
		}
		else if (arr[i - 1][j] == player)
		{
			i--;
			arr[i + 1][j] = ' ';
		}
	}
	else if (i < n && arr[i + 1][j] != wall)
	{
		if (arr[i + 1][j] == ' ')
		{
			i++;
			arr[i - 1][j] = ' ';
		}
		else if (arr[i + 1][j] == '.')
		{
			i++;
			arr[i - 1][j] = '.';
		}
		else if (arr[i + 1][j] == player)
		{
			i++;
			arr[i - 1][j] = ' ';
		}
	}
	if (j > m && arr[i][j - 1] != wall)
	{
		if (arr[i][j - 1] == ' ')
		{
			j--;
			arr[i][j + 1] = ' ';
		}
		else if (arr[i][j - 1] == '.')
		{
			j--;
			arr[i][j + 1] = '.';
		}
		else if (arr[i][j - 1] == player)
		{
			j--;
			arr[i][j + 1] = ' ';
		}
	}
	else if (j < m && arr[i][j + 1] != wall) {
		if (arr[i][j + 1] == ' ')
		{
			j++;
			arr[i][j - 1] = ' ';
		}
		else if (arr[i][j + 1] == '.')
		{
			j++;
			arr[i][j - 1] = '.';
		}
		else if (arr[i][j + 1] == player)
		{
			j++;
			arr[i][j - 1] = ' ';
		}
	}
	if (arr[i][j] == player)
	{
		//addscore();
		system("cls");
		system("color 4");
		cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tGame Over!\n\n\n\n";
		flag = false;
		Sleep(2500);
		return;
	}
}
void input(char arr[][50])//this function will be uesd to take inputs from the user
{
	char input;
	input = _getch();
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
	else if (input == 'D' && arr[n][m + 1] != enemy)//to add wall
	{
		arr[n][m + 1] = wall;
	}
	else if (input == 'A' && arr[n][m - 1] != enemy)
	{
		arr[n][m - 1] = wall;
	}
	else if (input == 'W' && arr[n - 1][m] != enemy)
	{
		arr[n - 1][m] = wall;
	}
	else if (input == 'S' && arr[n + 1][m] != enemy)
	{
		arr[n + 1][m] = wall;
	}
}
void movement(char arr[][50])
{
	int k = 0, l = 0, o = 0, p = 0, q = 0, r = 0, s = 0, t = 0, u = 0, v = 0;
	int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
	while (flag)
	{
		input(arr);
		if (arr[i][j] == player || arr[k][l] == player || arr[o][p] == player || arr[q][r] == player || arr[s][t] == player || arr[u][v] == player)
		{
			//addscore();
			system("cls");
			system("color 4");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tGame Over!\n\n\n\n";
			flag = false;
			Sleep(2500);
			break;
		}
		arr[n][m] = player;
		opp(arr, i, j);
		arr[i][j] = enemy;
		if (score == 100)
		{
			system("cls");
			system("color d");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tLevel 2\n\n\n\n";
			Sleep(500);
			score++;
			k = 18; l = 48;
			system("cls");
		}
		else if (score >= 100)
		{
			opp(arr, k, l);
			arr[k][l] = enemy;
		}
		if (score == 200)
		{
			system("cls");
			system("color d");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tLevel 3\n\n\n\n";
			Sleep(500);
			score++;
			o = 18; p = 40;
			system("cls");
		}
		else if (score >= 200)
		{
			opp(arr, o, p);
			arr[o][p] = enemy;
		}
		if (score == 300)
		{
			system("cls");
			system("color d");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tLevel 4\n\n\n\n";
			Sleep(500);
			score++;
			q = 18; r = 45;
			system("cls");
		}
		else if (score >= 300)
		{
			opp(arr, q, r);
			arr[q][r] = enemy;
		}

		if (score == 450)
		{
			system("cls");
			system("color d");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tLevel 5\n\n\n\n";
			Sleep(500);
			score++;
			s = 10; t = 48;
			system("cls");
		}
		else if (score >= 450)
		{
			opp(arr, s, t);
			arr[s][t] = enemy;
		}
		if (score == 600)
		{
			system("cls");
			system("color d");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\Level 6\n\n\n\n";
			Sleep(500);
			u = 18; v = 10;
			score++;
			system("cls");
		}
		else if (score > 60)
		{

			opp(arr, u, v);
			arr[u][v] = enemy;
		}
		if (score == 620)
		{
			system("cls");
			system("color d");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tFinal Level\n\n\n\n";
			Sleep(500);
			score++;
			a = 18; b = 10; c = 12; d = 45;
			e = 13; f = 35; g = 12; h = 20;
			system("cls");
		}
		else if (score >= 620)
		{
			opp(arr, a, b);
			arr[a][b] = enemy;
			opp(arr, c, d);
			arr[c][d] = enemy;
			opp(arr, e, f);
			arr[e][f] = enemy;
			opp(arr, g, h);
			arr[g][h] = enemy;
		}
		if (arr[i][j] == player || arr[k][l] == player || arr[o][p] == player || arr[q][r] == player || arr[s][t] == player || arr[u][v] == player)
		{
			//addscore();
			system("cls");
			system("color 4");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tGame Over!\n\n\n\n";
			flag = false;
			Sleep(2500);
			break;
		}

		if (score == 650)
		{
			system("cls");
			system("color 9");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tWinner!\n\n\n\n";
			Sleep(2000);
			flag = false;
			break;
		}
		display(arr);
	}
}
void menu(char arr[][50])
{
	system("cls");
	system("color d");
	cout << " 1) start New Game" << endl;
	cout << " 2) See Highscore" << endl;
	cout << " 3) continue game\n";
	cout << " 4) Help" << endl;
	cout << " 5) Exit" << endl;
	char option;
	option = _getch();
	if (option == '1')
	{
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tLevel 1\n\n\n\n";
		Sleep(1000);
		board(arr);
		n = 1; m = 1; i = 18; j = 48;
		arr[n][m] = player;
		arr[i][j] = enemy;
		system("color 6");
		system("cls");
		display(arr);
		movement(arr);

	}
	else if (option == '2')
	{
		system("cls");
		//displayscore();
		system("pause");
		menu(arr);
	}
	else if (option == '4')
	{
		system("cls");
		system("color b");
		cout << "Moves:-\n";
		cout << "w = up\ns = down\na = left\nd = rigth\np = pause\n\n";
		cout << "Moves to add blocks:-\n";
		cout << "shift + w (W) = block above the player\n";
		cout << "shift + s (S) = block under the player\n";
		cout << "shift + a (A) = block left to the player\n";
		cout << "shift + d (D) = block rigth to the player player\n\n";
		cout << "Player = " << player << "\n";
		cout << "enemy = " << enemy << "\n\n\n";
		cout << "Rules:-\n";
		cout << "dots on the map increases scores\n";
		cout << "after certain score level will increase\n";
		cout << "With incrrease in level number of enemies increase\n";
		cout << "enemy will follow the player\n";
		cout << "Player should place blocks in a way that the enemy will be stuck\n";
		cout << "player will win when player is at level 6 and score is equal to 650\n\n\n";
		system("pause");
		menu(arr);
	}
	else if (option == '3')
	{
		movement(arr);
	}
	else if (option == '5')
	{
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tGAME EXIIED\n\n\n\n\n\n\n" << endl;
	}
}
int main()
{
	char arr[20][50];
	board(arr);
	menu(arr);
	return 0;
}
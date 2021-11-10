//#include<iostream>
//#include <windows.h>	// general windows definitions
//#include <thread>
//#include<string>
//#include <stdio.h>
//#include <stdlib.h>
//#include <conio.h>
//#include <gdiplus.h>
//
//using namespace std;
//
//VOID WINAPI SetConsoleColors(WORD attribs);
//void FixConsoleWindow();
//void GotoXY(int x, int y);
//void exitGame(thread* t);
//void ThreadFunc1();
//void DrawRect(int x, int y, int width, int height, int curPosX = 0, int curPosY = 0);
//
//bool IS_RUNNING = true;
//
//
//
//int main() {
//	FixConsoleWindow();
//
//	thread t1(ThreadFunc1);
//	while (true) {
//
//		char temp = toupper(_getch());
//		if (temp == 27) {
//			exitGame(&t1); return 0;
//		}
//	}
//	return 0;
//}
//
//void FixConsoleWindow() {
//	HWND consoleWindow = GetConsoleWindow();
//	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
//	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
//	SetWindowLong(consoleWindow, GWL_STYLE, style);
//}
//
//void GotoXY(int x, int y) {
//	COORD coord;
//	coord.X = x;
//	coord.Y = y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//}
//
//void exitGame(thread* t) {
//	system("cls");
//	IS_RUNNING = false;
//	t->join();
//}
//void ThreadFunc1() {
//
//	while (IS_RUNNING) {
//
//		/*DrawRect(0, 0, 10, 20);
//		DrawRect(10, 0, 10, 20);*/
//	}
//}
//
//void DrawRect(int x, int y, int width, int height, int curPosX, int curPosY)
//{
//	GotoXY(x, y); cout << char(201);
//	for (int i = 1; i < width; i++)cout << char(205);
//	cout << char(187);
//	GotoXY(x, height + y); cout << char(200);
//	for (int i = 1; i < width; i++)cout << char(205);
//	cout << char(188);
//	for (int i = y + 1; i < height + y; i++)
//	{
//		GotoXY(x, i); cout << char(186);
//		GotoXY(x + width, i); cout << char(186);
//	}
//	GotoXY(curPosX, curPosY);
//}
//
//VOID WINAPI SetConsoleColors(WORD attribs) {
//	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//
//	CONSOLE_SCREEN_BUFFER_INFOEX cbi;
//	cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
//	GetConsoleScreenBufferInfoEx(hOutput, &cbi);
//	cbi.wAttributes = attribs;
//	SetConsoleScreenBufferInfoEx(hOutput, &cbi);
//}
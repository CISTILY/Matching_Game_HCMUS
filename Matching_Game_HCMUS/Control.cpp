﻿#include "Control.h"

HWND Control::consoleWindow = GetConsoleWindow();
HANDLE Control::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void Control::setUpConsole()
{
	setFontInfo();
	setAndCenterWindow();
	hideScrollBars();
	//ShowScrollbar(0);
	setConsoleTitle();
	disableMaximize();
	showCursor(false);
	disableMouseInput();
}

void Control::setFontInfo()
{
	// 12 - 24 
	CONSOLE_FONT_INFOEX info;
	info.cbSize = sizeof(info);
	GetCurrentConsoleFontEx(consoleOutput, FALSE, &info);
	info.dwFontSize.X = 12;
	info.dwFontSize.Y = 24;
	wcscpy_s(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(consoleOutput, FALSE, &info);
}

void Control::setAndCenterWindow()
{	//1220 - 768
	RECT rectOfClient, rectOfWindow;
	GetClientRect(consoleWindow, &rectOfClient);
	GetWindowRect(consoleWindow, &rectOfWindow);
	int width = 1220;
	int height = 820;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	int	posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
}

void Control::setAndCenterWindow(int _row, int _col)
{
	RECT rectOfClient, rectOfWindow;
	GetClientRect(consoleWindow, &rectOfClient);
	GetWindowRect(consoleWindow, &rectOfWindow);
	int width = (_col + 1) * 110 + 410;
	int height = 820;
	if (_row > 6)
		height = 1080;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	int	posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
}

void Control::hideScrollBars()
{
	ShowScrollBar(consoleWindow, SB_BOTH, 0);
}

//void Control::ShowScrollbar(BOOL Show)
//{
//	HWND hWnd = GetConsoleWindow();
//	ShowScrollBar(hWnd, SB_BOTH, Show);
//}

void Control::setConsoleTitle()
{
	SetConsoleTitle(L"MATCHING GAME");
}

void Control::disableMaximize()
{
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));
}

void Control::setConsoleColor(int background, int text)
{
	SetConsoleTextAttribute(consoleOutput, background * 16 + text);
}

void Control::showCursor(bool show)
{
	CONSOLE_CURSOR_INFO info = { 1, show };
	SetConsoleCursorInfo(consoleOutput, &info);
}

void Control::clearConsole()
{
	system("cls");
}

void Control::clearArea(int left, int top, int width, int height)
{
	for (int i = top; i <= top + height; ++i)
		for (int j = left; j <= left + width; ++j)
		{
			gotoXY(j, i);
			putchar(32);
		}
}

void Control::disableMouseInput()
{
	DWORD prev_mode;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

void Control::gotoXY(int pX, int pY)
{
	SetConsoleCursorPosition(consoleOutput, COORD{ (short)pX, (short)pY });
}

int Control::getConsoleInput()
{
	int c = _getch();
	// Arrow key
	if (c == 0 || c == 224)
	{
		switch (_getch())
		{
		case KEY_UP:				// Mũi tên lên
			return 2;
		case KEY_LEFT:				// Mũi tên trái
			return 3;
		case KEY_RIGHT:				// Mũi tên phải
			return 4;
		case KEY_DOWN:				// Mũi tên xuống
			return 5;
		default:					// Nút khác
			return 0;
		}
	}
	else
	{
		if (c == KEY_ESC)					// Nút esc
			return 1;
		else if (c == 87 || c == 119)		// Nút W, w
			return 2;
		else if (c == 65 || c == 97)		// Nút A, a
			return 3;
		else if (c == 68 || c == 100)		// Nút D, d
			return 4;
		else if (c == 83 || c == 115)		// Nút S, s
			return 5;
		else if (c == 13)					// Nút Enter
			return 6;
		else if (c == 72 || c == 104)		// Nút H, h
			return 7;
		else if (c == 77 || c == 109)		// Nút M, m
			return 8;
		else                                // Nút khác
			return 0;
	}
}

void Control::playSound(int i)
{
	static vector<const wchar_t*> soundFile{ L"Error.wav", L"Enter.wav", L"EnterMenu.wav", L"GameStart.wav", L"Win.wav",  L"Move.wav", L"GetPoint.wav", L"Wrong.wav"};
	PlaySound(soundFile[i], NULL, SND_FILENAME | SND_ASYNC);
}

int getRandomInt(int begin, int end)
{
	static random_device rd;
	static mt19937 mt(rd());
	uniform_int_distribution<int> dist(0, end);
	return dist(mt);
}
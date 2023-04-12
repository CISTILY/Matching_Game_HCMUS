#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <conio.h>
#include <vector>
#include <Random>
#include <string>
#include <winuser.h>

// COLOR CODE
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

// DI CHUYỂN
#define KEY_UP 72		// Mũi tên lên
#define KEY_DOWN 80		// Mũi tên xuống
#define KEY_LEFT 75		// Mũi tên trái
#define KEY_RIGHT 77	// Mũi tên phải
#define KEY_ESC 27		// Nút ESC

using namespace std;

struct Control {
	Control() {};
	~Control() {};
	static HWND consoleWindow;						// Con trỏ xử lý cửa sổ console
	static HANDLE consoleOutput;					// Con trỏ xử lý output của console
	static void setUpConsole();						// Thiết lập cửa sổ game
	static void gotoXY(int, int);					// Di chuyển đến toạ độ (x, y)
	static void setAndCenterWindow();				// Thiết lập và canh giữa cửa sổ game
	static void setAndCenterWindow(int, int);		// Thiết lập và canh giữa cửa sổ game
	static void setConsoleColor(int, int);			// Thiết lập màu cho cửa sổ game
	static void hideScrollBars();					// Ẩn thanh cuộn của cửa sổ
	static void setConsoleTitle();					// Thiết lập tiêu đề cho cửa sổ
	static void disableMaximize();					// Tắt chức năng toàn màn hình
	static void showCursor(bool);					// Tất con trỏ
	static void setFontInfo();						// Thiết lập font chữ
	static void clearConsole();						// Xoá cửa sổ
	static void clearArea(int, int, int, int);		// Xoá vùng
	static void disableMouseInput();				// Tắt đầu vào từ chuột
	static int getConsoleInput();					// Lấy đầu vào từ bàn phím
};
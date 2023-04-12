#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <random>
#include <fstream>
#include "Control.h"
#include "Game.h"
#include <windows.h>
#include <iomanip>

#define _EASY 4
#define _MEDIUM 6

#define PADDING 500
#define NAMESIZE 50
#define PASSSIZE 50
#define MODESIZE 15
#define BOARDSIZE 999
#define URLSIZE 100

using namespace std;

struct Time
{
	int minuteplay;
	int secondplay;
};

struct Date {
	int dd, mm, yy;
};

struct Record {
	Date date;
	Time time;
	int points;
};

struct State {
	Record state_record;
	char mode[MODESIZE];
	int p, q;
	int p_, q_;
	char board[BOARDSIZE];
	int status[100];
	char file_background[URLSIZE];
};

struct savefile {
	char mask;
	char name[NAMESIZE];
	char password[PASSSIZE];
	Record record[5];
	State state[5];
};


struct Menu
{
	static savefile account;												// Account của người chơi
	static bool exitGame;													// Event thoát game
	static int current_option;												// Lựa chọn hiện tại
	const static string options[12];										// Tên các lựa chọn
	static void mainScreen();												// Màn hình chính
	static void mainMenu();													// Menu
	static void playMenu();													// Menu play
	static void leaderBoard();												// Màn hình load file leaderboard
	static void helpScreen();												// Màn hình hướng dẫn
	static void exitScreen();												// Màn hình thoát
	static void UserMode();													// Màn hình User
	static void guestMode();												// Màn hình Guest
	static void signIn();													// Đăng nhập tài khoản
	static void signUp();													// Đăng ký tài khoản
	static void playEasy();													// Chế độ easy
	static void playMedium();												// Chế độ medium
	static void playCustom();												// Chế độ custom
	static void changeFile(int, bool, int&);								// Thay đổi file game
	static void chooseFile(int&);											// Chọn file
	static void xorChararter(char[], char);									// XOR các kí tự
	static void readFileGame(int&);											// Đọc file save
	static void loadGame();													// Chơi file đã lưu
	static void printLogo();												// In ra logo
	static void printOptionsBoard();										// In ra các bảng lựa chọn
	static void changeOption(bool, bool);									// Thay đổi lựa chọn
	static void chooseMode(bool, bool, int);								// Thay đổi chế độ
	static void readFileAccounts(ifstream&, char[][50], char[][50]);		// Đọc file accounts
	static void enterAccount();												// Nhập tài khoản, mật khẩu
	static bool rightAccount(char[][50], char[][50]);						// Kiểm tra đúng tài khoản
	static bool appropriateAccount(char[][50]);								// Kiểm tra đã tồn tại tài khoản
	static void printMode();
};
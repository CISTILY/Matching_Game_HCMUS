#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "Control.h"
#include "Game.h"
#include <random>
#include <fstream>
#include <windows.h>

#define _EASY 4
#define _MEDIUM 6

#define NAMESIZE 50
#define PASSSIZE 50

using namespace std;

struct Player {
	char playerName[NAMESIZE];
	char password[PASSSIZE];
	int score;
	char mode[15];
};

struct Menu
{
	static Player account;
	static bool exitGame;											// Event thoát game
	static int current_option;										// Lựa chọn hiện tại
	const static string options[12];								// Tên các lựa chọn
	static void mainScreen();										// Màn hình chính
	static void mainMenu();											// Menu
	static void playMenu();											// Menu play
	static void leaderBoard();										// Màn hình load file leaderboard
	static void helpScreen();										// Màn hình hướng dẫn
	static void exitScreen();										// Màn hình thoát
	static void UserMode();											// Màn hình User
	static void guestMode();										// Màn hình Guest
	static void signIn();											// Đăng nhập tài khoản
	static void signUp();											// Đăng ký tài khoản
	static void playEasy();											// Chế độ easy
	static void playMedium();										// Chế độ medium
	static void playCustom();										// Chế độ custom
	static void printLogo();										// In ra logo
	static void printOptionsBoard();								// In ra các bảng lựa chọn
	//static void printAnimation();									// In hiệu ứng mở đầu
	static void changeOption(bool, bool);							// Thay đổi lựa chọn
	static void chooseMode(bool, bool, int);						// Thay đổi chế độ
	static void readFileAccounts(ifstream& Acc, char[][50]);		// Đọc file accounts
	static void enterAccount();										// Nhập tài khoản, mật khẩu
	static bool rightAccount(char[][50]);							// Kiểm tra đúng tài khoản
	static bool appropriateAccount(char[][50]);						// Kiểm tra đã tồn tại tài khoản
	static void printMode();	
};
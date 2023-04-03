﻿#pragma once
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

using namespace std;

struct Menu
{
	static bool exitGame;									// Event thoát game
	static int current_option;								// Lựa chọn hiện tại
	const static string options[10];						// Tên các lựa chọn
	static void mainScreen();								// Màn hình chính
	static void mainMenu();									// Menu
	static void playMenu();									// Menu play
	static void leaderBoard();								// Màn hình load file leaderboard
	static void helpScreen();								// Màn hình hướng dẫn
	static void exitScreen();								// Màn hình thoát
	static void playEasy();									// Chế độ easy
	static void playMedium();								// Chế độ medium
	static void playCustom();								// Chế độ custom
	static void printLogo();								// In ra logo
	static void printOptionsBoard();						// In ra các bảng lựa chọn
	//static void printAnimation();							// In hiệu ứng mở đầu
	static void changeOption(bool, bool);					// Thay đổi lựa chọn
	static void chooseMode(bool, bool, int&);
	static void playUserMode();
	static void playGuestMode();
};
struct Player {
	string playerName;
	int score;
	string mode;
};

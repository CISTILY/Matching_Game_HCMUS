﻿#pragma once
#include "Control.h"
#include "Point.h"
#include <iostream>
#include <fstream> 
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Board {
	int size;						// Kích thước bàn cờ
	int left, top;					// tọa độ góc trên bàn cờ
	Point** pBoard;					// Mảng tọa độ ô cờ
	int** character;
	string* background;

	Board(int, int, int);
	void deleteBoard();

	int getSize();					//Lấy kích cỡ
	int getLeft();					//Lấy tọa độ trái bắt đầu bàn cờ
	int getTop();					//Lấy tọa độ trên bắt đầu bàn cờ
	int getXAt(int, int);			//Lấy tọa độ x tại ô
	int getYAt(int, int);			//Lấy tọa độ y tại ô
	int getCheckAtXY(int, int);
	int getRAt(int, int);			//Lấy tọa độ R (row) tại tọa độ x y
	int getCAt(int, int);			//Lấy tọa độ C (column) tại tọa độ x y
	char getCharacter(int, int);
	int getCheck(int, int);

	void showBoard();
	void renderBoard();
	void buildBoardData();

	void selectedBlock(int, int, int);
	void unselectedBlock(int, int);

	void lockBlock(int, int);
	void deleteBlock(int, int);

	void drawLineI(pair<int, int>, pair<int, int>);
	void deleteLineI(pair<int, int>, pair<int, int>);
	void drawLineL(pair<int, int>, pair<int, int>, pair<int, int>);
	void deleteLineL(pair<int, int>, pair<int, int>, pair<int, int>);
	void drawLineZ(pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>);
	void deleteLineZ(pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>);
	void drawLineU(pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>);
	void deleteLineU(pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>);

	void createBackground();
};
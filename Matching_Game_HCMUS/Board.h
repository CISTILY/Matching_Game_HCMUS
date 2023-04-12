#pragma once
#include "Control.h"
#include "Point.h"
#include "Graphic.h"
#include <iostream>
#include <fstream> 
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Board {
	int sizeRow, sizeCol;			// Kích thước bàn cờ					
	int left, top;					// tọa độ góc trên bàn cờ
	Point** pBoard;					// Mảng tọa độ ô cờ
	int** character;
	string* background;
	int stop = 1;

	Board(int, int, int, int, char[]);
	~Board();

	int getSizeRow();							//Lấy kích cỡ
	int getSizeCol();							//Lấy kích cỡ
	int getLeft();								//Lấy tọa độ trái bắt đầu bàn cờ
	int getTop();								//Lấy tọa độ trên bắt đầu bàn cờ
	int getXAt(int, int);						//Lấy tọa độ x tại ô
	int getYAt(int, int);						//Lấy tọa độ y tại ô
	int getCheckAtXY(int, int);					//Lấy trạng thái tại x y
	int getRAt(int, int);						//Lấy tọa độ R (row) tại tọa độ x y
	int getCAt(int, int);						//Lấy tọa độ C (column) tại tọa độ x y
	char getCharacter(int, int);				//Lấy kí tự của ô
	int getCheck(int, int);						//Kiểm tra trạng thái ô 
	int getCheckLockAll(int, int);
	int getCheckUpperLeft(int, int);
	int getCheckUpperRight(int, int);
	int getCheckBottomLeft(int, int);
	int getCheckBottomRight(int, int);



	void showBoard();							//Hiển thị viền của bảng
	void renderBoard();							//Hiện thị màu của bảng
	void renderBoardForLoad(int**);				//Hiện thị màu của bảng được load
	void buildBoardData();						//Tạo các kí tự ngẫu nhiên cho bảng
	void buildBoardDataForLoad(char**);			//Tạo các kí tự ngẫu nhiên cho bảng load

	void selectedBlock(int, int, int);			//Chọn ô
	void unselectedBlock(int, int);				//Bỏ chọn ô

	void lockBlock(int, int);					//Khoá ô
	void deleteBlock(int, int);					//Xoá ô
	void updateBackground();					//Hiển thị background

	void drawLineI(pair<int, int>, pair<int, int>);												//Vẽ đường I
	void deleteLineI(pair<int, int>, pair<int, int>);											//Xoá đường I
	void drawLineL(pair<int, int>, pair<int, int>, pair<int, int>);								//Vẽ đường L
	void deleteLineL(pair<int, int>, pair<int, int>, pair<int, int>);							//Xoá đường L
	void drawLineZ(pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>);				//Vẽ đường Z
	void deleteLineZ(pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>);			//Xoá đường Z
	void drawLineU(pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>);				//Vẽ đường U
	void deleteLineU(pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>);			//Xoá đường U

	void createBackground(char[]);				//Tạo background
};
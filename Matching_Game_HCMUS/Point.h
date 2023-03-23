#pragma once

#define NORMAL 0
#define LOCK 1
#define DEL -1

struct Point
{
	int _x = 0;						// Vị trí x
	int _y = 0;						// Vị trí y
	int _check = 0;					// 1: LOCK, 0: NORMAL, -1: DELETE
	char _character = ' ';
	Point();						// Tạo lập các biến
	Point(int, int, int, char);		// Thay đổi các biến

	int getX();						// Lấy vị trí x
	int getY();						// Lấy vị trí y
	int getCheck();					// Lấy ô

	void setX(int);					// Gán vị trí x
	void setY(int);					// Gán vị trí y
	void setCheck(int);				// Gán ô

	char getCharacter();
	void setCharacter(char);

};
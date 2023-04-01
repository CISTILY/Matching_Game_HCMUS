#pragma once
#include <iostream>
#include "Control.h"
#include "Board.h"

using namespace std;

struct Graphic {
	static void printRectangleSpecial(int, int, int, int);			// Vẽ hình chữ nhật đặc biệt
	static void printRectangleNormal(int, int, int, int);			// Vẽ hình chữ nhật thường
	static void printFrame(int, int);						// Vẽ khung 
	static void backUpperLeft(int, int, int);					// Vẽ trả phần khung trái trên
	static void backUpperRight(int, int, int);					// Vẽ trả phần khung phải trên
	static void backBottomLeft(int, int, int);					// Vẽ trả phần khung trái dưới
	static void backBottomRight(int, int, int);					// Vẽ trả phần khung phải dưới
};
#include "Graphic.h"

void Graphic::printRectangleSpecial(int left, int top, int width, int height)
{
	Control::gotoXY(left, top);
	putchar(201);
	for (int i = 0; i < width; i++)
		putchar(205);
	putchar(187);

	int i = 0;
	for (; i < height; i++)
	{
		Control::gotoXY(left, top + i + 1);
		putchar(186);
		Control::gotoXY(left + width + 1, top + i + 1);
		putchar(186);
	}

	Control::gotoXY(left, top + i);
	putchar(200);
	for (i = 0; i < width; i++)
		putchar(205);
	putchar(188);
}

void Graphic::printRectangleNormal(int left, int top, int width, int height)
{
	Control::gotoXY(left, top);
	putchar(218);
	for (int i = 0; i < width; i++)
		putchar(196);
	putchar(191);

	int i = 0;
	for (; i < height; i++)
	{
		Control::gotoXY(left, top + i + 1);
		putchar(179);
		Control::gotoXY(left + width + 1, top + i + 1);
		putchar(179);
	}

	Control::gotoXY(left, top + i);
	putchar(192);
	for (i = 0; i < width; i++)
		putchar(196);
	putchar(217);
}

void Graphic::printFrame(int x, int y)
{
	Control::gotoXY(x - 4, y - 2);
	putchar(201);
	Control::gotoXY(x + 4, y - 2);
	putchar(187);
	Control::gotoXY(x - 4, y + 2);
	putchar(200);
	Control::gotoXY(x + 4, y + 2);
	putchar(188);
}

void Graphic::backUpperLeft(int x, int y, int situation)
{
	Control::gotoXY(x - 4, y - 2);
	switch (situation) {
	case 1:
		Control::setConsoleColor(WHITE, LIGHT_RED);
		putchar(188);
		break;
	case 2:
		Control::setConsoleColor(WHITE, LIGHT_RED);
		putchar(200);
		break;
	case 4:
		Control::setConsoleColor(WHITE, LIGHT_RED);
		putchar(187);
		break;
	case 9:
		Control::setConsoleColor(WHITE, BLACK);
		//putchar(background[y - top][x - left]);
		putchar(32);
		break;
	default:
		Control::setConsoleColor(WHITE, BLACK);
		putchar(43);
		break;
	}
}

void Graphic::backUpperRight(int x, int y, int situation)
{
	Control::gotoXY(x + 4, y - 2);
	switch (situation) {
	case 2:
		Control::setConsoleColor(WHITE, LIGHT_RED);
		putchar(188);
		break;
	case 3:
		Control::setConsoleColor(WHITE, LIGHT_RED);
		putchar(200);
		break;
	case 5:
		Control::setConsoleColor(WHITE, LIGHT_RED);
		putchar(201);
		break;
	case 9:
		Control::setConsoleColor(WHITE, BLACK);
		//putchar(background[y - top][x - left]);
		putchar(32);
		break;
	default:
		Control::setConsoleColor(WHITE, BLACK);
		putchar(43);
		break;
	}
}

void Graphic::backBottomLeft(int x, int y, int situation)
{
	Control::gotoXY(x - 4, y + 2);
	switch (situation) {
	case 4:
		Control::setConsoleColor(WHITE, LIGHT_RED);
		putchar(188);
		break;
	case 6:
		Control::setConsoleColor(WHITE, LIGHT_RED);
		putchar(187);
		break;
	case 7:
		Control::setConsoleColor(WHITE, LIGHT_RED);
		putchar(201);
		break;
	case 9:
		Control::setConsoleColor(WHITE, BLACK);
		//putchar(background[y - top][x - left]);
		putchar(32);
		break;
	default:
		Control::setConsoleColor(WHITE, BLACK);
		putchar(43);
		break;
	}
}

void Graphic::backBottomRight(int x, int y, int situation)
{
	Control::gotoXY(x + 4, y + 2);
	switch (situation) {
	case 5:
		Control::setConsoleColor(WHITE, LIGHT_RED);
		putchar(200);
		break;
	case 7:
		Control::setConsoleColor(WHITE, LIGHT_RED);
		putchar(187);
		break;
	case 8:
		Control::setConsoleColor(WHITE, LIGHT_RED);
		putchar(201);
		break;
	case 9:
		Control::setConsoleColor(WHITE, BLACK);
		//putchar(background[y - top][x - left]);
		putchar(32);
		break;
	default:
		Control::setConsoleColor(WHITE, BLACK);
		putchar(43);
		break;
	}
}
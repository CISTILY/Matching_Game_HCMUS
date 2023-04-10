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

void Graphic::printRectangleBlock(int left, int top, int width, int height)
{
	Control::gotoXY(left, top);
	putchar(220);
	for (int i = 0; i < width; i++)
		putchar(220);
	putchar(220);

	int i = 0;
	for (; i < height; i++)
	{
		Control::gotoXY(left, top + i + 1);
		putchar(219);
		Control::gotoXY(left + width + 1, top + i + 1);
		putchar(219);
	}

	Control::gotoXY(left, top + i);
	putchar(223);
	for (i = 0; i < width; i++)
		putchar(223);
	putchar(223);
}

void Graphic::printFileBlock(int left, int top, int width, int height)
{
	Control::gotoXY(left + 1, top);
	for (int i = 0; i < width; i++)
		putchar(220);

	int i = 0;
	for (; i < height; i++)
	{
		Control::gotoXY(left, top + i + 1);
		putchar(219);

		Control::gotoXY(left + 2, top + i + 1);
		for (int j = 0; j < width - 2; ++j)
			putchar(254);

		Control::gotoXY(left + width + 1, top + i + 1);
		putchar(219);
	}

	Control::gotoXY(left + 1, top + i + 1);
	for (i = 0; i < width; i++)
		putchar(223);
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

void Graphic::backUpperLeft(int x, int y, int situation, string* background)
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
		putchar(background[y - 2 - Top][x - 4 - Left]);
		break;
	default:
		Control::setConsoleColor(WHITE, BLACK);
		putchar(43);
		break;
	}
}

void Graphic::backUpperRight(int x, int y, int situation, string* background)
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
		putchar(background[y - 2 - Top][x + 4 - Left]);
		break;
	default:
		Control::setConsoleColor(WHITE, BLACK);
		putchar(43);
		break;
	}
}

void Graphic::backBottomLeft(int x, int y, int situation, string* background)
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
		putchar(background[y + 2 - Top][x - 4 - Left]);
		break;
	default:
		Control::setConsoleColor(WHITE, BLACK);
		putchar(43);
		break;
	}
}

void Graphic::backBottomRight(int x, int y, int situation, string* background)
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
		putchar(background[y + 2 - Top][x + 4 - Left]);
		break;
	default:
		Control::setConsoleColor(WHITE, BLACK);
		putchar(43);
		break;
	}
}

void Graphic::createTimeNumber0(char Time_array[][41])
{
	strcat_s(Time_array[0], "  ___   ");
	strcat_s(Time_array[1], " / _ \\  ");
	strcat_s(Time_array[2], "( (_) ) ");
	strcat_s(Time_array[3], " \\___/  ");
}

void Graphic::createTimeNumber1(char Time_array[][41])
{
	strcat_s(Time_array[0], " __  ");
	strcat_s(Time_array[1], "(  ) ");
	strcat_s(Time_array[2], " )(  ");
	strcat_s(Time_array[3], "(__) ");
}

void Graphic::createTimeNumber2(char Time_array[][41])
{
	strcat_s(Time_array[0], " ___   ");
	strcat_s(Time_array[1], "(__ \\  ");
	strcat_s(Time_array[2], " / _/  ");
	strcat_s(Time_array[3], "(____) ");
}

void Graphic::createTimeNumber3(char Time_array[][41])
{
	strcat_s(Time_array[0], " ___  ");
	strcat_s(Time_array[1], "(__ ) ");
	strcat_s(Time_array[2], " (_ \\ ");
	strcat_s(Time_array[3], "(___/ ");
}
void Graphic::createTimeNumber4(char Time_array[][41])
{
	strcat_s(Time_array[0], "  __   ");
	strcat_s(Time_array[1], " /. |  ");
	strcat_s(Time_array[2], "(_  _) ");
	strcat_s(Time_array[3], "  (_)  ");
}

void Graphic::createTimeNumber5(char Time_array[][41])
{
	strcat_s(Time_array[0], " ___  ");
	strcat_s(Time_array[1], "| __) ");
	strcat_s(Time_array[2], "|__ \\ ");
	strcat_s(Time_array[3], "(___/ ");
}

void Graphic::createTimeNumber6(char Time_array[][41])
{
	strcat_s(Time_array[0], "  _   ");
	strcat_s(Time_array[1], " / )  ");
	strcat_s(Time_array[2], "/ _ \\ ");
	strcat_s(Time_array[3], "\\___/ ");
}

void Graphic::createTimeNumber7(char Time_array[][41])
{
	strcat_s(Time_array[0], " ___  ");
	strcat_s(Time_array[1], "(__ ) ");
	strcat_s(Time_array[2], " / /  ");
	strcat_s(Time_array[3], "(_/   ");
}

void Graphic::createTimeNumber8(char Time_array[][41])
{
	strcat_s(Time_array[0], " ___  ");
	strcat_s(Time_array[1], "( _ ) ");
	strcat_s(Time_array[2], "/ _ \\ ");
	strcat_s(Time_array[3], "\\___/ ");
}

void Graphic::createTimeNumber9(char Time_array[][41])
{
	strcat_s(Time_array[0], " ___   ");
	strcat_s(Time_array[1], "/ _ \\  ");
	strcat_s(Time_array[2], "\\_  /  ");
	strcat_s(Time_array[3], " (_/   ");
}

void Graphic::createTimeTwoDots(char Time_array[][41])
{
	strcat_s(Time_array[0], "     ");
	strcat_s(Time_array[1], " ()  ");
	strcat_s(Time_array[2], "     ");
	strcat_s(Time_array[3], " ()  ");
}

void Graphic::createTime(int x, char Time_array[][41])
{
	switch (x)
	{
	case 0:
		createTimeNumber0(Time_array);
		break;
	case 1:
		createTimeNumber1(Time_array);
		break;
	case 2:
		createTimeNumber2(Time_array);
		break;
	case 3:
		createTimeNumber3(Time_array);
		break;
	case 4:
		createTimeNumber4(Time_array);
		break;
	case 5:
		createTimeNumber5(Time_array);
		break;
	case 6:
		createTimeNumber6(Time_array);
		break;
	case 7:
		createTimeNumber7(Time_array);
		break;
	case 8:
		createTimeNumber8(Time_array);
		break;
	case 9:
		createTimeNumber9(Time_array);
		break;
	case 10:
		createTimeTwoDots(Time_array);
		break;
	}
}
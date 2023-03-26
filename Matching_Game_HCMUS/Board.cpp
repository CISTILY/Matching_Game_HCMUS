#include "Board.h"

Board::Board(int psize, int pX, int pY) : size(psize), left(pX), top(pY)
{
	character = new int* [size];
	for (int i = 0; i < psize; i++)
		character[i] = new int[size];

	pBoard = new Point * [psize];

	for (int i = 0; i < psize; i++)
		pBoard[i] = new Point[psize];

	background = new string[psize * 10];
}

void Board::deleteBoard()
{
	for (int i = 0; i < size; i++)
		delete[] pBoard[i];
	delete[] pBoard,
		pBoard = nullptr;
	delete[] background;
	background = nullptr;
}

int Board::getSize()
{
	return size;
}

int Board::getLeft()
{
	return left;
}

int Board::getTop()
{
	return top;
}

int Board::getXAt(int i, int j)
{
	return pBoard[i][j].getX();
}

int Board::getYAt(int i, int j)
{
	return pBoard[i][j].getY();
}

int Board::getRAt(int x, int y)
{
	return (y - 2 - top) / 4;
}

int Board::getCAt(int x, int y)
{
	return (x - 5 - left) / 8;
}

char Board::getCharacter(int x, int y)
{
	return pBoard[getRAt(x, y)][getCAt(x, y)].getCharacter();
}

int Board::getCheckAtXY(int pX, int pY)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (pBoard[i][j].getX() == pX && pBoard[i][j].getY() == pY)
				return pBoard[i][j].getCheck();
		}
	}
	throw "Problem with cursor position";
}
int Board::getCheck(int x, int y)
{
	int r = getRAt(x, y);
	int c = getCAt(x, y);
	return pBoard[r][c].getCheck();
}
/////////////////////////////////////////////////////////////////////

void Board::showBoard()
{
	if (pBoard == NULL)
		return;
	Control::setConsoleColor(BRIGHT_WHITE, BLACK);
	Control::clearConsole();

	// Draw top line
	Control::gotoXY(left + 1, top);
	putchar(201);
	for (int i = 1; i < size * 8; i++)
	{
		Sleep(5);
		if (i % 8 == 0)
			putchar(205);
		else
			putchar(205);
	}
	putchar(187);

	// Draw right line
	for (int i = 1; i < size * 4; i++)
	{
		Sleep(10);
		Control::gotoXY(size * 8 + left + 1, i + top);
		if (i % 4 != 0)
			putchar(186);
		else
			putchar(186);
	}
	Control::gotoXY(size * 8 + left + 1, size * 4 + top);
	putchar(188);

	// Draw bottom line
	for (int i = 1; i < size * 8; i++)
	{
		Control::gotoXY(size * 8 + left - i + 1, size * 4 + top);
		Sleep(5);
		if (i % 8 == 0)
			putchar(205);
		else
			putchar(205);
	}
	Control::gotoXY(left + 1, size * 4 + top);
	putchar(200);

	// Draw left line
	for (int i = 1; i < size * 4; i++)
	{
		Sleep(10);
		Control::gotoXY(left + 1, size * 4 + top - i);
		if (i % 4 != 0)
			putchar(186);
		else
			putchar(186);
	}

	// Draw vertical lines
	for (int i = 1; i < size * 4; i++)
	{
		for (int j = 8; j < size * 8; j += 8)
		{
			if (i % 4 != 0)
			{
				Control::gotoXY(j + left + 1, i + top);
				putchar(179);
			}
		}
		Sleep(10);
	}

	// Draw horizontal lines
	for (int i = 1; i < size * 8; i++)
	{
		for (int j = 4; j < size * 4; j += 4)
		{
			Control::gotoXY(i + left + 1, j + top);
			if (i % 8 == 0)
				//putchar(197);
				putchar(32);
			else
				putchar(196);
		}
		Sleep(5);
	}
}

void Board::renderBoard() {
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			pBoard[i][j].setX(8 * j + left + 5); // x-value of boardgame
			pBoard[i][j].setY(4 * i + top + 2); // y-value of boardgame
			pBoard[i][j].setCheck(0);

			int r = pBoard[i][j].getX();
			int c = pBoard[i][j].getY();

			Control::gotoXY(r, c);
			putchar(pBoard[i][j].getCharacter());
		}
	}
}

void Board::buildBoardData() {
	srand((unsigned int)time(NULL));

	bool* checkDuplicate = new bool[size * size];
	int* pos = new int[size * size];

	// Random pokemons
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j += 2) {
			character[i][j] = character[i][j + 1] = rand() % 26 + 'A';
		}
	}

	// Random pokemons position 
	for (int i = 0; i < size * size; i++)
		checkDuplicate[i] = 0;
	for (int i = 0; i < size * size; i++) {
		int tmp = 0;
		do {
			tmp = rand() % (size * size);
		} while (checkDuplicate[tmp]);
		checkDuplicate[tmp] = 1;
		pos[i] = tmp;
	}

	// Construct pokemons matrix
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int r = pos[size * i + j] / size;
			int c = pos[size * i + j] % size;
			pBoard[i][j].setCharacter(character[r][c]);
		}
	}

	delete[] pos;
	delete[] checkDuplicate;
}

void Board::selectedBlock(int x, int y, int color) {
	Control::setConsoleColor(color, BLACK);
	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 3; j <= x + 3; j++) {
			Control::gotoXY(j, i);
			putchar(32);
		}
	}
	if (getCheck(x, y) != DEL) {
		Control::gotoXY(x, y);
		putchar(getCharacter(x, y));
		Control::gotoXY(x, y);
	}
	else {
		for (int i = y - 1; i <= y + 1; i++) {
			for (int j = x - 3; j <= x + 3; j++) {
				Control::gotoXY(j, i);
				//putchar(32);
				putchar(background[i - top][j - left]);
			}
		}
	}
}

void Board::unselectedBlock(int x, int y) {
	int r = getRAt(x, y);
	int c = getCAt(x, y);
	if (getCheck(x, y) != DEL)
		pBoard[r][c].setCheck(NORMAL);

	Control::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 3; j <= x + 3; j++) {
			Control::gotoXY(j, i);
			putchar(32);
		}
	}
	if (getCheck(x, y) != DEL) {
		Control::gotoXY(x, y);
		putchar(getCharacter(x, y));
		Control::gotoXY(x, y);
	}
	else {
		for (int i = y - 1; i <= y + 1; i++) {
			for (int j = x - 3; j <= x + 3; j++) {
				Control::gotoXY(j, i);
				//putchar(32);
				putchar(background[i - top][j - left]);
			}
		}
	}
}

void Board::lockBlock(int x, int y)
{
	int r = getRAt(x, y);
	int c = getCAt(x, y);
	pBoard[r][c].setCheck(LOCK);

	Control::setConsoleColor(RED, BLACK);
	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 3; j <= x + 3; j++) {
			Control::gotoXY(j, i);
			putchar(32);
		}
	}
	Control::gotoXY(x, y);
	putchar(getCharacter(x, y));
	Control::gotoXY(x, y);
}

void Board::deleteBlock(int x, int y)
{
	int r = getRAt(x, y);
	int c = getCAt(x, y);
	pBoard[r][c].setCheck(DEL);

	Control::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 3; j <= x + 3; j++) {
			Control::gotoXY(j, i);
			// putchar(32);
			putchar(background[i - top][j - left]);

		}
	}
	//Delete top border
	Control::gotoXY(x, y);
	if (y - 4 >= getYAt(0, 0) && getCheck(x, y - 4) == DEL) {
		for (int i = x - 3; i <= x + 3; i++) {
			Control::gotoXY(i, y - 2);
			//putchar(32);
			putchar(background[y - 2 - top][i - left]);

		}
	}
	//Delete bottom border
	if (y + 4 <= getYAt(size - 1, size - 1) && getCheck(x, y + 4) == DEL) {
		for (int i = x - 3; i <= x + 3; i++) {
			Control::gotoXY(i, y + 2);
			//putchar(32);
			putchar(background[y + 2 - top][i - left]);
		}
	}
	//Delete left border
	if (x - 8 >= getXAt(0, 0) && getCheck(x - 8, y) == DEL) {
		for (int i = y - 1; i <= y + 1; i++) {
			Control::gotoXY(x - 4, i);
			//putchar(32);
			putchar(background[i - top][x - 4 - left]);
		}
	}
	//Delete right border
	if (x + 8 <= getXAt(size - 1, size - 1) && getCheck(x + 8, y) == DEL) {
		for (int i = y - 1; i <= y + 1; i++) {
			Control::gotoXY(x + 4, i);
			//putchar(32);
			putchar(background[i - top][x + 4 - left]);

		}
	}
}

void Board::drawLineI(pair<int, int>firstBlock, pair<int, int>secondBlock) {
	Control::setConsoleColor(RED, BRIGHT_WHITE);
	if (firstBlock.first == secondBlock.first) {
		Control::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(30);
		for (int i = firstBlock.second + 2; i <= secondBlock.second - 2; i++) {
			Control::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(31);
		return;
	}
	//========================================================================//
	if (firstBlock.second == secondBlock.second) {
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = firstBlock.first + 2; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
}

void Board::deleteLineI(pair<int, int>firstBlock, pair<int, int>secondBlock) {
	Control::setConsoleColor(BRIGHT_WHITE, BRIGHT_WHITE);
	if (firstBlock.first == secondBlock.first) {
		Control::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(32);
		for (int i = firstBlock.second + 2; i <= secondBlock.second - 2; i++) {
			Control::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(32);
		return;
	}
	//========================================================================//
	if (firstBlock.second == secondBlock.second) {
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(32);
		for (int i = firstBlock.first + 2; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(32);
		return;
	}
}

void Board::drawLineL(pair<int, int>firstBlock, pair<int, int>secondBlock, pair<int, int>Lcorner) {
	Control::setConsoleColor(RED, BRIGHT_WHITE);
	// down-left corner
	if (Lcorner.first < secondBlock.first && Lcorner.second > firstBlock.second) {
		Control::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(30);
		for (int i = firstBlock.second + 2; i <= Lcorner.second - 1; i++) {
			Control::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		for (int i = Lcorner.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
	//========================================================================//
	// up-left corner
	if (Lcorner.first < secondBlock.first && Lcorner.second < firstBlock.second) {
		Control::gotoXY(firstBlock.first, firstBlock.second - 1);
		putchar(31);
		for (int i = firstBlock.second - 2; i >= Lcorner.second + 1; i--) {
			Control::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		for (int i = Lcorner.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
	//========================================================================//
	// up-right corner
	if (Lcorner.second < secondBlock.second && Lcorner.first > firstBlock.first) {
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = firstBlock.first + 2; i <= Lcorner.first; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		for (int i = Lcorner.second + 1; i <= secondBlock.second - 2; i++) {
			Control::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(31);
		return;
	}
	//========================================================================//
	// down-right corner
	if (Lcorner.second > secondBlock.second && Lcorner.first > firstBlock.first) {
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = firstBlock.first + 2; i <= Lcorner.first; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		for (int i = Lcorner.second - 1; i >= secondBlock.second + 2; i--) {
			Control::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second + 1);
		putchar(30);
		return;
	}
}

void Board::deleteLineL(pair<int, int>firstBlock, pair<int, int>secondBlock, pair<int, int>Lcorner) {
	Control::setConsoleColor(BRIGHT_WHITE, BRIGHT_WHITE);
	// down-left corner
	if (Lcorner.first < secondBlock.first && Lcorner.second > firstBlock.second) {
		Control::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(32);
		for (int i = firstBlock.second + 2; i <= Lcorner.second - 1; i++) {
			Control::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		for (int i = Lcorner.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(32);
		return;
	}
	//========================================================================//
	// up-left corner
	if (Lcorner.first < secondBlock.first && Lcorner.second < firstBlock.second) {
		Control::gotoXY(firstBlock.first, firstBlock.second - 1);
		putchar(32);
		for (int i = firstBlock.second - 2; i >= Lcorner.second + 1; i--) {
			Control::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		for (int i = Lcorner.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(32);
		return;
	}
	//========================================================================//
	// up-right corner
	if (Lcorner.second < secondBlock.second && Lcorner.first > firstBlock.first) {
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(32);
		for (int i = firstBlock.first + 2; i <= Lcorner.first; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		for (int i = Lcorner.second + 1; i <= secondBlock.second - 2; i++) {
			Control::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(32);
		return;
	}
	//========================================================================//
	// down-right corner
	if (Lcorner.second > secondBlock.second && Lcorner.first > firstBlock.first) {
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(32);
		for (int i = firstBlock.first + 2; i <= Lcorner.first; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		for (int i = Lcorner.second - 1; i >= secondBlock.second + 2; i--) {
			Control::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second + 1);
		putchar(32);
		return;
	}
}

void Board::drawLineZ(pair<int, int>firstBlock, pair<int, int>secondBlock, pair<int, int>Zcorner1, pair<int, int>Zcorner2) {
	Control::setConsoleColor(RED, BRIGHT_WHITE);
	// down-left corner
	if (Zcorner1.first < secondBlock.first && Zcorner1.second > firstBlock.second) {
		Control::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(30);
		for (int i = firstBlock.second + 2; i <= Zcorner1.second - 1; i++) {
			Control::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		for (int i = Zcorner1.first; i <= Zcorner2.first; i++) {
			Control::gotoXY(i, Zcorner1.second);
			putchar(45);
		}
		for (int i = Zcorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Control::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(31);
		return;
	}
	//========================================================================//
	// up-left corner
	if (Zcorner1.first > secondBlock.first && Zcorner1.second > firstBlock.second) {
		Control::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(30);
		for (int i = firstBlock.second + 2; i <= Zcorner1.second - 1; i++) {
			Control::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		for (int i = Zcorner1.first; i >= Zcorner2.first; i--) {
			Control::gotoXY(i, Zcorner1.second);
			putchar(45);
		}
		for (int i = Zcorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Control::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(31);
		return;
	}
	//========================================================================//
	// up-right corner
	if (Zcorner1.second < secondBlock.second && Zcorner1.first > firstBlock.first) {
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = firstBlock.first + 2; i <= Zcorner1.first; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		for (int i = Zcorner1.second + 1; i <= Zcorner2.second - 1; i++) {
			Control::gotoXY(Zcorner1.first, i);
			putchar(179);
		}
		for (int i = Zcorner2.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
	//========================================================================//
	// down-right corner
	if (Zcorner1.second > secondBlock.second && Zcorner1.first > firstBlock.first) {
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = firstBlock.first + 2; i <= Zcorner1.first; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		for (int i = Zcorner1.second - 1; i >= Zcorner2.second + 1; i--) {
			Control::gotoXY(Zcorner1.first, i);
			putchar(179);
		}
		for (int i = Zcorner2.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
}

void Board::deleteLineZ(pair<int, int>firstBlock, pair<int, int>secondBlock, pair<int, int>Zcorner1, pair<int, int>Zcorner2) {
	Control::setConsoleColor(BRIGHT_WHITE, BRIGHT_WHITE);
	// down-left corner
	if (Zcorner1.first < secondBlock.first && Zcorner1.second > firstBlock.second) {
		Control::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(32);
		for (int i = firstBlock.second + 2; i <= Zcorner1.second - 1; i++) {
			Control::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		for (int i = Zcorner1.first; i <= Zcorner2.first; i++) {
			Control::gotoXY(i, Zcorner1.second);
			putchar(32);
		}
		for (int i = Zcorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Control::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(32);
		return;
	}
	//========================================================================//
	// up-left corner
	if (Zcorner1.first > secondBlock.first && Zcorner1.second > firstBlock.second) {
		Control::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(32);
		for (int i = firstBlock.second + 2; i <= Zcorner1.second - 1; i++) {
			Control::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		for (int i = Zcorner1.first; i >= Zcorner2.first; i--) {
			Control::gotoXY(i, Zcorner1.second);
			putchar(32);
		}
		for (int i = Zcorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Control::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(32);
		return;
	}
	//========================================================================//
	// up-right corner
	if (Zcorner1.second < secondBlock.second && Zcorner1.first > firstBlock.first) {
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(32);
		for (int i = firstBlock.first + 2; i <= Zcorner1.first; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		for (int i = Zcorner1.second + 1; i <= Zcorner2.second - 1; i++) {
			Control::gotoXY(Zcorner1.first, i);
			putchar(32);
		}
		for (int i = Zcorner2.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(32);
		return;
	}
	//========================================================================//
	// down-right corner
	if (Zcorner1.second > secondBlock.second && Zcorner1.first > firstBlock.first) {
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(32);
		for (int i = firstBlock.first + 2; i <= Zcorner1.first; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		for (int i = Zcorner1.second - 1; i >= Zcorner2.second + 1; i--) {
			Control::gotoXY(Zcorner1.first, i);
			putchar(32);
		}
		for (int i = Zcorner2.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(32);
		return;
	}
}

void Board::drawLineU(pair<int, int>firstBlock, pair<int, int>secondBlock, pair<int, int>Ucorner1, pair<int, int>Ucorner2) {
	Control::setConsoleColor(RED, BRIGHT_WHITE);
	//========================================================================//
	if (Ucorner1.first < firstBlock.first && Ucorner1.second < secondBlock.second) {
		for (int i = Ucorner1.first; i <= firstBlock.first - 2; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		Control::gotoXY(firstBlock.first - 1, firstBlock.second);
		putchar(16);
		for (int i = Ucorner1.second + 1; i <= Ucorner2.second - 1; i++) {
			Control::gotoXY(Ucorner1.first, i);
			putchar(179);
		}
		for (int i = Ucorner2.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
	if (Ucorner1.first < firstBlock.first && Ucorner1.second > secondBlock.second) {
		for (int i = Ucorner1.first; i <= firstBlock.first - 2; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		Control::gotoXY(firstBlock.first - 1, firstBlock.second);
		putchar(16);
		for (int i = Ucorner1.second - 1; i >= Ucorner2.second + 1; i--) {
			Control::gotoXY(Ucorner1.first, i);
			putchar(179);
		}
		for (int i = Ucorner2.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
	//========================================================================//
	if (Ucorner1.first > firstBlock.first && Ucorner1.second < secondBlock.second) {
		for (int i = Ucorner1.first; i >= firstBlock.first + 2; i--) {
			Control::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = Ucorner1.second + 1; i <= Ucorner2.second - 1; i++) {
			Control::gotoXY(Ucorner1.first, i);
			putchar(179);
		}
		for (int i = Ucorner2.first; i >= secondBlock.first + 2; i--) {
			Control::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Control::gotoXY(secondBlock.first + 1, secondBlock.second);
		putchar(17);
		return;
	}
	if (Ucorner1.first > firstBlock.first && Ucorner1.second > secondBlock.second) {
		for (int i = Ucorner1.first; i >= firstBlock.first + 2; i--) {
			Control::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = Ucorner1.second - 1; i >= Ucorner2.second + 1; i++) {
			Control::gotoXY(Ucorner1.first, i);
			putchar(179);
		}
		for (int i = Ucorner2.first; i >= secondBlock.first + 2; i--) {
			Control::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Control::gotoXY(secondBlock.first + 1, secondBlock.second);
		putchar(17);
		return;
	}
	//========================================================================//
	if (Ucorner1.second < firstBlock.second && Ucorner1.first < secondBlock.first) {
		for (int i = Ucorner1.second + 1; i <= firstBlock.second - 2; i++) {
			Control::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		Control::gotoXY(firstBlock.first, firstBlock.second - 1);
		putchar(31);
		for (int i = Ucorner1.first; i <= Ucorner2.first; i++) {
			Control::gotoXY(i, Ucorner1.second);
			putchar(45);
		}
		for (int i = Ucorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Control::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(31);
		return;
	}
	if (Ucorner1.second < firstBlock.second && Ucorner1.first > secondBlock.first) {
		for (int i = Ucorner1.second + 1; i <= firstBlock.second - 2; i++) {
			Control::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		Control::gotoXY(firstBlock.first, firstBlock.second - 1);
		putchar(31);
		for (int i = Ucorner1.first; i >= Ucorner2.first; i--) {
			Control::gotoXY(i, Ucorner1.second);
			putchar(45);
		}
		for (int i = Ucorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Control::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(31);
		return;
	}
	//========================================================================//
	if (Ucorner1.second > firstBlock.second && Ucorner1.first < secondBlock.first) {
		for (int i = Ucorner1.second - 1; i >= firstBlock.second + 2; i--) {
			Control::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		Control::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(30);
		for (int i = Ucorner1.first; i <= Ucorner2.first; i++) {
			Control::gotoXY(i, Ucorner1.second);
			putchar(45);
		}
		for (int i = Ucorner2.second - 1; i >= secondBlock.second + 2; i--) {
			Control::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second + 1);
		putchar(30);
		return;
	}
	if (Ucorner1.second > firstBlock.second && Ucorner1.first > secondBlock.first) {
		for (int i = Ucorner1.second - 1; i >= firstBlock.second + 2; i--) {
			Control::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		Control::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(30);
		for (int i = Ucorner1.first; i >= Ucorner2.first; i--) {
			Control::gotoXY(i, Ucorner1.second);
			putchar(45);
		}
		for (int i = Ucorner2.second - 1; i >= secondBlock.second + 2; i--) {
			Control::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second + 1);
		putchar(30);
		return;
	}
}

void Board::deleteLineU(pair<int, int>firstBlock, pair<int, int>secondBlock, pair<int, int>Ucorner1, pair<int, int>Ucorner2) {
	Control::setConsoleColor(BRIGHT_WHITE, BRIGHT_WHITE);
	//========================================================================//
	if (Ucorner1.first < firstBlock.first && Ucorner1.second < secondBlock.second) {
		for (int i = Ucorner1.first; i <= firstBlock.first - 2; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		Control::gotoXY(firstBlock.first - 1, firstBlock.second);
		putchar(32);
		for (int i = Ucorner1.second + 1; i <= Ucorner2.second - 1; i++) {
			Control::gotoXY(Ucorner1.first, i);
			putchar(32);
		}
		for (int i = Ucorner2.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(32);
		return;
	}
	if (Ucorner1.first < firstBlock.first && Ucorner1.second > secondBlock.second) {
		for (int i = Ucorner1.first; i <= firstBlock.first - 2; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		Control::gotoXY(firstBlock.first - 1, firstBlock.second);
		putchar(32);
		for (int i = Ucorner1.second - 1; i >= Ucorner2.second + 1; i--) {
			Control::gotoXY(Ucorner1.first, i);
			putchar(32);
		}
		for (int i = Ucorner2.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(32);
		return;
	}
	//========================================================================//
	if (Ucorner1.first > firstBlock.first && Ucorner1.second < secondBlock.second) {
		for (int i = Ucorner1.first; i >= firstBlock.first + 2; i--) {
			Control::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(32);
		for (int i = Ucorner1.second + 1; i <= Ucorner2.second - 1; i++) {
			Control::gotoXY(Ucorner1.first, i);
			putchar(32);
		}
		for (int i = Ucorner2.first; i >= secondBlock.first + 2; i--) {
			Control::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first + 1, secondBlock.second);
		putchar(32);
		return;
	}
	if (Ucorner1.first > firstBlock.first && Ucorner1.second > secondBlock.second) {
		for (int i = Ucorner1.first; i >= firstBlock.first + 2; i--) {
			Control::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(32);
		for (int i = Ucorner1.second - 1; i >= Ucorner2.second + 1; i++) {
			Control::gotoXY(Ucorner1.first, i);
			putchar(32);
		}
		for (int i = Ucorner2.first; i >= secondBlock.first + 2; i--) {
			Control::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first + 1, secondBlock.second);
		putchar(32);
		return;
	}
	//========================================================================//
	if (Ucorner1.second < firstBlock.second && Ucorner1.first < secondBlock.first) {
		for (int i = Ucorner1.second + 1; i <= firstBlock.second - 2; i++) {
			Control::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		Control::gotoXY(firstBlock.first, firstBlock.second - 1);
		putchar(32);
		for (int i = Ucorner1.first; i <= Ucorner2.first; i++) {
			Control::gotoXY(i, Ucorner1.second);
			putchar(32);
		}
		for (int i = Ucorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Control::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(32);
		return;
	}
	if (Ucorner1.second < firstBlock.second && Ucorner1.first > secondBlock.first) {
		for (int i = Ucorner1.second + 1; i <= firstBlock.second - 2; i++) {
			Control::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		Control::gotoXY(firstBlock.first, firstBlock.second - 1);
		putchar(32);
		for (int i = Ucorner1.first; i >= Ucorner2.first; i--) {
			Control::gotoXY(i, Ucorner1.second);
			putchar(32);
		}
		for (int i = Ucorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Control::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(32);
		return;
	}
	//========================================================================//
	if (Ucorner1.second > firstBlock.second && Ucorner1.first < secondBlock.first) {
		for (int i = Ucorner1.second - 1; i >= firstBlock.second + 2; i--) {
			Control::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		Control::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(32);
		for (int i = Ucorner1.first; i <= Ucorner2.first; i++) {
			Control::gotoXY(i, Ucorner1.second);
			putchar(32);
		}
		for (int i = Ucorner2.second - 1; i >= secondBlock.second + 2; i--) {
			Control::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second + 1);
		putchar(32);
		return;
	}
	if (Ucorner1.second > firstBlock.second && Ucorner1.first > secondBlock.first) {
		for (int i = Ucorner1.second - 1; i >= firstBlock.second + 2; i--) {
			Control::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		Control::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(32);
		for (int i = Ucorner1.first; i >= Ucorner2.first; i--) {
			Control::gotoXY(i, Ucorner1.second);
			putchar(32);
		}
		for (int i = Ucorner2.second - 1; i >= secondBlock.second + 2; i--) {
			Control::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Control::gotoXY(secondBlock.first, secondBlock.second + 1);
		putchar(32);
		return;
	}
}

void Board::createBackground() {
	ifstream bg;
	if (size == 4)
		bg.open("easy.txt");
	else
		bg.open("images\\medium.txt");
	int i = 0;
	while (!bg.eof()) {
		getline(bg, background[i]);
		i++;
		break;
	}
	bg.close();
}
#include "Board.h"

Board::Board(int psizeRow, int psizeCol, int pX, int pY, char mode[]) : sizeRow(psizeRow), sizeCol(psizeCol), left(pX), top(pY)
{
	character = new int* [sizeRow];
	for (int i = 0; i < sizeRow; i++)
		character[i] = new int[sizeCol];

	pBoard = new Point * [sizeRow];
	for (int i = 0; i < sizeRow; i++)
		pBoard[i] = new Point[sizeCol];

	if (strcmp(mode, "EASY") == 0 || strcmp(mode, "MEDIUM") == 0)
		background = new string[sizeRow * 4 + 1];
	else
		background = new string[10 * 4 + 1];
}

Board::~Board()
{
	for (int i = 0; i < sizeRow; i++)
		delete[] pBoard[i];
	delete[] pBoard,
		pBoard = nullptr;

	for (int i = 0; i < sizeRow; i++)
		delete[] character[i];
	delete[] character,
		character = nullptr;

	delete[] background;
	background = nullptr;
}

int Board::getSizeRow()
{
	return sizeRow;
}

int Board::getSizeCol()
{
	return sizeCol;
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
	for (int i = 0; i < sizeRow; i++)
	{
		for (int j = 0; j < sizeCol; j++)
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

int Board::getCheckLockAll(int x, int y)
{
	for (int i = -4; i <= 4; i += 4) {
		for (int j = -8; j <= 8; j += 8) {
			if (x + j < getXAt(0, 0) || x + j > getXAt(0, sizeCol - 1) || y + i < getYAt(0, 0) || y + i > getYAt(sizeRow - 1, 0) || i == j)
				continue;
			if (getCheck(x + j, y + i) == LOCK)
			{
				if (j == -8 && i == -4)
					return 1;
				if (j == 0 && i == -4)
					return 2;
				if (j == 8 && i == -4)
					return 3;
				if (j == -8 && i == 0)
					return 4;
				if (j == 8 && i == 0)
					return 5;
				if (j == -8 && i == 4)
					return 6;
				if (j == 0 && i == 4)
					return 7;
				if (j == 8 && i == 4)
					return 8;
			}
		}
	}
	return 0;
}

int Board::getCheckUpperLeft(int x, int y)
{
	int j = -8, i = -4;

	if ((x + j >= getXAt(0, 0) && x + j <= getXAt(0, sizeCol - 1) && y + i >= getYAt(0, 0) && y + i <= getYAt(sizeRow - 1, 0))
		&& (getCheck(x + j, y + i) == DEL && getCheck(x + j, y) == DEL && getCheck(x, y + i) == DEL) && getCheck(x, y) == DEL)
		return 9;
	else
		return getCheckLockAll(x, y);
}


int Board::getCheckUpperRight(int x, int y)
{
	int j = +8, i = -4;

	if ((x + j >= getXAt(0, 0) && x + j <= getXAt(0, sizeCol - 1) && y + i >= getYAt(0, 0) && y + i <= getYAt(sizeRow - 1, 0))
		&& (getCheck(x + j, y + i) == DEL && getCheck(x + j, y) == DEL && getCheck(x, y + i) == DEL) && getCheck(x, y) == DEL)
		return 9;
	else
		return getCheckLockAll(x, y);
}


int Board::getCheckBottomLeft(int x, int y)
{
	int j = -8, i = +4;

	if ((x + j >= getXAt(0, 0) && x + j <= getXAt(0, sizeCol - 1) && y + i >= getYAt(0, 0) && y + i <= getYAt(sizeRow - 1, 0))
		&& (getCheck(x + j, y + i) == DEL && getCheck(x + j, y) == DEL && getCheck(x, y + i) == DEL) && getCheck(x, y) == DEL)
		return 9;
	else
		return getCheckLockAll(x, y);
}



int Board::getCheckBottomRight(int x, int y)
{
	int j = +8, i = +4;

	if ((x + j >= getXAt(0, 0) && x + j <= getXAt(0, sizeCol - 1) && y + i >= getYAt(0, 0) && y + i <= getYAt(sizeRow - 1, 0))
		&& (getCheck(x + j, y + i) == DEL && getCheck(x + j, y) == DEL && getCheck(x, y + i) == DEL) && getCheck(x, y) == DEL)
		return 9;
	else
		return getCheckLockAll(x, y);
}



/////////////////////////////////////////////////////////////////////

void Board::showBoard()
{
	if (pBoard == NULL)
		return;
	Control::setConsoleColor(WHITE, BLACK);
	Control::clearConsole();

	// Draw top line
	Control::gotoXY(left + 1, top);
	putchar(43);
	for (int i = 1; i < sizeCol * 8; i++)
	{
		Sleep(5);
		if (i % 8 == 0)
			putchar(43);
		else
			putchar(45);
	}
	putchar(43);

	// Draw right line
	for (int i = 1; i < sizeRow * 4; i++)
	{
		Sleep(10);
		Control::gotoXY(sizeCol * 8 + left + 1, i + top);
		if (i % 4 != 0)
			putchar(179);
		else
			putchar(43);
	}
	Control::gotoXY(sizeCol * 8 + left + 1, sizeRow * 4 + top);
	putchar(43);

	// Draw bottom line
	for (int i = 1; i < sizeCol * 8; i++)
	{
		Control::gotoXY(sizeCol * 8 + left - i + 1, sizeRow * 4 + top);
		Sleep(5);
		if (i % 8 == 0)
			putchar(43);
		else
			putchar(45);
	}
	Control::gotoXY(left + 1, sizeRow * 4 + top);
	putchar(43);

	// Draw left line
	for (int i = 1; i < sizeRow * 4; i++)
	{
		Sleep(10);
		Control::gotoXY(left + 1, sizeRow * 4 + top - i);
		if (i % 4 != 0)
			putchar(179);
		else
			putchar(43);
	}

	// Draw vertical lines
	for (int i = 1; i < sizeRow * 4; i++)
	{
		for (int j = 8; j < sizeCol * 8; j += 8)
		{
			Control::gotoXY(j + left + 1, i + top);
			if (i % 4 != 0)
				putchar(179);
			else
				putchar(43);
		}
		Sleep(10);
	}

	// Draw horizontal lines
	for (int i = 1; i < sizeCol * 8; i++)
	{
		for (int j = 4; j < sizeRow * 4; j += 4)
		{
			Control::gotoXY(i + left + 1, j + top);
			if (i % 8 == 0)
				putchar(43);
			else
				putchar(45);
		}
		Sleep(5);
	}
}

void Board::renderBoard() {
	for (int i = 0; i < sizeRow; i++)
	{
		for (int j = 0; j < sizeCol; j++)
		{
			pBoard[i][j].setX(8 * j + left + 5); // x-value of boardgame
			pBoard[i][j].setY(4 * i + top + 2); // y-value of boardgame
			pBoard[i][j].setCheck(0);

			int r = pBoard[i][j].getX();
			int c = pBoard[i][j].getY();

			if (pBoard[i][j].getCharacter() % 16 != 7 && pBoard[i][j].getCharacter() % 16 != 11
				&& pBoard[i][j].getCharacter() % 16 != 14 && pBoard[i][j].getCharacter() % 16 != 15)
				Control::setConsoleColor(WHITE, pBoard[i][j].getCharacter() % 16);
			else
				Control::setConsoleColor(WHITE, (pBoard[i][j].getCharacter() + 2) % 16);


			Control::gotoXY(r, c);
			putchar(pBoard[i][j].getCharacter());
		}
	}
}

void Board::renderBoardForLoad(int** status) {
	for (int i = 0; i < sizeRow; i++)
	{
		for (int j = 0; j < sizeCol; j++)
		{
			pBoard[i][j].setX(8 * j + left + 5); // x-value of boardgame
			pBoard[i][j].setY(4 * i + top + 2); // y-value of boardgame
			pBoard[i][j].setCheck(status[i][j]);

			if (pBoard[i][j].getCheck() == 1)
				pBoard[i][j].setCheck(0);

			int r = pBoard[i][j].getX();
			int c = pBoard[i][j].getY();

			if (pBoard[i][j].getCheck() != -1)
			{
				if (pBoard[i][j].getCharacter() % 16 != 7 && pBoard[i][j].getCharacter() % 16 != 11
					&& pBoard[i][j].getCharacter() % 16 != 14 && pBoard[i][j].getCharacter() % 16 != 15)
					Control::setConsoleColor(WHITE, pBoard[i][j].getCharacter() % 16);
				else
					Control::setConsoleColor(WHITE, (pBoard[i][j].getCharacter() + 2) % 16);


				Control::gotoXY(r, c);
				putchar(pBoard[i][j].getCharacter());
			}

		}
	}
}

void Board::buildBoardData() {
	srand((unsigned int)time(NULL));

	bool* checkDuplicate = new bool[sizeRow * sizeCol];
	int* pos = new int[sizeRow * sizeCol];

	// Random characters
	for (int i = 0; i < sizeRow; i++) {
		for (int j = 0; j < sizeCol; j += 2) {
			character[i][j] = character[i][j + 1] = rand() % 26 + 'A';
		}
	}

	// Random characters position 
	for (int i = 0; i < sizeRow * sizeCol; i++)
		checkDuplicate[i] = 0;
	for (int i = 0; i < sizeRow * sizeCol; i++) {
		int tmp = 0;
		do {
			tmp = rand() % (sizeRow * sizeCol);
		} while (checkDuplicate[tmp]);
		checkDuplicate[tmp] = 1;
		pos[i] = tmp;
	}
	Control::gotoXY(0, 0);
	// Construct pokemons matrix
	for (int i = 0; i < sizeRow; i++) {
		for (int j = 0; j < sizeCol; j++) {
			int r = pos[sizeCol * i + j] / sizeCol;
			int c = pos[sizeCol * i + j] % sizeCol;
			pBoard[i][j].setCharacter(character[r][c]);
		}
	}

	delete[] pos;
	delete[] checkDuplicate;
}

void Board::buildBoardDataForLoad(char** pokemon) {
	// Construct pokemons matrix
	for (int i = 0; i < sizeRow; ++i)
		for (int j = 0; j < sizeCol; ++j)
			pBoard[i][j].setCharacter(pokemon[i][j]);
}

void Board::selectedBlock(int x, int y, int color) {
	Control::setConsoleColor(WHITE, color);
	Graphic::printFrame(x, y);
}

void Board::unselectedBlock(int x, int y) {
	if (getCheck(x, y) != DEL) {
		int r = getRAt(x, y);
		int c = getCAt(x, y);
		pBoard[r][c].setCheck(NORMAL);
	}

	Graphic::backUpperLeft(x, y, getCheckUpperLeft(x, y), background);
	Graphic::backUpperRight(x, y, getCheckUpperRight(x, y), background);
	Graphic::backBottomLeft(x, y, getCheckBottomLeft(x, y), background);
	Graphic::backBottomRight(x, y, getCheckBottomRight(x, y), background);
	Control::setConsoleColor(WHITE, BLACK);
}

void Board::lockBlock(int x, int y)
{
	int r = getRAt(x, y);
	int c = getCAt(x, y);	
	pBoard[r][c].setCheck(LOCK);

	Control::setConsoleColor(WHITE, LIGHT_RED);
	Graphic::printFrame(x, y);
}

void Board::deleteBlock(int x, int y)
{
	int r = getRAt(x, y);
	int c = getCAt(x, y);
	pBoard[r][c].setCheck(DEL);

	Control::setConsoleColor(WHITE, BLACK);
	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 3; j <= x + 3; j++) {
			Control::gotoXY(j, i);
			putchar(background[i - top][j - left]);
		}
	}

	unselectedBlock(x, y);

	Control::setConsoleColor(WHITE, BLACK);

	//Delete top border
	if (y - 4 >= Board::getYAt(0, 0) && Board::getCheck(x, y - 4) == DEL) {
		for (int i = x - 3; i <= x + 3; i++) {
			Control::gotoXY(i, y - 2);
			putchar(background[y - 2 - Top][i - Left]);
		}
	}

	//Delete bottom border
	if (y + 4 <= getYAt(sizeRow - 1, sizeCol - 1) && getCheck(x, y + 4) == DEL) {
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
	if (x + 8 <= getXAt(sizeRow - 1, sizeCol - 1) && getCheck(x + 8, y) == DEL) {
		for (int i = y - 1; i <= y + 1; i++) {
			Control::gotoXY(x + 4, i);
			//putchar(32);
			putchar(background[i - top][x + 4 - left]);
		}
	}
}

void Board::updateBackground()
{
	for (int i = getYAt(0, 0); i <= getYAt(sizeRow - 1, 0); i += 4)
		for (int j = getXAt(0, 0); j <= getXAt(0, sizeCol - 1); j += 8)
			if (Board::getCheck(j, i) == DEL)
				Board::deleteBlock(j, i);
}


//////////////////////////////////////////////////////////////////////////////

void Board::drawLineI(pair<int, int>firstBlock, pair<int, int>secondBlock) {
	Control::setConsoleColor(WHITE, BLACK);
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
			putchar(196);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
}

void Board::deleteLineI(pair<int, int>firstBlock, pair<int, int>secondBlock) {
	Control::setConsoleColor(WHITE, WHITE);
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
	Control::setConsoleColor(WHITE, BLACK);
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
			putchar(196);
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
			putchar(196);
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
			putchar(196);
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
			putchar(196);
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
	Control::setConsoleColor(WHITE, WHITE);
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
	Control::setConsoleColor(WHITE, BLACK);
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
			putchar(196);
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
			putchar(196);
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
			putchar(196);
		}
		for (int i = Zcorner1.second + 1; i <= Zcorner2.second - 1; i++) {
			Control::gotoXY(Zcorner1.first, i);
			putchar(179);
		}
		for (int i = Zcorner2.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(196);
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
			putchar(196);
		}
		for (int i = Zcorner1.second - 1; i >= Zcorner2.second + 1; i--) {
			Control::gotoXY(Zcorner1.first, i);
			putchar(179);
		}
		for (int i = Zcorner2.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(196);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
}

void Board::deleteLineZ(pair<int, int>firstBlock, pair<int, int>secondBlock, pair<int, int>Zcorner1, pair<int, int>Zcorner2) {
	Control::setConsoleColor(WHITE, WHITE);
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
	Control::setConsoleColor(WHITE, BLACK);
	//========================================================================//
	if (Ucorner1.first < firstBlock.first && Ucorner1.second < secondBlock.second) {
		for (int i = Ucorner1.first; i <= firstBlock.first - 2; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(196);
		}
		Control::gotoXY(firstBlock.first - 1, firstBlock.second);
		putchar(16);
		for (int i = Ucorner1.second + 1; i <= Ucorner2.second - 1; i++) {
			Control::gotoXY(Ucorner1.first, i);
			putchar(179);
		}
		for (int i = Ucorner2.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(196);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
	if (Ucorner1.first < firstBlock.first && Ucorner1.second > secondBlock.second) {
		for (int i = Ucorner1.first; i <= firstBlock.first - 2; i++) {
			Control::gotoXY(i, firstBlock.second);
			putchar(196);
		}
		Control::gotoXY(firstBlock.first - 1, firstBlock.second);
		putchar(16);
		for (int i = Ucorner1.second - 1; i >= Ucorner2.second + 1; i--) {
			Control::gotoXY(Ucorner1.first, i);
			putchar(179);
		}
		for (int i = Ucorner2.first; i <= secondBlock.first - 2; i++) {
			Control::gotoXY(i, secondBlock.second);
			putchar(196);
		}
		Control::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
	//========================================================================//
	if (Ucorner1.first > firstBlock.first && Ucorner1.second < secondBlock.second) {
		for (int i = Ucorner1.first; i >= firstBlock.first + 2; i--) {
			Control::gotoXY(i, firstBlock.second);
			putchar(196);
		}
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = Ucorner1.second + 1; i <= Ucorner2.second - 1; i++) {
			Control::gotoXY(Ucorner1.first, i);
			putchar(179);
		}
		for (int i = Ucorner2.first; i >= secondBlock.first + 2; i--) {
			Control::gotoXY(i, secondBlock.second);
			putchar(196);
		}
		Control::gotoXY(secondBlock.first + 1, secondBlock.second);
		putchar(17);
		return;
	}
	if (Ucorner1.first > firstBlock.first && Ucorner1.second > secondBlock.second) {
		for (int i = Ucorner1.first; i >= firstBlock.first + 2; i--) {
			Control::gotoXY(i, firstBlock.second);
			putchar(196);
		}
		Control::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = Ucorner1.second - 1; i <= Ucorner2.second + 1; i++) {
			Control::gotoXY(Ucorner1.first, i);
			putchar(179);
		}
		for (int i = Ucorner2.first; i >= secondBlock.first + 2; i--) {
			Control::gotoXY(i, secondBlock.second);
			putchar(196);
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
			putchar(196);
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
			putchar(196);
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
			putchar(196);
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
			putchar(196);
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
	Control::setConsoleColor(WHITE, WHITE);
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
		for (int i = Ucorner1.second - 1; i <= Ucorner2.second + 1; i++) {
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

//notice
void Board::createBackground(char mode[]) {
	ifstream bg;
	if (strcmp(mode, "EASY") == 0)
		bg.open("background\\easy.txt");
	else if (strcmp(mode, "MEDIUM") == 0)
		bg.open("background\\medium.txt");
	else
		bg.open("background\\custom.txt");
	int i = 0;
	while (!bg.eof()) {
		getline(bg, background[i]);
		i++;
	}
	bg.close();
}
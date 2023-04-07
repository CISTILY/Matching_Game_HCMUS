#pragma once
#include "Board.h"
#include "Point.h"
#include "Menu.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define LEFT 6
#define TOP 2
#define DISTANCE 6

#define NAMESIZE 50
#define PASSSIZE 50

using namespace std;

struct Game {
	Board* board;				// Create new board
	char playerName[NAMESIZE] = "", password[PASSSIZE] = "", mode[15] = "";
	int _row;
	int _col;
	int _x, _y;
	bool isPlaying;
	int _lockedBlock;
	int _remainBlocks;
	int score;

	vector<pair<int, int>> _lockedBlockPair; //First: row - Second: column

	bool checkMatchedPokemons(pair<int, int>, pair<int, int>);
	int checkIMatching(pair<int, int>, pair<int, int>, bool);
	bool checkLMatching(pair<int, int>, pair<int, int>, bool);
	bool checkZMatching(pair<int, int>, pair<int, int>, bool);
	bool checkUMatching(pair<int, int>, pair<int, int>, bool);
	bool checkMatching(pair<int, int>, pair<int, int>, bool);

	Game(char[], char[], int, int, int);
	~Game();

	void setupGame(int);
	void startGame();
	void printInterface();
	void saveData();

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	char getCharacter(int x, int y);

	void lockBlock();
	void deleteBlock();
	bool isAvailableBlock(bool);

	void askContinue();
	void moveSuggestion();
};


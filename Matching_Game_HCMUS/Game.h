#pragma once
#include "Board.h"
#include "Point.h"
#include "Menu.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <thread>
#include <ctime>


#define LEFT 6
#define TOP 2
#define DISTANCE 6

#define PADDING 500 // bytes
#define NAMESIZE 50
#define PASSSIZE 50
#define BOARDSIZE 999
#define URLSIZE 100

using namespace std;

struct Date {
	int dd, mm, yy;
};
struct Time {
	int minute, second;
};
struct Record {
	Date date; // Date of completed record
	Time time;	// Time playing
	int points; // points achieved
	// 500 byte NULL
};

void WriteBlockChar(char[][41], int, int, int, int, int);
void findTimeLeft(int, int, int, int, int, int, int&, int&);
void createClock(int, int, int, Board*, Record*);

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
	int minute;
	int second;
	int play_minute;
	int play_second;
	Record* record;


	vector<pair<int, int>> _lockedBlockPair; //First: row - Second: column

	bool checkMatchedPokemons(pair<int, int>, pair<int, int>, Board*);
	int checkIMatching(pair<int, int>, pair<int, int>, bool, Board*);
	bool checkLMatching(pair<int, int>, pair<int, int>, bool, Board*);
	bool checkZMatching(pair<int, int>, pair<int, int>, bool, Board*);
	bool checkUMatching(pair<int, int>, pair<int, int>, bool, Board*);
	bool checkMatching(pair<int, int>, pair<int, int>, bool, Board*);

	Game(char[], char[], int, int, int);
	Game(char[], char[], char[], int, int, int, int, int, int**);
	~Game();

	void startGame();
	void startGameForLoad(char**, int**, int, int);
	void printInterface();
	void printInterfaceForLoad(char**, int**);
	void saveData();
	void saveGame();

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	char getCharacter(int x, int y);

	void lockBlock();
	void deleteBlock();
	bool isAvailableBlock(bool, Board*);

	void askContinue();
	void moveSuggestion();
};

struct State { //Representing a board state
	int p, q; // Size of the board game
	int p_, q_; // Current cursor position
	char board[BOARDSIZE]; // Current board state
	char file_background[URLSIZE]; // Link to background file. This variable’s value is NULL if there is no current background

	// 500 byte NULL
};

struct savefile {
	char mask; // You are required to transfer all char-type variables by performing xor each with the mask - variable, bit - by - bit.
	char name[NAMESIZE]; // username
	char password[PASSSIZE]; // password
	// 500 byte NULL
	Record record[5]; // List of sorted best records
	State state[5]; // List of save state
};
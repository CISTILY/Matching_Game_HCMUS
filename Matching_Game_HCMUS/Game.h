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

#define PADDING 500
#define NAMESIZE 50
#define PASSSIZE 50
#define MODESIZE 15
#define BOARDSIZE 999
#define URLSIZE 100

using namespace std;

struct Date2 {
	int dd, mm, yy;
};

struct Time2 {
	int minuteplay, secondplay;
};

struct Record2 {
	Date2 date; // Date of completed record
	Time2 time;	// Time playing
	int points; // points achieved
	// 500 byte NULL
};

struct State2 { //Representing a board state
	Record2 state_record;
	char mode[MODESIZE];
	int p, q;
	int p_, q_;
	char board[BOARDSIZE];
	int status[100];
	char file_background[URLSIZE];
};

struct savefile2 {
	char mask; // You are required to transfer all char-type variables by performing xor each with the mask - variable, bit - by - bit.
	char name[NAMESIZE]; // username
	char password[PASSSIZE]; // password
	// 500 byte NULL
	Record2 record[5]; // List of sorted best records
	State2 state[5]; // List of save state
};

void WriteBlockChar(char[][41], int, int, int, int, int);
void findTimeLeft(int, int, int, int, int, int, int&, int&);
void createClock(int, int, int, Board*, savefile2*);

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
	savefile2* save = NULL;


	vector<pair<int, int>> _lockedBlockPair; //First: row - Second: column

	bool checkMatchedCharacters(pair<int, int>, pair<int, int>, Board*);
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

	void changeFile2(int, bool, int&);					// Thay đổi file game
	void chooseFile2(int&);								// Chọn file
	void readFileGame2(int&);									// Đọc file save
	void saveGame();

	void moveRight();							//Di chuyển qua phải
	void moveLeft();							//Di chuyển qua trái	
	void moveUp();								//Di chuyển qua lên
	void moveDown();							//Di chuyển qua xuống

	char getCharacter(int x, int y);			//Lấy toạ độ của chữ

	void lockBlock();
	void deleteBlock();
	bool isAvailableBlock(bool, Board*);

	void askContinue();							//Chơi tiếp
	void moveSuggestion();						//Gợi ý
};


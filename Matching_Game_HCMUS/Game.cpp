#include "Game.h"

Game::Game(char accountplayerName[], char accountpassword[], int row, int col, int curent_option)
{
	_row = row;
	_col = col;
	_x = LEFT, _y = TOP;

	isPlaying = true;
	_lockedBlock = 0;
	_lockedBlockPair.clear();
	_remainBlocks = _row * _col;
	score = 0;

	strcpy_s(playerName, accountplayerName);
	strcpy_s(password, accountpassword);

	if (curent_option == 8)
	{
		strcpy_s(mode, "EASY");
		minute = 0;
		second = 45;
	}

	else if (curent_option == 9)
	{
		strcpy_s(mode, "MEDIUM");
		minute = 1;
		second = 30;
	}
	else
	{
		strcpy_s(mode, "CUSTOM ");
		strcat_s(mode, to_string(_row).c_str());
		strcat_s(mode, " x ");
		strcat_s(mode, to_string(_col).c_str());

		second = row * col * 6;
		minute = second / 60;
		second = second % 60;
	}

	board = new Board(_row, _col, LEFT, TOP, mode);
	board->stop = 1;
	save = new savefile2[2];
}

Game::Game(char accountplayerName[], char accountpassword[], char accountmode[], int accountscore, int accountminuteplay, int accountsecondplay,
	int accountrowplay, int accountcolplay, int** accountstatus)
{
	int i = 0, j = 0;


	_row = accountrowplay;
	_col = accountcolplay;
	_x = LEFT, _y = TOP;
	_remainBlocks = 0;
	isPlaying = true;

	_lockedBlock = 0;
	_lockedBlockPair.clear();

	for (i = 0; i < accountrowplay; ++i)
		for (j = 0; j < accountcolplay; ++j)
			if (accountstatus[i][j] != -1)
				++_remainBlocks;

	score = accountscore;

	strcpy_s(playerName, accountplayerName);
	strcpy_s(password, accountpassword);
	strcpy_s(mode, accountmode);

	if (strcmp(mode, "EASY") == 0)
	{
		second = 45 - accountsecondplay;
		minute = 0 - accountminuteplay;
	}
	else if (strcmp(mode, "MEDIUM") == 0)
	{
		second = 30 - accountsecondplay;
		if (second < 0)
		{
			second += 60;
			minute = 0 - accountminuteplay;
		}
		else
			minute = 1 - accountminuteplay;
	}
	else
	{
		second = _row * _col * 6;
		minute = second / 60;
		second = second % 60;

		second -= accountsecondplay;
		if (second < 0)
		{
			second += 60;
			minute = minute - 1 - accountminuteplay;
		}
		else
			minute -= accountminuteplay;
	}

	board = new Board(_row, _col, LEFT, TOP, mode);
	board->stop = 1;
	save = new savefile2;
}

Game::~Game() {
	delete board;
	board = nullptr;
	delete[] save;
	save = nullptr;
}


void findTimeLeft(int hour_limit, int minute_limit, int second_limit, int hour_now, int minute_now, int second_now, int& minute_left, int& second_left)
{
	if (second_limit - second_now < 0)
	{
		second_left = second_limit - second_now + 60;
		--minute_limit;
	}
	else
		second_left = second_limit - second_now;

	if (minute_limit - minute_now < 0)
	{
		minute_left = minute_limit - minute_now + 60;
		--hour_limit;
	}
	else
		minute_left = minute_limit - minute_now;

	minute_left += (hour_limit - hour_now) * 60;
}

void WriteBlockChar(char array[][41], int row, int col, int x, int y, int color)
{
	int j = 0;
	CHAR_INFO* charater = new CHAR_INFO[row * col];
	for (int i = 0; i < row * col; i++) {
		charater[i].Attributes = color;
		charater[i].Char.AsciiChar = array[i / col][j++];
		if (j == col)
			j = 0;
	}
	COORD sizebuff = { col,row };
	COORD pos = { 0,0 };
	SMALL_RECT earea = { x,y,x + col - 1,y + row - 1 };
	WriteConsoleOutputA(GetStdHandle(STD_OUTPUT_HANDLE), charater, sizebuff, pos, &earea);
	delete[] charater;
}

void createClock(int minute, int second, int _col, Board* board, savefile2* save)
{
	Game* gameplay = nullptr;
	Graphic* graphic = nullptr;

	board->stop = 1;

	char Time_array[4][41]{};
	char Space[4][41]{};

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 41; ++j)
			Space[i][j] = 32;

	time_t t = time(0);   // get time now
	tm now;
	localtime_s(&now, &t);

	save[1].state->state_record.date.yy = now.tm_year + 1900;
	save[1].state->state_record.date.mm = now.tm_mon + 1;
	save[1].state->state_record.date.dd = now.tm_mday;

	int second_limit = second + now.tm_sec;
	int minute_limit = minute + now.tm_min + second_limit / 60;
	second_limit = second_limit % 60;
	int hour_limit = now.tm_hour + minute_limit / 60;
	minute_limit = minute_limit % 60;

	int minute_left = minute, second_left = second;
	int tmp = second_left;

	while ((minute_left != 0 || second_left != 0) && gameplay->isAvailableBlock(true, board) && board->stop)
	{
		time_t t = time(0);   // get time now
		tm now;
		localtime_s(&now, &t);   // get the tm structure representing local time
		findTimeLeft(hour_limit, minute_limit, second_limit, now.tm_hour, now.tm_min, now.tm_sec, minute_left, second_left);

		save[1].state->state_record.time.minuteplay = minute_left;
		save[1].state->state_record.time.secondplay = second_left;

		graphic->createTime(minute_left / 10, Time_array);
		graphic->createTime(minute_left % 10, Time_array);
		graphic->createTime(10, Time_array);
		graphic->createTime(second_left / 10, Time_array);
		graphic->createTime(second_left % 10, Time_array);

		if (tmp != second_left)
		{
			WriteBlockChar(Space, 4, 35, _col * 8 + LEFT + DISTANCE + 3, 7, 0x008 | 0x070);
			tmp = second_left;
		}

		WriteBlockChar(Time_array, 4, strlen(Time_array[0]), _col * 8 + LEFT + DISTANCE + 3, 7, 0x008 | 0x070);

		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 41; ++j)
				Time_array[i][j] = 0;
	}

	int min = 0, sec = 0;

	sec += second - save[1].state->state_record.time.secondplay;

	if (sec < 0)
	{
		sec += 60;
		--min;
	}
	min = minute - save[1].state->state_record.time.minuteplay;

	save[1].state->state_record.time.secondplay = sec;
	save[1].state->state_record.time.minuteplay = min;

	if (minute_left == 0 && second_left == 0)
		board->stop = 2;
}

void Game::startGame()
{
	Control::clearConsole();
	PlaySound(TEXT("Sound effects\\GameStart.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (isPlaying) {
		_remainBlocks = _row * _col;
		score = 0;
		bool isPause = false;
		printInterface();
		_x = board->getXAt(0, 0);
		_y = board->getYAt(0, 0);
		board->selectedBlock(_x, _y, GREEN);
		//putchar(board->getCharacter(_x, _y));
		//Control::gotoXY(_x, _y);

		thread clock;
		clock = thread(createClock, minute, second, _col, board, save);
		clock.detach();

		if (!isAvailableBlock(true, board)) {
			Control::setConsoleColor(WHITE, RED);
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 13, 19);
			cout << "Game Announcement";
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 8, 20);
			cout << "There are no more ways left!";
			Sleep(800);
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 6, 22);
			cout << "Auto reset the board. Have fun!";
			Sleep(800);
			startGame();
		}

		while (_remainBlocks && !isPause && board->stop != 2) {
			switch (Control::getConsoleInput())
			{
			case 0:
				PlaySound(TEXT("Wtrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
				break;
			case 1:
				saveData();
				board->stop = 0;
				Menu::exitScreen();
				return;
			case 2:
				moveUp();
				break;
			case 3:
				moveLeft();
				break;
			case 4:
				moveRight();
				break;
			case 5:
				moveDown();
				break;
			case 6:
				lockBlock();
				break;
			case 7:
				isPause = true;
				board->stop = 0;
				Menu::helpScreen();
				break;
			case 8:
				moveSuggestion();
				break;
			case 9:
				isPause = true;
				board->stop = 0;
				saveGame();
				saveData();
				break;
			}
		}
		if (isPause)
			continue;

		if (board->stop == 2) {
			PlaySound(TEXT("Sound effects\\Wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
			Control::setConsoleColor(WHITE, RED);
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 13, 19);
			cout << "Game Announcement";
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 12, 20);
			cout << "You are out of time!";
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 17, 22);
			cout << "You lose!";
			Sleep(5000);
		}

		askContinue();
	}
	saveData();
}

void Game::startGameForLoad(char** pokemon, int** status, int xcursor, int ycursor)
{
	Control::clearConsole();
	PlaySound(TEXT("Sound effects\\GameStart.wav"), NULL, SND_FILENAME | SND_ASYNC);

	bool isPause = false;
	while (isPlaying) {
		if (isPause == true)
		{
			if (strcmp(mode, "EASY") == 0)
			{
				minute = 0;
				second = 45;
			}

			else if (strcmp(mode, "MEDIUM") == 0)
			{
				minute = 1;
				second = 30;
			}
			else
			{
				second = _row * _col * 6;
				minute = second / 60;
				second = second % 60;
			}

			_remainBlocks = _row * _col;
			score = 0;
			printInterface();
			_x = board->getXAt(0, 0);
			_y = board->getYAt(0, 0);
			board->selectedBlock(_x, _y, GREEN);
			isPause = false;
		}
		else
		{
			printInterfaceForLoad(pokemon, status);

			_x = board->getXAt(0, 0);
			_y = board->getYAt(0, 0);
			board->selectedBlock(_x, _y, GREEN);

			int r = 0, c = 0, lock = 0;

			if (status[r][c] == 1)
				lock = 1;
			for (r = 0; r < _row; ++r)
			{
				for (c = 0; c < _col; ++c)
				{
					if (status[r][c] == 1)
					{
						lock = 1;
						break;
					}
				}
				if (status[r][c] == 1)
					break;
			}

			if (lock)
			{
				for (int i = 0; i < c; ++i)
				{
					moveRight();
					Sleep(350);
				}

				for (int i = 0; i < r; ++i)
				{
					moveDown();
					Sleep(350);
				}

				lockBlock();
			}
			else
			{
				r = 0;
				c = 0;
			}

			for (int i = c; i < ycursor; ++i)
			{
				moveRight();
				Sleep(350);
			}

			for (int i = c; i > ycursor; --i)
			{
				moveLeft();
				Sleep(350);
			}

			for (int i = r; i < xcursor; ++i)
			{
				moveDown();
				Sleep(350);
			}

			for (int i = r; i > xcursor; --i)
			{
				moveUp();
				Sleep(350);
			}

			int tmpxcursor = board->getXAt(xcursor, ycursor);
			int tmpycursor = board->getYAt(xcursor, ycursor);

			xcursor = tmpxcursor;
			ycursor = tmpycursor;


			if (board->pBoard[board->getRAt(xcursor, ycursor)][board->getCAt(xcursor, ycursor)].getCheck() == 1)
				board->selectedBlock(xcursor, ycursor, LIGHT_RED);
			else
				board->selectedBlock(xcursor, ycursor, GREEN);
		}


		thread clock;
		clock = thread(createClock, minute, second, _col, board, save);
		clock.detach();

		if (!isAvailableBlock(true, board)) {
			Control::setConsoleColor(WHITE, RED);
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 13, 19);
			cout << "Game Announcement";
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 8, 20);
			cout << "There are no more ways left!";
			Sleep(800);
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 6, 22);
			cout << "Auto reset the board. Have fun!";
			Sleep(800);
			startGame();
		}

		while (_remainBlocks && !isPause && board->stop != 2) {
			switch (Control::getConsoleInput())
			{
			case 0:
				PlaySound(TEXT("Sound effects\\Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
				break;
			case 1:
				saveData();
				board->stop = 0;
				Menu::exitScreen();
				return;
			case 2:
				moveUp();
				break;
			case 3:
				moveLeft();
				break;
			case 4:
				moveRight();
				break;
			case 5:
				moveDown();
				break;
			case 6:
				lockBlock();
				break;
			case 7:
				isPause = true;
				board->stop = 0;
				Menu::helpScreen();
				break;
			case 8:
				moveSuggestion();
				break;
			case 9:
				isPause = true;
				board->stop = 0;
				saveGame();
				saveData();
				break;
			}
		}
		if (isPause)
			continue;

		if (board->stop == 2) {
			PlaySound(TEXT("Sound effects\\Wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
			Control::setConsoleColor(WHITE, RED);
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 13, 19);
			cout << "Game Announcement";
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 12, 20);
			cout << "You are out of time!";
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 17, 22);
			cout << "You lose!";
			Sleep(5000);
		}

		askContinue();

		if (strcmp(mode, "EASY") == 0)
		{
			minute = 0;
			second = 45;
		}

		else if (strcmp(mode, "MEDIUM") == 0)
		{
			minute = 1;
			second = 30;
		}
		else
		{
			second = _row * _col * 6;
			minute = second / 60;
			second = second % 60;
		}

		isPause = true;
	}
	saveData();
}

void Game::saveData() {
	char trash = NULL;
	ofstream fOut("file\\leaderboard.bin", ios::binary | ios::app);
	fOut.seekp(0, ios::end);
	fOut.write(playerName, NAMESIZE);
	fOut.write(mode, 15);

	for (int i = 0; i < 3; ++i)
		fOut.write(&trash, 1);

	fOut.write((char*)&score, 4);
	fOut.write((char*)&save[1].state->state_record.time.minuteplay, 4);
	fOut.write((char*)&save[1].state->state_record.time.secondplay, 4);
	fOut.write((char*)&save[1].state->state_record.date.dd, 4);
	fOut.write((char*)&save[1].state->state_record.date.mm, 4);
	fOut.write((char*)&save[1].state->state_record.date.yy, 4);

	fOut.close();
}

void Game::changeFile2(int direction, bool flag, int& current_file) //0: lên, 1: xuống, 2: trái, 3: phải 
{
	int leftFile = 26, topFile = 7, xDistance = 22, yDistance = 10;

	if (((direction == 0) && (current_file == 0 || current_file == 1 || current_file == 2))
		|| ((direction == 1) && (current_file == 3 || current_file == 4))
		|| (direction == 2 && current_file == 0)
		|| (direction == 3 && current_file == 4))
	{
		PlaySound(TEXT("Sound effects\\Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return;
	}

	Control::setConsoleColor(WHITE, GRAY);
	if (current_file < 3)
	{
		Graphic::printFileBlock(leftFile + current_file * xDistance, topFile, 8, 4);
		Control::gotoXY(leftFile + current_file * xDistance + 1, topFile + 6);
		if (save[0].state[current_file].state_record.date.dd == 0)
			cout << "  Empty";
		else
			cout << save[0].state[current_file].state_record.date.dd << "/" << save[0].state[current_file].state_record.date.mm
			<< "/" << save[0].state[current_file].state_record.date.yy;
	}
	else
	{
		Graphic::printFileBlock(leftFile + (current_file - 2.5) * xDistance, topFile + yDistance, 8, 4);
		Control::gotoXY(leftFile + (current_file - 2.5) * xDistance + 1, topFile + yDistance + 6);
		if (save[0].state[current_file].state_record.date.dd == 0)
			cout << "  Empty";
		else
			cout << save[0].state[current_file].state_record.date.dd << "/" << save[0].state[current_file].state_record.date.mm
			<< "/" << save[0].state[current_file].state_record.date.yy;
	}

	if ((current_file == 0 || current_file == 1) && direction == 1)
		current_file = 3;
	else if (current_file == 2 && direction == 1)
		current_file = 4;
	else if (current_file == 3 && direction == 0)
		current_file = 0;
	else if (current_file == 4 && direction == 0)
		current_file = 2;
	else if (direction == 3)
		++current_file;
	else if (direction == 2)
		--current_file;

	if (flag)
	{
		PlaySound(TEXT("Sound effects\\Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Control::setConsoleColor(WHITE, GREEN);

		if (current_file < 3)
			Graphic::printFileBlock(leftFile + current_file * xDistance, topFile, 8, 4);
		else
			Graphic::printFileBlock(leftFile + (current_file - 2.5) * xDistance, topFile + yDistance, 8, 4);
	}
}

void Game::chooseFile2(int& current_file)
{
	Control::clearConsole();
	Control::setAndCenterWindow();

	int loop = 1;


	changeFile2(2, 0, current_file);
	changeFile2(2, 0, current_file);
	changeFile2(2, 0, current_file);
	changeFile2(2, 0, current_file);
	changeFile2(3, 0, current_file);
	changeFile2(2, 1, current_file);

	while (loop)
	{
		switch (Control::getConsoleInput())
		{
		case 2:
			changeFile2(0, 1, current_file);
			break;
		case 3:
			changeFile2(2, 1, current_file);
			break;
		case 4:
			changeFile2(3, 1, current_file);
			break;
		case 5:
			changeFile2(1, 1, current_file);
			break;
		case 6:
			loop = 0;
			break;
		default:
			PlaySound(TEXT("Sound effects\\Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
	}
}

void Game::readFileGame2(int& current_file)
{
	char fileName[64]{};
	strcpy_s(fileName, "gamesave\\");
	strcat_s(fileName, playerName);
	strcat_s(fileName, ".bin");

	ifstream load2;
	load2.open(fileName, ios::binary);

	load2.read(&save[0].mask, 1);

	load2.read(save[0].name, NAMESIZE);
	Menu::xorChararter(save[0].name, save[0].mask);


	load2.read(save[0].password, PASSSIZE);
	Menu::xorChararter(save[0].password, save[0].mask);



	load2.seekg(3, ios::cur);

	for (int i = 0; i < 5; ++i)
	{
		load2.read((char*)&save[0].record[i].date.dd, 4);
		load2.read((char*)&save[0].record[i].date.mm, 4);
		load2.read((char*)&save[0].record[i].date.yy, 4);
		load2.read((char*)&save[0].record[i].time.minuteplay, 4);
		load2.read((char*)&save[0].record[i].time.secondplay, 4);
		load2.read((char*)&save[0].record[i].points, 4);
		load2.seekg(492, ios::cur);
	}
	for (int i = 0; i < 5; ++i)
	{
		load2.read((char*)&save[0].state[i].state_record.date.dd, 4);
		load2.read((char*)&save[0].state[i].state_record.date.mm, 4);
		load2.read((char*)&save[0].state[i].state_record.date.yy, 4);

		load2.read((char*)&save[0].state[i].state_record.time.minuteplay, 4);
		load2.read((char*)&save[0].state[i].state_record.time.secondplay, 4);

		load2.read((char*)&save[0].state[i].state_record.points, 4);

		load2.read(save[0].state[i].mode, MODESIZE);
		Menu::xorChararter(save[0].state[i].mode, save[0].mask);
		load2.seekg(1, ios::cur);

		load2.read((char*)&save[0].state[i].p, 4);
		load2.read((char*)&save[0].state[i].q, 4);
		load2.read((char*)&save[0].state[i].p_, 4);
		load2.read((char*)&save[0].state[i].q_, 4);


		load2.read((char*)&save[0].state[i].board, BOARDSIZE);
		Menu::xorChararter(save[0].state[i].board, save[0].mask);
		load2.seekg(1, ios::cur);

		load2.read((char*)save[0].state[i].status, 400);

		load2.read((char*)&save[0].state[i].file_background, URLSIZE);
		Menu::xorChararter(save[0].state[i].file_background, save[0].mask);
		load2.seekg(36, ios::cur);
	}
	load2.close();


	chooseFile2(current_file);
}

void Game::saveGame() {

	int current_file = 4;
	int count = 0;

	readFileGame2(current_file);

	char fileName[64]{};
	strcpy_s(fileName, "gamesave\\");
	strcat_s(fileName, playerName);
	strcat_s(fileName, ".bin");

	save[1].state->state_record.points = score;

	strcpy_s(save[1].state->mode, mode);

	Record2 tmp = save[1].state->state_record;

	for (int i = 0; i < 5; ++i)
	{
		if (save[0].record[i].points < tmp.points)

			swap(save[0].record[i], tmp);
	}


	for (int i = 0; i < _row; ++i)
		for (int j = 0; j < _col; ++j)
		{
			save[1].state->board[count] = board->pBoard[i][j].getCharacter();
			save[1].state->status[count] = board->pBoard[i][j].getCheck();
			++count;
		}


	if (strcmp(mode, "EASY") == 0)
		strcpy_s(save[1].state->file_background, "background\\easy.txt");
	else if (strcmp(mode, "MEDIUM") == 0)
		strcpy_s(save[1].state->file_background, "background\\medium.txt");
	else
		strcpy_s(save[1].state->file_background, "background\\custom.txt");

	save[1].state->p = _row;
	save[1].state->q = _col;
	save[1].state->p_ = board->getRAt(_x, _y);
	save[1].state->q_ = board->getCAt(_x, _y);

	swap(save[0].state[current_file].mode, save[1].state->mode);
	swap(save[0].state[current_file].board, save[1].state->board);
	swap(save[0].state[current_file].status, save[1].state->status);
	swap(save[0].state[current_file].file_background, save[1].state->file_background);
	swap(save[0].state[current_file].p, save[1].state->p);
	swap(save[0].state[current_file].q, save[1].state->q);
	swap(save[0].state[current_file].p_, save[1].state->p_);
	swap(save[0].state[current_file].q_, save[1].state->q_);
	swap(save[0].state[current_file].state_record, save[1].state->state_record);

	Menu::xorChararter(save[0].name, save[0].mask);
	Menu::xorChararter(save[0].password, save[0].mask);
	for (int i = 0; i < 5; ++i)
	{
		Menu::xorChararter(save[0].state[i].mode, save[0].mask);
		Menu::xorChararter(save[0].state[i].board, save[0].mask);
		Menu::xorChararter(save[0].state[i].file_background, save[0].mask);
	}

	char trash = NULL;
	ofstream fs(fileName, ios::binary);

	fs.write(&save[0].mask, 1);
	fs.write(save[0].name, NAMESIZE);
	fs.write(save[0].password, PASSSIZE);

	for (int i = 0; i < 3; ++i)
		fs.write(&trash, 1);

	for (int i = 0; i < 5; ++i)
	{
		fs.write((char*)&save[0].record[i].date.dd, 4);
		fs.write((char*)&save[0].record[i].date.mm, 4);
		fs.write((char*)&save[0].record[i].date.yy, 4);
		fs.write((char*)&save[0].record[i].time.minuteplay, 4);
		fs.write((char*)&save[0].record[i].time.secondplay, 4);
		fs.write((char*)&save[0].record[i].points, 4);

		for (int j = 0; j < 492; ++j)
			fs.write(&trash, 1);
	}

	for (int i = 0; i < 5; ++i)
	{
		fs.write((char*)&save[0].state[i].state_record.date.dd, 4);
		fs.write((char*)&save[0].state[i].state_record.date.mm, 4);
		fs.write((char*)&save[0].state[i].state_record.date.yy, 4);

		fs.write((char*)&save[0].state[i].state_record.time.minuteplay, 4);
		fs.write((char*)&save[0].state[i].state_record.time.secondplay, 4);

		fs.write((char*)&save[0].state[i].state_record.points, 4);

		fs.write(save[0].state[i].mode, MODESIZE);
		fs.write(&trash, 1);

		fs.write((char*)&save[0].state[i].p, 4);
		fs.write((char*)&save[0].state[i].q, 4);
		fs.write((char*)&save[0].state[i].p_, 4);
		fs.write((char*)&save[0].state[i].q_, 4);

		fs.write((char*)&save[0].state[i].board, BOARDSIZE);
		fs.write(&trash, 1);
		fs.write((char*)save[0].state[i].status, 400);
		fs.write((char*)&save[0].state[i].file_background, URLSIZE);

		for (int j = 0; j < 36; ++j)
			fs.write(&trash, 1);
	}
	fs.close();
}

void Game::moveRight()
{
	if (_x < board->getXAt(board->getSizeRow() - 1, board->getSizeCol() - 1))
	{
		
		PlaySound(TEXT("Sound effects\\Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (board->getCheck(_x, _y) != LOCK) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Control::gotoXY(_x, _y);
		}
		_x += 8;

		if (board->getCheck(_x, _y) != LOCK) {
			board->selectedBlock(_x, _y, GREEN);
		}
	}
	else
		PlaySound(TEXT("Sound effects\\Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Game::moveLeft()
{
	if (_x > board->getXAt(0, 0))
	{
		PlaySound(TEXT("Sound effects\\Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (board->getCheck(_x, _y) != LOCK) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Control::gotoXY(_x, _y);
		}
		_x -= 8;

		if (board->getCheck(_x, _y) != LOCK) {
			board->selectedBlock(_x, _y, GREEN);
		}
	}
	else
		PlaySound(TEXT("Sound effects\\Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Game::moveDown()
{
	if (_y < board->getYAt(board->getSizeRow() - 1, board->getSizeCol() - 1))
	{
		PlaySound(TEXT("Sound effects\\Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (board->getCheck(_x, _y) != LOCK) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Control::gotoXY(_x, _y);
		}
		_y += 4;

		if (board->getCheck(_x, _y) != LOCK) {
			board->selectedBlock(_x, _y, GREEN);
		}
	}
	else
		PlaySound(TEXT("Sound effects\\Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Game::moveUp()
{
	if (_y > board->getYAt(0, 0))
	{
		PlaySound(TEXT("Sound effects\\Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (board->getCheck(_x, _y) != LOCK) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Control::gotoXY(_x, _y);
		}
		_y -= 4;

		if (board->getCheck(_x, _y) != LOCK) {
			board->selectedBlock(_x, _y, GREEN);
		}
	}
	else
		PlaySound(TEXT("Sound effects\\Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Game::printInterface()
{
	Control::setAndCenterWindow(_row, _col);

	board->createBackground(mode);
	board->showBoard();
	board->buildBoardData();
	board->renderBoard();

	Control::setConsoleColor(WHITE, BLACK);
	Graphic::printRectangleSpecial(_col * 8 + LEFT + DISTANCE, 2, 39, 10);
	Graphic::printRectangleSpecial(_col * 8 + LEFT + DISTANCE, 13, 39, 10);

	Graphic::printRectangleNormal(_col * 8 + LEFT + DISTANCE + 1, 3, 37, 2);
	Control::setConsoleColor(WHITE, RED);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 16, 4);
	cout << "LET'S PLAY";

	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 4, 6);
	cout << "Player's name: " << playerName;

	Control::setConsoleColor(WHITE, BLACK);
	Graphic::printRectangleNormal(_col * 8 + LEFT + DISTANCE + 1, 14, 37, 2);
	Control::setConsoleColor(WHITE, RED);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 13, 15);
	cout << "GAME INFORMATION";
	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 9, 17);
	cout << "Moves:";
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 9, 18);
	cout << "Current score:";
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 24, 18);
	cout << score;

	Control::setConsoleColor(WHITE, BLACK);
	Graphic::printRectangleNormal(_col * 8 + LEFT + DISTANCE, 25, 21, 2);
	Graphic::printRectangleNormal(_col * 8 + LEFT + DISTANCE + 25, 25, 14, 2);
	Graphic::printRectangleNormal(_col * 8 + LEFT + DISTANCE, 28, 12, 2);
	Graphic::printRectangleNormal(_col * 8 + LEFT + DISTANCE + 16, 28, 23, 2);

	Control::setConsoleColor(WHITE, PURPLE);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 2, 26);
	cout << "M : Move suggestion";
	Control::setConsoleColor(WHITE, AQUA);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 29, 26);
	cout << "H : Help";
	Control::setConsoleColor(WHITE, YELLOW);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 2, 29);
	cout << "Esc : Exit";
	Control::setConsoleColor(WHITE, GREEN);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 20, 29);
	cout << "G : Save file game";
}

void Game::printInterfaceForLoad(char** pokemon, int** status)
{
	Control::setAndCenterWindow(_row, _col);

	board->createBackground(mode);
	board->showBoard();
	board->buildBoardDataForLoad(pokemon);
	board->renderBoardForLoad(status);
	board->updateBackground();

	Control::setConsoleColor(WHITE, BLACK);
	Graphic::printRectangleSpecial(_col * 8 + LEFT + DISTANCE, 2, 39, 10);
	Graphic::printRectangleSpecial(_col * 8 + LEFT + DISTANCE, 13, 39, 10);

	Graphic::printRectangleNormal(_col * 8 + LEFT + DISTANCE + 1, 3, 37, 2);
	Control::setConsoleColor(WHITE, RED);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 16, 4);
	cout << "LET'S PLAY";

	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 4, 6);
	cout << "Player's name: " << playerName;

	Control::setConsoleColor(WHITE, BLACK);
	Graphic::printRectangleNormal(_col * 8 + LEFT + DISTANCE + 1, 14, 37, 2);
	Control::setConsoleColor(WHITE, RED);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 13, 15);
	cout << "GAME INFORMATION";
	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 9, 17);
	cout << "Moves:";
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 9, 18);
	cout << "Current score:";
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 24, 18);
	cout << score;

	Control::setConsoleColor(WHITE, BLACK);
	Graphic::printRectangleNormal(_col * 8 + LEFT + DISTANCE, 25, 21, 2);
	Graphic::printRectangleNormal(_col * 8 + LEFT + DISTANCE + 25, 25, 14, 2);
	Graphic::printRectangleNormal(_col * 8 + LEFT + DISTANCE, 28, 12, 2);
	Graphic::printRectangleNormal(_col * 8 + LEFT + DISTANCE + 16, 28, 23, 2);

	Control::setConsoleColor(WHITE, PURPLE);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 2, 26);
	cout << "M : Move suggestion";
	Control::setConsoleColor(WHITE, AQUA);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 29, 26);
	cout << "H : Help";
	Control::setConsoleColor(WHITE, YELLOW);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 2, 29);
	cout << "Esc : Exit";
	Control::setConsoleColor(WHITE, GREEN);
	Control::gotoXY(_col * 8 + LEFT + DISTANCE + 20, 29);
	cout << "G : Save file game";
}

char Game::getCharacter(int x, int y)
{
	return board->getCharacter(x, y);
}

void Game::lockBlock()
{
	PlaySound(TEXT("Sound effects\\Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
	if (board->getCheck(_x, _y) == LOCK || board->getCheck(_x, _y) == DEL) {
		return;
	}
	board->lockBlock(_x, _y);

	_lockedBlockPair.push_back(pair<int, int>(_x, _y));
	_lockedBlock++;

	if (_lockedBlock == 2) {
		deleteBlock();
	}
}

bool Game::checkMatchedCharacters(pair<int, int> firstBlock, pair<int, int> secondBlock, Board* board)
{
	return (board->getCharacter(firstBlock.first, firstBlock.second) == board->getCharacter(secondBlock.first, secondBlock.second));
}

int Game::checkIMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking, Board* board)
{
	if (firstBlock.first == secondBlock.first && firstBlock.second == secondBlock.second) {
		return 2;
	}
	// check line y -> check value of x
	if (firstBlock.second == secondBlock.second) {
		if (firstBlock.first > secondBlock.first)
			swap(firstBlock, secondBlock);

		for (int i = firstBlock.first; i <= secondBlock.first; i += 8) {
			if (i == firstBlock.first || i == secondBlock.first)
				continue;
			if (board->getCheck(i, firstBlock.second) != DEL) {
				return 0;
			}
		}
		if (board->getCheck(firstBlock.first, firstBlock.second) == DEL
			|| board->getCheck(secondBlock.first, secondBlock.second) == DEL) {
			return 2;
		}

		if (checkMatchedCharacters(firstBlock, secondBlock, board)) {
			if (isChecking == false) {
				board->drawLineI(firstBlock, secondBlock);
				Sleep(200);
				board->deleteLineI(firstBlock, secondBlock);
			}
			return 1;
		}
	}
	// check line x -> check value of y
	if (firstBlock.first == secondBlock.first) {
		if (firstBlock.second > secondBlock.second)
			swap(firstBlock, secondBlock);

		for (int i = firstBlock.second; i <= secondBlock.second; i += 4) {
			if (i == firstBlock.second || i == secondBlock.second)
				continue;
			if (board->getCheck(firstBlock.first, i) != DEL) {
				return 0;
			}
		}
		if (board->getCheck(firstBlock.first, firstBlock.second) == DEL
			|| board->getCheck(secondBlock.first, secondBlock.second) == DEL) {
			return 2;
		}

		if (checkMatchedCharacters(firstBlock, secondBlock, board)) {
			if (isChecking == false) {
				board->drawLineI(firstBlock, secondBlock);
				Sleep(200);
				board->deleteLineI(firstBlock, secondBlock);
			}
			return 1;
		}
	}
	return 0;
}
bool Game::checkLMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking, Board* board)
{
	if (firstBlock.first > secondBlock.first)
		swap(firstBlock, secondBlock);

	pair<int, int> Lcorner;
	Lcorner.first = firstBlock.first;
	Lcorner.second = secondBlock.second;
	if (board->getCheck(Lcorner.first, Lcorner.second) == DEL) {
		if (checkIMatching(Lcorner, firstBlock, isChecking, board) && checkIMatching(Lcorner, secondBlock, isChecking, board)) {
			if (isChecking == false) {
				board->drawLineL(firstBlock, secondBlock, Lcorner);
				Sleep(200);
				board->deleteLineL(firstBlock, secondBlock, Lcorner);
			}
			return 1;
		}
	}

	Lcorner.first = secondBlock.first;
	Lcorner.second = firstBlock.second;
	if (board->getCheck(Lcorner.first, Lcorner.second) == DEL) {
		if (checkIMatching(Lcorner, secondBlock, isChecking, board) && checkIMatching(Lcorner, firstBlock, isChecking, board)) {
			if (isChecking == false) {
				board->drawLineL(firstBlock, secondBlock, Lcorner);
				Sleep(200);
				board->deleteLineL(firstBlock, secondBlock, Lcorner);
			}
			return 1;
		}
	}
	return 0;
}
bool Game::checkZMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking, Board* board)
{
	if (firstBlock.first > secondBlock.first)
		swap(firstBlock, secondBlock);

	pair<int, int> Zcorner1;
	pair<int, int> Zcorner2;

	for (int i = firstBlock.first + 8; i < secondBlock.first; i += 8) {
		if (board->getCheck(i, firstBlock.second) == DEL) {
			if (board->getCheck(i, secondBlock.second) == DEL) {
				Zcorner1.first = i;
				Zcorner1.second = firstBlock.second;
				Zcorner2.first = i;
				Zcorner2.second = secondBlock.second;
				if (checkIMatching(Zcorner1, Zcorner2, isChecking, board) &&
					checkIMatching(Zcorner2, secondBlock, isChecking, board)) {
					if (isChecking == false) {
						board->drawLineZ(firstBlock, secondBlock, Zcorner1, Zcorner2);
						Sleep(200);
						board->deleteLineZ(firstBlock, secondBlock, Zcorner1, Zcorner2);
					}
					return 1;
				}
			}
		}
		else break;
	}

	if (firstBlock.second > secondBlock.second)
		swap(firstBlock, secondBlock);
	for (int i = firstBlock.second + 4; i < secondBlock.second; i += 4) {
		if (board->getCheck(firstBlock.first, i) == DEL) {
			if (board->getCheck(secondBlock.first, i) == DEL) {
				Zcorner1.first = firstBlock.first;
				Zcorner1.second = i;
				Zcorner2.first = secondBlock.first;
				Zcorner2.second = i;
				if (checkIMatching(Zcorner1, Zcorner2, isChecking, board) &&
					checkIMatching(Zcorner2, secondBlock, isChecking, board)) {
					if (isChecking == false) {
						board->drawLineZ(firstBlock, secondBlock, Zcorner1, Zcorner2);
						Sleep(200);
						board->deleteLineZ(firstBlock, secondBlock, Zcorner1, Zcorner2);
					}
					return 1;
				}
			}
		}
		else break;
	}
	return 0;
}
bool Game::checkUMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking, Board* board)
{
	pair<int, int> Ucorner1;
	pair<int, int> Ucorner2;
	const int sizeRow = board->getSizeRow();
	const int sizeCol = board->getSizeCol();
	const int x = board->getXAt(0, 0);
	const int y = board->getYAt(0, 0);

	if (firstBlock.first == secondBlock.first)
		if (firstBlock.second > secondBlock.second)
			swap(firstBlock, secondBlock);

	// U ngang trai
	if (firstBlock.first > secondBlock.first)
		swap(firstBlock, secondBlock);
	for (int i = firstBlock.first - 8; i >= x - 8; i -= 8) {
		Ucorner1.first = i;
		Ucorner1.second = firstBlock.second;
		Ucorner2.first = i;
		Ucorner2.second = secondBlock.second;

		if (i == x - 8) {
			Ucorner1.first = x;
			Ucorner1.second = firstBlock.second;
			Ucorner2.first = x;
			Ucorner2.second = secondBlock.second;
			if (Ucorner1.first == firstBlock.first && Ucorner2.first == secondBlock.first)
				return 1;
			if ((board->getCheck(Ucorner1.first, Ucorner1.second) == DEL ||
				(Ucorner1.first == firstBlock.first && Ucorner1.second == firstBlock.second))
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == DEL) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking, board) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking, board) == 2)
					return 1;
			}
			else break;
		}
		if (board->getCheck(Ucorner1.first, Ucorner1.second) == DEL
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == DEL) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking, board) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking, board) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking, board) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(200);
					board->deleteLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
				}
				return 1;
			}
		}
		else break;
	}
	// U ngang phai
	if (firstBlock.first < secondBlock.first)
		swap(firstBlock, secondBlock);
	for (int i = firstBlock.first + 8; i <= x + sizeCol * 8; i += 8) {
		Ucorner1.first = i;
		Ucorner1.second = firstBlock.second;
		Ucorner2.first = i;
		Ucorner2.second = secondBlock.second;

		if (i == x + sizeCol * 8) {
			Ucorner1.first = x + sizeCol * 8 - 8;
			Ucorner1.second = firstBlock.second;
			Ucorner2.first = x + sizeCol * 8 - 8;
			Ucorner2.second = secondBlock.second;

			if (Ucorner1.first == firstBlock.first && Ucorner2.first == secondBlock.first)
				return 1;
			if ((board->getCheck(Ucorner1.first, Ucorner1.second) == DEL ||
				(Ucorner1.first == firstBlock.first && Ucorner1.second == firstBlock.second))
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == DEL) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking, board) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking, board) == 2)
					return 1;
			}
			else break;
		}

		if (board->getCheck(Ucorner1.first, Ucorner1.second) == DEL
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == DEL) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking, board) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking, board) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking, board) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(1200);
					board->deleteLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
				}
				return 1;
			}
		}
		else break;
	}
	if (firstBlock.second == secondBlock.second)
		if (firstBlock.first > secondBlock.first)
			swap(firstBlock, secondBlock);

	// U doc tren
	if (firstBlock.second > secondBlock.second)
		swap(firstBlock, secondBlock);
	for (int i = firstBlock.second - 4; i >= y - 4; i -= 4) {
		Ucorner1.first = firstBlock.first;
		Ucorner1.second = i;
		Ucorner2.first = secondBlock.first;
		Ucorner2.second = i;

		if (i == y - 4) {
			Ucorner2.first = secondBlock.first;
			Ucorner2.second = y;
			Ucorner1.first = firstBlock.first;
			Ucorner1.second = y;

			if (Ucorner1.second == firstBlock.second && Ucorner2.second == secondBlock.second)
				return 1;
			if ((board->getCheck(Ucorner1.first, Ucorner1.second) == DEL ||
				(Ucorner1.first == firstBlock.first && Ucorner1.second == firstBlock.second))
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == DEL) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking, board) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking, board) == 2)
					return 1;
			}
			else break;
		}

		if (board->getCheck(Ucorner1.first, Ucorner1.second) == DEL
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == DEL) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking, board) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking, board) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking, board) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(200);
					board->deleteLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
				}
				return 1;
			}
		}
		else break;
	}
	// U doc duoi
	if (firstBlock.second < secondBlock.second)
		swap(firstBlock, secondBlock);
	for (int i = firstBlock.second + 4; i <= y + sizeRow * 4; i += 4) {
		Ucorner1.first = firstBlock.first;
		Ucorner1.second = i;
		Ucorner2.first = secondBlock.first;
		Ucorner2.second = i;

		if (i == y + sizeRow * 4) {
			Ucorner2.first = secondBlock.first;
			Ucorner2.second = y + sizeRow * 4 - 4;
			Ucorner1.first = firstBlock.first;
			Ucorner1.second = y + sizeRow * 4 - 4;

			if (Ucorner1.second == firstBlock.second && Ucorner2.second == secondBlock.second)
				return 1;
			if ((board->getCheck(Ucorner1.first, Ucorner1.second) == DEL ||
				(Ucorner1.first == firstBlock.first && Ucorner1.second == firstBlock.second))
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == DEL) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking, board) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking, board) == 2)
					return 1;
			}
			else break;
		}

		if (board->getCheck(Ucorner1.first, Ucorner1.second) == DEL
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == DEL) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking, board) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking, board) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking, board) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(200);
					board->deleteLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
				}
				return 1;
			}
		}
		else break;
	}
	return 0;
}
bool Game::checkMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking, Board* board)
{
	if (!checkMatchedCharacters(firstBlock, secondBlock, board)) {
		if (isChecking == false) {
			PlaySound(TEXT("Sound effects\\Wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
			Control::setConsoleColor(WHITE, BLUE);
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 16, 17);
			cout << "Not Matched";
			score -= 2;
			Control::setConsoleColor(WHITE, RED);
			if (score >= 0) {
				Control::gotoXY(_col * 8 + LEFT + DISTANCE + 24, 18);
				cout << score << " BTC ";
			}
			else {
				Control::gotoXY(_col * 8 + LEFT + DISTANCE + 24, 18);
				cout << score << " BTC";
			}
		}
		return 0;
	}
	if (checkIMatching(firstBlock, secondBlock, isChecking, board)) {
		if (isChecking == false) {
			Control::setConsoleColor(WHITE, BLUE);
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 16, 17);
			cout << "I Matching.";
			score += 1;
			Control::setConsoleColor(WHITE, GREEN);
			if (score >= 0) {
				Control::gotoXY(_col * 8 + LEFT + DISTANCE + 24, 18);
				cout << score << " BTC ";
			}
			else {
				Control::gotoXY(_col * 8 + LEFT + DISTANCE + 24, 18);
				cout << score << " BTC";
			}
		}
		return 1;
	}
	if (checkLMatching(firstBlock, secondBlock, isChecking, board)) {
		if (isChecking == false) {
			Control::setConsoleColor(WHITE, BLUE);
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 16, 17);
			cout << "L Matching.";
			score += 2;
			Control::setConsoleColor(WHITE, GREEN);
			if (score >= 0) {
				Control::gotoXY(_col * 8 + LEFT + DISTANCE + 24, 18);
				cout << score << " BTC ";
			}
			else {
				Control::gotoXY(_col * 8 + LEFT + DISTANCE + 24, 18);
				cout << score << " BTC";
			}
		}
		return 1;
	}
	if (checkZMatching(firstBlock, secondBlock, isChecking, board)) {
		if (isChecking == false) {
			Control::setConsoleColor(WHITE, BLUE);
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 16, 17);
			cout << "Z Matching.";
			score += 3;
			Control::setConsoleColor(WHITE, GREEN);
			if (score >= 0) {
				Control::gotoXY(_col * 8 + LEFT + DISTANCE + 24, 18);
				cout << score << " BTC ";
			}
			else {
				Control::gotoXY(_col * 8 + LEFT + DISTANCE + 24, 18);
				cout << score << " BTC";
			}
		}
		return 1;
	}
	if (checkUMatching(firstBlock, secondBlock, isChecking, board)) {
		if (isChecking == false) {
			Control::setConsoleColor(WHITE, BLUE);
			Control::gotoXY(_col * 8 + LEFT + DISTANCE + 16, 17);
			cout << "U Matching.";
			score += 4;
			Control::setConsoleColor(WHITE, GREEN);
			if (score >= 0) {
				Control::gotoXY(_col * 8 + LEFT + DISTANCE + 24, 18);
				cout << score << " BTC ";
			}
			else {
				Control::gotoXY(_col * 8 + LEFT + DISTANCE + 24, 18);
				cout << score << " BTC";
			}
		}
		return 1;
	}
	return 0;
}

void Game::deleteBlock() {

	_lockedBlock = 0;
	bool isChecking = false;
	if (!checkMatching(_lockedBlockPair[0], _lockedBlockPair[1], isChecking, board)) {
		PlaySound(TEXT("Sound effects\\Wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);

		for (auto block : _lockedBlockPair)
			board->unselectedBlock(block.first, block.second);
		_lockedBlockPair.clear();
		board->selectedBlock(_x, _y, GREEN);
		return;
	}

	PlaySound(TEXT("Sound effects\\GetPoint.wav"), NULL, SND_FILENAME | SND_ASYNC);

	for (auto block : _lockedBlockPair)
		board->deleteBlock(block.first, block.second);
	_lockedBlockPair.clear();

	board->updateBackground();

	board->selectedBlock(_x, _y, GREEN);
	_remainBlocks -= 2;
	if (_remainBlocks == 0) {
		Control::setConsoleColor(WHITE, RED);
		Control::gotoXY(_col * 8 + LEFT + DISTANCE + 13, 19);
		cout << "Game Announcement";
		Control::setConsoleColor(WHITE, BLUE);
		Control::gotoXY(_col * 8 + LEFT + DISTANCE + 10, 20);
		cout << "You have won the game.";
		Control::setConsoleColor(WHITE, BLUE);
		Control::gotoXY(_col * 8 + LEFT + DISTANCE + 13, 21);
		cout << "CONGRATULATIONS!";
		Control::gotoXY(_col * 8 + LEFT + DISTANCE + 14, 22);
		cout << "Your score: " << score;
		PlaySound(TEXT("Sound effects\\Win.wav"), NULL, SND_FILENAME | SND_ASYNC);
		board->unselectedBlock(_x, _y);
		Sleep(5000);
		return;
	}
	isChecking = true;
	if (!isAvailableBlock(isChecking, board)) {
		Control::setConsoleColor(WHITE, RED);
		Control::gotoXY(_col * 8 + LEFT + DISTANCE + 13, 19);
		cout << "Game Announcement";
		Control::gotoXY(_col * 8 + LEFT + DISTANCE + 8, 20);
		cout << "There are no more ways left!";
		Sleep(1000);
		Control::gotoXY(_col * 8 + LEFT + DISTANCE + 6, 22);
		cout << "Auto reset the board. Have fun!";
		Sleep(4000);
		startGame();
	}
}

bool Game::isAvailableBlock(bool isChecking, Board* board) {
	int sizeRow = board->getSizeRow();
	int sizeCol = board->getSizeCol();
	pair<int, int> firstBlock;
	pair<int, int> secondBlock;
	for (int i = 0; i < sizeRow; i++) {
		for (int j = 0; j < sizeCol; j++) {
			firstBlock.first = board->getXAt(i, j);
			firstBlock.second = board->getYAt(i, j);
			if (board->getCheck(firstBlock.first, firstBlock.second) == DEL) {
				continue;
			}
			for (int m = i; m < sizeRow; m++) {
				for (int n = 0; n < sizeCol; n++) {
					if (i == m && n <= j) continue;
					secondBlock.first = board->getXAt(m, n);
					secondBlock.second = board->getYAt(m, n);
					if (board->getCheck(secondBlock.first, secondBlock.second) == DEL)
						continue;
					if (checkMatching(firstBlock, secondBlock, isChecking, board)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Game::askContinue()
{
	Control::setAndCenterWindow();
	Control::setConsoleColor(WHITE, BLACK);
	Control::clearConsole();

	Menu::printLogo();
	Control::setConsoleColor(WHITE, BLACK);
	Graphic::printRectangleBlock(34, 18, 36, 8);
	Control::setConsoleColor(BRIGHT_WHITE, BLACK);
	Control::clearArea(35, 19, 35, 6);
	Graphic::printRectangleNormal(38, 22, 7, 2);
	Graphic::printRectangleNormal(59, 22, 6, 2);


	Control::gotoXY(36, 20);
	Control::setConsoleColor(BRIGHT_WHITE, GREEN);
	cout << "Do you want to play another round?";
	string str[2] = { "Yes", "No" };
	int left[] = { 36,41,48,57,62,68 }, word[] = { 32,32,175,174 }, color[] = { BLACK, GREEN }, top = 23;
	bool choice = 1;
	auto print1 = [&]()
	{
		int i = 0;
		while (i < 2)
		{
			PlaySound(TEXT("Sound effects\\Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
			Control::setConsoleColor(BRIGHT_WHITE, color[i]);
			Control::gotoXY(left[choice * 3], top);        putchar(word[i * 2]);
			Control::gotoXY(left[choice * 3 + 1], top);    cout << str[choice];
			Control::gotoXY(left[choice * 3 + 2], top);    putchar(word[i * 2 + 1]);
			if (!i++)
				choice = !choice;
		}
	};
	print1();
	while (true)
	{
		int key = Control::getConsoleInput();
		if ((key == 3 && choice == 1) || (key == 4 && choice == 0))
			print1();
		else if (key == 6)
		{
			if (!choice)
				isPlaying = true;
			else
				isPlaying = false;
			return;
		}
		else
			PlaySound(TEXT("Sound effects\\Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}

void Game::moveSuggestion() {
	bool isHelp = true;
	int sizeRow = board->getSizeRow();
	int sizeCol = board->getSizeCol();
	pair<int, int> firstBlock;
	pair<int, int> secondBlock;
	PlaySound(TEXT("Sound effects\\MoveSuggestion.wav"), NULL, SND_FILENAME | SND_ASYNC);
	for (int i = 0; i < sizeRow; i++) {
		for (int j = 0; j < sizeCol; j++) {
			firstBlock.first = board->getXAt(i, j);
			firstBlock.second = board->getYAt(i, j);
			if (board->getCheck(firstBlock.first, firstBlock.second) == DEL) {
				continue;
			}
			for (int m = i; m < sizeRow; m++) {
				for (int n = 0; n < sizeCol; n++) {
					if (i == m && n <= j) continue;
					secondBlock.first = board->getXAt(m, n);
					secondBlock.second = board->getYAt(m, n);
					if (board->getCheck(secondBlock.first, secondBlock.second) == DEL)
						continue;
					if (checkMatching(firstBlock, secondBlock, isHelp, board)) {
						if (isHelp) {
							board->selectedBlock(firstBlock.first, firstBlock.second, PURPLE);
							board->selectedBlock(secondBlock.first, secondBlock.second, PURPLE);
							Sleep(1000);
							board->unselectedBlock(firstBlock.first, firstBlock.second);
							board->unselectedBlock(secondBlock.first, secondBlock.second);
							score -= 2;
							Control::setConsoleColor(WHITE, RED);
							if (score >= 0) {
								Control::gotoXY(_col * 8 + LEFT + DISTANCE + 24, 18);
								cout << score << " BTC ";
							}
							else {
								Control::gotoXY(_col * 8 + LEFT + DISTANCE + 24, 18);
								cout << score << " BTC";
							}
							return;
						}
					}
				}
			}
		}
	}
}
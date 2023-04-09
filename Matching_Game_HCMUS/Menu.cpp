#include "Menu.h"
int Menu::current_option;
Player Menu::account;
const string Menu::options[12] = { "Play", "LeaderBoard", "Help", "Exit", "User Mode", " Guest Mode", "Sign in", "Sign up", "Easy", "   Medium   ", "Custom", "Exit" };

void Menu::mainScreen()
{
	unordered_map<string, void(*)()> function_map = {
		{options[0], playMenu},
		{options[1], leaderBoard},
		{options[2], helpScreen},
		{options[3], exitScreen},
		{options[4], UserMode},
		{options[5], guestMode},
		{options[6], signIn},
		{options[7], signUp},
		{options[8], playEasy},
		{options[9], playMedium},
		{options[10], playCustom},
		{options[11], exitScreen}
	};
	//Control::playSound(BACKGROUND_SOUND);
	//printAnimation();

	bool loadMenu = 1;
	while (true)
	{
		if (loadMenu)
			mainMenu();
		switch (Control::getConsoleInput())
		{
		case 2:
			changeOption(0, 1);
			loadMenu = 0;
			break;
		case 5:
			changeOption(1, 1);
			loadMenu = 0;
			break;
		case 6:
			if (current_option == 0)
			{
				loadMenu = 0;
				function_map[options[current_option]]();

				if (current_option == 4)
					function_map[options[current_option]]();
			}
			else
				loadMenu = 1;
			function_map[options[current_option]]();
			break;
		default:
			Control::playSound(ERROR_SOUND);
			loadMenu = 0;
		}
	}

	Control::clearConsole();
}

void Menu::printLogo()
{
	SetConsoleOutputCP(CP_UTF8);

	unsigned char logo[] = u8R"(

     ████─╮  ████─╮      ███─╮    ████████─╮   ███████─╮  ██─╮  ██─╮  ██─╮  ████─╮  ██─╮   ███████─╮
     ██ ██╰╮██ ██ │     ██ ██╰╮   ╰──██ ╭──╯  ██ ╭─────╯  ██ │  ██ │  ██ │  ██ ██╰╮ ██ │  ██ ╭─────╯
     ██ │████ ╭██ │    ██ ╭╯██╰╮     ██ │     ██ │        ████████ │  ██ │  ██ │██╰╮██ │  ██ │  ████─╮
     ██ │ ╰───╯██ │   █████████╰╮    ██ │     ██ │        ██ ╭──██ │  ██ │  ██ │ ██╰██ │  ██ │   ██ ╭╯
     ██ │      ██ │  ██ ╭─────██╰╮   ██ │      ███████─╮  ██ │  ██ │  ██ │  ██ │  ████ │   ███████ ╭╯
     ╰──╯      ╰──╯  ╰──╯     ╰──╯   ╰──╯      ╰───────╯  ╰──╯  ╰──╯  ╰──╯  ╰──╯  ╰────╯   ╰───────╯


		           ███████─╮       ███─╮      ████─╮  ████─╮  ████████─╮
		          ██ ╭─────╯      ██ ██╰╮     ██ ██╰╮██ ██ │  ██ ╭─────╯
		          ██ │  ████─╮   ██ ╭╯██╰╮    ██ │████ ╭██ │  ███████─╮
		          ██ │   ██ ╭╯  █████████╰╮   ██ │ ╰───╯██ │  ██ ╭────╯
		           ███████ ╭╯  ██ ╭─────██╰╮  ██ │      ██ │  ████████─╮
		           ╰───────╯   ╰──╯     ╰──╯  ╰──╯      ╰──╯  ╰────────╯

	)";

	Control::setConsoleColor(WHITE, LIGHT_RED);
	Control::gotoXY(0, 0);
	cout << logo;

	SetConsoleOutputCP(437);
}

void Menu::printOptionsBoard()
{
	Control::setConsoleColor(WHITE, BLACK);
	int left = 46; //48
	int top = 19;

	Graphic::printRectangleNormal(left, top + 2, 12, 2);
	Graphic::printRectangleNormal(left, top + 4, 12, 2);
	Graphic::printRectangleSpecial(left, top, 12, 8);

	for (int i = top + 2; i < top + 7; i += 2)
	{
		Control::gotoXY(left, i);
		putchar(199);
	}
	for (int i = top + 2; i < top + 7; i += 2)
	{
		Control::gotoXY(left + 13, i);
		putchar(182);
	}
}
//
//void Menu::printAnimation()
//{
//	Control::setConsoleColor(WHITE, BLACK);
//	Control::clearConsole();
//	char symbolpos[] = { 5,0,19,0,33,0,47,0,61,0,75,0,89,0,0,103,5,13,19,
//							   13,33,13,47,13,61,13,75,13,89,13,13,103,13,18,26,18,40,18,
//							   54,18,68,18,82,18,18,96,5,24,19,24,33,24,47,24,61,24,75,24,
//							   89,24,24,103,12,30,26,30,40,30,54,30,68,30,82,30,96,30 };
//	int n = (sizeof(symbolpos) / sizeof(symbolpos[0])) / 2;
//	bool turn = 0;
//	unsigned char symbol[] = { 4,15 };
//
//	int color[] = { LIGHT_AQUA, AQUA, LIGHT_BLUE, BLUE, LIGHT_PURPLE, PURPLE };
//	int colorcount = 0;
//	int loop = 10;
//	while (loop--)
//	{
//		for (int i = 0; i < n; i += 2)
//		{
//			Control::setConsoleColor(WHITE, getRandomInt(0, 15));
//			Control::gotoXY(symbolpos[i * 2], symbolpos[i * 2 + 1]);
//			putchar(symbol[turn]);
//		}
//		for (int i = 1; i < n; i += 2)
//		{
//			Control::setConsoleColor(WHITE, getRandomInt(0, 15));
//			Control::gotoXY(symbolpos[i * 2], symbolpos[i * 2 + 1]);
//			putchar(symbol[!turn]);
//		}
//		Control::gotoXY(0, 0);
//		printLogo();
//		colorcount++;
//		turn = !turn;
//		Sleep(250);
//	}
//}

void Menu::changeOption(bool direction, bool flag) //0: lên, 1: xuống
{
	int top = 20;

	if ((direction == 0 && (current_option == 0 || current_option == 8))
		|| (direction == 1 && (current_option == 3 || current_option == 11)))
	{
		Control::playSound(ERROR_SOUND);
		return;
	}

	Control::setConsoleColor(WHITE, BLACK);
	Control::gotoXY(53 - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
	cout << options[current_option];

	if (flag)
	{
		Control::gotoXY(43, top + current_option % 4 * 2);
		putchar(32);
		Control::gotoXY(62, top + current_option % 4 * 2);
		putchar(32);
	}

	if (direction == 1)
		++current_option;
	else
		--current_option;

	if (flag)
	{
		Control::playSound(ENTER_SOUND);
		Control::setConsoleColor(WHITE, RED);

		Control::gotoXY(43, top + current_option % 4 * 2);
		putchar(175);

		Control::gotoXY(53 - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
		cout << options[current_option];

		Control::gotoXY(62, top + current_option % 4 * 2);
		putchar(174);
	}
}

void Menu::chooseMode(bool direction, bool flag, int count) //0: lên, 1: xuống
{
	int leftRec = 40, topRec = 20;
	int top = 21;

	if (((direction == 0) && (current_option == 4 || current_option == 6))
		|| ((direction == 1) && (current_option == 5 || current_option == 7)))
	{
		Control::playSound(ERROR_SOUND);
		return;
	}

	Control::setConsoleColor(WHITE, LIGHT_BLUE);
	Graphic::printRectangleSpecial(leftRec, topRec + (current_option - count) % 2 * 3, 25, 2);


	Control::gotoXY(53 - (int)options[current_option].length() / 2, top + (current_option - count) % 2 * 3);
	cout << options[current_option];

	if (flag)
	{
		Control::gotoXY(36, top + (current_option - count) % 2 * 3);
		putchar(32);
		Control::gotoXY(70, top + (current_option - count) % 2 * 3);
		putchar(32);
	}

	if (direction == 1)
		++current_option;
	else
		--current_option;

	if (flag)
	{
		Control::playSound(ENTER_SOUND);
		Control::setConsoleColor(WHITE, BLUE);

		Graphic::printRectangleSpecial(leftRec, topRec + (current_option - count) % 2 * 3, 25, 2);

		Control::gotoXY(36, top + (current_option - count) % 2 * 3);
		putchar(175);

		Control::gotoXY(53 - (int)options[current_option].length() / 2, top + (current_option - count) % 2 * 3);
		cout << options[current_option];

		Control::gotoXY(70, top + (current_option - count) % 2 * 3);
		putchar(174);
	}
}	

void Menu::mainMenu()
{
	Control::setConsoleColor(WHITE, RED);
	Control::clearConsole();
	printLogo();
	printOptionsBoard();
	current_option = 3;
	changeOption(0, 0);
	changeOption(0, 0);
	changeOption(0, 1);
}

void Menu::playMenu()
{
	int loop = 1;
	current_option = 5;

	Control::setConsoleColor(WHITE, BLACK);
	Control::clearArea(30, 19, 40, 8);

	Menu::chooseMode(0, 1, 4);

	while (loop)
	{
		switch (Control::getConsoleInput())
		{
		case 2:
			Menu::chooseMode(0, 1, 4);
			break;
		case 5:
			Menu::chooseMode(1, 1, 4);
			break;
		case 6:
			loop = 0;
			break;
		default:
			Control::playSound(ERROR_SOUND);
		}
	}
}

void Menu::helpScreen()
{
	Control::setAndCenterWindow();
	Control::showCursor(false);
	Control::setConsoleColor(WHITE, BLACK);
	Control::clearConsole();
	int left = 9, top = 2, width = 85, height = 23;
	int line1 = 6, line2 = 19, line3 = 24, line4 = 15;
	Graphic::printRectangleSpecial(left, top, width, height);
	Control::gotoXY(left + 1, line1);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	Control::gotoXY(left + 1, line2);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	Control::gotoXY(left + 1, line4);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	for (int i = 1; i < height; i++)
	{
		Control::gotoXY(line3, top + i);
		putchar(179);
	}
	Control::gotoXY(line3, line1);
	putchar(197);
	Control::gotoXY(line3, line2);
	putchar(197);
	Control::gotoXY(line3, line4);
	putchar(197);

	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(left + 3, top + 2);
	cout << "Moves:";
	Control::gotoXY(left + 20, top + 1);
	putchar(249); cout << "Up:    W, up arrow";
	Control::gotoXY(left + 52, top + 1);
	putchar(249); cout << "Down:  S, down arrow";
	Control::gotoXY(left + 20, top + 3);
	putchar(249); cout << "Left:  A, left arrow";
	Control::gotoXY(left + 52, top + 3);
	putchar(249); cout << "Right: D, right arrow";


	Control::gotoXY(left + 3, top + 8);
	cout << "Rules:";
	Control::gotoXY(left + 17, top + 5);
	int left1 = left + 17;
	putchar(249); cout << " The Matching Game (commonly known as the Pikachu Puzzle Game)";
	Control::gotoXY(left1, top + 6);
	cout << " includes a board of multiple cells, each of which presents a figure.";
	Control::gotoXY(left1, top + 8);
	putchar(249); cout << " The player finds and matches a pair of cells that contain the same";
	Control::gotoXY(left1, top + 9);
	cout << " figure and connect each other in some particular pattern.";
	Control::gotoXY(left1, top + 11);
	putchar(249); cout << " A legal match will make the two cells disappear. The game ends when";
	Control::gotoXY(left1, top + 12);
	cout << " all matching pairs are found.";

	Control::gotoXY(left + 3, top + 15);
	cout << "Scoring:";
	Control::setConsoleColor(WHITE, GREEN);
	Control::gotoXY(left1 + 10, top + 14);
	putchar(249); cout << " I Matching: +1 BTC";
	Control::setConsoleColor(WHITE, GREEN);
	Control::gotoXY(left1 + 40, top + 14);
	putchar(249); cout << " L Matching: +2 BTC";
	Control::setConsoleColor(WHITE, GREEN);
	Control::gotoXY(left1 + 10, top + 15);
	putchar(249); cout << " Z Matching: +3 BTC";
	Control::gotoXY(left1 + 40, top + 15);
	putchar(249); cout << " U Matching: +4 BTC";
	Control::setConsoleColor(WHITE, RED);
	Control::gotoXY(left1 + 10, top + 16);
	putchar(249); cout << " Not Matched: -2 BTC";
	Control::setConsoleColor(WHITE, RED);
	Control::gotoXY(left1 + 40, top + 16);
	putchar(249); cout << " Move suggestion: -2 BTC";

	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(left + 3, top + 20);
	cout << "Developers:";
	Control::gotoXY(left + 31, top + 19);
	cout << "Dev 1: Nguyen Van Le Ba Thanh (22127390)";
	Control::gotoXY(left + 31, top + 21);
	cout << "Dev 2: Vu Thai Phuc (22127337)";

	Control::setConsoleColor(WHITE, BLACK);
	Graphic::printRectangleNormal(49, 27, 8, 2);
	Control::setConsoleColor(WHITE, RED);
	Control::gotoXY(47, 28);
	putchar(175);
	Control::gotoXY(52, 28);
	cout << "Back";
	Control::gotoXY(60, 28);
	putchar(174);
	while (Control::getConsoleInput() != 6)
	{
		Control::playSound(ERROR_SOUND);
	}
}

void Menu::exitScreen()
{
	Control::setAndCenterWindow();
	Control::showCursor(false);
	Control::setConsoleColor(WHITE, BLACK);
	Control::clearConsole();
	Graphic::printRectangleBlock(34, 18, 35, 8);
	Control::setConsoleColor(BRIGHT_WHITE, BLACK);
	Control::clearArea(35, 19, 34, 6);
	Graphic::printRectangleNormal(38, 22, 7, 2);
	Graphic::printRectangleNormal(59, 22, 6, 2);
	Control::setConsoleColor(WHITE, RED);
	printLogo();


	Control::setConsoleColor(BRIGHT_WHITE, RED);
	Control::gotoXY(42, 20);
	cout << "Do you want to exit?";
	string str[2] = { "Yes", "No" };
	int left[] = { 36,41,48,57,62,68 }, word[] = { 32,32,175,174 }, color[] = { BLACK, RED }, top = 23;
	bool choice = 0;
	bool loop = 1;
	auto print1 = [&]()
	{
		int i = 0;
		while (i < 2)
		{
			Control::playSound(MOVE_SOUND);
			Control::setConsoleColor(BRIGHT_WHITE, color[i]);
			Control::gotoXY(left[choice * 3], top);        putchar(word[i * 2]);
			Control::gotoXY(left[choice * 3 + 1], top);    cout << str[choice];
			Control::gotoXY(left[choice * 3 + 2], top);    putchar(word[i * 2 + 1]);
			if (!i++)
				choice = !choice;
		}
	};
	print1();
	while (loop)
	{
		int key = Control::getConsoleInput();
		if ((key == 3 && choice == 1) || (key == 4 && choice == 0))
		{
			print1();
		}
		else if (key == 6)
		{
			if (!choice)
			{
				Control::setConsoleColor(BLACK, WHITE);
				Control::clearConsole();
				exit(0);
			}
			return;
		}
		else
		{
			Control::playSound(ERROR_SOUND);
		}
	}
}

void Menu::playEasy()
{
	Game g(account.playerName, account.password, _EASY, _EASY, current_option);
	g.startGame();
}

void Menu::playMedium()
{
	Game g(account.playerName, account.password, _MEDIUM, _MEDIUM, current_option);
	g.startGame();
}

void Menu::playCustom()
{
	Control::playSound(ENTER_SOUND);

	int _ROW = 1, _COL = 1;

	Control::clearConsole();
	printLogo();

	int leftRec = 37, topRec = 17;
	int widthRec = 30, heightRec = 10;
	int leftCha = 47, topCha = 18;
	int xInput = leftCha + 11, yInput = topCha + 4;

	Control::setConsoleColor(WHITE, GRAY);
	for (int j = leftRec; j < leftRec + widthRec; ++j)
	{
		Control::gotoXY(j, topRec);
		putchar(45);
	}
	for (int j = leftRec; j < leftRec + widthRec; ++j)
	{
		Control::gotoXY(j, topRec + heightRec);
		putchar(45);
	}

	Control::setConsoleColor(WHITE, RED);
	Control::gotoXY(leftCha, topCha);
	cout << "SIZE BOARD";
	Control::setConsoleColor(WHITE, GRAY);
	Control::gotoXY(leftCha - 12, topCha + 2);
	cout << "Input even numbers between 2 and 12";

	Control::setConsoleColor(WHITE, BLACK);
	Control::gotoXY(leftCha - 5, topCha + 4);
	cout << "Rows: ";
	Control::gotoXY(leftCha - 5, topCha + 7);
	cout << "Cols: ";

	for (int i = 0; i <= 3; i += 3)
	{
		Control::gotoXY(xInput - 3, yInput - 1 + i);
		putchar(201);
		Control::gotoXY(xInput + 3, yInput - 1 + i);
		putchar(187);
		Control::gotoXY(xInput - 3, yInput + 1 + i);
		putchar(200);
		Control::gotoXY(xInput + 3, yInput + 1 + i);
		putchar(188);
		Control::gotoXY(xInput - 3, yInput + i);
		putchar(186);
		Control::gotoXY(xInput + 3, yInput + i);
		putchar(186);
	}

	Control::showCursor(true);
	while (_ROW % 2 != 0 || _ROW <= 2 || _ROW >= 12)
	{
		Control::gotoXY(xInput, yInput);
		cin >> _ROW;
		Control::gotoXY(xInput, yInput);
		putchar(32);
		putchar(32);
	}
	Control::playSound(ENTER_SOUND);

	Control::setConsoleColor(WHITE, LIGHT_RED);
	Control::gotoXY(xInput - 3, yInput - 1);
	putchar(201);
	Control::gotoXY(xInput + 3, yInput - 1);
	putchar(187);
	Control::gotoXY(xInput - 3, yInput + 1);
	putchar(200);
	Control::gotoXY(xInput + 3, yInput + 1);
	putchar(188);
	Control::gotoXY(xInput - 3, yInput);
	putchar(186);
	Control::gotoXY(xInput + 3, yInput);
	putchar(186);

	Control::gotoXY(xInput, yInput);
	cout << _ROW;

	Control::setConsoleColor(WHITE, BLACK);
	while (_COL % 2 != 0 || _COL <= 2 || _COL >= 12)
	{
		Control::gotoXY(xInput, yInput + 3);
		cin >> _COL;
		Control::gotoXY(xInput, yInput + 3);
		putchar(32);
		putchar(32);
	}
	Control::playSound(ENTER_SOUND);
	Control::showCursor(false);

	Control::setConsoleColor(WHITE, LIGHT_RED);
	Control::gotoXY(xInput - 3, yInput - 1 + 3);
	putchar(201);
	Control::gotoXY(xInput + 3, yInput - 1 + 3);
	putchar(187);
	Control::gotoXY(xInput - 3, yInput + 1 + 3);
	putchar(200);
	Control::gotoXY(xInput + 3, yInput + 1 + 3);
	putchar(188);
	Control::gotoXY(xInput - 3, yInput + 3);
	putchar(186);
	Control::gotoXY(xInput + 3, yInput + 3);
	putchar(186);

	Control::gotoXY(xInput, yInput + 3);
	cout << _COL;

	Control::setConsoleColor(WHITE, GRAY);
	for (int i = 0; i < 3; ++i)
	{
		Control::gotoXY(leftCha - 5, topCha + 1);
		cout << "Generating board ";
		Control::gotoXY(leftCha + 12, topCha + 1);
		putchar(16);
		Sleep(500);
		Control::gotoXY(leftCha + 13, topCha + 1);
		putchar(16);
		Sleep(500);
		Control::gotoXY(leftCha + 14, topCha + 1);
		putchar(16);
		Sleep(500);
		Control::gotoXY(leftCha + 12, topCha + 1);
		putchar(32);
		putchar(32);
		putchar(32);
		Sleep(200);
	}

	Game g(account.playerName, account.password, _ROW, _COL, current_option);
	g.startGame();
}

void Menu::leaderBoard()
{
	current_option = 0;
	Control::clearConsole();

	Player p[200];
	int leftRec = 24, topRec = 9;

	Control::setConsoleColor(WHITE, RED);
	cout << R"(
	    _      ______          _____  ______ _____       ____   ____          _____  _____  
	   | |    |  ____|   /\   |  __ \|  ____|  __ \     |  _ \ / __ \   /\   |  __ \|  __ \ 
	   | |    | |__     /  \  | |  | | |__  | |__) |    | |_) | |  | | /  \  | |__) | |  | |
	   | |    |  __|   / /\ \ | |  | |  __| |  _  /     |  _ <| |  | |/ /\ \ |  _  /| |  | |
	   | |____| |____ / ____ \| |__| | |____| | \ \     | |_) | |__| / ____ \| | \ \| |__| |
	   |______|______/_/    \_\_____/|______|_|  \_\    |____/ \____/_/    \_\_|  \_\_____/ 
                                                                                                                                                                                                         
	)";

	Control::setConsoleColor(WHITE, BLACK);
	Graphic::printRectangleNormal(leftRec, topRec, 56, 17);

	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(leftRec + 3, topRec + 1);
	cout << "STT";
	Control::setConsoleColor(WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Control::gotoXY(leftRec + 8, topRec + i);
		putchar(179);
	}
	for (int i = 1; i < 8; i++)
	{
		Control::gotoXY(leftRec + i, topRec + 2);
		putchar(196);
	}
	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(leftRec + 15, topRec + 1);
	cout << "NAME";
	Control::setConsoleColor(WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Control::gotoXY(leftRec + 25, topRec + i);
		putchar(179);
	}
	for (int i = 9; i < 25; i++)
	{
		Control::gotoXY(leftRec + i, topRec + 2);
		putchar(196);
	}
	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(leftRec + 33, topRec + 1);
	cout << "MODE";
	Control::setConsoleColor(WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Control::gotoXY(leftRec + 44, topRec + i);
		putchar(179);
	}
	for (int i = 26; i < 44; i++)
	{
		Control::gotoXY(leftRec + i, topRec + 2);
		putchar(196);
	}
	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(leftRec + 48, topRec + 1);
	cout << "SCORE";
	Control::setConsoleColor(WHITE, BLACK);

	/*for (int i = 1; i < 17; i++)
	{
		Control::gotoXY(leftRec + 57, topRec + i);
		putchar(179);
	}*/

	for (int i = 45; i < 57; i++)
	{
		Control::gotoXY(leftRec + i, topRec + 2);
		putchar(196);
	}



	int y = topRec + 3;
	int lines = 8;
	int n = 0;
	string tmp;
	fstream fs("file\\leaderboard.txt", ios::in);

	while (!fs.eof()) {
		fs.getline(p[n].playerName, NAMESIZE + 1);
		fs.getline(p[n].mode, 15);
		fs >> p[n].score;
		fs.ignore();
		n++;
	}
	fs.close();
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (p[j].score > p[i].score) {
				swap(p[i], p[j]);
			}
		}
	}
	for (int i = 1; i < lines; i++) {
		Control::gotoXY(leftRec + 4, y);
		cout << i;
		Control::gotoXY(leftRec + 11, y);
		cout << p[i - 1].playerName;
		Control::gotoXY(leftRec + 28, y);
		cout << p[i - 1].mode;
		Control::gotoXY(leftRec + 50, y);
		cout << p[i - 1].score;
		y += 2;
	}

	Control::setConsoleColor(WHITE, BLACK);
	Graphic::printRectangleSpecial(48, 27, 8, 2);
	Control::setConsoleColor(WHITE, RED);
	Control::gotoXY(46, 28);
	putchar(175);
	Control::gotoXY(51, 28);
	cout << "Back";
	Control::gotoXY(59, 28);
	putchar(174);
	while (Control::getConsoleInput() != 6)
	{
		Control::playSound(ERROR_SOUND);
	}
}

void Menu::UserMode()
{
	int loop = 1;
	current_option = 7;

	Control::setConsoleColor(WHITE, WHITE);
	Control::clearArea(30, 19, 40, 6);

	Menu::chooseMode(0, 1, 6);

	while (loop)
	{
		switch (Control::getConsoleInput())
		{
		case 2:
			Menu::chooseMode(0, 1, 6);
			break;
		case 5:
			Menu::chooseMode(1, 1, 6);
			break;
		case 6:
			loop = 0;
			break;
		default:
			Control::playSound(ERROR_SOUND);
		}
	}
}

void Menu::guestMode()
{
	srand((unsigned)time(0));

	for (int i = 0; i < 12; ++i)
		account.playerName[i] = rand() % 62 + 65;

	strcpy_s(account.password, "123");

	ofstream Create;
	Create.open("file\\accounts.txt", ios::app);
	Create << endl << account.playerName << endl << account.password;
	Create.close();

	printMode();
}

void Menu::readFileAccounts(ifstream& Acc, char accounts_game[][50])
{
	int i = 0;
	while (!Acc.eof()) {
		Acc.getline(accounts_game[i], 100);
		i++;
	}
}

void Menu::enterAccount()
{
	account.playerName[0] = 0;
	account.password[0] = 0;

	Control::setConsoleColor(WHITE, WHITE);
	Control::clearArea(30, 19, 40, 6);

	Control::setConsoleColor(WHITE, RED);
	Control::gotoXY(22, 18);
	cout << "Please enter Username and Password shortly, under 12 characters!";

	int leftCha = 45, topCha = 17;
	int xInput = leftCha + 14, yInput = topCha + 4;

	Control::setConsoleColor(WHITE, BLACK);
	Control::gotoXY(leftCha - 10, topCha + 4);
	cout << "Username: ";
	Control::gotoXY(leftCha - 10, topCha + 8);
	cout << "Password: ";

	for (int i = 0; i <= 4; i += 4)
	{
		Control::gotoXY(xInput - 9, yInput - 1 + i);
		putchar(201);
		Control::gotoXY(xInput + 9, yInput - 1 + i);
		putchar(187);
		Control::gotoXY(xInput - 9, yInput + 1 + i);
		putchar(200);
		Control::gotoXY(xInput + 9, yInput + 1 + i);
		putchar(188);
		Control::gotoXY(xInput - 9, yInput + i);
		putchar(186);
		Control::gotoXY(xInput + 9, yInput + i);
		putchar(186);
	}

	Control::showCursor(true);
	while (strlen(account.playerName) == 0 || account.playerName[0] == 0)
	{
		Control::gotoXY(xInput - 6, yInput);
		cin.getline(account.playerName, NAMESIZE + 1);
	}

	Control::playSound(ENTER_SOUND);

	Control::setConsoleColor(WHITE, LIGHT_RED);
	Control::gotoXY(xInput - 9, yInput - 1);
	putchar(201);
	Control::gotoXY(xInput + 9, yInput - 1);
	putchar(187);
	Control::gotoXY(xInput - 9, yInput + 1);
	putchar(200);
	Control::gotoXY(xInput + 9, yInput + 1);
	putchar(188);
	Control::gotoXY(xInput - 9, yInput);
	putchar(186);
	Control::gotoXY(xInput + 9, yInput);
	putchar(186);

	Control::gotoXY(xInput - 6, yInput);
	cout << account.playerName;

	Control::setConsoleColor(WHITE, BLACK);
	while (strlen(account.password) == 0 || account.password[0] == 0)
	{
		Control::gotoXY(xInput - 6, yInput + 4);
		cin.getline(account.password, PASSSIZE + 1);
	}

	Control::playSound(ENTER_SOUND);
	Control::showCursor(false);

	Control::setConsoleColor(WHITE, LIGHT_RED);
	Control::gotoXY(xInput - 9, yInput - 1 + 4);
	putchar(201);
	Control::gotoXY(xInput + 9, yInput - 1 + 4);
	putchar(187);
	Control::gotoXY(xInput - 9, yInput + 1 + 4);
	putchar(200);
	Control::gotoXY(xInput + 9, yInput + 1 + 4);
	putchar(188);
	Control::gotoXY(xInput - 9, yInput + 4);
	putchar(186);
	Control::gotoXY(xInput + 9, yInput + 4);
	putchar(186);

	Control::gotoXY(xInput - 6, yInput + 4);
	cout << account.password;

	Control::setConsoleColor(WHITE, WHITE);
	Control::clearArea(30, 28, 40, 1);
}

bool Menu::rightAccount(char accounts_game[][50])
{
	int i = 0;
	bool username = false;

	while (accounts_game[i][0] != NULL)
	{
		if (strcmp(account.playerName, accounts_game[i]) == 0)
		{
			username = true;
			break;
		}
		i += 2;
	}

	if (username == true)
	{
		if (strcmp(account.password, accounts_game[i + 1]) == 0)
		{
			Control::gotoXY(44, 28);
			Control::setConsoleColor(WHITE, RED);
			cout << "Loggin sucessfully";

			Sleep(1200);
			return true;
		}
	}	

	Control::gotoXY(40, 28);
	Control::setConsoleColor(WHITE, RED);
	cout << "Wrong Username or Password";

	Sleep(1200);
	return false;
}

bool Menu::appropriateAccount(char accounts_game[][50])
{
	int i = 0;
	bool username = true;

	while (accounts_game[i][0] != NULL)
	{
		if (strcmp(account.playerName, accounts_game[i]) == 0)
		{
			username = false;
			break;
		}
		i += 2;
	}

	if (username == true)
	{
		Control::gotoXY(40, 28);
		Control::setConsoleColor(WHITE, RED);
		cout << "Create account sucessfully";

		Sleep(1200);
		return true;
	}

	Control::gotoXY(42, 28);
	Control::setConsoleColor(WHITE, RED);
	cout << "Username already exist";

	Sleep(1200);
	return false;
}

void Menu::printMode()
{
	Control::setConsoleColor(WHITE, WHITE);
	Control::clearArea(20, 18, 65, 10);

	current_option = 11;

	printOptionsBoard();

	changeOption(0, 0);
	changeOption(0, 0);
	changeOption(0, 1);
}

void Menu::signIn()
{
	ifstream Acc;
	char accounts_game[200][50];
	Acc.open("file\\accounts.txt");
	readFileAccounts(Acc, accounts_game);
	Acc.close();

	do {
		enterAccount();
	} while (!rightAccount(accounts_game));

	printMode();
}

void Menu::signUp()
{
	ifstream Acc;
	char accounts_game[200][50];
	Acc.open("file\\accounts.txt");
	readFileAccounts(Acc, accounts_game);
	Acc.close();

	do {
		enterAccount();
	} while (!appropriateAccount(accounts_game));

	ofstream Create;
	Create.open("file\\accounts.txt", ios::app);
	Create << endl << account.playerName << endl << account.password;
	Create.close();

	printMode();
}


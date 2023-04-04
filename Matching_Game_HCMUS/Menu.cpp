﻿#include "Menu.h"
int Menu::current_option;
const string Menu::options[10] = { "Play", "Leader Board", "Help", "Exit", "Easy", "   Medium   ", "Custom", "Exit", "Username:            ", "Guest Mode" };

void Menu::mainScreen()
{
	unordered_map<string, void(*)()> function_map = {
		{options[0], playMenu},
		{options[1], leaderBoard},
		{options[2], helpScreen},
		{options[3], exitScreen},
		{options[4], playEasy},
		{options[5], playMedium},
		{options[6], playCustom},
		{options[7], exitScreen},
		{options[8], playUserMode},
		{options[9], playGuestMode}
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
				loadMenu = 0;
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
{/*

		██─╮  ██─╮      █─╮    ███████─╮      █████─╮  █─╮  █─╮  █─╮  ██─╮  █─╮   █████─╮
		█ █╰╮█ █ │     █ █╰╮   ╰──█ ╭──╯     █╭─────╯  █ │  █ │  █ │  █ █╰╮ █ │  █ ╭────╯
		█ │██ ╭█ │    █ ╭╯█╰╮     █ │        █│        ██████ │  █ │  █ │█╰╮█ │  █ │ ███─╮
		█ │╰──╯█ │   ███████╰╮    █ │        █│        █ ╭──█ │  █ │  █ │ █╰█ │  █ │   █ │
		█ │    █ │  █ ╭─────█╰╮   █ │         █████─╮  █ │  █ │  █ │  █ │  ██ │   █████ ╭╯
		╰─╯    ╰─╯  ╰─╯     ╰─╯   ╰─╯         ╰─────╯  ╰─╯  ╰─╯  ╰─╯  ╰─╯  ╰──╯   ╰─────╯







		*/
		/*string startback[50];
		ifstream ip;

		ip.open("start");

		int i = 0;
		while (!ip.eof()) {
			getline(ip, startback[i]);
			i++;
		}
		ip.close();*/

		/*for (int n = 0; n < i; n++)
			cout << startback[i] << endl;*/

			//cout << startback[1];

	/*for (int i = 0; i < 100; ++i)
		cout << i << endl;*/



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

	Control::gotoXY(0, 0);
	Control::setConsoleColor(WHITE, LIGHT_RED);
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

	if ((direction == 0 && (current_option == 4 || current_option == 0))
		|| (direction == 1 && (current_option == 3 || current_option == 7)))
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

void Menu::chooseMode(bool direction, bool flag, int& current_option) //0: lên, 1: xuống
{
	int leftRec = 38, topRec = 20;
	int top = 21;

	if ((direction == 0 && current_option == 8)
		|| (direction == 1 && current_option == 9))
	{
		Control::playSound(ERROR_SOUND);
		return;
	}

	Control::setConsoleColor(WHITE, LIGHT_BLUE);

	Control::gotoXY(leftRec, topRec + (current_option - 8) % 2 * 3);
	putchar(201);
	for (int i = 1; i < 25; i++)
	{
		putchar(205);

	}
	putchar(187);

	Control::gotoXY(leftRec, topRec + (current_option - 8) % 2 * 3 + 1);
	putchar(186);
	Control::gotoXY(leftRec + 25, topRec + (current_option - 8) % 2 * 3 + 1);
	putchar(186);

	Control::gotoXY(leftRec, topRec + (current_option - 8) % 2 * 3 + 2);
	putchar(200);
	for (int i = 1; i < 25; i++)
	{
		putchar(205);

	}
	putchar(188);

	Control::gotoXY(51 - (int)options[current_option].length() / 2, top + (current_option - 8) % 2 * 3);
	cout << options[current_option];

	if (flag)
	{
		Control::gotoXY(34, top + (current_option - 8) % 2 * 3);
		putchar(32);
		Control::gotoXY(67, top + (current_option - 8) % 2 * 3);
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

		Control::gotoXY(leftRec, topRec + (current_option - 8) % 2 * 3);
		putchar(201);
		for (int i = 1; i < 25; i++)
		{
			putchar(205);

		}
		putchar(187);

		Control::gotoXY(leftRec, topRec + (current_option - 8) % 2 * 3 + 1);
		putchar(186);
		Control::gotoXY(leftRec + 25, topRec + (current_option - 8) % 2 * 3 + 1);
		putchar(186);

		Control::gotoXY(leftRec, topRec + (current_option - 8) % 2 * 3 + 2);
		putchar(200);
		for (int i = 1; i < 25; i++)
		{
			putchar(205);

		}
		putchar(188);

		Control::gotoXY(34, top + (current_option - 8) % 2 * 3);
		putchar(175);
		Control::gotoXY(51 - (int)options[current_option].length() / 2, top + (current_option - 8) % 2 * 3);
		cout << options[current_option];
		Control::gotoXY(67, top + (current_option - 8) % 2 * 3);
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
	current_option = 7;
	changeOption(0, 0);
	changeOption(0, 0);
	changeOption(0, 1);
}

void Menu::helpScreen()
{
	Control::showCursor(false);
	Control::setConsoleColor(WHITE, BLACK);
	Control::clearConsole();
	int left = 5, top = 2, width = 85, height = 23;
	int line1 = 6, line2 = 19, line3 = 20, line4 = 15;
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
	Graphic::printRectangleNormal(45, 27, 8, 2);
	Control::setConsoleColor(WHITE, RED);
	Control::gotoXY(43, 28);
	putchar(175);
	Control::gotoXY(48, 28);
	cout << "Back";
	Control::gotoXY(56, 28);
	putchar(174);
	while (Control::getConsoleInput() != 6)
	{
		Control::playSound(ERROR_SOUND);
	}
}

void Menu::exitScreen()
{
	Control::showCursor(false);
	Control::setConsoleColor(WHITE, BLACK);
	Control::clearConsole();
	Control::setConsoleColor(WHITE, BLACK);
	Graphic::printRectangleSpecial(34, 17, 35, 6);
	Graphic::printRectangleNormal(37, 20, 7, 2);
	Graphic::printRectangleNormal(60, 20, 6, 2);
	Control::setConsoleColor(WHITE, RED);
	Control::gotoXY(0, 0);
	printLogo();


	Control::setConsoleColor(WHITE, RED);
	Control::gotoXY(42, 18);
	cout << "Do you want to exit?";
	string str[2] = { "Yes", "No" };
	int left[] = { 35,40,47,58,63,69 }, word[] = { 32,32,175,174 }, color[] = { BLACK, RED }, top = 21;
	bool choice = 0;
	bool loop = 1;
	auto print1 = [&]()
	{
		int i = 0;
		while (i < 2)
		{
			Control::playSound(MOVE_SOUND);
			Control::setConsoleColor(WHITE, color[i]);
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
	current_option = 9;

	Game g(_EASY, _EASY);
	g.setupGame(current_option);
	g.startGame();
}

void Menu::playMedium()
{
	current_option = 9;

	Game g(_MEDIUM, _MEDIUM);
	g.setupGame(current_option);
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
	for (int j = leftRec; j <= leftRec + widthRec; ++j)
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

	current_option = 9;

	Game g(_ROW, _COL);
	g.setupGame(current_option);
	g.startGame();
}

void Menu::leaderBoard()
{
	current_option = 0;
	Control::clearConsole();

	Player p[100];
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
	fstream fs("leaderboard.txt", ios::in);

	while (!fs.eof()) {
		getline(fs, p[n].playerName);
		getline(fs, p[n].mode);
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

void Menu::playUserMode()
{

}

void Menu::playGuestMode()
{

}



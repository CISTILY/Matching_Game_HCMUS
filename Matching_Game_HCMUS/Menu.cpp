#include "Menu.h"
int Menu::current_option;
const string Menu::options[10] = { "Play", "LeaderBoard", "Help", "Exit", "Easy", "  Medium   ", "Back", "Exit", "Username", "Guest Mode" };

void Menu::mainScreen()
{
	unordered_map<string, void(*)()> function_map = {
		{options[0], playMenu},
		{options[1], leaderBoard},
		{options[2], helpScreen},
		{options[3], exitScreen},
		{options[4], playEasy},
		{options[5], playMedium},
		{options[6], goBack},
		{options[7], exitScreen},
		{options[8], enterUsername},
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
		          ██ │  ████─╮   ██ ╭╯██╰╮    ██ │████ ╭██ │  ████████─╮
		          ██ │   ██ ╭╯  █████████╰╮   ██ │ ╰───╯██ │  ██ ╭─────╯
		           ███████ ╭╯  ██ ╭─────██╰╮  ██ │      ██ │  ████████─╮
		           ╰───────╯   ╰──╯     ╰──╯  ╰──╯      ╰──╯  ╰────────╯

	)";

	Control::gotoXY(1, 0);
	Control::setConsoleColor(WHITE, LIGHT_RED);
	cout << logo;
}

void Menu::printOptionsBoard()
{
	SetConsoleOutputCP(437);
	SetConsoleCP(437);

	Control::setConsoleColor(WHITE, BLACK);
	int left = 47; //48
	int top = 19;

	Control::gotoXY(left, top);

	putchar(201);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);

	}
	putchar(187);


	for (int i = 1; i < 8; i++)
	{
		Control::gotoXY(left, top + i);
		if (i % 2 != 0)
		{
			putchar(186);
			Control::gotoXY(left + 12, top + i);
			putchar(186);
		}
		else
		{
			putchar(199);
			for (int i = 1; i < 12; i++)
			{
				putchar(196);
			}
			putchar(182);
		}
	}
	Control::gotoXY(left, top + 8);
	putchar(200);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(188);
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
		Control::gotoXY(63, top + current_option % 4 * 2);
		putchar(32);
	}
	(direction == 1) ? current_option++ : current_option--;
	if (flag)
	{
		Control::playSound(ENTER_SOUND);
		Control::setConsoleColor(WHITE, RED);
		Control::gotoXY(43, top + current_option % 4 * 2);
		putchar(175);
		Control::gotoXY(53 - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
		cout << options[current_option];
		Control::gotoXY(63, top + current_option % 4 * 2);
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
	printRectangle(left, top, width, height);
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
	printRectangle(45, 27, 8, 2);
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

void Menu::printRectangle(int left, int top, int width, int height)
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

void Menu::exitScreen()
{
	Control::showCursor(false);
	Control::setConsoleColor(WHITE, BLACK);
	Control::clearConsole();
	Control::setConsoleColor(WHITE, BLACK);
	Menu::printRectangle(34, 17, 35, 6);
	Menu::printRectangle(37, 20, 7, 2);
	Menu::printRectangle(60, 20, 6, 2);
	Control::setConsoleColor(WHITE, RED);
	Control::gotoXY(0, 0);
	printLogo();

	SetConsoleOutputCP(437);

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
	Game g(_EASY);
	g.setupGame();
	g.startGame();
}

void Menu::playMedium()
{
	Game g(_MEDIUM);
	g.setupGame();
	g.startGame();
}

void Menu::leaderBoard()
{
	current_option = 0;
	Control::clearConsole();
	Player p[100];
	Control::setConsoleColor(BRIGHT_WHITE, RED);
	cout << R"(
	  _      ______          _____  ______ _____  ____   ____          _____  _____  
	 | |    |  ____|   /\   |  __ \|  ____|  __ \|  _ \ / __ \   /\   |  __ \|  __ \ 
	 | |    | |__     /  \  | |  | | |__  | |__) | |_) | |  | | /  \  | |__) | |  | |
	 | |    |  __|   / /\ \ | |  | |  __| |  _  /|  _ <| |  | |/ /\ \ |  _  /| |  | |
	 | |____| |____ / ____ \| |__| | |____| | \ \| |_) | |__| / ____ \| | \ \| |__| |
	 |______|______/_/    \_\_____/|______|_|  \_\____/ \____/_/    \_\_|  \_\_____/                                                                 
	)";
	Control::setConsoleColor(WHITE, BLACK);
	printRectangle(5, 8, 85, 17);

	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(8, 9);
	cout << "STT";
	Control::setConsoleColor(WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Control::gotoXY(13, 8 + i);
		putchar(179);
	}
	for (int i = 6; i < 13; i++)
	{
		Control::gotoXY(i, 10);
		putchar(196);
	}
	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(18, 9);
	cout << "Name";
	Control::setConsoleColor(WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Control::gotoXY(30, 8 + i);
		putchar(179);
	}
	for (int i = 14; i < 30; i++)
	{
		Control::gotoXY(i, 10);
		putchar(196);
	}
	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(36, 9);
	cout << "ID";
	Control::setConsoleColor(WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Control::gotoXY(45, 8 + i);
		putchar(179);
	}
	for (int i = 31; i < 45; i++)
	{
		Control::gotoXY(i, 10);
		putchar(196);
	}
	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(52, 9);
	cout << "Class";
	Control::setConsoleColor(WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Control::gotoXY(62, 8 + i);
		putchar(179);
	}
	for (int i = 46; i < 62; i++)
	{
		Control::gotoXY(i, 10);
		putchar(196);
	}
	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(68, 9);
	cout << "Mode";
	Control::setConsoleColor(WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Control::gotoXY(78, 8 + i);
		putchar(179);
	}
	for (int i = 63; i < 78; i++)
	{
		Control::gotoXY(i, 10);
		putchar(196);
	}

	Control::setConsoleColor(WHITE, BLUE);
	Control::gotoXY(82, 9);
	cout << "Score";
	Control::setConsoleColor(WHITE, BLACK);
	for (int i = 79; i < 91; i++)
	{
		Control::gotoXY(i, 10);
		putchar(196);
	}
	int y = 11;
	int lines = 8;
	int n = 0;
	string tmp;
	fstream fs("rank\\leaderboard.txt", ios::in);

	while (!fs.eof()) {
		getline(fs, p[n].playerName);
		getline(fs, p[n].playerID);
		getline(fs, p[n].className);
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
		Control::gotoXY(9, y);
		cout << i;
		Control::gotoXY(16, y);
		cout << p[i - 1].playerName;
		Control::gotoXY(33, y);
		cout << p[i - 1].playerID;
		Control::gotoXY(50, y);
		cout << p[i - 1].className;
		Control::gotoXY(68, y);
		cout << p[i - 1].mode;
		Control::gotoXY(84, y);
		cout << p[i - 1].score;
		y += 2;
	}

	Control::setConsoleColor(WHITE, BLACK);
	printRectangle(45, 27, 8, 2);
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

void Menu::enterUsername()
{

}

void Menu::playGuestMode()
{

}



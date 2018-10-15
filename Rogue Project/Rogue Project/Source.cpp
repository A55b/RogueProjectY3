#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

const int LEVELWIDTH = 20;
const int LEVELHEIGHT = 10;

unsigned int playerPositionX = 5;
unsigned int playerPositionY = 5;
unsigned int newPlayerPositionX = playerPositionX;
unsigned int newPlayerPositionY = playerPositionY;

//unsigned int MenuPositionX = 5;
unsigned int MenuPositionY = 5;

unsigned int health = 0;
unsigned int sword = 1;
unsigned int healthPotiton = 2;
unsigned int menucount = 1;

char playerChar = 'P';


char map[LEVELHEIGHT][LEVELWIDTH + 1] =
{ "aaaaaaaaaaaaaaaaaaaa",
"a         +      H a",
"a                  a",
"a                  a",
"a                  a",
"a               +  a",
"a                  a",
"a     +         S  a",
"a          +       a",
"aaaaaaaaaaaaaaaaaaaa"
};

void gotoScreenPosition(short C, short R);

void handleCollisions();

void renderMap();

void renderDrop(char d);

void Menu();

void handleInput();

void handleInventoryInput();

void renderMenu();

void renderControls();

void renderPlayer();

void renderGUI();

void renderItems();

void main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	MoveWindow(console, r.left, r.top, 800, 800, TRUE);

	renderMap();
	renderControls();

	while (true)
	{
		// Handles the input and updates the players position
		handleInput();

		// Handle collisions
		handleCollisions();

		// Render the scene
		renderPlayer();

		// Render the GUI
		renderGUI();
	}

	system("pause");
}

void gotoScreenPosition(short C, short R)
{
	COORD xy;
	xy.X = C;
	xy.Y = R;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

void handleCollisions()
{
	renderItems();

	// Check the location that the player wants to move to on the map
	char nextLocation = map[newPlayerPositionY][newPlayerPositionX];

	// If the nextLocation is a border....
	if (nextLocation == 'a')
	{
		// ....then don't move i.e. set the new position back to the old position
		newPlayerPositionX = playerPositionX;
		newPlayerPositionY = playerPositionY;
	}
	// If the nextLocation is a health pack
	if (nextLocation == '+')
	{
		// Increase our health
		health++;

		// Remove it from the map
		map[newPlayerPositionY][newPlayerPositionX] = ' ';
	}
	if (nextLocation == 'S')
	{
		// Increase our health
		sword++;

		// Remove it from the map
		map[newPlayerPositionY][newPlayerPositionX] = ' ';
	}
	if (nextLocation == 'H')
	{
		// Increase our health
		healthPotiton++;

		// Remove it from the map
		map[newPlayerPositionY][newPlayerPositionX] = ' ';
	}
}

void renderMap()
{
	for (int i = 0; i < LEVELHEIGHT; i++)
	{
		std::cout << map[i] << std::endl;
	}
}

void Menu()
{
	for (int i = 0; i < LEVELHEIGHT; i++)
	{
		std::cout << map[i] << std::endl;
	}
}

void handleInput()
{
	newPlayerPositionX = playerPositionX;
	newPlayerPositionY = playerPositionY;

	if (GetKeyState(VK_UP) & 0x8000)
	{
		newPlayerPositionY = playerPositionY - 1;
	}

	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		newPlayerPositionY = playerPositionY + 1;
	}

	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		newPlayerPositionX = playerPositionX + 1;
	}

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		newPlayerPositionX = playerPositionX - 1;
	}

	if (GetAsyncKeyState('I') & 0x8000)
	{
		Sleep(90);
		handleInventoryInput();
	}
}

void handleInventoryInput()
{
	MenuPositionY = 2;
	menucount = 1;
	while (true)
	{
		gotoScreenPosition(28, MenuPositionY);
		//MenuPositionY = MenuPositionY;

		if ((GetKeyState(VK_UP) & 0x8000) && (MenuPositionY > 2))
		{
			Sleep(90);
			MenuPositionY = MenuPositionY - 1;
			menucount--;
		}

		if ((GetKeyState(VK_DOWN) & 0x8000) && (MenuPositionY < 10))
		{
			Sleep(90);
			MenuPositionY = MenuPositionY + 1;
			menucount++;
		}

		if (GetKeyState('D') & 0x8000)
		{
			if ((menucount == 1) && (sword > 0))
			{
				char d = 'S';
				sword--;
				renderDrop(d);
				renderItems();
				Sleep(90);
			}

			if ((menucount == 2) && (healthPotiton > 0))
			{
				char d = 'H';
				healthPotiton--;
				renderDrop(d);
				renderItems();
				Sleep(90);
			}
		}

		if (GetKeyState('U') & 0x8000)
		{
			if ((menucount == 2) && (healthPotiton > 0))
			{
				healthPotiton--;
				health = health + 10;
				renderItems();
				renderGUI();
				Sleep(90);
			}
		}

		if (GetAsyncKeyState('I') & 0x8000)
		{
			Sleep(90);
			return;
		}
	}
}

void renderMenu()
{
	// Blank old enemy position
	gotoScreenPosition(30, MenuPositionY);
	std::cout << ' ';

	// Draw new enemy position
	gotoScreenPosition(30, newPlayerPositionY);
	std::cout << playerChar;

	playerPositionX = newPlayerPositionX;
	playerPositionY = newPlayerPositionY;

	Sleep(60);
}

void renderPlayer()
{
	// Blank old enemy position
	gotoScreenPosition(playerPositionX, playerPositionY);
	std::cout << ' ';

	// Draw new enemy position
	gotoScreenPosition(newPlayerPositionX, newPlayerPositionY);
	std::cout << playerChar;

	playerPositionX = newPlayerPositionX;
	playerPositionY = newPlayerPositionY;

	Sleep(60);
}

void renderDrop(char d)
{
	renderItems();
	// Blank old enemy position
	gotoScreenPosition((playerPositionX - 1), playerPositionY);
	std::cout << d;
	map[newPlayerPositionY][(newPlayerPositionX - 1)] = d;

	playerPositionX = newPlayerPositionX;
	playerPositionY = newPlayerPositionY;

	Sleep(60);
}

void renderGUI()
{
	gotoScreenPosition(2, LEVELHEIGHT + 3);
	std::cout << "Health: " << health << std::endl;
}

void renderControls()
{
	gotoScreenPosition(2, LEVELHEIGHT + 5);
	std::cout << "Press I for inventory";
	gotoScreenPosition(2, LEVELHEIGHT + 7);
	std::cout << "Press D to drop";
	gotoScreenPosition(2, LEVELHEIGHT + 9);
	std::cout << "Press U to use";
	gotoScreenPosition(30, 1);
	std::cout << "Inventory";
}

void renderItems()
{
	gotoScreenPosition(30, 2);
	std::cout << "Swords: " << sword;
	gotoScreenPosition(30, 3);
	std::cout << "Health Potiton: " << healthPotiton;
}
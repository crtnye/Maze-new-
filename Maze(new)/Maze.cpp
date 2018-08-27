#include<iostream>
#include<stack>
#include<cstdlib>
#include<ctime>
#include"Maze.h"

using std::cout;
using std::cin;

Maze::Maze()
{
}

Maze::~Maze()
{
}

void Maze::playMaze()
{
	initializeGrid();
	digMaze();
	printMaze();
	navigateMaze();
}

void Maze::initializeGrid()
{
	for (int row = 0; row < NUM_ROWS; row++)
	{
		for (int column = 0; column < NUM_COLS; column++)
		{
			grid[row][column] = MAZE_WALL;
		}
	}
}

void Maze::findValidDirections(bool &canGoUp, bool &canGoRight, bool &canGoDown, bool &canGoLeft, COORD currentLocation)
{
	canGoUp = (currentLocation.Y >= 3) && (grid[currentLocation.Y - 2][currentLocation.X] == MAZE_WALL);
	canGoRight = (currentLocation.X <= (NUM_COLS - 4)) && (grid[currentLocation.Y][currentLocation.X + 2] == MAZE_WALL);
	canGoDown = (currentLocation.Y <= (NUM_ROWS - 4)) && (grid[currentLocation.Y + 2][currentLocation.X] == MAZE_WALL);
	canGoLeft = (currentLocation.X >= 3) && (grid[currentLocation.Y][currentLocation.X - 2] == MAZE_WALL);
}

void Maze::chooseAndMoveADirection(bool canGoUp, bool canGoRight, bool canGoDown, bool canGoLeft, 
	COORD &currentLocation, bool &directionFound)
{
	int direction = rand() % 4;
	if (direction == 0 && canGoUp == true)
	{
		directionFound = true;
		grid[currentLocation.Y - 1][currentLocation.X] = ' ';
		grid[currentLocation.Y - 2][currentLocation.X] = ' ';
		currentLocation.Y = currentLocation.Y - 2;
	}
	else if (direction == 1 && canGoRight == true)
	{
		directionFound = true;
		grid[currentLocation.Y][currentLocation.X + 1] = ' ';
		grid[currentLocation.Y][currentLocation.X + 2] = ' ';
		currentLocation.X = currentLocation.X + 2;
	}
	else if (direction == 2 && canGoDown == true)
	{
		directionFound = true;
		grid[currentLocation.Y + 1][currentLocation.X] = ' ';
		grid[currentLocation.Y + 2][currentLocation.X] = ' ';
		currentLocation.Y = currentLocation.Y + 2;
	}
	else if (direction == 3 && canGoLeft == true)
	{
		directionFound = true;
		grid[currentLocation.Y][currentLocation.X - 1] = ' ';
		grid[currentLocation.Y][currentLocation.X - 2] = ' ';
		currentLocation.X = currentLocation.X - 2;
	}
}

void Maze::backtrack(COORD &currentLocation, stack<COORD> &locations)
{
	currentLocation = locations.top();
	locations.pop();
}

void Maze::digMaze()
{
	std::stack<COORD> locations;
	COORD currentLocation = start = getMazeStart();
	grid[start.Y][start.X] = 'S';

	do
	{
		bool canGoUp, canGoRight, canGoDown, canGoLeft;
		findValidDirections(canGoUp, canGoRight, canGoDown, canGoLeft, currentLocation);

		if (canGoUp == true || canGoRight == true || canGoDown == true || canGoLeft == true)
		{
			locations.push(currentLocation);
			bool directionFound = false;
			do
			{
				chooseAndMoveADirection(canGoUp, canGoRight, canGoDown, canGoLeft, currentLocation, directionFound);
			} while (directionFound == false);
		}
		else
		{
			if (!locations.empty())
			{
				backtrack(currentLocation, locations);
			}
		}
	} while (!locations.empty());
	finish = getMazeFinish();
	grid[finish.Y][finish.X] = 'F';
}

void Maze::printMaze()
{
	for (int row = 0; row < NUM_ROWS; row++)
	{
		for (int column = 0; column < NUM_COLS; column++)
		{
			addColor(row, column);
			cout << grid[row][column];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		cout << std::endl;
	}
}

//makes the start and end symbols a color of choice
void Maze::addColor(int row, int column)
{
	if (row == start.Y && column == start.X)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	}
	else if (row == finish.Y && column == finish.X)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	}
}

COORD Maze::getMazeStart()
{
	COORD start;
	srand(time(NULL));
	do
	{
		start.X = rand() % NUM_COLS;
	} while (start.X % 2 == 0);
	do
	{
		start.Y = rand() % NUM_ROWS;
	} while (start.Y % 2 == 0);

	return start;
}

COORD Maze::getMazeFinish()
{
	COORD finish;
	srand(time(NULL));
	do
	{
		do
		{
			finish.X = rand() % NUM_COLS;
		} while (finish.X % 2 == 0);

		do
		{
			finish.Y = rand() % NUM_ROWS;
		} while (finish.Y % 2 == 0);
	} while (grid[finish.Y][finish.X] != ' ');

	return finish;
}

void Maze::changePosition(int key, COORD currentPosition, COORD &newPosition)
{
	if (key == VK_LEFT && grid[currentPosition.Y][currentPosition.X - 1] != MAZE_WALL)
	{
		newPosition.X--;
	}
	else if (key == VK_RIGHT && grid[currentPosition.Y][currentPosition.X + 1] != MAZE_WALL)
	{
		newPosition.X++;
	}
	else if (key == VK_UP && grid[currentPosition.Y - 1][currentPosition.X] != MAZE_WALL)
	{
		newPosition.Y--;
	}
	else if (key == VK_DOWN && grid[currentPosition.Y + 1][currentPosition.X] != MAZE_WALL)
	{
		newPosition.Y++;
	}
}

void Maze::moveAvatar(COORD &currentPosition, COORD newPosition)
{
	if (grid[currentPosition.Y][currentPosition.X] == 'S')
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPosition);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << 'S';
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPosition);
		cout << ' ';
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPosition);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << avatar;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	currentPosition = newPosition;
}

//handles the user's maze navigation
void Maze::navigateMaze()
{
	COORD currentPosition = start;
	COORD newPosition = currentPosition;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPosition);
	int key = getKey();

	while (currentPosition.X != finish.X || currentPosition.Y != finish.Y)
	{
		changePosition(key, currentPosition, newPosition);
		moveAvatar(currentPosition, newPosition);

		if (currentPosition.X == finish.X && currentPosition.Y == finish.Y)
		{
			COORD bottom = {0, NUM_ROWS};
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), bottom);
			cout << "Congratulations, you solved the maze!" << std::endl;
		}
		else
		{
			key = getKey();
		}
	}
}

int Maze::getKey()
{
	int result = 0;
	while (result == 0)
	{
		short MAX_SHORT = 0x7FFF; //111111111111111
		if (GetAsyncKeyState(VK_LEFT) & MAX_SHORT) {
			result = VK_LEFT;
		}
		else if (GetAsyncKeyState(VK_UP) & MAX_SHORT) {
			result = VK_UP;
		}
		else if (GetAsyncKeyState(VK_RIGHT) & MAX_SHORT) {
			result = VK_RIGHT;
		}
		else if (GetAsyncKeyState(VK_DOWN) & MAX_SHORT) {
			result = VK_DOWN;
		}
	}
	return result;
}
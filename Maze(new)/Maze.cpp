#include<iostream>
#include"Maze.h"
#include<stack>
#include<cstdlib>
#include<ctime>

using std::cout;
using std::cin;


Maze::Maze()
{

}

Maze::~Maze()
{

}
Maze Maze::generateFunctionalMaze()
{
	fillGrid(grid);
	digMaze(grid);
	printMaze();
}

void Maze::fillGrid(char grid[NUM_ROWS][NUM_COLS]) //written in class
{
	for (int row = 0; row < NUM_ROWS; row++)
	{
		for (int column = 0; column < NUM_COLS; column++)
		{
			grid[row][column] = MAZE_WALL;
		}
	}
}

void Maze::digMaze(char grid[NUM_ROWS][NUM_COLS])
{
	std::stack<COORD> locations;
	COORD currentLocation;
	currentLocation = markMazeStart();

	do
	{
		bool canGoUp = currentLocation.Y >= 3 && (grid[currentLocation.Y - 2][currentLocation.X] == MAZE_WALL);
		bool canGoRight = currentLocation.X <= NUM_COLS - 4 && (grid[currentLocation.Y][currentLocation.X + 2] == MAZE_WALL);
		bool canGoDown = currentLocation.Y >= NUM_ROWS - 4 && (grid[currentLocation.Y + 2][currentLocation.X] == MAZE_WALL);
		bool canGoLeft = currentLocation.X >= 3 && (grid[currentLocation.Y][currentLocation.X - 2] == MAZE_WALL);

		if (canGoUp == true || canGoRight == true || canGoDown == true || canGoLeft == true)
		{
			locations.push(currentLocation);
			bool directionFound = false;
			do
			{
				int direction = rand() % 4;
				if (direction == 0 && canGoUp == true)
				{
					directionFound = true;

				}
				else if (direction == 1 && canGoRight == true)
				{
					directionFound = true;
				}
				else if (direction == 2 && canGoDown == true)
				{
					directionFound = true;
				}
				else if (direction == 3 && canGoLeft == true)
				{
					directionFound = true;
				}
			} while (directionFound = false);

		}
	} while (locations.empty());
}


void Maze::printMaze()
{
	for (int row = 0; row < NUM_ROWS; row++)
	{
		for (int column = 0; column < NUM_COLS; column++)
		{
			cout << grid[row][column];
		}
		cout << std::endl;
	}
}


COORD Maze::markMazeStart()
{
	COORD start;
	srand(time(NULL));
	do
	{
		start.X = rand() % NUM_COLS;
	} while (start.X % 2 != 0);

	do
	{
		start.Y = rand() % NUM_COLS;
	} while (start.Y % 2 != 0);

	return start;
}

void Maze::markMazeFinish()
{
	//set finish variable
}

void Maze::moveAvatar(COORD newPosition)
{
	cout << "";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPosition);
	cout << avatar;
}

void Maze::playMaze() //needs modification
{
	
	int key = getKey();

	COORD currentPosition;
	currentPosition.Y = start.Y;
	currentPosition.X = start.X;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPosition);
	cout << avatar;

	while (currentPosition.X != finish.X && currentPosition.Y != finish.Y)
	{
		if (key == VK_LEFT && currentPosition.X > 0) 
		{
			currentPosition.X--;
			moveAvatar(currentPosition);
		}
		else if (key == VK_RIGHT && currentPosition.X < NUM_COLS) 
		{
			currentPosition.X++;
			moveAvatar(currentPosition);
		}
		else if (key == VK_UP && currentPosition.Y > 0) 
		{
			currentPosition.Y--;
			moveAvatar(currentPosition);
		}
		else if (key == VK_DOWN && currentPosition.Y < NUM_ROWS) 
		{
			currentPosition.Y++;
			moveAvatar(currentPosition);
		}

		COORD newCoord = {currentPosition.X, currentPosition.Y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newCoord);
		cout << MAZE_WALL;
		key = getKey();
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
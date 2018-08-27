#pragma once
#include<stack>
#include<Windows.h>

using std::stack;

const int NUM_ROWS = 7; //must be an odd number for digMaze algorithm to work properly
const int NUM_COLS = 13; //''
const char MAZE_WALL = (char)219; //white block character

class Maze
{
public:
	void playMaze();
	Maze();
	~Maze();

private:
	char grid[NUM_ROWS][NUM_COLS];
	COORD start;
	COORD finish;
	char avatar = 'P';

	void initializeGrid();
	void digMaze();
	void findValidDirections(bool &canGoUp, bool &canGoRight, bool &canGoDown, bool &canGoLeft, COORD currentLocation);
	void chooseAndMoveADirection(bool canGoUp, bool canGoRight, bool canGoDown, bool canGoLeft, COORD &currentLocation, 
		bool &directionFound);
	void backtrack(COORD &currentLocation, stack<COORD> &locations);
	void changePosition(int key, COORD currentPosition, COORD &newPosition);
	void moveAvatar(COORD &currentPosition, COORD newPosition);
	void printMaze();
	void addColor(int row, int column);
	COORD getMazeStart();
	COORD getMazeFinish();
	void navigateMaze();
	int getKey();
};

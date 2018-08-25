#pragma once
#include<stack>
#include<Windows.h>
#include<vld.h>

using std::stack;

const int NUM_ROWS = 11; //must be an odd number
const int NUM_COLS = 11; //must be an odd number
const char MAZE_WALL = (char)219;

//COORD or another location data type
struct Position
{
	int row;
	int column;
};

class Maze
{
public:
	void generateFunctionalMaze(); //calls all of the private functions to set up maze
	Maze();
	~Maze();

private:
	char grid[NUM_ROWS][NUM_COLS];
	COORD start;
	COORD finish;
	char avatar = 'P';


	void fillGrid();
	void digMaze();
	void findValidDirections(bool &canGoUp, bool &canGoRight, bool &canGoDown, bool &canGoLeft, COORD currentLocation);
	void chooseAndMoveADirection(bool canGoUp, bool canGoRight, bool canGoDown, bool canGoLeft,
		COORD &currentLocation, bool &directionFound);
	void backtrack(COORD &currentLocation, stack<COORD> &locations);
	void printMaze();
	COORD getMazeStart();
	COORD getMazeFinish();
	void playMaze();
	int getKey();
	void moveAvatar(COORD);
};

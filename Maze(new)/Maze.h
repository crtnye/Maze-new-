#pragma once
#include<stack>
#include<Windows.h>

using std::stack;

const int NUM_ROWS = 15; //must be an odd number
const int NUM_COLS = 15; //must be an odd number
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


	void fillGrid(char[NUM_ROWS][NUM_COLS]);
	void digMaze(char[NUM_ROWS][NUM_COLS]);
	void printMaze(char[NUM_ROWS][NUM_COLS]);
	COORD markMazeStart();
	COORD markMazeFinish();
	void playMaze();
	int getKey();
	void moveAvatar(COORD);
};

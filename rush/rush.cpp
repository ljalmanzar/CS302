/** @file Rush Hour
@author Luis Almanzar
@version 1.0
@brief This program will solve a traffic jam. The result will be the 
solution with the smallest number of moves.
@details This will solve the traffic jam for the game Rush Hour.
@date Wednesday, October 1st
*/
// include files
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

// global constants 
const int GRID_SIZE = 8;
/** Car Struct
These will be the cars of the program. 
Will store the size, direction, y coordinate and x coordiante
*/
struct car
	{
		int size;
		char direction;
		int ycoor;
		int xcoor;
	};
	
// function prototypes
void printGrid(int grid[][GRID_SIZE]);
/**
This function is going to edit the grid to have all the cars in their proper place

@param the playing grid which is an integer 2D array
@param the cars which are in an array of type Car
@return void function
@pre a grid and cars have been created
@post the playing grid will be loaded
*/
void fillTable(int grid [][GRID_SIZE], car theCars[], int carSize); 
/**
This function is going to move the car in the parameter forward
If the car is veritcal it will move it down and if it is horizontal it will move it right

@param the playing grid which is an integer 2D array
@param the car desired to move
@return if the car was able to move (true) or not (false)
@pre a grid and cars have been filled properly
@post the playing grid will be good with the car moved one spot forward
*/
bool moveForward (int grid [][GRID_SIZE], car& theCar);
/**
This function is going to move the car in the parameter back
If the car is veritcal it will move it up and if it is horizontal it will move it left

@param the playing grid which is an integer 2D array
@param the car desired to move
@return if the car was able to move (true) or not (false)
@pre a grid and cars have been filled properly
@post the playing grid will be good with the car moved one spot backwards
*/
bool moveBack (int grid [][GRID_SIZE], car& theCar);
/**
This function is going to check if our main car has reached the edge

@param the playing grid which is an integer 2D array
@param the car array
@return if the car is at the edge (true) and if it is not (false)
@pre a grid and cars have been filled properly
@post everything will be the same
*/
bool solved (int grid [][GRID_SIZE], car theCars[]);
/**
This function is going to solve the puzzle recursively

@param the playing grid which is an integer 2D array
@param the car array
@param the number of moves
@return if the game is solved true if not false
@pre a grid and cars have been filled properly
@post our car will be at the end of the board
*/
bool solveIt (int grid[][GRID_SIZE], car theCars[], int& moveCounter, int& minMoves, int carSize);
	
int main()
{
	int numOfMoves = 0;
	int minMoves = 10;
	int numOfCars;
	int board[GRID_SIZE][GRID_SIZE];
	
	// get cars
	cin >> numOfCars;
	
	// make array
	car carArr[numOfCars];
	
	// load array
	for (int ndx = 0; ndx < numOfCars; ndx++)
		{
			cin >> carArr[ndx].size;
			cin >> carArr[ndx].direction;
			cin >> carArr[ndx].ycoor;
			cin >> carArr[ndx].xcoor;
		}
	
	/*	
	for (int ndx = 0; ndx < numOfCars; ndx++)
		{
			cout << carArr[ndx].size;
			cout << carArr[ndx].direction;
			cout << carArr[ndx].ycoor;
			cout << carArr[ndx].xcoor;
			cout << endl;
		}
	*/
		
	fillTable(board, carArr, numOfCars);
	
	solveIt(board, carArr, numOfMoves, minMoves, numOfCars);
	
	cout << "Scenario 1 requires " << minMoves << " moves";

	return 0;
}

// function implementations
void printGrid(int grid[][GRID_SIZE])
{
	for (int ndx = 0; ndx < 8; ndx++)
		{
			for (int cndx = 0; cndx < 8; cndx++)
				{
					cout << grid[ndx][cndx];
				}
			cout << endl;
		}
}
void fillTable(int grid [][GRID_SIZE], car theCars[], int carSize)
	{
		/// empty grid
		for (int ndx = 0; ndx < 8; ndx++)
			{
				for (int cndx = 0; cndx < 8; cndx++)
					{
						grid[ndx][cndx] = 0;
					}
			}
			
		///fill border of game with flag
		for (int ndx = 0; ndx < 8; ndx++)
			{
				grid[0][ndx] = -1;
				grid[ndx][0] = -1;
				grid[GRID_SIZE-1][ndx] = -1;
				grid[ndx][GRID_SIZE-1] = -1;
			}
			
		/// insert cars
		for (int ndx = 0; ndx < carSize; ndx++)
			{
				/// add first part
				grid[theCars[ndx].ycoor+1][theCars[ndx].xcoor+1] = 1;
				
				/// add rest of each car
				if (theCars[ndx].direction == 'h' || theCars[ndx].direction == 'H')
					{
						grid[theCars[ndx].ycoor+1][theCars[ndx].xcoor+2] = 1;
						
						if (theCars[ndx].size == 3)
							{
								grid[theCars[ndx].ycoor+1][theCars[ndx].xcoor+3] = 1;
							}
					}
				if (theCars[ndx].direction == 'v' || theCars[ndx].direction == 'V')
					{
						grid[theCars[ndx].ycoor+2][theCars[ndx].xcoor+1] = 1;
						
						if (theCars[ndx].size == 3)
							{
								grid[theCars[ndx].ycoor+3][theCars[ndx].xcoor+1] = 1;
							}
					}
			}
		
	}
	
	bool moveForward (int grid [][GRID_SIZE], car& theCar)
		{
			/// check for direction
			if (theCar.direction == 'h' || theCar.direction == 'H')
				{
					/// check size
					if (theCar.size == 2)
						{
							/// check space in front
							if (grid[theCar.ycoor+1][theCar.xcoor+3] == 0)
								{
									//edit table
									grid[theCar.ycoor+1][theCar.xcoor+3] = 1;
									grid[theCar.ycoor+1][theCar.xcoor+1] = 0;
									theCar.xcoor++;
									return true;
								}
						}
					if (theCar.size == 3)
						{
							if (grid[theCar.ycoor+1][theCar.xcoor+4] == 0)
								{
									grid[theCar.ycoor+1][theCar.xcoor+4] = 1;
									grid[theCar.ycoor+1][theCar.xcoor+1] = 0;
									theCar.xcoor++;
									return true;
								}
						}
				}
				
			if (theCar.direction == 'v' || theCar.direction == 'V')
				{
					if (theCar.size == 2)
						{
							if (grid[theCar.ycoor+3][theCar.xcoor+1] == 0)
								{
									grid[theCar.ycoor+3][theCar.xcoor+1] = 1;
									grid[theCar.ycoor+1][theCar.xcoor+1] = 0;
									theCar.ycoor++;
									return true;
								}
						}
					if (theCar.size == 3)
						{
							if (grid[theCar.ycoor+4][theCar.xcoor+1] == 0)
								{
									grid[theCar.ycoor+4][theCar.xcoor+1] = 1;
									grid[theCar.ycoor+1][theCar.xcoor+1] = 0;
									theCar.ycoor++;
									return true;
								}
						}
				}
				
			return false;
		}
		
bool moveBack (int grid [][GRID_SIZE], car& theCar)
	{
			/// check for direction
			if (theCar.direction == 'h' || theCar.direction == 'H')
				{
					/// check for size
					if (theCar.size == 2)
						{
							// check if next is empty
							if (grid[theCar.ycoor+1][theCar.xcoor] == 0)
								{
									/// update
									grid[theCar.ycoor+1][theCar.xcoor] = 1;
									grid[theCar.ycoor+1][theCar.xcoor+2] = 0;
									theCar.xcoor--;
									return true;
								}
						}
					if (theCar.size == 3)
						{
							if (grid[theCar.ycoor+1][theCar.xcoor] == 0)
								{
									grid[theCar.ycoor+1][theCar.xcoor] = 1;
									grid[theCar.ycoor+1][theCar.xcoor+3] = 0;
									theCar.xcoor--;
									return true;
								}
						}
				}
				
			if (theCar.direction == 'v' || theCar.direction == 'V')
				{
					if (theCar.size == 2)
						{
							if (grid[theCar.ycoor][theCar.xcoor+1] == 0)
								{
									grid[theCar.ycoor][theCar.xcoor+1] = 1;
									grid[theCar.ycoor+2][theCar.xcoor+1] = 0;
									theCar.ycoor--;
									return true;
								}
						}
					if (theCar.size == 3)
						{
							if (grid[theCar.ycoor][theCar.xcoor+1] == 0)
								{
									grid[theCar.ycoor][theCar.xcoor+1] = 1;
									grid[theCar.ycoor+3][theCar.xcoor+1] = 0;
									theCar.ycoor--;
									return true;
								}
						}
				}
				
			return false;	
	}
	
bool solved (int grid [][GRID_SIZE], car theCars[])
	{
		if (grid[theCars[0].ycoor+1][theCars[0].xcoor+3] == -1)
			{
				return true;
			}
				
		return false;
	}
	
bool solveIt (int grid[][GRID_SIZE], car theCars[], int& moveCounter, int& minMoves, int carSize)
	{
		/// check if solved
		for (int ndx = 0; ndx<carSize; ndx++)
			{
				if (!solved(grid, theCars))
					{
						if (moveForward(grid, theCars[ndx]))
							{
								return solveIt(grid, theCars, ++moveCounter, minMoves, carSize);
								moveBack(grid, theCars[ndx]);
							}
					}
				else 
					{
						moveBack(grid, theCars[ndx]);
						moveCounter--;
					}
				
				if (solved(grid, theCars) && moveCounter < minMoves)
					{
						//cout << "Move updated &solved" << endl;
						minMoves = moveCounter;
						return true;
					}
				if (solved(grid, theCars))
					{
						//cout << "solved" << endl;
						return true;
					}
			}
	}

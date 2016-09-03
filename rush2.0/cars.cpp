/** @file Heap Implementation
@author Luis Almanzar
@version 1.0
@brief Implementation for a heap.
@details 
@date Wednesday, November 5th
*/
#include "cars.h"

/**
 * Default Constructor
 * @details No purposes. 
 * @param None.
 * @return Constructor.
 * 
 * @pre -
 * @post -
 */
car::car()
{

}

/**
 * Board Constructor
 * @details This will initialize an empty grid, then set the other variables to 0 and NULL
 * @param None.
 * @return Constructor.
 * 
 * @pre None
 * @post Empty grid created.
 */
board::board()
{
	/// initialized the 6x6 parking lot grid
	grid = new int*[6];
	for(int i = 0; i < 6; ++i)
		grid[i] = new int[6];

	/// fill empty grid
	for (int ndx = 0; ndx < 6; ndx++)
		{
			for (int cndx = 0; cndx < 6; cndx++)
				{
					grid[ndx][cndx] = 0;
				}
		}

	cars == NULL;
	numOfCars = 0;
	moves = 0;
}

/**
 * Destructor
 * @details Just frees all memory. 
 * @param None.
 * @return Destructor.
 * 
 * @pre There is a board.
 * @post All memory used by the board is freed.
 */
board::~board()
{
	///deallocate sub arrays
	for (int i = 0; i < 6; ++i)
		{
			delete [] grid[i];
		}

	/// deallocate main array
	delete [] grid;
	/// deallocate car array
	if (cars!=NULL)
		delete [] cars;
}

/**
 * This is the "Fill Grid," essentially the get input
 * @details Gets the number of cars from the input, then created the car area for the needed size. 
 	Then it inserts every car's information into the car array. After that, it loops the car 
 	array and inserts each car into the board in their appropriate spots.
 * @param None.
 * @return True if get cars from keyboard, and False if input is 0 cars.
 * 
 * @pre There will be an initialized board.
 * @post The board will now have spots filled and car array will not be vacant.
 */
bool board::fillGrid()
{
	/// get num of cars
	cin >> numOfCars;
	if (numOfCars == 0)
		return false;

	/// make memory for car array
	if (cars!= NULL)
	///	delete [] cars; 

	cars = new car[numOfCars];

	/// load car array
	for (int ndx = 0; ndx < numOfCars; ndx++)
		{
			cin >> cars[ndx].size;
			cin >> cars[ndx].direction;
			cin >> cars[ndx].ycoor;
			cin >> cars[ndx].xcoor;
		}

	/// insert cars into the grid
	for (int ndx = 0; ndx < numOfCars; ndx++)
			{
				/// add first part
				grid[cars[ndx].ycoor][cars[ndx].xcoor] = 1;
				
				/// add rest of each car
				if (cars[ndx].direction == 'h' || cars[ndx].direction == 'H')
					{
						grid[cars[ndx].ycoor][cars[ndx].xcoor+1] = 1;
						
						if (cars[ndx].size == 3)
							{
								grid[cars[ndx].ycoor][cars[ndx].xcoor+2] = 1;
							}
					}
				if (cars[ndx].direction == 'v' || cars[ndx].direction == 'V')
					{
						grid[cars[ndx].ycoor+1][cars[ndx].xcoor] = 1;
						
						if (cars[ndx].size == 3)
							{
								grid[cars[ndx].ycoor+2][cars[ndx].xcoor] = 1;
							}
					}
			}

	/// return true
	return true;
}

/**
 * Move Forward
 * @details This moves forward by checking the cars orientation, then its size, then if the spot ahead is open, 
 	if it is, it overwrites the spot with a one and makes the last spot of the car 0. All this is commented in the 
 	first part of the function since the other three are the same thing with different iterations. 
 * @param Index of which car to move.
 * @return True if the car was successfully moved, false otherwise.
 * 
 * @pre A filled grid with at least one car.
 * @post The selected car will be one ahead.
 */
bool board::moveForward(int carNum)
{
	/// check for direction
		if (cars[carNum].direction == 'h' || cars[carNum].direction == 'H')
			{
				/// check size
				if (cars[carNum].size == 2)
					{
						/// check space in front and out of bounds
						if (((cars[carNum].xcoor+2) < 6))
							{
								if (grid[cars[carNum].ycoor][cars[carNum].xcoor+2] == 0)
									{
										//edit table and cars info
										grid[cars[carNum].ycoor][cars[carNum].xcoor+2] = 1;
										grid[cars[carNum].ycoor][cars[carNum].xcoor] = 0;
										cars[carNum].xcoor++;
										return true;
									}
							}
					}
				if (cars[carNum].size == 3)
					{
						if (((cars[carNum].xcoor+3) < 6))
							{
								if (grid[cars[carNum].ycoor][cars[carNum].xcoor+3] == 0)
									{
										grid[cars[carNum].ycoor][cars[carNum].xcoor+3] = 1;
										grid[cars[carNum].ycoor][cars[carNum].xcoor] = 0;
										cars[carNum].xcoor++;
										return true;
									}
							}
					}
			}
			
		if (cars[carNum].direction == 'v' || cars[carNum].direction == 'V')
			{
				if (cars[carNum].size == 2)
					{
						if (((cars[carNum].ycoor+2) < 6))
							{
								if (grid[cars[carNum].ycoor+2][cars[carNum].xcoor] == 0)
									{
										grid[cars[carNum].ycoor+2][cars[carNum].xcoor] = 1;
										grid[cars[carNum].ycoor][cars[carNum].xcoor] = 0;
										cars[carNum].ycoor++;
										return true;
									}
							}
					}
				if (cars[carNum].size == 3)
					{
						if (((cars[carNum].ycoor+3) < 6))
							{	
								if (grid[cars[carNum].ycoor+3][cars[carNum].xcoor] == 0)
									{
										grid[cars[carNum].ycoor+3][cars[carNum].xcoor] = 1;
										grid[cars[carNum].ycoor][cars[carNum].xcoor] = 0;
										cars[carNum].ycoor++;
										return true;
										}
							}
					}
			}
				
	return false;
}

/**
 * Move Back
 * @details This moves forward by checking the cars orientation, then its size, then if the spot behind is open, 
 	if it is, it overwrites the spot with a one and makes the front spot of the car 0. All this is commented in the 
 	first part of the function since the other three are the same thing with different iterations. 
 * @param Index of which car to move.
 * @return True if the car was successfully moved, false otherwise.
 * 
 * @pre A filled grid with at least one car.
 * @post The selected car will be one behind.
 */
bool board::moveBack(int carNum)
{
	/// check for direction
	if (cars[carNum].direction == 'h' || cars[carNum].direction == 'H')
		{
			/// check for out of bounds
			if ((cars[carNum].xcoor-1) > -1)
				{
					/// check for size
					if (cars[carNum].size == 2)
						{
							// check if next is empty
							if (grid[cars[carNum].ycoor][cars[carNum].xcoor-1] == 0)
								{
									/// update
									grid[cars[carNum].ycoor][cars[carNum].xcoor-1] = 1;
									grid[cars[carNum].ycoor][cars[carNum].xcoor+1] = 0;
									cars[carNum].xcoor--;
									return true;
								}
						}
					if (cars[carNum].size == 3)
						{
							if (grid[cars[carNum].ycoor][cars[carNum].xcoor-1] == 0)
								{
									grid[cars[carNum].ycoor][cars[carNum].xcoor-1] = 1;
									grid[cars[carNum].ycoor][cars[carNum].xcoor+2] = 0;
									cars[carNum].xcoor--;
									return true;
								}
						}
				}
		}
				
	if (cars[carNum].direction == 'v' || cars[carNum].direction == 'V')
		{
			if ((cars[carNum].ycoor-1) >= 0)
				{
					if (cars[carNum].size == 2)
						{
							if (grid[cars[carNum].ycoor-1][cars[carNum].xcoor] == 0)
								{
									grid[cars[carNum].ycoor-1][cars[carNum].xcoor] = 1;
									grid[cars[carNum].ycoor+1][cars[carNum].xcoor] = 0;
									cars[carNum].ycoor--;
									return true;
								}
						}
					if (cars[carNum].size == 3)
						{
							if (grid[cars[carNum].ycoor-1][cars[carNum].xcoor] == 0)
								{
									grid[cars[carNum].ycoor-1][cars[carNum].xcoor] = 1;
									grid[cars[carNum].ycoor+2][cars[carNum].xcoor] = 0;
									cars[carNum].ycoor--;
									return true;
								}
						}
				}
		}
				
	return false;
}

/**
 * Solved 
 * @details Checks if the puzzle is solved by checking if the spot in front of car 0 is the end. 
 * @param None.
 * @return True if solved, false otherwise.
 */
bool board::solved() const
{
	if ((cars[0].xcoor + cars[0].size) == 6)
		return true;
	else
		return false;
}

/**
 * Print
 * @details Prints the playing grid.
 */
void board::print() const
{
	for (int ndx = 0; ndx < 6; ndx++)
		{
			for (int cndx = 0; cndx < 6; cndx++)
				{
					cout << grid[ndx][cndx] << '\t';
				}
			cout << endl;
		}
}

/**
 * Clear
 * @details Initialized the grid to all 0s and defaults all other variables
 */
void board::clear()
{
	/// initialized the 6x6 parking lot grid
	if (grid == NULL){
	grid = new int*[6];
	for(int i = 0; i < 6; ++i)
		grid[i] = new int[6];
	}

	/// fill empty grid
	for (int ndx = 0; ndx < 6; ndx++)
		{
			for (int cndx = 0; cndx < 6; cndx++)
				{
					grid[ndx][cndx] = 0;
				}
		}

	if (cars != NULL)
		//delete [] cars;

	cars == NULL;
	numOfCars = 0;
	moves = 0;
}

/**
 * @details Returns the number of cars on the current board.
 */
int board::getNumCars() const
{
	return numOfCars;
}

/**
 * Fix Moves
 * @details If moves are greater than 80, they become negative and since 
 	it is an 8 bit number adding 2^8 to the negavtive number fixed the moves. 
 	Would cause problems for very large amount of moves. 
 * @param None.
 * @return None
 * 
 * @pre -
 * @post Moves will be the correct nunmber if it wasn't before.
 */
void board::fixMoves()
{
	moves = moves + 256;
}	

/**
 * @details Returns the number of moves.
 */
int board::getMoves() const
{
	return moves;
}

/**
 * @details Adds 1 to the number of moves.
 */
void board::incrementMoves()
{
	moves++;
}	

/**
 * @details Subtracts 1 to the number of moves.
 */
void board::decrementMoves()
{
	if(moves!=0)
		moves--;
}

/**
 * Board to String 
 * @details Basically I take every bit of information I have and then subtract the character '0' to it
 	and put it into a string, then I return that string. More detailed in the function.
 * @param None.
 * @return The string that has the boards information.
 * 
 * @pre -
 * @post The board will have all it's information within a string.
 */
string board::toString() const
{
	///declare variable
	int carIndex = 0;
	string final;
	char * str = new char [120];

	///copy over board
	for ( int i = 0; i < 6; i++ )
		{
			for( int j = 0; j < 6; j++ )
				{
					str[i*6 + j] = grid[i][j] + '0';
				}	
		}

	/// transition into the data
	str[36] = '-';

	/// copy moves
	str[37] = moves + '0';
	str[38] = '-';

	/// copy num of cars
	str[39] = numOfCars + '0';

	/// copy the cars info
	for( int i = 40; i < 40+(numOfCars*4); i++ )
		{
			str[i] =cars[carIndex].size + '0';
			str[++i] = cars[carIndex].direction;
			str[++i] = cars[carIndex].ycoor + '0';
			str[++i] = cars[carIndex].xcoor + '0';
			carIndex++;

			//add the null at the end
			if( carIndex == numOfCars )
				{
					str[++i] = '\0';
				}
		}

	//assign to variable
	final.assign(str);

	//deallocate memory
	delete [] str;

	//return that memory
	return final;
}

/**
 * String to Board
 * @details The inverse of the previous function. Since I know the process I used to go to a string I just follow it
 	and subtract the character '0' and put everything into it's right variables and arrays.
 * @param The string to convert.
 * @return Void.
 * 
 * @pre -
 * @post The board will the information carried by the string that was input.
 */
void board::toBoard( const string& input )
	{
		int carIndex = 0;

		//copy board
		for( int i = 0; i < 6; i++ )
			{
				for( int j = 0; j < 6; j++ )
					{
						grid[i][j] = input[i*6 + j] - '0';
					}
			}

		/// get moves
		moves = input[37] - '0';

		/// get num of cars
		numOfCars = input[39] - '0';

		cars = NULL;

		/// get cars
		if (cars == NULL){
			cars = new car [numOfCars];

			for( int i = 40; i < 40+(numOfCars*4); i++ )
				{
					cars[carIndex].size = input[i] - '0';
					cars[carIndex].direction = input[++i];
					cars[carIndex].ycoor = input[++i] - '0';
					cars[carIndex].xcoor = input[++i] - '0';
					carIndex++;
				}
		}

		else{
			delete [] cars;
			cars= new car [numOfCars];

			for( int i = 40; i < 40+(numOfCars*4); i++ )
				{
					cars[carIndex].size = input[i] - '0';
					cars[carIndex].direction = input[++i];
					cars[carIndex].ycoor = input[++i] - '0';
					cars[carIndex].xcoor = input[++i] - '0';
					carIndex++;
				}
		}
	}
/** @file Heap Implementation
@author Luis Almanzar
@version 1.0
@brief Implementation for a heap.
@details 
@date Wednesday, November 5th
*/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue> 
#include <map>
#include "cars.h"

using namespace std;

int main()
{
	/// initialize the data structures and game board
	map<string, int> dejaVu;
	queue <string> myBoards;
	board* mainBoard;
	board* workBoard;

	/// initialized other used variables
	bool solved = false;
	string str;
	char numMoves;
	int scenario = 1;

	/// allocate memory for boards	
	mainBoard = new board;
	workBoard = new board;

	/// get inputs

while (mainBoard->fillGrid()){
	/// convert to string, to store
	str = mainBoard->toString();

	/// put in Q
	myBoards.push(str);

	/// put into map
	str[37] = '-';
	dejaVu.insert(pair<string, int>(str, 0));

	/// solve it loop
	while (!myBoards.empty() && !solved){
		/// dequeue
		str = myBoards.front();
		myBoards.pop();
		workBoard->toBoard(str);

		/// check if we are solved
		solved = workBoard->solved();

		for (int i = 0; i < workBoard->getNumCars(); ++i){
			/// move current car forward
			if (workBoard->moveForward(i))
			{
				/// incrememnt moves
				workBoard->incrementMoves();

				/// check for used dejaVu have to empty the num of moves for dejavu
				str = workBoard->toString();
				numMoves = str[37];
				str[37] = '-';

				/// if in the dejavu, insert number into string and move back
				if (dejaVu.count(str)){
					str[37]=numMoves;
					workBoard->moveBack(i);
					workBoard->decrementMoves();
				}
				/// if not in the dejavu, insert into string, then into queue and move back
				else{
					dejaVu.insert(pair<string, int>(str, 0));
					str[37] = numMoves;
					myBoards.push(str);
					workBoard->moveBack(i);
					workBoard->decrementMoves();
				}
			}

			/// move back (everything same as above but for moving backwards)
			if (workBoard->moveBack(i))
			{
				/// incrememnt moves
				workBoard->incrementMoves();

				/// check for used dejaVu
				str = workBoard->toString();
				numMoves = str[37];
				str[37] = '-';

				if (dejaVu.count(str)){
					str[37]=numMoves;
					workBoard->moveForward(i);
					workBoard->decrementMoves();
				}
				else{
					dejaVu.insert(pair<string, int>(str, 0));
					str[37] = numMoves;
					myBoards.push(str);
					workBoard->moveForward(i);
					workBoard->decrementMoves();
				}

			}
			
		}
	}

	/// correction for bigger numbers (greater than 80)
	if (workBoard->getMoves() < 0)
		workBoard->fixMoves();

	/// print out results
	cout << "Scenario " << scenario << " requires " << workBoard->getMoves() << " moves" <<endl;
	scenario++;

	/// clear everything for new scenario
	solved = false;
	mainBoard -> clear();
	workBoard -> clear();
	/// clear queue
	while (!myBoards.empty())
        myBoards.pop();

    /// clear dejavu
    dejaVu.clear();
}

	/// free memory
	delete mainBoard;
	delete workBoard;

return 0;
}
#ifndef CARS_H
#define CARS_H

#include <iostream>
#include <fstream>

using namespace std;

class board;

class car
{
	friend class board;

	public:
	car();
	int size;
	int xcoor, ycoor; /// the "back" of the car
	char direction;
};

class board
{
	friend class car;

	public:
	board();
	~board();

	bool fillGrid();
	bool moveForward(int); /// which car
	bool moveBack(int); /// which car
	bool solved() const; 
	void print() const;

	void clear(); 
	int getNumCars() const;
	void fixMoves();
	int getMoves() const;
	void incrementMoves();
	void decrementMoves();
	string toString() const;
	void toBoard(const string& input);


	private:
	int** grid;
	car* cars;
	int moves;
	int numOfCars;
};

#endif
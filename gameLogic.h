#pragma once

#include "drawBoard.h" // Used to be able to have drawboard as a parameter to functions.



class gameLogic
{
public:
	gameLogic(); //  constructor
	
	
	void makeMove(int column,int side, drawBoard board);
	bool isMoveLegal(int column, drawBoard board);
	int getLegalIndex(int column, drawBoard board);


private:
	const int CROSSES;
	const int NOUGHTS;
	const int INTERNAL_BOARD_MAX_ROWS;
	const int INTERNAL_BOARD_MAX_COLUMNS; 
	const int FREE;
	const std::vector<int> INTERNAL_BOARD_INDEX; // the internal index of the avalible game squares.


};


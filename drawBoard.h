#pragma once
#include <vector>
#include <string>
#include <iostream>


class drawBoard
{
public:
	drawBoard();									// Constructor
	void print_board(); 
	void initialise_board(); 
	void update_board(int newMoveIndex, int side);  // update board after a move is made
	
	std::string m_board;
	const std::string PIECES = "X0";				// contains the two different pices that the players use to indicate their move.

private:
	const int LINE_LENGTH = 29;
};


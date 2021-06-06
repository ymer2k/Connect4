#pragma once
#include <vector>
#include <string>
#include <iostream>


class drawBoard
{
public:
	drawBoard();		// Constructor
	

	

	void print_board();
	void initialise_board(); 
	void update_board(int newMoveIndex, int side); // update board after a move is made


	std::string m_board;
	const int LINE_LENGTH = 29;




private:
	const std::string pieces = "X0"; //contains the two different pices that the players use to indicate their move.





};

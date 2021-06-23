// Handles everything that updates or prints the board.

#include "drawBoard.h"


drawBoard::drawBoard() // Default constructor (runs everytime a new object is made)
{
	initialise_board();
}

void drawBoard::update_board(int newMoveIndex, int side)
{ // takes in the exact index and which side made the move and updates the board with the new move. The exact index is handled in the gameLogic class
	m_board[newMoveIndex] = PIECES[side];
}


void drawBoard::print_board()
{	// Loop through the string and put new lines at the right places.
	for (struct { int count; int row_count; } v = { 0, 1 }; v.count < (int)m_board.size(); v.count++)
	{
		if (m_board[v.count] == 'F') // I use the letter F to indicate empty positions so when printing, just print an empty space instead of the F.
		{
			std::cout << " ";

		}else
			std::cout << m_board[v.count];

		if ((v.count % ((LINE_LENGTH * v.row_count) - 1) == 0) && v.count != 0) // Put a new line char at the right place.
		{
			std::cout << std::endl;
			v.row_count++;
		}
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void drawBoard::initialise_board()
{
	m_board = 
		"+ - + - + - + - + - + - + - +"
		"| F | F | F | F | F | F | F |"
		"+ - + - + - + - + - + - + - +"
		"| F | F | F | F | F | F | F |"
		"+ - + - + - + - + - + - + - +"
		"| F | F | F | F | F | F | F |"
		"+ - + - + - + - + - + - + - +"
		"| F | F | F | F | F | F | F |"
		"+ - + - + - + - + - + - + - +"
		"| F | F | F | F | F | F | F |"
		"+ - + - + - + - + - + - + - +"
		"| F | F | F | F | F | F | F |"
		"+ - + - + - + - + - + - + - +"
		"  1   2   3   4   5   6   7  ";
}


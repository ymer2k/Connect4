// Handles everything that updates or prints the board.

#include "drawBoard.h"


drawBoard::drawBoard() // Default constructor (runs everytime a new object is made)
{
	initialise_board();
	//print_board();


}

void drawBoard::update_board(int newMoveIndex, int side)
{ // takes in the exact index and which side made the move and updates the board with the new move. The exact index is handled in the gameLogic class
	m_board[newMoveIndex] = pieces[side];
}


void drawBoard::print_board()
{	// Loop through the string and put new lines at the right places.
	for (struct { int count; int row_count; } v = { 0, 1 }; v.count < (int)m_board.size(); v.count++)
	{
		if (m_board[v.count] == '2') // I use 2s to indicate empty positions so when printing, just print an empty space instead of the 2.
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
		"| 2 | 2 | 2 | 2 | 2 | 2 | 2 |"
		"+ - + - + - + - + - + - + - +"
		"| 2 | 2 | 2 | 2 | 2 | 2 | 2 |"
		"+ - + - + - + - + - + - + - +"
		"| 2 | 2 | 2 | 2 | 2 | 2 | 2 |"
		"+ - + - + - + - + - + - + - +"
		"| 2 | 2 | 2 | 2 | 2 | 2 | 2 |"
		"+ - + - + - + - + - + - + - +"
		"| 2 | 2 | 2 | 2 | 2 | 2 | 2 |"
		"+ - + - + - + - + - + - + - +"
		"| 2 | 2 | 2 | 2 | 2 | 2 | 2 |"
		"+ - + - + - + - + - + - + - +";


	/*
	* 	m_board = 
		"+ - + - + - + - + - + - + - +"
		"|   |   |   |   |   |   |   |"
		"+ - + - + - + - + - + - + - +"
		"|   |   |   |   |   |   |   |"
		"+ - + - + - + - + - + - + - +"
		"|   |   |   |   |   |   |   |"
		"+ - + - + - + - + - + - + - +"
		"|   |   |   |   |   |   |   |"
		"+ - + - + - + - + - + - + - +"
		"|   |   |   |   |   |   |   |"
		"+ - + - + - + - + - + - + - +"
		"|   |   |   |   |   |   |   |"
		"+ - + - + - + - + - + - + - +";
	*/

	
		


	//int index = 0;
	////TODO add the vertical lines and the EMPTY spaces. Make the chars '+' '-' '|' into constants.
	//for (index = 0; index < BOARD_ARRAY_SIZE; index++)
	//{
	//	if (index % 2 == 0) // if index is an even number
	//	{
	//		m_border.push_back('+');
	//	}
	//	else // else index is odd
	//	{
	//		m_border.push_back('-');
	//	}
	//}
}


#include "gameLogic.h"



gameLogic::gameLogic() : // initializer-list  // Default constructor
	CROSSES{ 0 },
	NOUGHTS{ 1 },
	FREE { 2 },
	INTERNAL_BOARD_MAX_ROWS{ 6 },
	INTERNAL_BOARD_MAX_COLUMNS{ 7 },
	INTERNAL_BOARD_INDEX // represents the internal board of the main board with the possible indexes.
	{
		31,35,39,43, 47, 51, 55,
		89, 93, 97, 101,105,109,113,
		147,151,155,159,163,167,171,
		205,209,213,217,221,225,229,
		263,267,271,275,279,283,287,
		321,325,329,333,337,341,345
	}
{


}

void gameLogic::makeMove(int column,int side, drawBoard Board)
{	//input from the player is the column number (1-7) and this function figures out at which index to place the move (by looking at the board to find the correct index)
	if (int index = getLegalIndex(column, Board))
	{
		Board.update_board(index, side);
	}

}

int gameLogic::getLegalIndex(int column, drawBoard Board)
{ // Returns the next legal index using the column input by the palyer.
	int internalIndex = 0;
	for (int i = INTERNAL_BOARD_MAX_ROWS - 1; i >= 0; i--) //  INTERNAL_BOARD_MAX_ROWS - 1) because at the first position (when i= 0) MAX_COL* MAX_ROW should be zero)
	{
		internalIndex = INTERNAL_BOARD_INDEX[INTERNAL_BOARD_MAX_COLUMNS * i + column - 1]; // Get the internal index of the move.  (-1 due to zero index ie if column is 1 we should look at position 0)
		if ( (Board.m_board[internalIndex] - '0' ) == FREE) // check if the position is free.  (recasting the char from the board to an int using - '0') 
		{
			std::cout << Board.m_board[internalIndex] << std::endl; // Print 2 if free
			std::cout << internalIndex << std::endl; // print the internalindex
			return internalIndex;
		}
	}

	return 0; // returns 0 if no legal index is found.
}

bool gameLogic::isMoveLegal(int column, drawBoard board)
{ // Determines if the move is legal or not. checks from the bottom and up.
	for (int i = INTERNAL_BOARD_MAX_ROWS-1; i >= 0; i--) //  INTERNAL_BOARD_MAX_ROWS - 1) because at the first position (when i= 0) MAX_COL* MAX_ROW should be zero)
	{
		if( ( board.m_board[ (INTERNAL_BOARD_MAX_COLUMNS*i+column)-1] - '0' ) == FREE) // check if the position is free (-1 due to zero index) (recasting the char from the board to an int using - '0') 
		{
			return true;
		}
	}

	return false;
}

#include "gameLogic.h"



gameLogic::gameLogic() : // initializer-list  // Default constructor
	CROSSES{ 0 },
	NOUGHTS{ 1 },
	FREE { 'F' },
	INTERNAL_BOARD_MAX_ROWS{ 6 },
	INTERNAL_BOARD_MAX_COLUMNS{ 7 },
	INTERNAL_BOARD_MAX_ROWS_WITH_BOARDER{ 8 },
	INTERNAL_BOARD_MAX_COLUMNS_WITH_BOARDER{ 9 },
	INTERNAL_BOARD_INDEX // represents the internal board of the main board with the possible indexes.
	{
		31, 35, 39,  43, 47, 51, 55,
		89, 93, 97, 101,105,109,113,
		147,151,155,159,163,167,171,
		205,209,213,217,221,225,229,
		263,267,271,275,279,283,287,
		321,325,329,333,337,341,345
	},
	INTERNAL_BOARD_INDEX_WITH_BOARDER
{
	0, 0, 0, 0, 0,  0,  0,  0,  0,0,
	0,31, 35, 39,  43, 47, 51, 55,0,
	0,89, 93, 97, 101,105,109,113,0,
	0,147,151,155,159,163,167,171,0,
	0,205,209,213,217,221,225,229,0,
	0,263,267,271,275,279,283,287,0,
	0,321,325,329,333,337,341,345,0,
	0, 0, 0, 0, 0,  0,  0,  0,  0,0
},
	MAX_MOVE_LIMIT{ 7 },
	MIN_MOVE_LIMIT{ 1 },
	SQUARES_IN_A_ROW_TO_WIN{ 4 },
	m_side(CROSSES) //Crosses always start.
{


}

void gameLogic::makeMove(int move,int side, drawBoard & Board)
{	//input from the player is the column number (1-7) and this function figures out at which index to place the move (by looking at the board to find the correct index)
	if (int index = getMoveIndex(move, Board))
	{
		Board.update_board(index, side); //updates the game Board.
	}

}

int gameLogic::getMoveIndex(int move, drawBoard Board)
{ // Returns the next legal index using the column input by the player. E.g: if the bottom square is occupied check the square above it and so on.
	int internalMoveIndex = 0;
	for (int i = INTERNAL_BOARD_MAX_ROWS - 1; i >= 0; i--) //  INTERNAL_BOARD_MAX_ROWS - 1) because at the first position (when i= 0) MAX_COL* MAX_ROW should be zero)
	{
		internalMoveIndex = INTERNAL_BOARD_INDEX[INTERNAL_BOARD_MAX_COLUMNS * i + move - 1]; // Get the internal index of the move.  (-1 due to zero index ie if column is 1 we should look at position 0)
		if ( (Board.m_board[internalMoveIndex]) == FREE) // check if the position is free.  (recasting the char from the board to an int using - '0') 
		{
			//std::cout << Board.m_board[internalIndex] << std::endl; // Print 2 if free
			//std::cout << internalIndex << std::endl; // print the internalindex
			return internalMoveIndex;
		}
	}

	return 0; // returns 0 if no legal index is found.
}

// Loop until we get a valid move.
int gameLogic::getValidMove(drawBoard Board)
{
	moveStatus status = moveStatus::INVALID_STATUS;
	std::string moveString;
	int move = 0;
	while (status != moveStatus::OK)
	{
		std::cout << Board.PIECES[m_side] << " turn to make a move!" << std::endl;
		std::cout << "Enter a move between column 1 and 7: ";
		//get the move from a player. (cant handle negative numbers)
		std::cin >> moveString;
		move = stoi(moveString);

		status = checkMoveValidity(move, Board);
		
		switch (status)
		{
			case moveStatus::NOT_IN_RANGE:
				std::cout << "Move not between 1 and 7." << std::endl;
				break;
			case moveStatus::COLUMN_FULL:
				std::cout << "Column is full" << std::endl;
				break;
			default:
				return move;
		}

	}

	return 0;
}

moveStatus gameLogic::checkMoveValidity(int move, drawBoard Board) const
{
	if (!isInrange(move))
	{
		return moveStatus::NOT_IN_RANGE;
	}

	else if (!isColumnFree(move, Board))
	{
		return moveStatus::COLUMN_FULL;
	}
	else
	{
		return moveStatus::OK;
	}
}

bool gameLogic::isGameWon()
{
	return false;
}
//Checks if a player has 4 in a row.
gameOverStatus gameLogic::check4InARow(int moveIndex, drawBoard Board)
{
	char otherSidePiece = '\0';
	if (m_side == 0)
	{
		otherSidePiece = Board.PIECES[1];
	}
	else
	{
		otherSidePiece = Board.PIECES[0];
	}
	//int lineLengthIncludingBorder = Board.LINE_LENGTH; //+ 1;
	int adjacentIndex[8] = { -1, 0, 1, -1, 1, -1, 0, 1 }; // Used for check the adjacent squares
	int directionSign[8] = { -1, -1, -1, 0, 0, 1, 1, 1 }; //Check in the "minus" direction for the first four and "positive" direction for the remaining four. 0 for left and right.
	char currentSquare = '\0';
	int squaresInARow = 1; // starts on 1 because the first square that it starts looking from.
	int index = getArrayIndex(moveIndex);
	for (int i = 0; i < 8; i++) //cycles through viewing directions
	{
		for (int j = 1; (currentSquare = Board.m_board[INTERNAL_BOARD_INDEX[index + j * (directionSign[i] * INTERNAL_BOARD_MAX_COLUMNS + adjacentIndex[i])]]) == Board.PIECES[m_side]; j++)  //'F' && currentSquare != otherSidePiece && (j < 4) ; j++) //continues until we reach '2' or otherSides square or until we checked 3 squares in a row from the starting square i.e. (j < 4)
		{
			if (currentSquare == Board.PIECES[m_side]) // Checks if the current seat we are on is on the same side as the players (it has to be to pass the for loop condition, so this if statment is redundant)
				squaresInARow++;
			if (squaresInARow == SQUARES_IN_A_ROW_TO_WIN) //checks if we reached enough squares to have a winner
				if (m_side == (int)gameOverStatus::CROSSES_WIN) // Checks which side won.
				{
					return gameOverStatus::CROSSES_WIN;

				}
				else
				{
					return gameOverStatus::NOUGHTS_WIN;
				}
		}
	}

	return gameOverStatus::NO_WINNER; // Didnt find enough squares to have a winner.
}

void gameLogic::changeSide()
{
	if (m_side == CROSSES)
	{
		m_side = NOUGHTS;
	}
	else
	{
		m_side = CROSSES;
	}
}

// Checks if the move is in range.
bool gameLogic::isInrange(int move) const
{
	if (move <= MAX_MOVE_LIMIT && move >= MIN_MOVE_LIMIT)
	{
		return true;
	}
	else
	{
		return false;
	}

}
// Checks if the chosen column is free or not. (checks the top row)
bool gameLogic::isColumnFree(int move, drawBoard board) const
{
	if (board.m_board[INTERNAL_BOARD_INDEX[move - 1]] == FREE)		// -1 because zero index.
	{
		return true;
	}
	else
	{
		return false;
	}
}

int gameLogic::getArrayIndex(int element)
{
	auto it = find(INTERNAL_BOARD_INDEX.begin(), INTERNAL_BOARD_INDEX.end(), element);
	int index = it - INTERNAL_BOARD_INDEX.begin();

	return index;

}



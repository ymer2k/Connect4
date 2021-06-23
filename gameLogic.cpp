// Handles everything related to game logic AND printing game intro & summary.

#include "gameLogic.h"

gameLogic::gameLogic() : // initializer-list  // Default constructor
	CROSSES{ 0 },
	NOUGHTS{ 1 },
	FREE { 'F' },
	INTERNAL_BOARD_MAX_ROWS{ 6 },
	INTERNAL_BOARD_MAX_COLUMNS{ 7 },
	INTERNAL_BOARD_MAX_ROWS_WITH_BORDER{ 8 },
	INTERNAL_BOARD_MAX_COLUMNS_WITH_BORDER{ 9 },
	INTERNAL_BOARD_INDEX					// represents the internal board of the main board with the possible indexes.
	{
		31, 35, 39,  43, 47, 51, 55,
		89, 93, 97, 101,105,109,113,
		147,151,155,159,163,167,171,
		205,209,213,217,221,225,229,
		263,267,271,275,279,283,287,
		321,325,329,333,337,341,345
	},
	INTERNAL_BOARD_INDEX_WITH_BORDER
{
	0, 0,  0,  0,   0,  0,  0,  0,0,
	0,31, 35,  39, 43, 47, 51, 55,0,
	0,89, 93,  97,101,105,109,113,0,
	0,147,151,155,159,163,167,171,0,
	0,205,209,213,217,221,225,229,0,
	0,263,267,271,275,279,283,287,0,
	0,321,325,329,333,337,341,345,0,
	0,  0,  0,  0,  0,  0,  0,  0,0
},
	SQUARES_IN_A_ROW_TO_WIN{ 4 },
	m_side{0},								//Crosses always start.
	m_isGameOver{false},
	m_gameOverStatus{gameOverStatus::NO_WINNER},
	MIN_ASCII_RANGE{ '1' },
	MAX_ASCII_RANGE{ '7' }
{
	// constructor body
}

void gameLogic::makeMove(int move,int side, drawBoard & Board)
{	//input from the player is the column number (1-7) and this function figures out at which index to place the move (by looking at the board to find the correct index)
	if (int index = getMoveIndex(move, Board))
	{
		Board.update_board(index, side); //updates the game Board.
	}
}

int gameLogic::getMoveIndexWithBoarder(std::string move, drawBoard Board)
{ // Returns the next legal index using the column input by the player. E.g: if the bottom square is occupied check the square above it and so on.
	int moveInt = stoi(move);
	int internalMoveIndex = 0;
	// INTERNAL_BOARD_MAX_ROWS_WITH_BOARDER -2 becasue 8*9 (With border size) is 72 which would place us in the lower right corner but we want to start
	// two rows above the last (the border + the last game board row) because we want to add the player move (1-7) ontop of that which will take us to the last row. BUT when calculating
	// internalMoveIndex below we need to have "move + 1" because we want to skip the left side border. i > = 1 becauase the top position should be below the border. (columns*1+move+1)
	for (int i = INTERNAL_BOARD_MAX_ROWS_WITH_BORDER - 2; i >= 1; i--)  
	{
		internalMoveIndex = INTERNAL_BOARD_INDEX_WITH_BORDER[INTERNAL_BOARD_MAX_COLUMNS_WITH_BORDER * i + moveInt]; // Get the internal index of the move.  
		if ( (Board.m_board[internalMoveIndex]) == FREE) // check if the position is free. 
		{
			return internalMoveIndex;
		}
	}
	return 0; // returns 0 if no legal index is found.
}

int gameLogic::getMoveIndex(int move, drawBoard Board)
{ // Returns the next legal index using the column input by the player. E.g: if the bottom square is occupied check the square above it and so on.
	int internalMoveIndex = 0;
	for (int i = INTERNAL_BOARD_MAX_ROWS - 1; i >= 0; i--) //  INTERNAL_BOARD_MAX_ROWS - 1) because at the first position (when i= 0) MAX_COL* MAX_ROW should be zero)
	{
		internalMoveIndex = INTERNAL_BOARD_INDEX[INTERNAL_BOARD_MAX_COLUMNS * i + move - 1]; // Get the internal index of the move.  (-1 due to zero index ie if column is 1 we should look at position 0)
		if ((Board.m_board[internalMoveIndex]) == FREE) // check if the position is free.
		{
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
		std::cin.ignore();							//removes the new line chars from cin that would otherwise be immeietly inputed into any 	std::getline() I would use later.
		status = checkMoveValidity(moveString, Board);
		
		switch (status)
		{
			case moveStatus::NOT_IN_RANGE:
				std::cout << "Move not between 1 and 7." << std::endl;
				std::cout << std::endl;
				break;
			case moveStatus::COLUMN_FULL:
				std::cout << "Column is full." << std::endl;
				std::cout << std::endl;
				break;
			case moveStatus::NOT_ONE_CHAR:
				std::cout << "Input only one character." << std::endl;
				std::cout << std::endl;
				break;
			default:
				move = stoi(moveString);
				return move;
		}
	}
	return 0;
}

moveStatus gameLogic::checkMoveValidity(std::string move, drawBoard Board) const
{
	if (!isOneChar(move)) //this if statment have to be first.
	{
		return moveStatus::NOT_ONE_CHAR;
	}
	else if (!isInrange(move))
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
	return m_isGameOver;
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
	int adjacentIndex[8] = { -1, 1, 0, 0, 1, -1, -1, 1 };	// Used for check the adjacent squares. Checks diag top left to lower right, up down, topright to lower left and left to right.
	int directionSign[8] = { -1, 1, -1, 1, -1, 1, 0, 0 };	//Check in the "minus" direction for the  four and "positive" direction for the remaining four. 0 for left and right
	char currentSquare = '\0';
	int squaresInARow = 1;									// starts on 1 because the first square that it starts looking from.
	int index = getArrayIndex(moveIndex, INTERNAL_BOARD_INDEX_WITH_BORDER);
	for (int i = 0; i < 8; i++)								//cycles through viewing directions
	{
		if (i % 2 == 0)										//if "i" is even reset squareInARow
		{
			squaresInARow = 1;								// reset when we start looking in a new direction
		}
		for (int j = 1; (currentSquare = Board.m_board[INTERNAL_BOARD_INDEX_WITH_BORDER[index + j * (directionSign[i] * INTERNAL_BOARD_MAX_COLUMNS_WITH_BORDER + adjacentIndex[i])]]) == Board.PIECES[m_side]; j++)  //'F' && currentSquare != otherSidePiece && (j < 4) ; j++) //continues until we reach '2' or otherSides square or until we checked 3 squares in a row from the starting square i.e. (j < 4)
		{
			if (currentSquare == Board.PIECES[m_side])		// Checks if the current seat we are on is on the same side as the players (it has to be to pass the for loop condition, so this if statment is redundant)
			{
				squaresInARow++;
			}
			if (squaresInARow == SQUARES_IN_A_ROW_TO_WIN)	//checks if we reached enough squares to have a winner
			{
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

void gameLogic::checkGameOverStatus(int moveIndex, drawBoard Board)
{
	gameOverStatus status = check4InARow(moveIndex, Board);
	if (isDraw(Board))
	{
		m_gameOverStatus = gameOverStatus::DRAW;
		m_isGameOver = true;
	}
	else if(status == gameOverStatus::CROSSES_WIN || status == gameOverStatus::NOUGHTS_WIN)
	{
		m_gameOverStatus = status;
		m_isGameOver = true;
	}
	else //Then the game is not over and it returns NO_WINNER
	{
		m_gameOverStatus = gameOverStatus::NO_WINNER;
		m_isGameOver = false;
	}
}

bool gameLogic::AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	std::string Response = "";
	std::getline(std::cin, Response);
	if (((Response[0] == 'y') || (Response[0] == 'Y')))
	{
		return true;
	}
	else
	{
		return false;
	}
	std::cout << std::endl;
}

bool gameLogic::isDraw(drawBoard Board)
{
	for (int i = 1; i <= INTERNAL_BOARD_MAX_COLUMNS; i++)
	{
		std::string number =  std::to_string(i);
		if (isColumnFree(number, Board)) //checks if any of the columns are free.
		{
			return false;
		}
	}
	return true; //if we go through all columns and non of them were free then we know it's a draw.
}

void gameLogic::printGameSummary()
{
	switch (m_gameOverStatus)
	{
		case gameOverStatus::CROSSES_WIN:
			std::cout << "< = > Congratulations! CROSSES WIN! < = >" << std::endl;
			break;
		case  gameOverStatus::NOUGHTS_WIN:
			std::cout << "< = > Congratulations! NOUGHTS WIN! < = >" << std::endl;
 			break;
		default:
			std::cout << "Game Over." << std::endl;
			std::cout << "It's a draw." << std::endl;
	}
}

void gameLogic::printGameIntro()
{
	std::cout << "Welcome to Connect 4!" << std::endl;
	std::cout << "Made by Jonas." << std::endl;
	std::cout << std::endl;
}

void gameLogic::reset(drawBoard & Board)
{
	m_isGameOver = false;
	m_gameOverStatus = gameOverStatus::NO_WINNER;
	m_isGameOver = false;
	Board.initialise_board();
}

// Checks if the move is in range.
bool gameLogic::isInrange(std::string move) const
{
	if (move <= MAX_ASCII_RANGE && move >= MIN_ASCII_RANGE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool gameLogic::isOneChar(std::string move) const
{
	if (move.length() > 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Checks if the chosen column is free or not. (checks the top row)
bool gameLogic::isColumnFree(std::string move, drawBoard board) const
{
	int moveInt = stoi(move);
	if (board.m_board[INTERNAL_BOARD_INDEX[moveInt - 1]] == FREE)		// -1 because zero index.
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Returns the corresponding index in the array for the input element.
int gameLogic::getArrayIndex(int element, std::vector<int> array)
{
	auto it = find(array.begin(), array.end(), element);
	int index = it - array.begin();
	return index;
}



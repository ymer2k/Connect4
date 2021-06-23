#pragma once

#include "drawBoard.h" // Used to be able to have drawboard as a parameter to functions.


enum class moveStatus
{
	INVALID_STATUS,
	OK,
	NOT_IN_RANGE,
	COLUMN_FULL,
	NOT_ONE_CHAR
};

enum class gameOverStatus
{
	CROSSES_WIN,
	NOUGHTS_WIN,
	DRAW,
	NO_WINNER
};

class gameLogic
{
public:
	gameLogic(); //  constructor
	
	int getMoveIndex(int column, drawBoard board);							// Returns the index where to put the move on the full board.
	int getValidMove(drawBoard board);										// loops until we get a valid move and returns error messages if the player makes an illegal move.
	bool isGameWon();
	void changeSide();														// Changes m_side between CROSSES and NOUGHTS
	void checkGameOverStatus(int move, drawBoard Board);					// Checks different test functions if the game is over like isDraw() Or check4InARow() and returns corresponding GameOverStatus
	bool AskToPlayAgain();
	void printGameSummary();
	void printGameIntro();
	void reset(drawBoard & Board);											// resets variables for  new game.

	// Member varaibles
	int m_side;

private:
	void makeMove(int column, int side, drawBoard& board);					// Call by reference because we want to change board.
	int getMoveIndexWithBoarder(std::string column, drawBoard board);		// Returns the index where to put the move on the full board.
	moveStatus checkMoveValidity(std::string move, drawBoard board) const;	// takes player move as input. calls different test functions like isInrange or isColumnFree and returns corresponding "moveStatus" if something is wrong.
	gameOverStatus check4InARow(int move, drawBoard Board);
	bool isDraw(drawBoard Board);
	bool isInrange(std::string) const;										// checks if the move is between 1-7. 	//	If legal move returns OK. const is an assurance that the functions dosnt change the input move. if it does it will cause an error.
	bool isOneChar(std::string) const;										// checks if input is one char long.
	bool isColumnFree(std::string move, drawBoard board) const;				// Checks if the chosen column is free
	int getArrayIndex(int element, std::vector<int> array);					// Returns the index of the given element

	// Member variables
	bool m_isGameOver;
	gameOverStatus m_gameOverStatus;

	// Constants
	const int CROSSES;
	const int NOUGHTS;
	const int INTERNAL_BOARD_MAX_ROWS;
	const int INTERNAL_BOARD_MAX_COLUMNS; 
	const int INTERNAL_BOARD_MAX_ROWS_WITH_BORDER;
	const int INTERNAL_BOARD_MAX_COLUMNS_WITH_BORDER;
	const char FREE;
	const int SQUARES_IN_A_ROW_TO_WIN;
	const std::vector<int> INTERNAL_BOARD_INDEX;							// the internal index of the avalible game squares.
	const std::vector<int> INTERNAL_BOARD_INDEX_WITH_BORDER; 
	std::string MIN_ASCII_RANGE;											// min ASCII is 49 representing a '1' char
	std::string MAX_ASCII_RANGE;											// max ASCII is 55 representing a '7' char	
};


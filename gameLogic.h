#pragma once

#include "drawBoard.h" // Used to be able to have drawboard as a parameter to functions.



enum class moveStatus
{
	INVALID_STATUS,
	OK,
	NOT_IN_RANGE,
	COLUMN_FULL
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
	
	void makeMove(int column,int side, drawBoard &  board); // Call by reference because we want to change board.
	int getMoveIndex(int column, drawBoard board);			//Returns the index where to put the move on the full board.
	int getValidMove(drawBoard board); //loops until we get a valid move and returns error messages if the player makes an illegal move.
	moveStatus checkMoveValidity(int move, drawBoard board) const; // takes player move as input. calls different test functions like isInrange or isColumnFree and returns corresponding "moveStatus" if something is wrong.
	//	If legal move returns OK. const is an assurance that the functions dosnt change the input move. if it does it will cause an error.
	bool isGameWon();
	gameOverStatus check4InARow(int move, drawBoard Board);
	int m_side;
	void changeSide(); //Changes m_side between CROSSES and NOUGHTS


private:
	const int CROSSES;
	const int NOUGHTS;
	const int INTERNAL_BOARD_MAX_ROWS;
	const int INTERNAL_BOARD_MAX_COLUMNS; 
	const int INTERNAL_BOARD_MAX_ROWS_WITH_BOARDER;
	const int INTERNAL_BOARD_MAX_COLUMNS_WITH_BOARDER;
	const char FREE;
	const int MAX_MOVE_LIMIT;
	const int MIN_MOVE_LIMIT;
	const int SQUARES_IN_A_ROW_TO_WIN;
	const std::vector<int> INTERNAL_BOARD_INDEX; // the internal index of the avalible game squares.
	const std::vector<int> INTERNAL_BOARD_INDEX_WITH_BOARDER; 
	bool isInrange(int) const; // checks if the move is between 1-7.
	bool isColumnFree(int move, drawBoard board) const; // Checks if the chosen column is free
	int getArrayIndex(int element); //Returns the index of the given element


};


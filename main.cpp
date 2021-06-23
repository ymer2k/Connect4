// Connect4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Connect 4 game. Author: Jonas Date created:2021-05-26

#include <iostream>
#include "drawBoard.h"
#include "gameLogic.h"

// Prototypes
void runGame();

drawBoard Board; //board initilization class
gameLogic Game;  //Game initilization class

int main()
{
    /* Board Layout design:

    * + - + - + - + - + - + - + - +
    * |   |   |   |   |   |   |   |
    * + - + - + - + - + - + - + - +
    * |   |   |   |   |   |   |   |
    * + - + - + - + - + - + - + - +
    * |   |   |   |   |   |   |   |
    * + - + - + - + - + - + - + - +
    * |   |   |   |   |   |   |   |
    * + - + - + - + - + - + - + - +
    * |   |   |   |   |   |   |   |
    * + - + - + - + - + - + - + - +
    * |   |   |   |   |   |   |   |
    * + - + - + - + - + - + - + - +
    */

    do 
    {
        Game.printGameIntro();
        runGame();
        Game.printGameSummary();
    } while (Game.AskToPlayAgain());
}

void runGame()
{   
    Game.reset(Board);
    int move;                                           // a move between 1 and 7.
    int moveIndex;                                      // The moves corresponding index on the board.
    Board.print_board();                                //print the game Board
    while (!Game.isGameWon())
    {
        move = Game.getValidMove(Board);                //Get a VALID move from current player
        moveIndex = Game.getMoveIndex(move, Board);     //Get the moveIndex of the previously received VALID move.
        Board.update_board(moveIndex, Game.m_side);     //Update the Board
        Game.checkGameOverStatus(moveIndex, Board);            
        Game.changeSide();                              //Changes sides after a player made a move
        Board.print_board();
    }
}
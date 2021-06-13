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
    
    /* Board Layout:

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

    runGame();
}

void runGame()
{   /*
        
        loop until isGameWon() returns 1 or 2 (for player 1 or 2). isGamewWon just returns m_GameIsWon (1,2 if won and 0 if not won) m_GameisWon checks after every move
        if game is won or not and changes the member variable m_GameIsWon. This should be in the gameLogic class.

        
    */
    int move; // a move between 1 and 7.
    int moveIndex; // The moves corresponding index on the board.
    //while (!Game.isGameWon())
    //{
    //    Board.print_board();                            //print the game Board
    //    move = Game.getValidMove(Board);                //Get a VALID move from current player
    //    moveIndex = Game.getMoveIndex(move, Board);     //Get the moveIndex of the previously received VALID move.
    //    Board.update_board(moveIndex, Game.m_side);     //Update the Board
    //    Game.changeSide();                              //Changes sides after a player made a move
    //}


    //Test win condition
    //enter lots of different moves and then test if it produces a win or a draw. or nothing.
    //Board.print_board();                            //print the game Board
    //moveIndex = Game.getMoveIndex(5, Board);     //Get the moveIndex of the previously received VALID move.
    //Board.update_board(moveIndex, 0);     //Update the Board
    //moveIndex = Game.getMoveIndex(5, Board);     //Get the moveIndex of the previously received VALID move.
    //Board.update_board(moveIndex, 0);     //Update the Board
    //moveIndex = Game.getMoveIndex(5, Board);     //Get the moveIndex of the previously received VALID move.
    //Board.update_board(moveIndex, 0);     //Update the Board
    moveIndex = Game.getMoveIndex(5, Board);     //Get the moveIndex of the previously received VALID move.
    Board.update_board(moveIndex, 0);     //Update the Board
    Board.print_board();                            //print the game Board
    Game.check4InARow(moveIndex,Board);



}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

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
{
    //TODO loops a while loop while the game is being played. Prints a new board everytime a new move is made.

    Board.print_board();
    //Board.update_board(337, 0);
    Game.makeMove(1, 0, Board);
    Board.print_board();



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

#include "TicTacToeBoard.h"
/**
 * Class for representing a 3x3 Tic-Tac-Toe game board, using the Piece enum
 * to represent the spaces on the board.
**/

//Switches turn member variable to represent whether it's X's or O's turn
void TicTacToeBoard::toggleTurn()
{	if (turn == X)
		turn = O;
	else
		turn = X;}

//Constructor sets an empty board and specifies it is X's turn first
TicTacToeBoard::TicTacToeBoard()
{	clearBoard();
	if (turn != X)
		turn=X;}

//Resets each board location to the Blank Piece value
void TicTacToeBoard::clearBoard()
{	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = Blank;}	}	}

/**
 * Places the piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. placePiece does 
 * NOT allow to place a piece in a location where there is already a piece.
 * In that case, placePiece just returns what is already at that location. 
 * Out of bounds coordinates return the Piece Invalid value
**/ 
Piece TicTacToeBoard::placePiece(int row, int column)
{	Piece get;
	if (getPiece(row, column) == Blank) {
		board[row][column] = turn;
		get = turn;
	} else {
		get = getPiece(row, column);
	}
	toggleTurn();
	return get;}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece TicTacToeBoard::getPiece(int row, int column)
{	if ((row > 2) || (row < 0) || (column > 2) || (column < 0))
		return Invalid;
	else
		return board[row][column];}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won.
**/
Piece TicTacToeBoard::getWinner()
{	for (int i = 0; i < 3; i ++) {
		if ((getPiece(i,0) == getPiece(i,1)) && (getPiece(i, 0) == getPiece(i, 2))
			&& (getPiece(i, 0) != Blank))
			return getPiece(i,0);
		if ((getPiece(0, i) == getPiece(1, i)) && getPiece(0, i) == getPiece(2, i)
			&& getPiece(0, i) != Blank)
			return getPiece(0,i); 	}
	if (getPiece(0,0) == getPiece(1,1) && getPiece(0,0) == getPiece(2,2)
		&& getPiece(0,0) != Blank)
		return getPiece(0,0);
	if (getPiece(2,0) == getPiece(1,1) && getPiece(2,0) == getPiece(0,2)
		&& getPiece(2,0) != Blank)
		return getPiece(2,0);
	return Invalid;}

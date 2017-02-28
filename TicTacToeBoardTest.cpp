/**
 * Unit Tests for TicTacToeBoard
**/

#include <gtest/gtest.h>
#include "TicTacToeBoard.h"
#include <iostream>
#include <time.h>

class TicTacToeBoardTest : public ::testing::Test
{
	protected:
		TicTacToeBoardTest(){} //constructor runs before each test
		virtual ~TicTacToeBoardTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(TicTacToeBoardTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

/* Create a TTTB. Checks for segfault */
TEST(TicTacToeBoardTest,  createSegFault)
{
	try {
		TicTacToeBoard x; // create TicTacToeBoard
		SetUp();
		ASSERT_TRUE(true);  // No segfaults so far.
		TearDown();
	} catch (std::exception& e) {
		std::cerr << "Exception thrown on board creation: " << e.what() << std::endl;
	}
}

/* Make board. Clear a blank board. */
TEST(TicTacToeBoardTest, clearBoard) {
	TicTacToeBoard x; // create TicTacToeBoard. Hopefully no segfaults here, per previous testing
	SetUp();
	try {x.clearBoard(); ASSERT_TRUE(true);} // successfully cleared board
	catch (std::exception& e)
		{std::cerr << "Exception thrown when clearing board: " << e.what() << std::endl;
		ASSERT_TRUE(false);} // didn't clear board. Seg faulted.
	TearDown();
}

/* Make board. Place X in center. */
TEST(TicTacToeBoardTest, placeXInCenter){
	TicTacToeBoard x; // createTicTacToeBoard
	SetUp();
	try {ASSERT_EQ(x.placePiece(1,1), 'X');}
	catch (std::exception& e) {
		std::cerr << "Exception thrown when placing x in center: " << e.what() << std::endl;
		ASSERT_TRUE(false); // Segfault, yo. RIP
	}
}

/* Make board. Place X in center. Place O in top left */
TEST(TicTacToeBoardTest, placeXInCenterPlaceOTopLeft){
	TicTacToeBoard x; // create TicTacToeBoard
	SetUp();
	x.placePiece(1,1);
	ASSERT_EQ(x.placePiece(0,0), 'O'); // place O in top left. No segfault, hopefully.
	TearDown();
}

/* Make board. Place X Center. Place O Top Left. Attempt to place X Top Left. Return O. 
 * Place O  Mid Left. Return O. */
TEST(TicTacToeBoardTest, overlapTest){
	TicTacToeBoard x; // create TicTacToeBoard
	SetUp();
	x.placePiece(1,1); // X plays center
	x.placePiece(0,0); // O plays top left
	ASSERT_EQ(x.placePiece(0,0), 'O'); // X attempts top left, get's rejected.
	//ASSERT_EQ(x.placePiece(1,0), 'O'); // O seizes the opportunity, places mid left.
	TearDown();
}

/* Make board. Place X Center. Place O Top Left. Attempt to place X Top Left. Return O. 
 * Place O  Mid Left. Return O. */
TEST(TicTacToeBoardTest, overlapTest2){
	TicTacToeBoard x; // create TicTacToeBoard
	SetUp();
	x.placePiece(1,1); // X plays center
	x.placePiece(0,0); // O plays top left
	x.placePiece(0,0); // X attempts top left, get's rejected.
	ASSERT_EQ(x.placePiece(1,0), 'O'); // O seizes the opportunity, places mid left.
	TearDown();
}

/* Make board. Place X in 3, 0. Should return invalid  */
TEST(TicTacToeBoardTest, invalidPlace1){
	TicTacToeBoard x; // create TicTacToeBoard
	SetUp();
	ASSERT_EQ(x.placePiece(3,0), '?');
	TearDown();
}

/* Make board. Place X in 0, 3. Should return invalid  */
TEST(TicTacToeBoardTest, invalidPlace2){
	TicTacToeBoard x; // create TicTacToeBoard
	SetUp();
	ASSERT_EQ(x.placePiece(0,3), '?');
	TearDown();
}

/* Make board. Place X in -1, 0. Should return invalid  */
TEST(TicTacToeBoardTest, invalidPlace3){
	TicTacToeBoard x; // create TicTacToeBoard
	SetUp();
	ASSERT_EQ(x.placePiece(-1,0), '?');
	TearDown();
}

/* Make board. Place X in -1, 0. Should return invalid  */
TEST(TicTacToeBoardTest, invalidPlace4){
	TicTacToeBoard x; // create TicTacToeBoard
	SetUp();
	ASSERT_EQ(x.placePiece(0,-1), '?');
	TearDown();
}


/* Make board. Sweep board to see if all board spaces are clear*/
TEST(TicTacToeBoardTest, boardSweep){
	TicTacToeBoard x; // create TicTacToeBoard
	SetUp();
	x.clearBoard();  // Should clear the board.
	char get = x.getPiece(0,0);  // Checking every single space on the board
	int i = 0, j = 0;

	/* Loop through the board.  */
	while (get == ' ' && (i < 3)){
		for (j = 0; j < 3; j++)
			get = x.getPiece(i,j);
		i++;
	}
	ASSERT_EQ(get, ' '); // Test after checking for cleared board.
	TearDown();
}

/* Make board. Sweep board to see if all board spaces are clear. 
Pervert the test by inserting an X in the center. */
TEST(TicTacToeBoardTest, boardSweepPlace){
	TicTacToeBoard x; // create TicTacToeBoard
	SetUp();
	x.clearBoard();  // Should clear the board.
	char get = x.getPiece(0,0);  // Checking every single space on the board
	int i = 0, j = 0;

	/* Loop through the board.  */
	while (get == ' ' && (i < 3)){
		for (j = 0; j < 3; j++)
			get = x.getPiece(i,j);
		i++;
	}
	ASSERT_NE(x.placePiece(1,1), ' '); // Test after checking for cleared board.
	TearDown();
}

/* Make board. getWinner() should return invalid  */
TEST(TicTacToeBoardTest, noWinner){
	TicTacToeBoard x;
	SetUp();
	ASSERT_EQ(x.getWinner(), '?');
	TearDown();
}

/* A battery of random tests. Not ideal for checking every win situation, but <insert something
 * about law of averages>, and it's 10 o'clock at night and my eyes weigh heavy. */


/* Make board. Do 10000 turns in random order, or until getWinner() is no longer invalid.  */
TEST(TicTacToeBoardTest, significantlyStatisticallyLikelyToChooseAWinner1){
	TicTacToeBoard x;
	SetUp();
	std::srand(time(NULL)+0); // offset added after weird pseudo-random related test errors 
	int turnCounter = 0;
	while (turnCounter < 10000 && x.getWinner() == '?'){
		x.placePiece((std::rand() % 3), (std::rand() % 3));
		turnCounter++;
	}
	ASSERT_NE(x.getWinner(), '?');
	std::cout << "The winner was: " << x.getWinner() << " " << x.getWinner() << std::endl;
	TearDown();
}

/* Make board. Do 10000 turns in random order, or until getWinner() is no longer invalid.  */
TEST(TicTacToeBoardTest, significantlyStatisticallyLikelyToChooseAWinner2){
	TicTacToeBoard x;
	SetUp();
	std::srand(time(NULL)+1);
	int turnCounter = 0;
	while (turnCounter < 10000 && x.getWinner() == '?'){
		x.placePiece(std::rand() % 3, std::rand() % 3);
		turnCounter++;
	}
	ASSERT_NE(x.getWinner(), '?');
	std::cout << "The winner was: " << x.getWinner() << " " << x.getWinner() << std::endl;
	TearDown();
}


/* Make board. Do 10000 turns in random order, or until getWinner() is no longer invalid.  */
TEST(TicTacToeBoardTest, significantlyStatisticallyLikelyToChooseAWinner3){
	TicTacToeBoard x;
	SetUp();
	std::srand(time(NULL)+2);
	int turnCounter = 0;
	while (turnCounter < 10000 && x.getWinner() == '?'){
		x.placePiece(std::rand() % 3, std::rand() % 3);
		turnCounter++;
	}
	ASSERT_NE(x.getWinner(), '?');
	std::cout << "The winner was: " << x.getWinner() << " " << x.getWinner() << std::endl;
	TearDown();
}

/* Make board. Do 10000 turns in random order, or until getWinner() is no longer invalid.  */
TEST(TicTacToeBoardTest, significantlyStatisticallyLikelyToChooseAWinner4){
	TicTacToeBoard x;
	SetUp();
	std::srand(time(NULL)+3);
	int turnCounter = 0;
	while (turnCounter < 10000 && x.getWinner() == '?'){
		x.placePiece(std::rand() % 3, std::rand() % 3);
		turnCounter++;
	}
	ASSERT_NE(x.getWinner(), '?');
	std::cout << "The winner was: " << x.getWinner() << " " << x.getWinner() << std::endl;
	TearDown();
}


/* Make board. Do 10000 turns in random order, or until getWinner() is no longer invalid.  */
TEST(TicTacToeBoardTest, significantlyStatisticallyLikelyToChooseAWinner5){
	TicTacToeBoard x;
	SetUp();
	std::srand(time(NULL)+4);
	int turnCounter = 0;
	while (turnCounter < 10000 && x.getWinner() == '?'){
		x.placePiece(std::rand() % 3, std::rand() % 3);
		turnCounter++;
	}
	ASSERT_NE(x.getWinner(), '?');
	std::cout << "The winner was: " << x.getWinner() << " " << x.getWinner() << std::endl;
	TearDown();
}

/* Make board. Do 10000 turns in random order, or until getWinner() is no longer invalid.  */
TEST(TicTacToeBoardTest, significantlyStatisticallyLikelyToChooseAWinner6){
	TicTacToeBoard x;
	SetUp();
	std::srand(time(NULL)+5);
	int turnCounter = 0;
	while (turnCounter < 10000 && x.getWinner() == '?'){
		x.placePiece(std::rand() % 3, std::rand() % 3);
		turnCounter++;
	}
	ASSERT_NE(x.getWinner(), '?');
	std::cout << "The winner was: " << x.getWinner() << " " << x.getWinner() << std::endl;
	TearDown();
}

/* Make board. Do 10000 turns in random order, or until getWinner() is no longer invalid.  */
TEST(TicTacToeBoardTest, significantlyStatisticallyLikelyToChooseAWinner7){
	TicTacToeBoard x;
	SetUp();
	std::srand(time(NULL)+6);
	int turnCounter = 0;
	while (turnCounter < 10000 && x.getWinner() == '?'){
		x.placePiece(std::rand() % 3, std::rand() % 3);
		turnCounter++;
	}
	ASSERT_NE(x.getWinner(), '?');
	std::cout << "The winner was: " << x.getWinner() << " " << x.getWinner() << std::endl;
	TearDown();
}

/* Make board. Do 10000 turns in random order, or until getWinner() is no longer invalid.  */
TEST(TicTacToeBoardTest, significantlyStatisticallyLikelyToChooseAWinner8){
	TicTacToeBoard x;
	SetUp();
	std::srand(time(NULL)+7);
	int turnCounter = 0;
	while (turnCounter < 10000 && x.getWinner() == '?'){
		x.placePiece(std::rand() % 3, std::rand() % 3);
		turnCounter++;
	}
	ASSERT_NE(x.getWinner(), '?');
	std::cout << "The winner was: " << x.getWinner() << " " << x.getWinner() << std::endl;
	TearDown();
}

/* Make board. Do 10000 turns in random order, or until getWinner() is no longer invalid.  */
TEST(TicTacToeBoardTest, significantlyStatisticallyLikelyToChooseAWinner9){
	TicTacToeBoard x;
	SetUp();
	std::srand(time(NULL)+8);
	int turnCounter = 0;
	while (turnCounter < 10000 && x.getWinner() == '?'){
		x.placePiece(std::rand() % 3, std::rand() % 3);
		turnCounter++;
	}
	ASSERT_NE(x.getWinner(), '?');
	std::cout << "The winner was: " << x.getWinner() << " " << x.getWinner() << std::endl;
	TearDown();
}

/* Make board. Do 10000 turns in random order, or until getWinner() is no longer invalid.  */
TEST(TicTacToeBoardTest, significantlyStatisticallyLikelyToChooseAWinner10){
	TicTacToeBoard x;
	SetUp();
	std::srand(time(NULL)+9);
	int turnCounter = 0;
	while (turnCounter < 10000 && x.getWinner() == '?'){
		x.placePiece(std::rand() % 3, std::rand() % 3);
		turnCounter++;
	}
	ASSERT_NE(x.getWinner(), '?');
	std::cout << "The winner was: " << x.getWinner() << " " << x.getWinner() << std::endl;
	TearDown();
}

 /* end test */

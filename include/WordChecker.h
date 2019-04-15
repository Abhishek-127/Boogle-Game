#include <string.h>
#include <stdlib.h>

#include "BoardGenerator.h"

/*
	Given the game board and a word, find if that word is in the game board

	@param gameBoard The board containing all characters of the game
	@param word The full string of the word that is to be found

	@return 0 (false) or 1 (true) depending on whether the word was found on the board
*/
int wordChecker(struct rolledDice **gameBoard, char *word);

/*
	RECURSIVE FUNCTION

	Checks to ensure the word that was found abides by the game rules
	that the letters in the found word must be in a path that doesn't cross

	@param previousX The index of the previously found character of the found word on the x-axis of the game board
	@param previousY The index of the previously found character of the found word on the y-axis of the game board
	@param word The full string of the word that was found
	@param gameBoard The board containing all characters of the game
	@param substringLength The length of the found word that has currently been checked
	@param visited The board positions that have already been checked (to prevent crossing of the word path)

	@return 0 (false) or 1 (true) depending on whether the word's character being looked for was found in the adjacent positions
*/
int abidesRules(int previousX, int previousY, char *word, struct rolledDice** gameBoard, int substringLength, int **visited);

/*
	Returns the character at position (x,y) on the game board

	@param x The index of the target character on the x-axis of the game board
	@param y The index of the target character on the y-axis of the game board
	@param gameBoard The game board where the game is played

	@return The character at the position (x,y) on the game board
*/
char getLetter(int x, int y, struct rolledDice **gameBoard);

/*
	Tests the functionality of the previously defined wordChecker function
	All parameters and returns are the same
*/
int testWordChecker(char **boggle, char *word);

/*
	Tests the functionality of the previously defined abidesRules function
	All parameters and returns are the same
*/
int testAbidesRules(int previousX, int previousY, char *word, char **gameBoard, int substringLength, int **visited);

/*
	Tests the functionality of the previously defined getLetter function
	All parameters are returns are the same

	Gets the letter at position (x,y) on the game board

	@param x The x-index of the character to return
	@param y The y-index of the character to return
	@param boggle The game board to return the character at the (x,y) position from

	@return The character on the board at position (x,y)
*/
char testGetLetter(int x, int y, char **boggle);


/*
	Tests the functionality of the previously defined wordChecker function
	All parameters and returns are functionally the same
*/
int hcWordChecker(char boggle[][4], char *word);

/*
	Tests the functionality of the previously defined abidesRules function
	All parameters and returns are the same
*/
int hcAbidesRules(int previousX, int previousY, char *word, char boggle[][4], int substringLength, int **visited);

/*
	Tests the functionality of the previously defined getLetter function
	All parameters are returns are the same

	Gets the letter at position (x,y) on the game board

	@param x The x-index of the character to return
	@param y The y-index of the character to return
	@param boggle The game board to return the character at the (x,y) position from

	@return The character on the board at position (x,y)
*/
char hcGetLetter(int x, int y, char boggle[][4]);





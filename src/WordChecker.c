#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "WordChecker.h"


/**
 *	Given the game board and a word, find if that word is in the game board
 *
 *	@param gameBoard The board containing all characters of the game
 *	@param word The full string of the word that is to be found
 *
 *	@return 0 (false) or 1 (true) depending on whether the word was found on the board
 */
int wordChecker(RolledDice **gameBoard, char *word){

	// Initializes visited to a 2D integer array of size 4x4
	int **visited = malloc(sizeof(int *) * 4);
	visited[0] = malloc(sizeof(int) * 4);
	visited[1] = malloc(sizeof(int) * 4);
	visited[2] = malloc(sizeof(int) * 4);
	visited[3] = malloc(sizeof(int) * 4);

	/*	Fills the visited array with 0s except for the first element (0,0)
		which it sets to 1 */
	for (int row = 0; row < 4; row += 1) {
		for (int column = 0; column < 4; column += 1) {
			if (row == 0 && column == 0) {
				visited[row][column] = 1;
			} else {
				visited[row][column] = 0;
			}
		}
	}

	// Finds the given word in the game board and returns 1 (true) if it finds it
	int startingSubstringLength = 0;
	for (int row = 0; row < 4; row += 1) {
		for (int column = 0; column < 4; column += 1) {
			if (abidesRules(row, column, word, gameBoard, startingSubstringLength, visited)) {
				free(visited[0]);
				free(visited[1]);
				free(visited[2]);
				free(visited[3]);
				// Missing free? free(visited);
				return 1;
			}
		}
	}

	// If the loop to find the word is unsuccessful, 0 (false) is returned
	free(visited[0]);
	free(visited[1]);
	free(visited[2]);
	free(visited[3]);
	// Missing free? free(visited);
	return 0;
}


/**
 *	RECURSIVE FUNCTION
 *
 *	Checks to ensure the word that was found abides by the game rules
 *	that the letters in the found word must be in a path that doesn't cross
 *
 *	@param previousX The index of the previously found character of the found word on the x-axis of the game board
 *	@param previousY The index of the previously found character of the found word on the y-axis of the game board
 *	@param word The full string of the word that was found
 *	@param gameBoard The board containing all characters of the game
 *	@param substringLength The length of the found word that has currently been checked
 *	@param visited The board positions that have already been checked (to prevent crossing of the word path)
 *
 *	@return 0 (false) or 1 (true) depending on whether the word's character being looked for was found in the adjacent positions
 */
int abidesRules(int previousX, int previousY, char *word, RolledDice **gameBoard, int substringLength, int **visited){

	/*	Preemptively returns 1 (true) if the entire length of the
		word has been checked and no more checking is required */
	if (substringLength == (strlen(word) - 1)) {
		return 1;
	}

	// The x-axis indices of the adjacent positions to the previous position
	int allX[] = {
		0,	// Right
		-1,	// Up-Right
		-1, // Up
		-1, // Up-Left
		0,	// Left
		1,	// Down-Left
		1,	// Down
		1	// Down-Right
	};

	// The y-axis indices of the adjacent positions to the previous position
	int allY[] = {
		1,	// Right
		1,	// Up-Right
		0,	// Up
		-1,	// Up-Left
		-1,	// Left
		-1,	// Down-Left
		0,	// Down
		1	// Down-Right
	};

	/*	The next character in the found word that is being looked for in the
		adjacent positions */
	char findLetter = word[substringLength + 1];

	/*	Iterates through the adjacent positions of the previous position,
		checking each position for the next target character */
	for (int adjacentCell = 0; adjacentCell < 8; adjacentCell += 1) {
		int newX = previousX + allX[adjacentCell]; // The x-index of the adjacent character to the previous character
		int newY = previousY + allY[adjacentCell]; // The y-index of the adjacent character to the previous character
		// Ensures the new position is within X-range (0 to 3)
		if ((newX >= 0) && (newX < 4)) {
			// Ensures the new position is within Y-range (0 to 3)
			if ((newY >=0) && (newY < 4)) {
				// Checks to ensure the new position hasn't already been checked
				if (!visited[newX][newY]) {
					// Checks if the letter at the new position is the letter to be found
					if (toupper(findLetter) == getLetter(newX, newY, gameBoard)) {
						// Prevents position from being checked again
						visited[newX][newY] = 1;

						// Increases the length of the valid string found
						substringLength += 1;

						/*	Performs the same process in a recursive fashion on the next letter in the
							word being checked. */
						int result = abidesRules(newX, newY, word, gameBoard, substringLength, visited);

						// Returns 1 (true) if the next-letter in the word being checked passed
						if (result) {
							return 1;
						} else {
							substringLength -= 1;
						}
					}
				}
			}
		}
	}
	// Returns 0 (false) if the checking process failed to find the findLetter in the adjacent characters
	return 0;
}


/**
 *	Returns the character at position (x,y) on the game board
 *
 *	@param x The index of the target character on the x-axis of the game board
 *	@param y The index of the target character on the y-axis of the game board
 *	@param gameBoard The game board where the game is played
 *
 *	@return The character at the position (x,y) on the game board
 */
char getLetter(int x, int y,   RolledDice** gameBoard){
	return gameBoard[x][y].character;
}


/**
 *	Tests the functionality of the previously defined wordChecker function
 *	All parameters and returns are the same
 */
int testWordChecker(char **boggle, char *word) {

	// Initializes visited to a 2D integer array of size 4x4
	int **visited = malloc(sizeof(int *) * 4);
	visited[0] = malloc(sizeof(int) * 4);
	visited[1] = malloc(sizeof(int) * 4);
	visited[2] = malloc(sizeof(int) * 4);
	visited[3] = malloc(sizeof(int) * 4);

	/*	Fills the visited array with 0s except for the first element (0,0)
		which it sets to 1 */
	for (int row = 0; row < 4; row += 1) {
		for (int column = 0; column < 4; column += 1) {
			if (row == 0 && column == 0) {
				visited[row][column] = 1;
			} else {
				visited[row][column] = 0;
			}
		}
	}

	// Finds the given word in the game board and returns 1 (true) if it finds it
	int startingSubstringLength = 0;
	for (int row = 0; row < 4; row += 1) {
		for (int column = 0; column < 4; column += 1) {
			if (testAbidesRules(row, column, word, boggle, startingSubstringLength, visited)){
				free(visited[0]);
				free(visited[1]);
				free(visited[2]);
				free(visited[3]);
				// Missing free? free(visited);
				return 1;
			}
		}
	}

	// If the loop to find the word is unsuccessful, 0 (false) is returned
	free(visited[0]);
	free(visited[1]);
	free(visited[2]);
	free(visited[3]);
	// Missing free? free(visited);
	return 0;
}


/**
 *	Tests the functionality of the previously defined abidesRules function
 *	All parameters and returns are the same
 */
int testAbidesRules(int previousX, int previousY, char *word, char **gameBoard, int substringLength, int **visited) {

	/*	Preemptively returns 1 (true) if the entire length of the
		word has been checked and no more checking is required */
	if(substringLength == (strlen(word) - 1)) {
		return 1;
	}

	// The x-axis indices of the adjacent positions to the previous position
	int allX[] = {
		0,	// Right
		-1,	// Up-Right
		-1, // Up
		-1, // Up-Left
		0,	// Left
		1,	// Down-Left
		1,	// Down
		1	// Down-Right
	};

	// The y-axis indices of the adjacent positions to the previous position
	int allY[] = {
		1,	// Right
		1,	// Up-Right
		0,	// Up
		-1,	// Up-Left
		-1,	// Left
		-1,	// Down-Left
		0,	// Down
		1	// Down-Right
	};

	// The most recently found letter from the word
	char previousLetter = word[substringLength];

	/*
		If the previous letter was a Q and letter 2 ahead in the word is equal to the letter at the previous letter's position,
		set the letter to be found to the letter in the word 3 positions ahead of the current one and the previous letter to 2
		positions ahead of the current one.
		Otherwise, set the letter to be found to the next letter in the word following the previous letter.
	*/
	if (toupper(previousLetter) == 'Q' && toupper(word[substringLength + 2]) == testGetLetter(previousX,previousY,gameBoard)) {
		substringLength += 2;
		previousLetter = word[substringLength];
	}
	
	// The next letter from the word to be found
	char findLetter = word[substringLength + 1];

	/*	Iterates through the adjacent positions of the previous position,
		checking each position for the next target character */
	for (int adjacentCell = 0; adjacentCell < 8; adjacentCell += 1) {
		int newX = previousX + allX[adjacentCell]; // The x-index of the adjacent character to the previous character
		int newY = previousY + allY[adjacentCell]; // The y-index of the adjacent character to the previous character
		// Ensures the new position is within X-range (0 to 3)
		if ((newX >= 0) && (newX < 4)) { 
			// Ensures the new position is within Y-range (0 to 3)
			if ((newY >=0) && (newY < 4)) {
				// Checks if the letter at the new position is the letter to be found
				if (toupper(findLetter) == testGetLetter(newX, newY, gameBoard)) {
					// Checks to ensure the new position hasn't already been checked
					if (!visited[newX][newY]) {
						// Prevents position from being checked again
						visited[newX][newY] = 1;

						// Increases the length of the valid string found
						substringLength += 1;

						/*	Performs the same process in a recursive fashion on the next letter in the
							word being checked. */
						int result = testAbidesRules(newX, newY, word, gameBoard, substringLength, visited);

						// Returns 1 (true) if the next-letter in the word being checked passed
						if (result) {
							return 1;
						} else {
							substringLength -= 1;
						}
					}
				}
			}
		}
	}
	// Returns 0 (false) if the checking process failed to find the findLetter in the adjacent characters
	return 0;
}


/**
 *	Tests the functionality of the previously defined getLetter function
 *	All parameters are returns are the same
 *
 *	Gets the letter at position (x,y) on the game board
 *
 *	@param x The x-index of the character to return
 *	@param y The y-index of the character to return
 *	@param boggle The game board to return the character at the (x,y) position from
 *
 *	@return The character on the board at position (x,y)
 */
char testGetLetter(int x, int y, char **boggle){
	return boggle[x][y];
}


/**
 *	Tests the functionality of the previously defined wordChecker function
 *	All parameters and returns are functionally the same
 */
int hcWordChecker(char boggle[][4], char *word){

	// Initializes visited to a 2D integer array of size 4x4
	int **visited = malloc(sizeof(int *) * 4);
	visited[0] = malloc(sizeof(int) * 4);
	visited[1] = malloc(sizeof(int) * 4);
	visited[2] = malloc(sizeof(int) * 4);
	visited[3] = malloc(sizeof(int) * 4);

	/*	Fills the visited array with 0s except for the first element (0,0)
		which it sets to 1 */
	for (int row = 0; row < 4; row += 1) {
		for (int column = 0; column < 4; column += 1) {
			if (row == 0 && column == 0) {
				visited[row][column] = 1;
			} else {
				visited[row][column] = 0;
			}
		}
	}

	// Finds the given word in the game board and returns 1 (true) if it finds it
	int startingSubstringLength = 0;
	for (int row = 0; row < 4; row += 1) {
		for (int column = 0; column < 4; column += 1) {
			if (hcAbidesRules(row, column, word, boggle, startingSubstringLength, visited)){
				free(visited[0]);
				free(visited[1]);
				free(visited[2]);
				free(visited[3]);
				// Missing free? free(visited);
				return 1;
			}
		}
	}

	// If the loop to find the word is unsuccessful, 0 (false) is returned
	free(visited[0]);
	free(visited[1]);
	free(visited[2]);
	free(visited[3]);
	// Missing free? free(visited);
	return 0;
}


/**
 *	Tests the functionality of the previously defined abidesRules function
 *	All parameters and returns are the same
 */
int hcAbidesRules(int previousX, int previousY, char *word, char boggle[][4], int substringLength, int **visited){

	/*	Preemptively returns 1 (true) if the entire length of the
		word has been checked and no more checking is required */
	if (substringLength == (strlen(word) - 1)){
		return 1;
	}

	// The x-axis indices of the adjacent positions to the previous position
	int allX[] = {
		0,	// Right
		-1,	// Up-Right
		-1, // Up
		-1, // Up-Left
		0,	// Left
		1,	// Down-Left
		1,	// Down
		1	// Down-Right
	};

	// The y-axis indices of the adjacent positions to the previous position
	int allY[] = {
		1,	// Right
		1,	// Up-Right
		0,	// Up
		-1,	// Up-Left
		-1,	// Left
		-1,	// Down-Left
		0,	// Down
		1	// Down-Right
	};
	
	// The most recently found letter from the word
	char previousLetter = word[substringLength];

	/*
		If the previous letter was a Q and letter 2 ahead in the word is equal to the letter at the previous letter's position,
		set the letter to be found to the letter in the word 3 positions ahead of the current one and the previous letter to 2
		positions ahead of the current one.
		Otherwise, set the letter to be found to the next letter in the word following the previous letter.
	*/
	if(toupper(previousLetter) == 'Q' && toupper(word[substringLength + 2]) == hcGetLetter(previousX,previousY,boggle)){
		substringLength += 2;
		previousLetter = word[substringLength];
	}

	// The next letter from the word to be found
	char findLetter = word[substringLength + 1];

	/*	Iterates through the adjacent positions of the previous position,
		checking each position for the next target character */
	for (int adjacentCell = 0; adjacentCell < 8; adjacentCell += 1) {
		int newX = previousX + allX[adjacentCell]; // The x-index of the adjacent character to the previous character
		int newY = previousY + allY[adjacentCell]; // The y-index of the adjacent character to the previous character
		// Ensures the new position is within X-range (0 to 3)
		if((newX >= 0) && (newX < 4)) {
			// Ensures the new position is within Y-range (0 to 3)
			if ((newY >=0) && (newY < 4)) {
				// Checks if the letter at the new position is the letter to be found
				if (toupper(findLetter) == hcGetLetter(newX, newY, boggle)) {
					// Checks to ensure the new position hasn't already been checked
					if (!visited[newX][newY]) {
						// Prevents position from being checked again
						visited[newX][newY] = 1;

						// Increases the length of the valid string found
						substringLength += 1;

						/*	Performs the same process in a recursive fashion on the next letter in the
							word being checked. */
						int result = hcAbidesRules(newX, newY, word, boggle, substringLength, visited);

						// Returns 1 (true) if the next-letter in the word being checked passed
						if (result) {
							return 1;
						} else {
							substringLength -= 1;
						}
					}
				}
			}
		}
	}
	// Returns 0 (false) if the checking process failed to find the findLetter in the adjacent characters
	return 0;
}


/**
 *	Tests the functionality of the previously defined getLetter function
 *	All parameters are returns are the same
 *
 *	Gets the letter at position (x,y) on the game board
 *
 *	@param x The x-index of the character to return
 *	@param y The y-index of the character to return
 *	@param boggle The game board to return the character at the (x,y) position from
 *
 *	@return The character on the board at position (x,y)
 */
char hcGetLetter(int x, int y, char boggle[][4]){
	return boggle[x][y];
}

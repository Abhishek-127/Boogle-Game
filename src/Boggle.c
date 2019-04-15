#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Dictionary.h"
#include "BoardGenerator.h"
#include "WordChecker.h"
#include "Scoreboard.h"

#define MAX_LINE 100

/**
 * set up board,
 * set up dictionary,
 */
void freeAndRestBoard(struct rolledDice **gameBoard, struct presetDice *inputArrayOfDice) {

    for (int i = 0; i < 4; i++) {
        free(gameBoard[i]);
    }
    rollDice(gameBoard, inputArrayOfDice);
}

/**
 * printToOutputFile is a macro used to improve efficiency
 * It prints out the char entered to the output file.
 */
void printToOutputFile(int begin, char p, FILE *outputFP) {
    if (begin == 0) {
        fprintf(outputFP, "%s", p);
        begin++;
    } else {
        fprintf(outputFP, ",%s", p);
    }
    return;
}

/**
 * converting everything to Upper Case
 */
char *convertToUpper(char **upper) {
    char *upperDeref = *upper;

    for (int i = 0; upperDeref[i]; i++) {
        upperDeref[i] = toupper(upperDeref[i]);
    }
    return upperDeref;
}

char *convertToUpper2(char (*upper)[]) {
    char *upperDeref = *upper;

    for (int i = 0; upperDeref[i]; i++) {
        upperDeref[i] = toupper(upperDeref[i]);
    }
    return upperDeref;
}

/**
 * scores for word lengths
 */
void incrementTotalScore(int *userScore, char *word) {
    int wordLen = strlen(word);
    fprintf(stdout, "wordLen: %d\n", wordLen);
    if (wordLen == 3 || wordLen == 4) {
        *userScore += 1;
    } else if (wordLen == 5) {
        *userScore += 2;
    } else if (wordLen == 6) {
        *userScore += 3;
    } else if (wordLen == 7) {
        *userScore += 5;
    } else if (wordLen >= 8) {
        *userScore += 11;
    }
}

int main(int argc, char **argv) {
    int testPoints = 0;
    char inputWord[100];
    char originalInputWord[100];

    FILE *inputFP;
    char line[MAX_LINE];
    char *fileName;

    const char *dictName = "../assets/EnglishWords.txt";
    DictionaryNode *checkEnglish;
    DictionaryNode *checkSubmitted;
    static DictionaryNode *englishDictionary[BIG_HASH_SIZE];
    static DictionaryNode *guessedWords[SMALL_HASH_SIZE];

    int currentScore = 0;
    int turnCount = 0;

    User *head = NULL;
    head = (User *) malloc(sizeof(User));

    PresetDice globalDice[16];
    RolledDice *gameBoard[4];

    FILE *outputFP;

    /**
     * reading the dictionary and storing the contents in MAX_LINE
     */
    if (!(inputFP = fopen(dictName, "r"))) {
        fprintf(stderr, "Could not open file \"%s\" for reading dictionary words\n", dictName);
        return 1;
    }

    while (fgets(line, MAX_LINE, inputFP) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';  //trim new line characters
        insert(englishDictionary, BIG_HASH_SIZE, convertToUpper2(&line));
    }
    fclose(inputFP);


    if (argc == 1) {
        fprintf(stdout, "playing in normal mode\n\n");

        //clear the board
        system("clear");

        initializePresetDice(globalDice);

        rollDice(gameBoard, globalDice);

        while (turnCount >= 0) {
            strcpy(originalInputWord, inputWord);

            convertToUpper2(&inputWord);

            User *thisUser;
            char inputName[100];

            if (strcmp(originalInputWord, "q") == 0) {
                printScoreboard(head);
                // "q" is the input, print scoreboard and exit game
                break;
            }
            // "n" is the input, adds user to/changes user in linked list and
            // resets game
            if (strcmp(originalInputWord, "n") == 0) {

                printScoreboard(head);
                fprintf(stdout, "Your current score: %d \n", currentScore);
                fprintf(stdout, "What is your name? \n");
                scanf("%s", inputName);

                if (userIsInList(head, inputName) == 0) {
                    addNode(head, inputName, currentScore);
                } else {
                    updateNodeWithName(head, inputName, currentScore);
                }

                currentScore = 0;

                strcpy(inputWord, "");

                freeAndRestBoard(gameBoard, globalDice);
                turnCount = 0;
                system("clear");
                continue;
            }

            printGameBoard(gameBoard);

            checkEnglish = lookup(englishDictionary, BIG_HASH_SIZE, inputWord);

            if (checkEnglish != NULL) {
                checkSubmitted = lookup(guessedWords, SMALL_HASH_SIZE, inputWord);

                /**
                 *checking for key points
                 *1)Your current score
                 *2)Checking if user input follows the rules
                 *3)User input lengths
                 *4)If user input has already been entered
                 *5)If the word is in the dictionary
                 **/
                if (checkSubmitted == NULL) {
                    if (strlen(inputWord) > 2) {
                        if (wordChecker(gameBoard, inputWord)) {
                            insert(guessedWords, SMALL_HASH_SIZE, inputWord);
                            incrementTotalScore(&currentScore, inputWord);
                            fprintf(stdout, "Correct! You current score is now: %d \n", currentScore);
                        } else {
                            fprintf(stderr, "The submitted word: \'%s\'' does not abide game rules. Try again!\n",
                                    originalInputWord);
                        }
                    } else {
                        fprintf(stderr, "The submitted word: \'%s\'' must be at least 3 letters long. Try again!\n",
                                originalInputWord);
                    }
                } else {
                    fprintf(stderr, "You have already submitted the word: \'%s\'' Try again!\n", originalInputWord);
                }
            } else if (turnCount > 0) {
                fprintf(stderr, "Incorrect word: \'%s\' is not in the English Dictionary. Try again!\n",
                        originalInputWord);
            }
            fprintf(stdout, "Submit a word you found:\n");
            scanf("%s", inputWord);
            turnCount++;
            system("clear");
        }

        /**
        *free everything
        **/
        for (int i = 0; i < 4; i++) {
            free(gameBoard[i]);
        }
        freeAll(head);

        /**
         * This Section of the code runs if there is a file on the command line.
         * It runs the program normally, but instead of printing to the screen, it writes to the specified output file
         * There are also a number of locally defined variables used only in this else if block
         */
    } else if (argc == 2) {
        fileName = argv[1];
        fprintf(stdout, "playing in test mode with file: %s\n", fileName);
        FILE *testFileFP;
        char testLine[MAX_LINE];
        char **testBoard = malloc(sizeof(char *));
        int fileLineCounter = 1;
        int i;
        int j;
        int begin = 0;

        /**
         * Ensures that the files can be opened safely
         * Displays warning message if file opening fails
         */
        if (!(testFileFP = fopen(fileName, "r"))) {
            fprintf(stderr, "Could not open test file \'%s\' for reading\n", fileName);
            return 1;
        } else if (!(outputFP = fopen("result.txt", "w"))) {
            fprintf(stderr, "Could not open result file \'%s\' for writing\n", "result.txt");
            return 1;
        }

        /**
         * Takes the content of the first line of of the file, and makes a board out of the content.
         * It also takes the rest of the lines of the file which is the user's input and verifies words given by the user.
         */
        while (fgets(testLine, MAX_LINE, testFileFP) != NULL) {
            testLine[strcspn(testLine, "\r\n")] = '\0';
            if (fileLineCounter == 1) {
                convertToBoard(testLine, &testBoard);

                /**
                 * This code chunk is responsible for the majority of the implementation of the major functions.
                 * The remaining lines in the file are intended to be used as user input and are verified or denied
                 * as valid words.
                 */
            } else if (fileLineCounter >= 2) {
                for (char *p = strtok(testLine, ","); p != NULL; p = strtok(NULL, ",")) {
                    checkEnglish = lookup(englishDictionary, BIG_HASH_SIZE, convertToUpper(&p));
                    if (checkEnglish != NULL) {
                        checkSubmitted = lookup(guessedWords, SMALL_HASH_SIZE, p);
                        if (checkSubmitted == NULL) {

                            /**
                             * Displays a relevant message to the output file if entered word is invalid to the user and adds correct
                             * words to a list, so as to prevent repeated entry of those valid words.
                             */
                            if (testWordChecker(testBoard, p)) {
                                insert(guessedWords, SMALL_HASH_SIZE, p);
                                incrementTotalScore(&testPoints, p);
                                fprintf(stdout, "Correct! You total score is now: %d \n", testPoints);
                            } else {
                                printToOutputFile(begin, p, outputFP);
                                fprintf(stderr, "The submitted word: \'%s\'' does not abide game rules. Try again!\n",
                                        p);
                            }
                        } else {
                            printToOutputFile(begin, p, outputFP);
                            fprintf(stderr, "You have already submitted the word: \'%s\'' Try again!\n", p);
                        }
                    } else {
                        printToOutputFile(begin, p, outputFP);

                        fprintf(stderr, "Incorrect word: \'%s\'' is not in the English Dictionary. Try again!\n", p);
                    }
                }
            }
            fileLineCounter++;
        }
        /**
         * Prints out the number of points, as well as freeing the board and closing files
         */
        fprintf(outputFP, "\n");
        fprintf(outputFP, "%d\n", testPoints);

        fclose(testFileFP);

        for (int i = 0; i < 4; i++) {
            free(testBoard[i]);
        }
        free(testBoard);

        fclose(outputFP);

    }

    freeDictionary(englishDictionary, BIG_HASH_SIZE);
    freeDictionary(guessedWords, SMALL_HASH_SIZE);

    return 0;
}


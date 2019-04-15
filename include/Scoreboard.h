#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <stdlib.h>


typedef struct users{
	char name[100];
	int maxScore;
	int totalGames;
	int totalScore;
	struct users *next;
} User;

User* findUserWithName(User *head, char *NameToFind);    

User* getUserAtIndex(User *head, int index);

int getIndexOfUserWithName(User *head, char *NameToFind);

int getLength(User *head);

User* getLastNode(User *head);

void printScoreboard(User *head);

void freeAll(User *head);
                      
void addNode(User *head, char *name, int MaxScore);

int userIsInList(User *head, char *NameToFind);

void updateNodeWithName(User *head, char *name, int CurrentScore); 

#endif

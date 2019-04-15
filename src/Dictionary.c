#include <string.h>
#include <stdio.h>
#include "Dictionary.h"

/**
 * Creates Unique hash value for given string
 * @param s string to generate hash for
 */
unsigned hash(const char *s){
    unsigned hashValue;
    for (hashValue = 0; *s != '\0'; s++){
      hashValue = *s + 31 * hashValue;
    }
    return hashValue;
}
/**
 * Looks up words based on key
 * @param dictionary pointer dictionaryNode array
 * @param hashSize size of the hash
 * @param key to lookup
 */
DictionaryNode *lookup(DictionaryNode **dictionary, int hashSize, const char *key){
    DictionaryNode *dictionaryNode;
    unsigned int hashValue = hash(key);
    for (dictionaryNode = dictionary[hashValue % hashSize]; dictionaryNode != NULL;
      dictionaryNode = dictionaryNode->next){
      if (strcmp (key, dictionaryNode->key) == 0){
        return dictionaryNode;
      }
    }
    return NULL; //not found
}

/**
 * Inserts Dictionary node into dictionaryArray
 * @pre 'dictionary' DictionaryNode array is defined and has memory allocated to it
 * @param dictionary pointer dictionaryNode array
 * @param hashSize size of the hash
 * @param key to lookup
 */
DictionaryNode *insert(DictionaryNode **dictionary, int hashSize, const char *key){
    unsigned int hashValue;
    DictionaryNode *dictionaryNode;

    if ((dictionaryNode = lookup(dictionary, hashSize, key)) == NULL ){
      dictionaryNode = (DictionaryNode *) malloc(sizeof (*dictionaryNode));
      if (dictionaryNode == NULL || (dictionaryNode->key = copyString (key)) == NULL){
          return NULL;
      }
      hashValue = hash(key) % hashSize;
      dictionaryNode->next = dictionary[hashValue];
      dictionary[hashValue] = dictionaryNode;
    }
    return dictionaryNode;
}

/**
 * Frees the dictionary
 * @pre dictionary is defined in memory
 * @param dictionary dictionary that is supposed to be freed
 * @param hashSize size of dictionary
 * @post given dictionary will be freed
 */
void freeDictionary(DictionaryNode **dictionary, int hashSize){
    int i;
    //Loop through dictionary list and free dictionary nodes
    for (i = 0; i < hashSize; i++){
      if (dictionary[i] != NULL){
          DictionaryNode *head = dictionary[i];
          DictionaryNode *current = head;
          while (current != NULL){
            DictionaryNode *temp = current;
            current = current->next;
            free(temp);
          }
          dictionary[i] = NULL;
      }
    }
}

/**
 * Copies string
 * @param s string to be copied
 * @return returns copied string
 */
char *copyString(const char *s){
    char *p;
    long len = strlen(s);
    //+1 to account for null terminator
    p = (char *) malloc(len+1);
    if (p != NULL){
      strncpy(p, s, len);
    }
    p[len] = '\0';

    return p;
}

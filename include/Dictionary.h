#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#define BIG_HASH_SIZE 20000
#define SMALL_HASH_SIZE 100

typedef struct dictionaryNode {
	char *key;
    struct dictionaryNode *next;
}DictionaryNode;

/**
 * Creates Unique hash value for given string
 * @param s string to generate hash for
 */
unsigned hash(const char *s);
/**
 * Looks up words based on key
 * @param dictionary pointer dictionaryNode array
 * @param hashSize size of the hash
 * @param key to lookup
 */
DictionaryNode *lookup(DictionaryNode **dictionary, int hashSize, const char *key);
/**
 * Inserts Dictionary node into dictionaryArray
 * @pre 'dictionary' DictionaryNode array is defined and has memory allocated to it
 * @param dictionary pointer dictionaryNode array
 * @param hashSize size of the hash
 * @param key to lookup
 */
DictionaryNode *insert(DictionaryNode **dictionary, int hashSize, const char * key);

/**
 * Frees the dictionary
 * @pre dictionary is defined in memory
 * @param dictionary dictionary that is supposed to be freed
 * @param hashSize size of dictionary
 * @post given dictionary will be freed
 */
void freeDictionary(DictionaryNode **dictionary, int hashSize);
/**
 * Copies string
 * @param s string to be copied
 * @return returns copied string
 */
char *copyString(const char *s);

#endif

// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// information about the type, size, and layout of a file

// typedef struct
// {
//    struct NODE *head;

// } __attribute__((__packed__))
// LINKEDLIST;

// typedef struct
// {
//    LINKEDLIST linkedlists[25]; // size of english alphabet -1
//    int hashFunction (char *word){
//       int resultingBucket = word[0] - 97; // need to double check so i don't get out of array bounds
//       return resultingBucket;
//    };

// } __attribute__((__packed__))
// HASHMAP;

// typedef struct
// {
//    struct NODE *head;

// } __attribute__((__packed__))
// LINKEDLIST;

// typedef struct
// {
//    char *word;
//    struct NODE *next;
// } __attribute__((__packed__))
// NODE;



// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H

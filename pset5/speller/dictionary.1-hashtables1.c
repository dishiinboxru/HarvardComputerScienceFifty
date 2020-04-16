/**
 * Implements a dictionary's functionality.
 */
/* The hash table works by taking the first character(lowercase) of the input word minus 97 and modulo 13 to determine the hash value. i.e 'a' and 'z' will be hashtable[0], 'b' and 'y' are hashtable[1]  */
#include <stdbool.h>
#include "dictionary.h"
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

 typedef struct node { //Structure that will be used for the linked list
        char word[LENGTH+1];
        struct node *next;
    } node;

    node *hashtable[13]; //This is the first node for each hashed linked list
    int wordcount = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int n = strlen(word); //Gets length of word
    string c = NULL; //Create a string variable to store lowercase word
    //loop that puts each lowercase character of word into c string.
    int ret;
    for (int i =0; i<n; i++) {
         c[i] = tolower(word[i]);
    }
    node *cursor = hashtable[(c[0]-97)%13]; //cursor is head of linked list
    while (cursor != NULL) {
        ret = strcmp(c, cursor->word);
        if (ret < 0 || ret > 0 ) {
        cursor = cursor->next;
        }
        else {
            return true;
        }
    }
       return false;


}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{

   //node *head; //Head of linked list
   // node *previous; //previously added value of linked list
    node *nword; //new word node
    string word = NULL;
    FILE *fp; //pointer to file we are opening
    fp = fopen(dictionary, "r"); //open the file in read only mode

    while (fscanf(fp, "%s", word) != EOF ) { //will scan through each word in the file and add it to word until EOF is reached.
/*
If the first character in the hashtable.value is not the same as the new word then there is no value in it.
Our hashfunction hashes the first letter of the word to determine in which part of the hashtable the word will be stored.*/

        if (hashtable[(word[0]-97)%13]->word[0] != word[0]) { //if the first character of the first node is not equal to the first character of the user typed word then...put that word in the first node

            hashtable[(word[0]-97)%13] = malloc(sizeof(node));
            if (hashtable[(word[0]-97)%13] != NULL) {
            strcpy(hashtable[(word[0]-97)%13]->word, word);
            hashtable[(word[0]-97)%13]->next = NULL;
            wordcount++;
            return true;
            }
            else {
                unload();
                return false;
            }
        }
        else { // there is already at least one value in the linked list so we will add on to it
            nword = malloc(sizeof(node)); //making links in the hash table. Hashtable[] is the header here and always points to first link.
            if (nword != NULL) {
            strcpy(nword->word, word);
            nword->next = hashtable[(word[0]-97)%13];
            hashtable[(word[0]-97)%13] = nword;
            wordcount++;
            return true;
            }
            else {
                unload();
                return false;
            }


        }

    }
  return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return wordcount;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    int freecount = 0; // the number of nodes free'd
    for (int i = 0; i < 12; i++) {
        node *cursor = hashtable[i];
        while (cursor != NULL) {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
            freecount++;
        }
    }
    if (wordcount == freecount) { //if all the words in dictonary have been free'd return true
        return true;
    }
    else {
        return false;
    }

}
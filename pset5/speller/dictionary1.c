// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Create a hashMap


    //open the dictionary file

    //create a temp word holder ( are you sure you will need that ?)
    char *word;

    //Scan dictionary word by word and load those words as nodes into corresponding entry in the linked list of the hashMap (char FirstLetter, LinkedList char *word)
    while (fscanf( file , "%s" , word ) != EOF) //iterating over the file
    {
        //here goes sorting and inserting logic
        NODE *new_node = malloc(sizeof(NODE));
        if (new_node == NULL) //checking if there is enough memory
        {
            unload;
            return false;
        }
        //copying the word
        strcopy(new_node->word, word);


        //inserting it into the linked list in the hashMap ( 2 methods implementation required - at first - hash-function in map, then - linkedList insertion.  )
        //thus here we call hashmap insert, which calculates hash
        //then call the insert method at the relevant linked list
        // which in turn performs that first node pointer shift, when header starts to point at new_node and new_node - at former first node. I can't wrap my head around how to do that without providing names to those nodes and their pointers

        //that' seems to be all

        // ? maybe some counter of the words is spposed to be implemented here so that size function may access it ?


    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO - perhaps just will need to replace names of arrays with my own structures names

    // Free memory
    node *ptr = numbers; //from linked list version
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }

    // Free memory - from simple array version.
    if (numbers)
    {
        free(numbers);
    }
    return false;
}

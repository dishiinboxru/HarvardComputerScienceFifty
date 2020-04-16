#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    char *word;
    struct node *next;
}
node;

int main(int argc, char *argv[])
{

    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./dictToList small\n");
        return 1;
    }

    char *infile = argv[1];

    //opening a file
    FILE *file = fopen(infile, "r");

    // memory for words
    node *words = NULL;

    // char temp[20]; // change from *word to word[20] to see if it works
    char entry[32] ;
    char test[32];

    // Prompt for words (until EOF)
    while (fscanf( file , "%s" , entry ) != EOF) //iterating over the file
    {
        printf (" given entry is %s\n" , entry);

            // Allocate space for word
            node *n = malloc(sizeof(node));

            if (n == NULL) // try equals NUll
            {
                return 1;
            }

           //checking if something wrong with strcpy
           strcpy(test, entry);
           printf ("%s \n" , test);

            strcpy(n->word, entry); // if un commented - read all words, but outputs rom list just last one
            n->next = NULL;

            if (words)
            {
                for (node *ptr = words; ptr != NULL; ptr = ptr->next)
                {
                    if (!ptr->next)
                    {
                        ptr->next = n;
                        break;
                    }
                }
            }
            else
            {
                words = n;
            }
        }

        // Print words
    printf("\n");
    for (node *ptr = words; ptr != NULL; ptr = ptr->next)
    {
        printf("%s\n", ptr->word);
    }

    // Free memory
    node *ptr = words;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
     }
}
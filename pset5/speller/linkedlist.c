#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct node
{
    char *word;
    struct node *next;
}
node;

int main(void)
{
    // memory for words
    node *words = NULL;

    // Prompt for words (until EOF)
    while (true)
    {

        // Prompt for a word
        char *word = get_string("please enter a word: ");
        char *terminator = "end";

        // Check for EOF
        if (strcmp( word , terminator) == 0)
        {
            break;
        }

            // Allocate space for word
            node *n = malloc(sizeof(node));
            if (!n)
            {
                return 1;
            }

            // Add word to list
            n->word = word;
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
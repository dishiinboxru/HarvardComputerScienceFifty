#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

// command line arguement should be included in the command. Thus start with a fancy line

int main(int argc, string argv[])

// prompt user for string of plain text
{

 string s = get_string("Enter plaintext: ");

    // ensure string was read
    if (s == NULL)
    {
        return 1;
    }

 //getting the key
int words =  argc ;

    string next = get_string("You just entered %s and %s . They are %i words totally. Enter a new string: ", s , argv[1] , words );

    if (next == NULL)
    {
        return 1;
    }

    printf("Your last string was %s\n", next);
}
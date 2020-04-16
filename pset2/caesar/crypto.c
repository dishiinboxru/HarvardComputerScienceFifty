// how to make a print output of ASCII ? or should I just convert letter => ASCI => ASCI-creypto => letter-crypto
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])

// prompt user for string of plain text
{

 string s = get_string("Enter string: ");

    // ensure string was read
    if (s == NULL)
    {
        return 1;
    }

 //getting the key
int words =  argc ;

   string text =  argv[1] ;
char a = text[0] + 2 ;
char b = text[1] + 2 ;
char c = text + 2 ;

    printf("Spells c% c% %c \n cypher c% c% c% ",  text[0] , text[1] , text[2] , a , b , c  );



}
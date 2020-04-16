#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
   int count = argc ;

   if (count != 2)
  {
      printf("WARNING ! Usage: ./caesar k\n");
return 1;
  }

   else
   {
    string plain = get_string("Enter plaintext: ");




int key = atoi(argv[1]);


printf("outro cyphertext :") ;

    for (int crypto = 0 ; crypto < strlen(plain); crypto++)
        {
             if(isalpha(plain[crypto]))
    {
        if(islower(plain[crypto]))
        {
            char cipher = ((plain[crypto] - 97 + key) % 26) + 97;
            printf("%c", cipher);
        }
        if(isupper(plain[crypto]))
        {
            char cipher = ((plain[crypto] - 65 + key) % 26) + 65;
            printf("%c", cipher);
        }
    }
    else
    {
        printf("%c", plain[crypto]);
    }
        }

        printf("\n") ;


}
}
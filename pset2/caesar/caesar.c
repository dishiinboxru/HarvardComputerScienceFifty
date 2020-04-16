#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//comand line input

int main(int argc, string argv[])
{
    int count = argc ;

//check the input for validity
    if (count != 2)
    {
        printf("WARNING ! Usage: ./caesar k\n");
        return 1;
    }

//prompting for input
    else
    {
        string plain = get_string("plaintext: ");

//getting the key
        int key = atoi(argv[1]);

//cryptography
        printf("ciphertext: ") ;

        for (int crypto = 0 ; crypto < strlen(plain); crypto++)
        {
            if (isalpha(plain[crypto]))
            {
                if (islower(plain[crypto]))
                {
                    char cipher = ((plain[crypto] - 97 + key) % 26) + 97;
                    printf("%c", cipher);
                }
                if (isupper(plain[crypto]))
                {
                    char cipher = ((plain[crypto] - 65 + key) % 26) + 65;
                    printf("%c", cipher);
                }
            }
            //managing the non-letters
            else
            {
                printf("%c", plain[crypto]);
            }
        }

        printf("\n") ;


    }
}
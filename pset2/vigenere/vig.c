    //!!! current stage - managing wrapping aroun the code. It started to skip first spaces, but now it deletes letters as well. Perhaps
    //must find a better position. and behaves strangely at all!!!

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
        printf("WARNING ! Usage: ./vigenere./ ABC\n");
        return 1;
    }


    string plain = get_string("plaintext: ");
    string code = argv[1];

     printf("ciphertext: ") ;
        int shuffle = 0;
        int length = strlen(code);

        for (int crypto = 0 ; crypto < strlen(plain); crypto++)
        {

             int key = (int) code[shuffle % length];


            if (isalpha(plain[crypto]))
            {

                 //conditions for upper and lower case key to make them similar shifts

                //!!! next to do - need to input isblank operator to avoid wasting code on spaces !!!

                if(isupper(code[shuffle]))
                 {
                     int coding = key - 13 ;

                     if (islower(plain[crypto]))
                {

                    char cipher = ((plain[crypto] - 97 + coding) % 26) + 97;
                    printf("%c", cipher);
                    shuffle++;

                }
                if (isupper(plain[crypto]))
                {

                    char cipher = ((plain[crypto] - 65 + coding) % 26) + 65;
                    printf("%c", cipher);
                    shuffle++;

                }

                 }
                 if(islower(code[shuffle]))
                 {
                     int coding = key - 19 ;

                     if (islower(plain[crypto]))
                {

                    char cipher = ((plain[crypto] - 97 + coding) % 26) + 97;
                    printf("%c", cipher);
                    shuffle++;
                }
                if (isupper(plain[crypto]))
                {

                    char cipher = ((plain[crypto] - 65 + coding) % 26) + 65;
                    printf("%c", cipher);
                    shuffle++;
                }
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
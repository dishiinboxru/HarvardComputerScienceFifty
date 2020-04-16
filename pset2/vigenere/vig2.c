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

          // Convert the keyword to all uppercase letters.
        for(int i = 0; code[i]; i++)
        {
            code[i] = toupper(code[i]);
        }



        for (int crypto = 0 ; crypto < strlen(plain); crypto++)
        {

            char key =  code[(shuffle % strlen(code))]  ;

                            //conditions for upper and lower case key to make them similar shifts


                    if (islower(plain[crypto]))
                {

                    char cipher = ((plain[crypto] - 97 + (key - 65)  ) % 26) + 97;
                    printf("%c", cipher);
                    shuffle++;

                }
                else if (isupper(plain[crypto]))
                {

                    char cipher = ((plain[crypto] - 65 + (key - 65) ) % 26) + 97;
                    printf("%c", cipher);
                    shuffle++;



                }





               //managing the non-letters

            else
            {
                printf("%c", plain[crypto]);
            }


        }





        printf("\n") ;
}

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//comand line input

int main(int argc, string argv[])
{
    string note = argv[1];

        string X = strtok(note, "/");
        string Y = strtok(NULL, "/");

printf("the duration entered is %s. There are %i words. first is %s , second is %s \n" , note , argc, X , Y );

     int first = atoi(X);
     int second = atoi (Y);

printf("processing as integers. First integer is %i, second is %i \n " , first , second );
        int base = 8;
        int modifier = base / second;
        int result = first * modifier;

printf("processng results in  %i \n " , result );

//     // TODO
//     string X = strtok(note, "/");
//     string Y = strtok(NULL, "/");

//     //convert strings to ints
//     int first = atoi(X);
//     int second = atoi (Y);

//     //math resulting in number of eights
//     int base = 8;
//     int modifier = base / second;
//   // int result = X * modifier;
//   int result = 10;

//     return result;


}
#include <stdio.h>
#include <cs50.h>

int main(void)
{
//taking cash from user
 int change;


    do
    {
        printf("how much change is owed: ");
        change  = get_float();
    }

    while (change < 0 );
    // converting cash into workable number
     int cents
     cents = change * 100

    // logical and math operations


// outputting result in coins
int coins;
coins = change*100/25 ;
printf(" %i \n" , coins) ;
    }



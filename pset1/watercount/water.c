#include <stdio.h>
#include <cs50.h>

int main (void)
{
    //prompt user for water
    int minutes=get_int ("How long do you take shower ? " );

    // print number of bottles
    int bottles = minutes * 12 ;

    printf (" You waste %i bottles of water\n" , bottles) ;
}
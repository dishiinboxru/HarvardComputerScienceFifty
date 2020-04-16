//mario

#include <stdio.h>
#include <cs50.h>

int main (void)
{

    //prompt user for n , i.e. height
    int h=get_int("Height: " ) ;

    while (h > 0  && h < 23)

    //printing pyramid
    for (int i=1; i < h ; i++)
{
        printf ("#" ) ;
}


}
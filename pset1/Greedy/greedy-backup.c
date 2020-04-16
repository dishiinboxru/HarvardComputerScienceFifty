#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;

    // requests from the user the amount of change due
    do
    {
        printf("how much change is owed: ");
        change  = get_float();
    }
    while (change < 0.0);

    // converts user input to int and calculates number of each coin due
    int input = round(change * 100);
    int quarters = input / 25;
    int dimes = (input % 25) / 10;
    int nickles = (input % 25 % 10) / 5;
    int pennies = (input % 5) / 1;

    // computes total number of coins due and prints to screen
    int total = quarters + dimes + nickles + pennies;
    printf("%d\n", total);
}
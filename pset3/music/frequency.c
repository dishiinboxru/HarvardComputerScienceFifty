#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
//comand line input , expect either XYZ or XY

int main(int argc, string argv[])
{
    // check if it's XYZ or XY
     string input = argv[1];
        int inputLength = strlen(input);

       // int note = 0;
        int octave = 0;
        int octaveLength = 12;
        int baseOctave = 4;

        int steps = 0;

     if (strlen(input) == 2)
     {
      char letter = input[0];
      //turns chars into ints via ASCII conversion.
      octave = input [1] -'0';
      //counting octave steps
      octave -= baseOctave;
      steps += octaveLength * octave;

      if (letter == 'B'){
       steps +=2;
      }
      if (letter == 'C'){
       steps -=9;
      }if (letter == 'D'){
       steps -=7;
      }if (letter == 'E'){
       steps -=5;
      }if (letter == 'F'){
       steps -=4;
      }if (letter == 'G'){
       steps -=2;
      }

        printf("the note entered is %s. . first is %c , second is %c . trying second as resulting interger -- %i \n Steps from A4 equal %i \n" , input , input[0] , input[1], octave, steps );
         //convert elements to appropriate ints

     }
     if(strlen(input) == 3)
     {

      char letter = input[0];
      //turns chars into ints via ASCII conversion.
      octave = input [2] -'0';
      //counting octave steps
      octave -= baseOctave;
      //octave adjustments
      steps += octaveLength * octave;

      //letter adjustments
      if (letter == 'B'){
       steps +=2;
      }
      if (letter == 'C'){
       steps -=9;
      }if (letter == 'D'){
       steps -=7;
      }if (letter == 'E'){
       steps -=5;
      }if (letter == 'F'){
       steps -=4;
      }if (letter == 'G'){
       steps -=2;
      }

      //accidental adjustments

      if (input[1] == 'b'){
       steps -=1;
      }if (input[1] == '#'){
       steps +=1;
      }

         printf("the note entered is %s. it's %i chars long ( three expected). first is %c , second is %c , third is %c \n Steps from A4 equal %i \n",  input , inputLength, input[0] , input[1], input [2], steps );
          //convert elements to appropriate ints
     }

    //do math (can be universal for both - just name elements accordingly)-number of steps from A4
    double A4frequency =440.00;
    double divider = 12;
    double power = steps/divider;
    double amplifier = 2;
    double modifier = pow(amplifier, power) ;


     double frequency = A4frequency*modifier;
    printf("Moment of truth ! power is %lf, modifier is %lf , Thus - Note %s has got frequency %lf . expected for B5 is 987.77 .  \n" ,   power, modifier, input, frequency );

    return frequency;

}
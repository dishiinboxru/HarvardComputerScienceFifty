// recovers a bunch of JPEGs from a raw memory

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    //  filenames -
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file

    unsigned char buffer[512] ;
    printf("buffer-512 initialised \n");
    int magicNumbersDetectedCounter = 0;
    char filename[512];
    printf("detector ready \n");

    FILE *outptr; // trying to initialise outside inner while-loop for visibility
    while (fread(&buffer, 1, 512, inptr) == 512)
    {


        printf("getting into first while loop \n");

        //alternative option for reading 512bytes in a row
        // printf ("number of bytes read is  %lu \n", fread(&buffer, 1 , 512, inptr));

        //checking if this block starts with JPEG magic numbers (converting from hexi to decimal)
        // if ( buffer[0] == 255 && buffer[1] == 216 && buffer[2] ==255 )
        if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255)
        {
            sprintf(filename, "%03i.jpg", magicNumbersDetectedCounter);

            printf("filename assigned is %s \n", filename);

            outptr = fopen(filename, "w");
            printf("FILE *outptr works \n");

            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 3;
            }
            magicNumbersDetectedCounter ++;

            printf("magic number verification \n");

            while (true)
            {
                printf("getting into second while loop \n");
                for (int j = 0; j < 512; j++)
                {
                    fwrite(&buffer[j], 1, 1, outptr); //guess that also can be a single liner without for-loop
                }
                printf("writing from the bufferblock  into jpg file \n");

                printf("read the buffer again \n");
                if (fread(&buffer, 1, 512, inptr) != 512) // try to get EoF detection inside that loop
                {
                    fseek(inptr, -512, SEEK_CUR); // attempt to rewind a block thus not to miss every other jpg
                    break;
                }

                if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255)// putting reversed condition in the while loop(didn' work)
                {
                    //   printf("supposedly escaping all those loops after 2nd magic number detection \n");
                    fseek(inptr, -512, SEEK_CUR);  // attempt to rewind a block thus not to miss every other jpg
                    break;
                }
            }
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    printf("finishing writing after detecting EoF\n");

    // success
    return 0;
}

// resizes a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    //format ratio
    float ratio = atof(argv[1]);

    if (ratio < 1 || ratio > 100)
    {
    printf("%f not within 0-100 range \n", ratio);
    return 2;
    }


    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    BITMAPFILEHEADER bfOutput = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    BITMAPINFOHEADER biOutput = bi;

     // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }





    //modifying infoheaders
    biOutput.biWidth *= ratio;
    biOutput.biHeight *= ratio;

    printf("reduced width is %i , expected is 4 . reduced height is %i , expected is -4\n . original value are  w = %i , h = %i\n " , biOutput.biWidth , biOutput.biHeight, bi.biWidth, bi.biHeight);
    int paddingOutput = (4 - (biOutput.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    biOutput.biSizeImage = ((biOutput.biWidth * sizeof(RGBTRIPLE)) + paddingOutput) *abs(biOutput.biHeight);


    //fileheader update
    bfOutput.bfSize = biOutput.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bfOutput, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biOutput, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int paddingInput = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    printf(" padding are - for input - %i , for output - %i \n " , paddingInput, paddingOutput );
 //TODO - here should start if-cases for ratio >1 and 0-1. ? what to do with negative ratio ?

    if (ratio >= 1.0)
    {
       // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {

        RGBTRIPLE scanline[bi.biWidth];

             // iterate over pixels in scanline and putting them into an array for further scaling
            for (int j = 0; j < bi.biWidth; j++)
            {
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                scanline[j] = triple;
               // fread(&scanline[j], sizeof(RGBTRIPLE), 1, inptr); // fix of smallbmp attempt
            }
            // skip over padding, if any - first position causing problems
                   fseek(inptr, paddingInput, SEEK_CUR);

            //repeat each row ratio times
            for (int y = 0 ; y < ratio; y++)
            {
                for (int x = 0; x < bi.biWidth; x++) // iterate over pixels in a scanline array
                {
                    for (int r =0 ; r <ratio ; r ++) //repeating each pixel from scanline ratio time
                    {
                        fwrite (&scanline[x] , sizeof(RGBTRIPLE), 1, outptr);
                    }

                }
                //padding insert

                     // skip over padding, if any - first position causing problems
                   //fseek(inptr, paddingInput, SEEK_CUR);

               // then add it back (to demonstrate how)

                      for (int k = 0; k < paddingOutput; k++) //trying to fix issue with 0 padding on the ouptut ( k<= paddingOutput - didn't work)
                {
                fputc(0x00, outptr);
                }


            }
    }

    }
    // else /// version for "more comfortable " - which is supposed to work with floats for more challenging option.
    // {
    //     for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    // {
    //     // iterate over pixels in scanline
    //     for (int j = 0; j < bi.biWidth; j++)
    //     {
    //         // temporary storage
    //         RGBTRIPLE triple;

    //         // read RGB triple from infile
    //         //loop to overwrite triple 1/ratio times
    //         for (int l=0 ; l< (1/ratio); l ++)
    //         {
    //             fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    //         }
    //         float reverseratio = 1/ratio;
    //         printf (" scaling ratio is  %f, shrinking ratio is %f \n" , ratio , reverseratio );


    //         // write RGB triple to outfile
    //         fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
    //     }

    //   //padding insert

    //                  // skip over padding, if any
    //                 fseek(inptr, paddingInput, SEEK_CUR);

    //             // then add it back (to demonstrate how)
    //             for (int k = 0; k < paddingOutput; k++)
    //             {
    //             fputc(0x00, outptr);
    //             }
    // }


    //     // iterate over infile's scanlines skipping each 1/ratio
    // // for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i += (1/ratio))
    // // {

    // // }

    // }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

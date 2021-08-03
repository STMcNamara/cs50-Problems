// Copies a BMP file

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

    // remember filenames
    int factor = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // check factor (argv[1]) is an int 0 < n <= 100
    if (factor < 1 || factor > 100)
    {
        fprintf(stderr, "Usage: 0 < resize factor <= 100\n");
        return 1;
    }

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

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // remember intial padding width and height (before changing biWidth)
    int paddingi = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int biWidthi = bi.biWidth;
    int biHeighti = bi.biHeight;

    // calculate oringinal width + paddingin bytes
    int biWidthB = biWidthi * sizeof(RGBTRIPLE) + paddingi;

    // calulate new image height and width (BITMAPINFOHEADER variables) from factor
    bi.biWidth *= factor;
    bi.biHeight *= factor;

    // calculate new padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;



    // claculate new image and file sizes (BITMAPINFOHEADER and BITMAPFILEHEADER variables)
    bi.biSizeImage = ((bi.biWidth * sizeof(RGBTRIPLE)) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //... TO READ FROM infile

    //Initialise repeat row tracker
    int row = 0;

    // iterate over outfiles scanlines - TODO
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {

        // iterate over pixels in in the imput file scanline
        for (int j = 0; j < biWidthi; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile once
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile factor number of times
            for (int x = 0; x < factor; x++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        // skip over inital padding, if any
        fseek(inptr, paddingi, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }

        //increment row
        row++;

        //If more rows to write - send the pointer back width btyes
        if (row < factor)
        {
            fseek(inptr, - biWidthB, SEEK_CUR);
        }
        else
        {
            row = 0;
        }


    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

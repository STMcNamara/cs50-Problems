#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: single input file onlyn");
        return 1;
    }

    //Remember filenames
    char *raw = argv[1];

    //open the card file
    FILE *rawptr = fopen(raw, "r");
    if (rawptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", raw);
        return 2;
    }

    //Create buffer block and file counter, outname
    unsigned char *buffer = malloc(512);
    int fileno = 0;
    char outname[8];
    FILE *img = NULL;

    // while not at the end of the card
    while ((fread(buffer, sizeof(buffer), 1, rawptr)) == 1)
    {
        //Check if the start of new JPEG
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            //If yes:
            //Close file, if opened
            if (img != NULL)
            {
                fclose(img);
            }

            //create new file
            sprintf(outname, "%03i.jpg", fileno);
            img = fopen(outname, "w");
            fileno++;

            //And write data
            fwrite(buffer, sizeof(buffer), 1, img);
        }
        // If not the start of a new JPEG
        else
        {
            // Check that we have already found a file and write
            if (fileno > 0)
            {
                fwrite(buffer, sizeof(buffer), 1, img);
            }
            // Otherwise do nothing
        }
    }

    // close all open files
    fclose(rawptr);

    // close outfile
    fclose(img);

    // success
    return 0;

}
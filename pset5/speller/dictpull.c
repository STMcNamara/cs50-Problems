// Test to figure out how to pull words from a dictionary type
// ONLY WORKS IN SPELLER FOLDER

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for the correct number of args
    if (argc != 2)
    {
        printf("Usage: dictpull [dictionary] text\n");
        return 1;
    }

    // Remember filenames
    char *dict = argv[1];

    // Open the file
    FILE *dptr = fopen(dict, "r");
    if (dptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dict);
        return 2;
    }

    // Initialise word, index, and word counter
    char word[45];
    int index = 0, wordcount = 0;

    // Select each char through the dictionary
    for (int letter = fgetc(dptr); letter != EOF; letter = fgetc(dptr))
    {
        // Check if at end of line
        if (letter != '\n')
        {
            word[index] = letter;
            index++;
        }
        else
        {
            // terminate the current word and reset index
            word[index] = '\0';
            index  = 0;

            // Increment word counter
            wordcount++;

            //print the word and the word count
            printf("Word %i is %s\n", wordcount, word);

        }
    }
}
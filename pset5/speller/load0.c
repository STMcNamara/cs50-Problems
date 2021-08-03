// Create a single linked list of word from a text file list of word and then prints them back
// Based on dictpull.c
// ONLY WORKS IN SPELLER FOLDER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Things that will be defined elsewhere in main code
#define LENGTH 45

//Define node Struct for words
typedef struct node
{
    char word[LENGTH+1];
    struct node *next;
}
w_node;

//Set the head variable as global
w_node *listhead;

//Set word count as global

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open the file
    // Open the file
    FILE *dptr = fopen(dictionary, "r");
    if (dptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return 2;
    }

    // Get words one at a time from the dictionary

    // Initialise dword, index, and word counter
    char dword[LENGTH];
    int index = 0, wordcount = 0;

    // Get the word one at a time
    for (int letter = fgetc(dptr); letter != EOF; letter = fgetc(dptr))
    {
        // Check if at end of line
        if (letter != '\n')
        {
            dword[index] = letter;
            index++;
        }
        else
        {
            // We have a word, and need to do something with it
            // terminate the current word and reset index
            dword[index] = '\0';
            index  = 0;

            // Increment word counter
            wordcount++;


            // Create a temporary node for that word and allocate memory
            w_node *tempnode = malloc(sizeof(w_node));
            if (tempnode == NULL)
            {
                return false;
            }

            // Copy dword into node word and point to NULL
            strcpy(tempnode->word, dword);
            tempnode -> next = NULL;

            //If first time operation make pointer to head and point to null
            if (listhead == NULL)
            {
                listhead = tempnode;
            }
            //Otherwise point to head, then make head
            else
            {
                //point new node to head
                tempnode -> next = listhead;
                listhead = tempnode;
            }
        }
    }
    return 1;
}

//Main function - call the load function and print
int main(int argc, char *argv[])
{
    // Check for the correct number of args
    if (argc != 2)
    {
        printf("Usage: dictpull [dictionary] text\n");
        return 1;
    }

    // Remember filenames
    char *dictionary = argv[1];

    // call the load function - TODO
    load(dictionary);

    // print one at a time from the loaded dictionary - TODO
    w_node *printpointer = listhead;

    while (printpointer != NULL)
    {
        printf("%s\n", printpointer -> word);
        printpointer = printpointer -> next;
    }
}

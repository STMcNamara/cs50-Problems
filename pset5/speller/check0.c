// Built upon load2, with functon of check included
// Create hash table array of linked lists, then prompt the user for a word hash and return words with that hash
// Solution for multiple functions
// Evolution of load0, and
// Based on dictpull.c
// ONLY WORKS IN SPELLER FOLDER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <cs50.h>
#include <ctype.h>

//Things that will be defined elsewhere in main code
#define LENGTH 45 //Max word length -> in dictionary.h for main implementation

//My definitions
#define TABLESIZE 100 //Size of the hashtable

//Define node Struct for words
typedef struct node
{
    char word[LENGTH+1];
    struct node *next;
}
w_node;

// Create the global variables
w_node* hashtable[TABLESIZE]; //hash table as an array of nodes
int wordcount;


// Define the hash function -> takes a word
// Utilises the djb2 hash from http://www.cse.yorku.ca/~oz/hash.html
int hash33(char* word)
{
    unsigned int hash = 5381;

    for (const char* c = word; *c != '\0'; c++)
    {
        hash = ((hash << 5) + hash) + tolower(*c); /* hash * 33 + c */
    }
    return hash%TABLESIZE;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open the file
    FILE *dptr = fopen(dictionary, "r");
    if (dptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return 2;
    }

    // Get words one at a time from the dictionary

    // Initialise dword, index, word counter, hashbucket
    char dword[LENGTH + 1];
    int index = 0;
    int hashval;
    wordcount = 0;

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

            // Hash the word
            hashval = hash33(dword);

            // Create a temporary node for that word and allocate memory
            w_node *tempnode = malloc(sizeof(w_node));
            if (tempnode == NULL)
            {
                return false;
            }

            // Copy dword into node word and point to NULL
            strcpy(tempnode->word, dword);
            tempnode -> next = NULL;

            // Index into array
            // If first time operation make hashpointer to temp to head and point to null
            if (hashtable[hashval] == NULL)
            {
                hashtable[hashval] = tempnode;
            }

            //Otherwise point to existing hashtable head, then make head
            else
            {
                //point new node to head
                tempnode -> next = hashtable[hashval];
                hashtable[hashval] = tempnode;
            }
        }
    }
    return 1;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char cword[LENGTH+1];
    strcpy(cword, word);

    int wordhash = hash33(cword);
    printf("The hash function is %i\n", wordhash);

    // Go to the  location and navigate along
    w_node *cursor = hashtable[wordhash];

    while (cursor != NULL)
    {
        // If strings match return true
        if (strcasecmp(cword, cursor->word) == 0)
        {
            return true;
        }
        // Move to next node
        else
        {
            cursor = cursor -> next;
        }
    }
    // If NULL return false
    return false;
}


//Main function - call the load function and request user word
//Use the check function to see if in dictionary
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

    // call the load function
    load(dictionary);

    printf("The number of words loaded is: %i\n", wordcount);

    //Request a word from the user and use check function to determine if in dictionary
    string word = get_string("Enter word to be hashed: ");

    if (check(word) == true)
    {
        printf("Word is in dictionary\n");
    }
    else
    {
        printf("Word is not in dictionary\n");
    }
}
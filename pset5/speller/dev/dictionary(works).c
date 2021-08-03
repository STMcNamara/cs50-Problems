// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <cs50.h>
#include <ctype.h>

#include "dictionary.h"

//Definition of constants for dictionary.c
#define TABLESIZE 100000 //Size of the hashtable

//Define node Struct for words
typedef struct node
{
    char word[LENGTH+1];
    struct node *next;
}
w_node;

// Create the global variables
w_node* hashtable[TABLESIZE]; //hash table as an array of nodes
int wordcount; // A tracker to be used when loading the dictionary

// Returns a hashed integer for the word provided
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

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char cword[LENGTH+1];
    strcpy(cword, word);

    int wordhash = hash33(cword);

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

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open the file
    FILE *dptr = fopen(dictionary, "r");
    if (dptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
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
            //free(tempnode);
        }


    }

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (wordcount == 0)
    {
        return 0;
    }
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // For each head in the table
    for (int i = 0; i == TABLESIZE - 1; i++)
    {
        w_node *cursor = hashtable[i];

        // Iterate and free until end of linked list
        while (cursor != NULL)
        {
            w_node* temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }

    }
return true;
}

// Simple test of too lower functionality for a word

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>


int main(void)
{
    // Get a string from the user
    string word = get_string("Enter word to be switched to lower case: ");

    // Apply lolower one char at a time
    for (int i = 0; word[i]; i++)
    {
        word[i] = tolower(word[i]);
    }
    printf("Word in lower case is %s\n", word);

}
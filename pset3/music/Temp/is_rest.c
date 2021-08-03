#include <cs50.h>
#include <string.h>
#include <stdio.h>



// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strlen(s) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(void)
{
    string s = "i";
    if (is_rest(s))
    {
        printf("true");
    }
    else
    {
        printf("false");
    }
}
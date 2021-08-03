#include <cs50.h>
#include <string.h>
#include <stdio.h>

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int num = fraction[0] - 48;
    int den = fraction[2] - 48;

    while(den != 8)
    {
        num *= 2;
        den *= 2;
    }

   return num;
}

int main(void)
{
    string x = "3/4";
    printf("%i\n", duration(x));
}
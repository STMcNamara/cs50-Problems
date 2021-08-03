#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //intitialise height outside of allowed values
    int h = -1;

    // while height outside limits, request height from the user
    while (h < 0 || h > 23)
    {
        h = get_int("Height: ");
        // test input: printf("%i\n", h);
    }
    // loop acrross each row (r) h number of times, starting at the top
    for (int r = h; r > 0; r--)
    {
        // On each position p, row print h - r blank, then r#
        for (int p = 0; p < h + 1; p++)
        {
            if (p < r - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }

}
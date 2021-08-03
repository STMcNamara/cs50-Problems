#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //Initialise float c
    float c = -1.0;

    //While loop if c not greater than 0. Re-prompt the user
    while (c < 0.0)
    {
        c = get_float("Change owed: ");
    }

    //Cast input to interger cents, s
    int s = round(c * 100);

    // Initialise no. coin counter, n
    int n = 0;


    //Use a while loop t0 run for c > 0.0
    while (s > 0)
    {
        //If s => 25, substact 25 from s, add 1 to n
        if (s >= 25)
        {
            s -= 25;
            n++;
        }

        //Else if s => 10, subtract 10 from s, add 1 to n etc
        else if (s >= 10)
        {
            s -= 10;
            n++;
        }
        else if (s >= 5)
        {
            s -= 5;
            n++;
        }
        else
        {
            s -= 1;
            n++;
        }

    }

    //print n
    printf("%i\n", n);
}
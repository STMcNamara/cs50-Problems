#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Return 1 if argc != 2, initialise k if 2
    if (argc != 2)
    {
        printf("Please provide 1 input only\n");
        return 1;
    }

    string key = argv[1];

    //Test the key for appropriateness (only letters)
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Please provide only alphabetical characters only\n");
            return 1;
        }
    }

    //Request plaintext from user an initialise c, p & k strings
    string p = get_string("plaintext: ");
    string c = p;
    int ki = 0;

    int j = 0;

    //For each element in p, conduct the conversion once with an if statement
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        //Calculate ki from key j position and add 1 to j if a letter is being evaluated
        if (isalpha(p[i]))
        {
            if (islower(key[j]))
            {
                ki = key[j] - 97;
            }
            else
            {
                ki = key[j] - 65;
            }

            if (j < strlen(key) - 1)
            {
                j++;
            }
            else
            {
                j = 0;
            }
        }

        //One way for lower
        if (islower(p[i]))
        {
            if (p[i] + ki > 'z')
            {
                c[i] = 'a' - 1 + (ki - ('z' - p[i]));
            }
            else
            {
                c[i] = p[i] + ki;
            }
        }
        //One way for upper
        else if (isupper(p[i]))
        {
            if (p[i] + ki > 'Z')
            {
                c[i] = 'A' - 1 + (ki - ('Z' - p[i]));
            }
            else
            {
                c[i] = p[i] + ki;
            }
        }

    }
    printf("ciphertext: %s\n", c);
}

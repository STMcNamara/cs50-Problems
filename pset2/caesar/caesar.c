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

    //Request plaintext from user an initialise c, p & k variables
    string p = get_string("plaintext: ");
    string c = p;
    int k = (atoi(argv[1])) % 26;

    //For each element in p, conduct the conversion once with an if statement
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        //One way for lower
        if (islower(p[i]))
        {
            if (p[i] + k > 'z')
            {
                c[i] = 'a' - 1 + (k - ('z' - p[i]));
            }
            else
            {
                c[i] = p[i] + k;
            }
        }
        //One way for upper
        else if (isupper(p[i]))
        {
            if (p[i] + k > 'Z')
            {
                c[i] = 'A' - 1 + (k - ('Z' - p[i]));
            }
            else
            {
                c[i] = p[i] + k;
            }
        }
    }
    printf("ciphertext: %s\n", c);
}

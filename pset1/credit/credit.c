#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{

    //Request user input - consider what checks are required
    long long cardno = get_long_long("Number: ");

    //Initialise working variables
    long long length = 0;
    long long sumsingle = 0;
    long long sumdub = 0;
    long long singles = cardno;
    long long doubles = cardno / 10;
    long long lennum = cardno;

    //Calculate sum of singles
    while (singles != 0)
    {

        //Sum alt digits starting with last
        sumsingle += singles % 10;
        //printf("digit = %lli\n", singles%10);
        singles /= 100;
        //printf("sumsingle = %lli\n", sumsingle);
    }
    //Calculate sum of doubles
    while (doubles != 0)
    {
        long long dubvalue = (doubles % 10) * 2;
        sumdub += dubvalue % 10 + (dubvalue / 10) % 10;
        //printf("digit = %lli\n", doubles%10);
        doubles /= 100;
        //printf("sumdouble = %lli\n", sumdub);
    }


    //Calulate length
    while (lennum != 0)
    {
        length ++;
        lennum /= 10;
        //printf("length = %lli\n", length);
    }

    //Determine 1st and 2nd digits
    long long first = cardno / pow(10, length - 1);
    long long second = cardno / pow(10, length - 2);
    //printf("1stnum = %lli\n", first);
    //printf("2ndnum = %lli\n", second);

    //Check if valid luhn
    if ((sumsingle + sumdub) % 10 == 0)
    {
        //Check if AMEX
        if (length == 15 && (second == 34 || second == 37))
        {
            printf("AMEX\n");
        }
        //Check if MASTERCARD
        else if (length == 16 && (second == 51 || second == 52 || second == 53 || second == 54 || second == 55))
        {
            printf("MASTERCARD\n");
        }
        //Check if VISA
        else if ((length == 16 || length == 13) && first == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }




}
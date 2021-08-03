// Helper functions for music

#include <cs50.h>
#include <string.h>
#include "helpers.h"
#include <math.h>


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int num = fraction[0] - 48;
    int den = fraction[2] - 48;

    while (den != 8)
    {
        num *= 2;
        den *= 2;
    }

    return num;

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    //Apply shift due to octaves
    int oct = note[strlen(note) - 1] - 48;

    float freq = 440 * pow(2, oct - 4);

    //Apply shift due to accidentals
    if (note[1] == '#')
    {
        freq *= pow(2, 1.0 / 12.0);
    }
    else if (note[1] == 'b')
    {
        freq *= pow(2, -1.0 / 12.0);
    }

    //Apply shift due to notes
    if (note[0] == 'B')
    {
        freq *= pow(2, 2.0 / 12);
    }
    else if (note[0] == 'G')
    {
        freq *= pow(2, -2.0 / 12);
    }
    else if (note[0] == 'F')
    {
        freq *= pow(2, -4.0 / 12);
    }
    else if (note[0] == 'E')
    {
        freq *= pow(2, -5.0 / 12);
    }
    else if (note[0] == 'D')
    {
        freq *= pow(2, -7.0 / 12);
    }
    else if (note[0] == 'C')
    {
        freq *= pow(2, -9.0 / 12);
    }

    freq = round(freq);
    return freq;
}

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

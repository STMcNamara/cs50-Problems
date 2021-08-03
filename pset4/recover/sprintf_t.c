#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int num = 23;
    char filename[7];
    sprintf(filename, "%03i.jpg", num);
    printf("%s\n", filename);
}
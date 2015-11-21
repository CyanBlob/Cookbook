#include <cstring>
#include <string>
#include "helpers.h"

char* helpers::myToLower(char *temp)
{
    int x;
    for(x = 0; x < strlen(temp); x++)
    {   
        temp[x] = tolower(temp[x]);
    }   
    return temp;
}


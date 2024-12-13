#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "db.h"
#define USER_DATABASE_NAME "db/users.csv"

int getlastAvalibleID(char *databaseName)
{
    int count = 0;
    char c;

    FILE *file = fopen(databaseName, "r");

    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            count++;
        }
    }

    return count + 1;
}

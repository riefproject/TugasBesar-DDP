#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "db.h"

int getlastAvalibleID(char *databaseName)
{
    int count = 0;
    char c;

    char *path = database(databaseName);
    FILE *file = fopen(path, "r");
    free(path);

    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            count++;
        }
    }

    return count + 1;
}

char *database(char *databaseName)
{
    size_t length = strlen(DATABASE_PATH) + strlen(databaseName) + 2;
    char *path = malloc(length);

    if (!path)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(0);
    }

    sprintf(path, "%s/%s", DATABASE_PATH, databaseName);
    return path;
}
#include "db.h"

int getlastAvalibleID(char *databaseName)
{
    int count = 0;
    char c;

    FILE *file = fopen(database(databaseName), "r");

    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            count++;
        }
    }

    fseek(file, -1, SEEK_END);

    if (fgetc(file) != '\n')
    {
        count++;
    }

    return count;
}

char *database(char *databaseName)
{
    char *path = "";

    sprintf(path, "%s/%s", DATABASE_PATH, databaseName);

    return path;
}
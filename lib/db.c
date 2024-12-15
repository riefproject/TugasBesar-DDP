#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "db.h"
#define USER_DATABASE_NAME "db/users.csv"

int getLastAvailableID(char *databaseName)
{
    FILE *file = fopen(databaseName, "r");
    if (file == NULL)
    {
        return 1;
    }

    int id;
    int maxID = 0;
    char line[256];

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%d", &id) == 1)
        {
            if (id > maxID)
            {
                maxID = id;
            }
        }
    }

    fclose(file);

    return maxID + 1;
}
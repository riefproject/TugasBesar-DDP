#ifndef DB_H
#define DB_H

#include <stdio.h>

#define DATABASE_PATH "db"

int getlastAvalibleID(char *databaseName);

char *database(char *databaseName);

#endif
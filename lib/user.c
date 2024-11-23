#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "db.h"

User *findUser(int id) {
    // int fscanf(FILE *ptr, const char *format, ...)

}

User *allUsers() {

}

int createUser(User user)
{
    FILE *file = fopen(database(USER_DATABASE_NAME), "a");

    int id = getlastAvalibleID(USER_DATABASE_NAME);    

    char * userFormat;
    sprintf(userFormat, "%s%s", USER_FORMAT, "\n");

    fprintf(file, userFormat,
            id,
            user.username,
            user.password,
            user.name,
            user.email,
            user.notelp,
            user.role);

    fclose(file);

    return 1;
}

int updateUser(int id, User user) {}

int destroyUser(int id) {
    
}

User *newUser()
{
    User *user = malloc(sizeof(User));
    if (!user)
    {
        return NULL;
    }

    FILE *file = fopen(database(USER_DATABASE_NAME), "a");
    if (!file)
    {
        free(user);
        return NULL;
    }
    fclose(file);

    user->find = findUser;
    user->all = allUsers;
    user->create = createUser;
    user->update = updateUser;
    user->destroy = destroyUser;

    return user;
}
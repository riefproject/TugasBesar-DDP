#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "security.h"
#include "user.h"
#include "db.h"

// ================================== setter ================================== //
void setUsername(User *user, const char *username)
{
    strncpy(user->username, username, sizeof(user->username) - 1);

    user->username[sizeof(user->username) - 1] = '\0';
}

void setPassword(User *user, const char *password)
{
    char hashedPassword[65];

    encrypt(password, hashedPassword);

    strncpy(user->password, hashedPassword, sizeof(user->password) - 1);

    user->password[sizeof(user->password) - 1] = '\0';
}

void setName(User *user, const char *name)
{
    strncpy(user->name, name, sizeof(user->name) - 1);

    user->name[sizeof(user->name) - 1] = '\0';
}

void setEmail(User *user, const char *email)
{
    strncpy(user->email, email, sizeof(user->email) - 1);

    user->email[sizeof(user->email) - 1] = '\0';
}

void setNoTelp(User *user, const char *notelp)
{
    strncpy(user->notelp, notelp, sizeof(user->notelp) - 1);

    user->notelp[sizeof(user->notelp) - 1] = '\0';
}

// ================================== getter ================================== //
const char *getUsername(const User *user) { return user->username; }
const char *getPassword(const User *user) { return user->password; }
const char *getName(const User *user) { return user->name; }
const char *getEmail(const User *user) { return user->email; }
const char *getNoTelp(const User *user) { return user->notelp; }

User *findUser(int id)
{
    char *path = database(USER_DATABASE_NAME);
    FILE *file = fopen(path, "r");
    free(path);

    if (!file)
    {
        return NULL;
    }

    User *user = malloc(sizeof(User));
    if (!user)
    {
        fclose(file);
        return NULL;
    }

    while (fscanf(file, USER_GETTER_FORMAT,
                  &user->id,
                  user->username,
                  user->password,
                  user->name,
                  user->email,
                  user->notelp,
                  (int *)&user->role) == 7)
    {
        if (user->id == id)
        {
            fclose(file);
            return user;
        }
    }

    fclose(file);
    free(user);
    return NULL;
}

User *findUserByUsername(const char *username)
{
    // printf("Cek username %s\n", username);
    FILE *file = fopen("db/users.csv", "r");
    if (!file)
    {
        printf("Error ketika membuka file\n");
        return NULL;
    }

    User *user = malloc(sizeof(User));
    if (!user)
    {
        printf("Gagal alokasi memory untuk user\n");
        fclose(file);
        return NULL;
    }

    while (fscanf(file, USER_GETTER_FORMAT,
                  &user->id,
                  user->username,
                  user->password,
                  user->name,
                  user->email,
                  user->notelp,
                  (int *)&user->role) != EOF)
    {
        if (strcmp(user->username, username) == 0)
        {
            fclose(file);
            // printf("ada cuyy\n");
            return user;
        }
    }

    // printf("gk ada cuyy\n");

    fclose(file);
    free(user);
    return NULL;
}

User *allUsers()
{
    char *path = database(USER_DATABASE_NAME);
    FILE *file = fopen(path, "r");
    free(path);

    if (!file)
    {
        return NULL;
    }

    // First count lines
    int lines = 0;
    char ch;
    while (!feof(file))
    {
        ch = fgetc(file);
        if (ch == '\n')
            lines++;
    }
    rewind(file);

    // Allocate memory for all users
    User *users = malloc(sizeof(User) * lines);
    if (!users)
    {
        fclose(file);
        return NULL;
    }

    // Read users
    int i = 0;
    while (i < lines && fscanf(file, USER_GETTER_FORMAT,
                               &users[i].id,
                               users[i].username,
                               users[i].password,
                               users[i].name,
                               users[i].email,
                               users[i].notelp,
                               (int *)&users[i].role) == 7)
    {
        i++;
    }

    fclose(file);
    return users;
}

User *createUser(const char *username, const char *password, const char *name, const char *email, const char *notelp, Role role)
{
    User *user = malloc(sizeof(User));
    if (!user)
    {
        printf("alokasi memori gagal, location: createUser");
        return NULL;
    }

    setUsername(user, username);
    setPassword(user, password);
    setName(user, name);
    setEmail(user, email);
    setNoTelp(user, notelp);
    user->role = role;

    char *path = database(USER_DATABASE_NAME);
    FILE *file = fopen(path, "a");
    free(path);

    if (!file)
    {
        free(user);
        return NULL;
    }

    int id = getlastAvalibleID(USER_DATABASE_NAME);
    user->id = id;

    fprintf(file, USER_SETTER_FORMAT,
            user->id,
            user->username,
            user->password,
            user->name,
            user->email,
            user->notelp,
            user->role);

    fclose(file);
    return user;
}

int updateUser(int id, User newData)
{
    int count;
    User *users = allUsers(&count);
    if (!users)
        return 0;

    // Update user yg id nya sama
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (users[i].id == id)
        {
            users[i] = newData;
            users[i].id = id;
            found = 1;
            break;
        }
    }

    if (!found)
    {
        free(users);
        return 0;
    }

    // tulis ulang
    char *path = database(USER_DATABASE_NAME);
    FILE *file = fopen(path, "w");
    free(path);

    if (!file)
    {
        free(users);
        return 0;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, USER_SETTER_FORMAT,
                users[i].id,
                users[i].username,
                users[i].password,
                users[i].name,
                users[i].email,
                users[i].notelp,
                users[i].role);
    }

    fclose(file);
    free(users);
    return 1;
}

int destroyUser(int id)
{
    int count;
    User *users = allUsers(&count);
    if (!users)
        return 0;

    char *path = database(USER_DATABASE_NAME);
    FILE *file = fopen(path, "w");
    free(path);

    if (!file)
    {
        free(users);
        return 0;
    }

    // Tulis ulang kecuali yang dihapus
    for (int i = 0; i < count; i++)
    {
        if (users[i].id != id)
        {
            fprintf(file, USER_SETTER_FORMAT,
                    users[i].id,
                    users[i].username,
                    users[i].password,
                    users[i].name,
                    users[i].email,
                    users[i].notelp,
                    users[i].role);
        }
    }

    fclose(file);
    free(users);
    return 1;
}

User *newUser()
{
    User *user = malloc(sizeof(User));
    if (!user)
    {
        return NULL;
    }

    char *path = database(USER_DATABASE_NAME);
    FILE *file = fopen(path, "a");
    free(path);

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
#include "security.h"
#include <openssl/sha.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "auth.h"
#include "security.h"

int isUnique(const char *username)
{
    char filepath[100];
    sprintf(filepath, "db/users/%s.dat", username);

    FILE *file = fopen(filepath, "rb");
    if (file)
    {
        fclose(file);
        return 0; // Username already exists
    }
    return 1; // Username is unique
}

int checkAuth(const User *user)
{
    char filepath[100];
    sprintf(filepath, "db/users/%s.dat", user->username);

    FILE *file = fopen(filepath, "rb");
    if (!file)
    {
        printf("Username tidak ditemukan.\n");
        return 0;
    }

    User check;
    fread(&check, sizeof(User), 1, file);
    fclose(file);

    char hashedInput[65];
    encrypt(user->password, hashedInput);

    if (strcmp(check.password, hashedInput) == 0)
    {
        return 1;
    }
    return 0;
}

void encrypt(const char *password, char *hashedOutput)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)password, strlen(password), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(hashedOutput + (i * 2), "%02x", hash[i]);
    }
    hashedOutput[64] = '\0'; // Null-terminate the string
}

// void generateSalt(char *salt, size_t length)
// {
//     const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
//     srand(time(NULL));
//     for (size_t i = 0; i < length; i++)
//     {
//         salt[i] = charset[rand() % (sizeof(charset) - 1)];
//     }
//     salt[length] = '\0';
// }

// void hashSalt(const char *password, const char *salt, char *hashedPassword)
// {
//     char saltedPassword[256];
//     snprintf(saltedPassword, sizeof(saltedPassword), "%s%s", password, salt);

//     unsigned char hash[SHA256_DIGEST_LENGTH];
//     SHA256((unsigned char *)saltedPassword, strlen(saltedPassword), hash);

//     for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
//     {
//         sprintf(hashedPassword + (i * 2), "%02x", hash[i]);
//     }
//     hashedPassword[SHA256_DIGEST_LENGTH * 2] = '\0';
// }

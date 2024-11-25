#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "security.h"
#include "auth.h"
#include "user.h"
#include "db.h"

void encrypt(const char *password, char *hashedOutput)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)password, strlen(password), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(hashedOutput + (i * 2), "%02x", hash[i]);
    }
    hashedOutput[64] = '\0';
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

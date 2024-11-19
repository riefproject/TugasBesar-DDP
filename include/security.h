#ifndef SECURITY_H
#define SECURITY_H
#include "auth.h"
int isUnique(const char *username);
int checkAuth(const User *user);
void generateSalt(char *salt, unsigned int length);
void hashSalt(const char *password, const char *salt, char *hashedPassword);
void encrypt(const char *password, char *hashedPassword);

#endif
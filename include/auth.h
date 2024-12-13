#ifndef AUTH_H
#define AUTH_H

#include "user.h"

void registerUser();

int loginUser();

int isLogin();

User *getCurrentUser();

void saveSession(User *user);

void clearSession();

int authenticateUser(const char *username, const char *password);

#endif

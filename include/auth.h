#ifndef AUTH_H
#define AUTH_H

#include "user.h"

void registerUser();
int loginUser(User *user);
int authenticateUser(const char *username, const char *password);

#endif

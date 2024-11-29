#ifndef SESSION_H
#define SESSION_H

#include <time.h>
#include <stdbool.h>

#include "user.h"

typedef struct
{
    int id;
    User user;
    time_t login_at;
} Session;

// masih dipikirkan ;-;

#endif
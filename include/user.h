#ifndef USER_H
#define USER_H

// Constants
#define MAX_USERNAME 255
#define MAX_PASSWORD 255
#define MAX_NAME 255
#define MAX_EMAIL 225
#define MAX_NOTELP 16
#define USER_DATABASE_NAME "users.csv"
#define USER_FORMAT "%d,%s,%s,%s,%s,%s,%d"

typedef struct User User;

typedef enum
{
    ADMIN,
    PETUGAS,
    CLIENT
} Role;

struct User
{
    int id;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char name[MAX_NAME];
    char email[MAX_EMAIL];
    char notelp[MAX_NOTELP];
    Role role;

    struct User *(*all)();
    struct User *(*find)(int);
    int (*create)(struct User);
    int (*update)(int, struct User);
    int (*destroy)(int);
};

User *newUser();
User *findUser(int id);
User *allUsers();
int createUser(User user);
int updateUser(int id, User user);
int destroyUser(int id);

#endif
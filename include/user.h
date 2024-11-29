#ifndef USER_H
#define USER_H

// ================================== constant ================================== //

#define MAX_USERNAME 255
#define MAX_PASSWORD 255
#define MAX_NAME 255
#define MAX_EMAIL 225
#define MAX_NOTELP 16
#define USER_DATABASE_NAME "users.csv"
#define USER_SETTER_FORMAT "%d,%s,%s,%s,%s,%s,%d\n"
#define USER_GETTER_FORMAT "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d\n"

// ================================== type definition ================================== //

typedef struct User User;
typedef enum
{
    ADMIN = 1,
    PETUGAS = 2,
    CLIENT = 3
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

    User *(*all)();
    User *(*find)(int);
    User *(*create)(const char *, const char *, const char *, const char *, const char *, Role);
    int (*update)(int, User);
    int (*destroy)(int);
};

// ================================== setter ================================== //

void setUsername(User *user, const char *username);
void setPassword(User *user, const char *password);
void setName(User *user, const char *name);
void setEmail(User *user, const char *email);
void setNoTelp(User *user, const char *notelp);

// ================================== getter ================================== //
const char *getUsername(const User *user);
const char *getPassword(const User *user);
const char *getName(const User *user);
const char *getEmail(const User *user);
const char *getNoTelp(const User *user);

// ================================== other ================================== //

User *newUser();
User *allUsers();
User *findUser(int id);
User *findUserByUsername(const char *username);
User *createUser(const char *username, const char *password, const char *name, const char *email, const char *notelp, Role role);
int updateUser(int id, User user);
int destroyUser(int id);

#endif
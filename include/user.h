#ifndef USER_H
#define USER_H

// ================================== constant ================================== //

#define MAX_USERNAME 255
#define MAX_PASSWORD 255
#define MAX_NAME 255
#define MAX_EMAIL 225
#define MAX_NOTELP 16
#define USER_SETTER_FORMAT "%d,%s,%s,%s,%s,%s,%d\n"
#define USER_GETTER_FORMAT "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d\n"
#define USER_DATABASE_NAME "db/users.csv"

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

// ================================== Main Menu ================================ //

int menuUser();
void createUserMenu();
void updateUserMenu(User user);

// ================================== Action ================================== //

User *findUser(int id);
User *findUserByUsername(const char *username);
User *createUser(const char *username, const char *password, const char *name, const char *email, const char *notelp, Role role);
User *updateUser(const int id, const char *username, const char *password, const char *name, const char *email, const char *notelp, const Role role);
int deleteUser(User user);

// ================================== Utils ================================== //

int countUserData();
int loadUser(User **users);
void printUserTable(User *users, int count, int page, int perPage, int selection);

#endif
#ifndef AUTH_H
#define AUTH_H

#define MAX_USERNAME 15
#define MAX_PASSWORD 65
#define MAX_NAME 25
#define MAX_EMAIL 20
#define MAX_NOTELP 16

typedef enum
{
    admin,
    client
} role;

typedef struct
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char name[MAX_NAME];
    char email[MAX_EMAIL];
    char notelp[MAX_NOTELP];
    role access;
    int numReservations; // Jumlah pemesanan
} User;

// Setter
void setUsn(User *user, const char *username);
void setPassword(User *user, const char *password);
void setName(User *user, const char *name);
void setEmail(User *user, const char *email);

// Getter
const char *getUsn(const User *user);
const char *getPassword(const User *user);
const char *getName(const User *user);
const char *getEmail(const User *user);

// Factory Function
User *createUser(const char *username, const char *password, const char *name, const char *email, const char *notelp, role access);

void addUser();
void authUser(User *user);
int checkAuth(const User *user);

#endif

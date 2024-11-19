#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "security.h"

// Setter
void setUsn(User *user, const char *username)
{
    strncpy(user->username, username, sizeof(user->username) - 1);
    user->username[sizeof(user->username) - 1] = '\0';
}
void setPassword(User *user, const char *password)
{
    strncpy(user->password, password, sizeof(user->password) - 1);
    user->password[sizeof(user->password) - 1] = '\0';
}
void setName(User *user, const char *name)
{
    strncpy(user->name, name, sizeof(user->name) - 1);
    user->name[sizeof(user->name) - 1] = '\0';
}
void setEmail(User *user, const char *email)
{
    strncpy(user->email, email, sizeof(user->email) - 1);
    user->email[sizeof(user->email) - 1] = '\0';
}

// Getter
const char *getUsn(const User *user) { return user->username; }
const char *getPassword(const User *user) { return user->password; }
const char *getName(const User *user) { return user->name; }
const char *getEmail(const User *user) { return user->email; }

// Factory Function
User *createUser(const char *username, const char *password, const char *name, const char *email, const char *notelp, role access)
{
    User *newUser = malloc(sizeof(User));
    if (!newUser)
    {
        printf("Error: Memory allocation failed.\n");
        return NULL;
    }

    setUsn(newUser, username);

    char hashedPassword[65];
    encrypt(password, hashedPassword);
    setPassword(newUser, hashedPassword);

    setName(newUser, name);
    setEmail(newUser, email);
    newUser->access = access;
    newUser->numReservations = 0;

    return newUser;
}

void addUser()
{
    char username[MAX_USERNAME], password[MAX_PASSWORD], confirmPassword[MAX_PASSWORD], name[MAX_NAME], email[MAX_EMAIL], notelp[MAX_NOTELP];

    printf("Masukkan username\t: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    if (!isUnique(username))
    {
        printf("Username sudah terdaftar. Silakan pilih username lain.\n");
        return;
    }

    printf("Masukkan password\t: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    printf("Konfirmasi password\t: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (strcmp(password, confirmPassword) != 0)
    {
        printf("Password tidak cocok. Pendaftaran gagal.\n");
        return;
    }

    printf("Masukkan nama\t: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Masukkan email\t: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    printf("Masukkan notelp\t: ");
    fgets(notelp, sizeof(notelp), stdin);
    notelp[strcspn(notelp, "\n")] = 0;

    User *newUser = createUser(username, password, name, email, notelp, 1);
    if (!newUser)
    {
        printf("Gagal membuat user baru.\n");
        return;
    }

    char filepath[100];
    sprintf(filepath, "db/users/%s.bin", newUser->username);

    FILE *file = fopen(filepath, "wb");
    if (!file)
    {
        printf("Registrasi Gagal. Harap Coba Lagi!\n");
        free(newUser);
        return;
    }

    fwrite(newUser, sizeof(User), 1, file);
    fclose(file);

    printf("Registrasi berhasil! Anda dapat login sekarang.\n");
    free(newUser);
}

void authUser(User *user)
{
    char username[50];
    char password[50];

    printf("Masukkan username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Masukkan password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    setUsn(user, username);
    setPassword(user, password);

    if (checkAuth(user))
    {
        printf("Selamat datang, %s!\n", getName(user));
    }
    else
    {
        printf("Username atau password salah.\n");
    }
}
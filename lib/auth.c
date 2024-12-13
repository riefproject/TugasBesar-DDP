#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "db.h"
#include "security.h"

int authenticateUser(const char *username, const char *password)
{
    User *user = findUserByUsername(username);
    if (user == NULL)
    {
        printf("Username tidak ada");
        return 0;
    }

    char hashedPassword[65];
    encrypt(password, hashedPassword);

    int result = strcmp(user->password, hashedPassword) == 0;
    free(user);
    return result;
}

void registerUser()
{
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    char confirmPassword[MAX_PASSWORD], name[MAX_NAME];
    char email[MAX_EMAIL], notelp[MAX_NOTELP];

    while (1)
    {
        printf("Masukkan username\t: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0;

        User *user = findUserByUsername(username);

        if (user != NULL)
        {
            printf("Username sudah terdaftar. Silakan pilih username lain.\n");
            continue;
        }
        break;
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

    User *newUser = createUser(username, password, name, email, notelp, CLIENT);
    if (!newUser)
    {
        printf("Registrasi Gagal. Harap Coba Lagi!\n");
        return;
    }

    printf("Registrasi berhasil! Anda dapat login sekarang.\n");
    free(newUser);
}

User *getCurrentUser()
{
    FILE *file = fopen("session.bin", "rb");
    if (file == NULL)
    {
        return NULL;
    }

    User *sessionUser = (User *)malloc(sizeof(User));
    if (sessionUser == NULL)
    {
        fclose(file);
        return NULL;
    }

    size_t readResult = fread(sessionUser, sizeof(User), 1, file);
    fclose(file);

    if (readResult != 1)
    {
        free(sessionUser);
        return NULL;
    }

    return sessionUser;
}

void saveSession(User *user)
{
    FILE *file = fopen("session.bin", "wb");
    if (file != NULL)
    {
        fwrite(user, sizeof(User), 1, file);
        fclose(file);
    }
}

void clearSession()
{
    remove("session.bin");
}

int loginUser()
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Masukkan username: ");
    if (fgets(username, sizeof(username), stdin) == NULL)
    {
        return 0;
    }
    username[strcspn(username, "\n")] = 0;

    printf("Masukkan password: ");
    if (fgets(password, sizeof(password), stdin) == NULL)
    {
        return 0;
    }
    password[strcspn(password, "\n")] = 0;

    if (authenticateUser(username, password))
    {
        User *foundUser = findUserByUsername(username);
        if (foundUser != NULL)
        {
            saveSession(foundUser);
            free(foundUser);
            printf("Login berhasil!\n");
            return 1;
        }
    }

    printf("Username atau password salah.\n");
    return 0;
}

int isLogin()
{
    FILE *file = fopen("session.bin", "rb");
    if (file == NULL)
    {
        return 0;
    }

    User temp;
    size_t readResult = fread(&temp, sizeof(User), 1, file);
    fclose(file);

    return (readResult == 1);
}
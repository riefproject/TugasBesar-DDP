#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>

#include "display.h"
#include "menu.h"
#include "security.h"
#include "user.h"
#include "db.h"

// ================================== setter ================================== //

void setUsername(User *user, const char *username)
{
    strncpy(user->username, username, sizeof(user->username) - 1);

    user->username[sizeof(user->username) - 1] = '\0';
}

void setPassword(User *user, const char *password)
{
    char hashedPassword[65];

    encrypt(password, hashedPassword);

    strncpy(user->password, hashedPassword, sizeof(user->password) - 1);

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

void setNoTelp(User *user, const char *notelp)
{
    strncpy(user->notelp, notelp, sizeof(user->notelp) - 1);

    user->notelp[sizeof(user->notelp) - 1] = '\0';
}

// ==================================== getter ==================================== //

const char *getUsername(const User *user) { return user->username; }
const char *getPassword(const User *user) { return user->password; }
const char *getName(const User *user) { return user->name; }
const char *getEmail(const User *user) { return user->email; }
const char *getNoTelp(const User *user) { return user->notelp; }

// ==================================== Main Menu =================================//

int menuUser()
{
    User *users;
    int count = loadUser(&users);

    if (getCurrentUser()->role == MANAGER)
    {
        filterUserByRole(&users, PETUGAS);
    }

    if (getCurrentUser()->role == PETUGAS)
    {
        filterUserByRole(&users, CLIENT);
    }

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        system("cls");
        selection = (page - 1) * perPage + pointer;

        printf(GREEN "====================================================\n");
        printf("             Menu Management Pengguna               \n");
        printf("====================================================\n" RESET);

        printUserTable(users, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page");
        printf(GREEN "\n[C]: Create" RESET " | " YELLOW "[U]: Update" RESET " | " RED "[D]: Delete" RESET " | " BG_RED WHITE "[E] Exit" RESET "\n" RESET);

        command = getch();

        if (command == 224)
        {
            command = getch();

            if (command == 77)
            {
                pointer = 1;
                if (page * perPage < count)
                    page++;
                else
                {
                    printf(BLUE "Sudah di halaman terakhir.\n");
                    sleep(1);
                }
            }
            else if (command == 75)
            {
                pointer = 1;
                if (page > 1)
                    page--;
                else
                {
                    printf(BLUE "Sudah di halaman pertama.\n");
                    sleep(1);
                }
            }
            else if (command == 72)
            {
                if (pointer > 1)
                {
                    pointer--;
                }
            }
            else if (command == 80)
            {
                if (pointer < perPage && (page - 1) * perPage + pointer < count)
                {
                    pointer++;
                }
            }
        }
        else if (command == 32)
        {
            printf("data terpilih %d", selection);
            free(users);
            return 0;
        }
        else if (command == 'C' || command == 'c')
        {
            createUserMenu();

            free(users);
            count = loadUser(&users);
            pointer = 1;
        }
        else if (command == 'U' || command == 'u')
        {
            updateUserMenu(users[selection - 1]);

            free(users);
            count = loadUser(&users);
            pointer = 1;
        }
        else if (command == 'D' || command == 'd')
        {
            deleteUser(users[selection - 1]);

            free(users);
            count = loadUser(&users);
            pointer = 1;
        }
        else if (command == 'E' || command == 'e')
        {
            free(users);
            return 0;
        }
        else
        {
            printf(YELLOW BOLD "perintah tidak ditemukan\n" RESET);
            sleep(1);
        }
    }
}

void createUserMenu()
{
    system("cls");

    printf(GREEN "====================================================\n");
    printf("                Menu Tambah Pengguna                \n");
    printf("====================================================\n" RESET);

    char username[MAX_USERNAME], password[MAX_PASSWORD];
    char confirmPassword[MAX_PASSWORD], name[MAX_USER_NAME];
    char email[MAX_EMAIL], notelp[MAX_NOTELP];
    int role = 0;

    while (1)
    {
        printf("Masukkan username\t: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0;

        User *user = findUserByUsername(username);

        if (user != NULL)
        {
            printf(RED BOLD "Username sudah terdaftar. Silakan pilih username lain.\n" RESET);
            sleep(1);
            continue;
        }

        if (strcmp(username, "") == 0)
        {
            printf(RED BOLD "Username tidak boleh kosong.\n" RESET);
            sleep(1);
            continue;
        }

        break;
    }

    while (1)
    {
        printf("Masukkan password\t: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = 0;

        printf("Konfirmasi password\t: ");
        fgets(confirmPassword, sizeof(confirmPassword), stdin);
        confirmPassword[strcspn(confirmPassword, "\n")] = 0;

        if (strcmp(password, confirmPassword) == 0)
        {
            break;
        }
        printf(RED BOLD "Password tidak cocok. Ulangi masukan password\n" RESET);
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

    int limitRole = 0;
    printf("Pilih role \n: ");
    while (role < 1 || role > 2)
    {
        printf("=================\n");
        printf("| No | Role     |\n");
        printf("=================\n");
        if (getCurrentUser()->role == SUPER_ADMIN)
        {
            printf("| 1 | Manager   |\n");
            printf("| 2 | Petugas   |\n");
            limitRole = 1;
        }
        if (getCurrentUser()->role == MANAGER)
        {
            printf("| 2 | Petugas   |\n");
            limitRole = 2;
        }
        printf("=================\n");

        scanf("%d", &role);

        if (role >= limitRole && role <= 2)
        {
            break;
        }
        printf(RED BOLD "Harap pilih role yang tersedia!\n" RESET);
    }

    User *newUser = createUser(username, password, name, email, notelp, role);
    if (!newUser)
    {
        printf(RED BOLD "Gagal menambah user. Harap Coba Lagi!\n" RESET);
        return;
    }

    printf(GREEN BOLD "Berhasil menambah user!.\n" RESET);
    sleep(2);
    free(newUser);
}

void updateUserMenu(User user)
{
    printf(YELLOW "====================================================\n");
    printf("                 Menu Edit Pengguna                 \n");
    printf("====================================================\n" RESET);

    char username[MAX_USERNAME], password[MAX_PASSWORD];
    char confirmPassword[MAX_PASSWORD], name[MAX_USER_NAME];
    char email[MAX_EMAIL], notelp[MAX_NOTELP];

    while (1)
    {
        printf("Masukkan username\t: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0;

        User *find = findUserByUsername(username);

        if (find != NULL && user.id != find->id)
        {
            printf(RED BOLD "Username sudah terdaftar. Silakan pilih username lain.\n" RESET);
            sleep(1);
            continue;
        }

        if (strcmp(username, "") == 0)
        {
            printf(RED BOLD "Username tidak boleh kosong.\n" RESET);
            sleep(1);
            continue;
        }

        break;
    }

    while (1)
    {
        printf("Masukkan password\t: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = 0;

        printf("Konfirmasi password\t: ");
        fgets(confirmPassword, sizeof(confirmPassword), stdin);
        confirmPassword[strcspn(confirmPassword, "\n")] = 0;

        if (strcmp(password, confirmPassword) == 0)
        {
            break;
        }
        printf(RED BOLD "Password tidak cocok. Ulangi masukan password\n" RESET);
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

    User *newUser = updateUser(user.id, username, password, name, email, notelp, user.role);
    if (!newUser)
    {
        printf(RED BOLD "Gagal mengubah user. Harap Coba Lagi!\n" RESET);
        return;
    }

    printf(GREEN BOLD "Berhasil mengubah user!.\n" RESET);
    sleep(2);
    free(newUser);
}

// ==================================== Action ====================================//

User *findUserByID(int id)
{
    FILE *file = fopen(USER_DATABASE_NAME, "r");

    if (!file)
    {
        return NULL;
    }

    User *user = malloc(sizeof(User));
    if (!user)
    {
        fclose(file);
        return NULL;
    }

    while (fscanf(file, USER_GETTER_FORMAT,
                  &user->id,
                  user->username,
                  user->password,
                  user->name,
                  user->email,
                  user->notelp,
                  (int *)&user->role) == 7)
    {
        if (user->id == id)
        {
            fclose(file);
            return user;
        }
    }

    fclose(file);
    // free(user);
    return NULL;
}

User *findUserByUsername(const char *username)
{
    // printf("Cek username %s\n", username);
    FILE *file = fopen(USER_DATABASE_NAME, "r");
    if (!file)
    {
        printf("Error ketika membuka file\n");
        return NULL;
    }

    User *user = malloc(sizeof(User));
    if (!user)
    {
        printf("Gagal alokasi memory untuk user\n");
        fclose(file);
        return NULL;
    }

    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d\n",
                  &user->id,
                  user->username,
                  user->password,
                  user->name,
                  user->email,
                  user->notelp,
                  (int *)&user->role) != EOF)
    {
        if (strcmp(user->username, username) == 0)
        {
            fclose(file);
            // printf("ada cuyy\n");
            return user;
        }
    }

    // printf("gk ada cuyy\n");

    fclose(file);
    free(user);
    return NULL;
}

User *createUser(const char *username, const char *password, const char *name, const char *email, const char *notelp, Role role)
{
    User *user = malloc(sizeof(User));
    if (!user)
    {
        printf("alokasi memori gagal, location: createUser");
        return NULL;
    }

    setUsername(user, username);
    setPassword(user, password);
    setName(user, name);
    setEmail(user, email);
    setNoTelp(user, notelp);
    user->role = role;

    FILE *file = fopen(USER_DATABASE_NAME, "a");

    if (!file)
    {
        free(user);
        return NULL;
    }

    int id = getLastAvailableID(USER_DATABASE_NAME);
    user->id = id;

    fprintf(file, USER_SETTER_FORMAT,
            user->id,
            user->username,
            user->password,
            user->name,
            user->email,
            user->notelp,
            user->role);

    fclose(file);
    return user;
}

User *updateUser(const int id, const char *username, const char *password, const char *name, const char *email, const char *notelp, const Role role)
{
    User *updatedUser = malloc(sizeof(User));
    if (!updatedUser)
    {
        printf("alokasi memori gagal, location: createUser");
        return NULL;
    }

    setUsername(updatedUser, username);
    setPassword(updatedUser, password);
    setName(updatedUser, name);
    setEmail(updatedUser, email);
    setNoTelp(updatedUser, notelp);
    updatedUser->role = role;

    FILE *fromFile = fopen(USER_DATABASE_NAME, "r");
    if (!fromFile)
    {
        free(updatedUser);
        return NULL;
    }

    int count = countUserData();
    if (count == -1)
    {
        printf("penghitungan data user gagal, location: updateUser");
        return NULL;
    }

    int i = 0;

    User users[count];

    while (fscanf(fromFile, USER_GETTER_FORMAT,
                  &users[i].id,
                  users[i].username,
                  users[i].password,
                  users[i].name,
                  users[i].email,
                  users[i].notelp,
                  &users[i].role) != EOF)
    {
        if (users[i].id == id)
        {
            updatedUser->id = id;
            users[i] = *updatedUser;
        }

        i++;
    }
    fclose(fromFile);

    FILE *toFile = fopen(USER_DATABASE_NAME, "w");
    i = 0;
    while (i < count)
    {
        fprintf(toFile, USER_SETTER_FORMAT,
                users[i].id,
                users[i].username,
                users[i].password,
                users[i].name,
                users[i].email,
                users[i].notelp,
                users[i].role);
        i++;
    }

    fclose(toFile);
    return updatedUser;
}

int deleteUser(User user)
{
    // Buat pesan konfirmasi
    int len = snprintf(NULL, 0, "Apakah Anda yakin ingin menghapus data user dengan username '%s'?\n", user.username) + 1;
    char *head = malloc(len);
    if (!head)
    {
        printf(RED "Gagal mengalokasikan memori.\n" RESET);
        sleep(1);

        return -1;
    }
    snprintf(head, len, "Apakah Anda yakin ingin menghapus data user dengan username '%s'?\n", user.username);

    char *menu[] = {
        "Tidak, Batalkan",
        "Ya, Hapus",
    };

    char *header[] = {
        RED BOLD "====================================================\n",
        "             Konfirmasi Hapus Pengguna              \n",
        "====================================================\n\n" RESET,
        head,
        NULL};

    int selection = showMenu(menu, 2, header);
    free(head);

    if (selection == 1)
    {
        return 1;
    }

    // cadangkan data
    FILE *fromFile = fopen(USER_DATABASE_NAME, "r");
    if (!fromFile)
    {
        printf(RED "Gagal membuka file, lokasi: deleteUser.\n" RESET);
        sleep(1);
        return -1;
    }

    int count = countUserData();
    if (count == -1)
    {
        printf(RED "Penghitungan data user gagal, lokasi: deleteUser.\n" RESET);
        fclose(fromFile);
        return -1;
    }

    User users[count], temp;
    int i = 0;
    while (fscanf(fromFile, USER_GETTER_FORMAT,
                  &temp.id,
                  temp.username,
                  temp.password,
                  temp.name,
                  temp.email,
                  temp.notelp,
                  &temp.role) != EOF)
    {
        if (temp.id != user.id)
        {
            users[i] = temp;
            i++;
        }
    }
    fclose(fromFile);

    // menulis ulang file dengan data pengguna yang diperbarui
    FILE *toFile = fopen(USER_DATABASE_NAME, "w");
    if (!toFile)
    {
        printf(RED "Gagal membuka file untuk ditulis, lokasi: deleteUser.\n" RESET);
        return -1;
    }

    i = 0;
    while (i < count - 1)
    {
        fprintf(toFile, USER_SETTER_FORMAT,
                users[i].id,
                users[i].username,
                users[i].password,
                users[i].name,
                users[i].email,
                users[i].notelp,
                users[i].role);
        i++;
    }

    fclose(toFile);

    return 1;
}

// ==================================== Utils ====================================//

int countUserData()
{
    FILE *file = fopen(USER_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int count = 0;
    User user;

    while (fscanf(file, USER_GETTER_FORMAT,
                  &user.id,
                  user.username,
                  user.password,
                  user.name,
                  user.email,
                  user.notelp,
                  &user.role) != EOF)
    {
        count++;
    }
    fclose(file);
    return count;
}

int loadUser(User **users)
{
    FILE *file = fopen(USER_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int count = countUserData();

    *users = (User *)malloc(count * sizeof(User));
    if (*users == NULL)
    {
        printf("Gagal mengalokasi memori.\n");
        fclose(file);
        return -1;
    }

    rewind(file);
    int i = 0;

    while (fscanf(file, USER_GETTER_FORMAT,
                  &(*users)[i].id,
                  (*users)[i].username,
                  (*users)[i].password,
                  (*users)[i].name,
                  (*users)[i].email,
                  (*users)[i].notelp,
                  &(*users)[i].role) != EOF)
    {
        i++;
    }

    fclose(file);
    return count;
}

void printUserTable(User *users, int count, int page, int perPage, int selection)
{
    int idWidth = 2, usernameWidth = 8, nameWidth = 4;
    int emailWidth = 5, notelpWidth = 6, roleWidth = 8; // Role membutuhkan setidaknya panjang 8 untuk "Pelanggan"

    int start = (page - 1) * perPage;
    int end = start + perPage;
    if (end > count)
        end = count;

    // Hitung panjang kolom terpanjang
    for (int i = start; i < end; i++)
    { // Konversi role ke string
        const char *roleString;
        switch (users[i].role)
        {
        case 1:
            roleString = "Manager";
            break;
        case 2:
            roleString = "Petugas";
            break;
        case 3:
            roleString = "Pelanggan";
            break;
        default:
            roleString = "Unknown";
        }

        int idLen = snprintf(NULL, 0, "%d", users[i].id);
        if (idLen > idWidth)
            idWidth = idLen;

        if ((int)strlen(users[i].username) > usernameWidth)
            usernameWidth = strlen(users[i].username);
            
        if ((int)strlen(users[i].name) > nameWidth)
            nameWidth = strlen(users[i].name);
            
        if ((int)strlen(users[i].email) > emailWidth)
            emailWidth = strlen(users[i].email);
            
        if ((int)strlen(users[i].notelp) > notelpWidth)
            notelpWidth = strlen(users[i].notelp);

        if ((int)strlen(roleString) > roleWidth)
            roleWidth = strlen(roleString);
    }

    int tableWidth = snprintf(NULL, 0,
                              "[ * ]| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
                              idWidth, "ID",
                              usernameWidth, "Username",
                              nameWidth, "Name",
                              emailWidth, "Email",
                              notelpWidth, "Notelp",
                              roleWidth, "Role");

    // Cetak garis atas tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak header tabel
    printf("[ * ]| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           idWidth, "ID",
           usernameWidth, "Username",
           nameWidth, "Name",
           emailWidth, "Email",
           notelpWidth, "Notelp",
           roleWidth, "Role");

    // Cetak garis bawah header
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak isi tabel
    for (int i = start; i < end; i++)
    {
        // Konversi role ke string
        const char *roleString;
        switch (users[i].role)
        {
        case 1:
            roleString = "Manager";
            break;
        case 2:
            roleString = "Petugas";
            break;
        case 3:
            roleString = "Pelanggan";
            break;
        default:
            roleString = "Unknown";
        }

        // Tampilkan dengan penanda jika dipilih
        if (selection == i + 1)
        {
            printf(BLUE BOLD "[ * ]| %-*d | %-*s | %-*s | %-*s | %-*s | %-*s |\n" RESET,
                   idWidth, users[i].id,
                   usernameWidth, users[i].username,
                   nameWidth, users[i].name,
                   emailWidth, users[i].email,
                   notelpWidth, users[i].notelp,
                   roleWidth, roleString);
        }
        else
        {
            printf("[   ]| %-*d | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
                   idWidth, users[i].id,
                   usernameWidth, users[i].username,
                   nameWidth, users[i].name,
                   emailWidth, users[i].email,
                   notelpWidth, users[i].notelp,
                   roleWidth, roleString);
        }
    }

    // Cetak garis bawah tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Informasi halaman
    printf("Page %d of %d\n", page, (count + perPage - 1) / perPage);
}

int filterUserByRole(User **users, Role role)
{
    FILE *file = fopen(USER_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int totalCount = countUserData();

    User *allUsers = (User *)malloc(totalCount * sizeof(User));
    if (allUsers == NULL)
    {
        printf("Gagal mengalokasi memori.\n");
        fclose(file);
        return -1;
    }

    int i = 0, validCount = 0;

    // Membaca semua data dari file
    while (fscanf(file, USER_GETTER_FORMAT,
                  &allUsers[i].id,
                  allUsers[i].username,
                  allUsers[i].password,
                  allUsers[i].name,
                  allUsers[i].email,
                  allUsers[i].notelp,
                  &allUsers[i].role) != EOF)
    {
        if (allUsers[i].role == role)
        {
            validCount++;
        }
        i++;
    }

    fclose(file);

    *users = (User *)malloc(validCount * sizeof(User));
    if (*users == NULL)
    {
        printf("Gagal mengalokasi memori untuk hasil filter.\n");
        free(allUsers);
        return -1;
    }

    int j = 0;
    for (i = 0; i < totalCount; i++)
    {
        if (allUsers[i].role == role)
        {
            (*users)[j] = allUsers[i];
            j++;
        }
    }

    free(allUsers);
    return validCount;
}
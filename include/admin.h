#ifndef ADMIN_H
#define ADMIN_H

// Struktur untuk menyimpan data admin
typedef struct {
    char username[50];
    char password[50];
} Admin;

// Fungsi untuk login sebagai admin
void loginAdmin();

// Fungsi untuk mengecek kredensial admin dari file
int cekAdminLogin(const char *username, const char *password);

// Fungsi untuk menambah admin baru
void tambahAdmin();

int adminUnik(const char *username);
#endif

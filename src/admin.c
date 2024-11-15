#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/admin.h"

// Fungsi untuk login sebagai admin
void loginAdmin()
{
    char username[50], password[50];

    printf("Masukkan username admin: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Hapus newline
    printf("Masukkan password admin: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Hapus newline

    // Cek kredensial admin
    if (cekAdminLogin(username, password))
    {
        printf("Login berhasil sebagai admin.\n");

        // Tampilkan menu admin setelah login berhasil
        int pilihan;
        printf("1. Tambah Admin\n");
        printf("2. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar(); // Menghapus newline setelah input

        if (pilihan == 1)
        {
            tambahAdmin();
        }
        else
        {
            printf("Keluar dari program.\n");
        }
    }
    else
    {
        printf("Username atau password salah.\n");
    }
}

// Fungsi untuk mengecek kredensial admin dari file
int cekAdminLogin(const char *username, const char *password)
{
    // Admin utama (master) dengan username 'admin' dan password 'admin123'
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0)
    {
        return 1; // Login berhasil
    }

    // Cek jika username dan password sesuai dengan yang ada di file
    char filepath[100];
    sprintf(filepath, "../db/admin/%s.dat", username); // Lokasi file admin
    FILE *file = fopen(filepath, "rb");
    if (file == NULL)
    {
        printf("Username tidak ditemukan.\n");
        return 0; // Username tidak ditemukan
    }

    Admin admin;
    while (fread(&admin, sizeof(Admin), 1, file))
    {
        if (strcmp(admin.username, username) == 0 && strcmp(admin.password, password) == 0)
        {
            fclose(file);
            return 1; // Login berhasil
        }
    }

    fclose(file);
    return 0; // Login gagal
}

void tambahAdmin()
{
    char username[50], password[50], confirmPassword[50];

    printf("Masukkan username baru: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Hapus newline

    // Pengecekan apakah username sudah terdaftar
    if (adminUnik(username) == 0)
    {
        printf("Username sudah terdaftar. Silakan pilih username lain.\n");
        return;
    }

    printf("Masukkan password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Hapus newline

    printf("Konfirmasi password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; // Hapus newline

    // Validasi password
    if (strcmp(password, confirmPassword) != 0)
    {
        printf("Password tidak cocok. Pendaftaran gagal.\n");
        return;
    }

    // Simpan data pengguna baru
    Admin newUser;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);

    // Tentukan path untuk file .dat
    char filepath[100];
    sprintf(filepath, "../db/admin/%s.dat", username);

    FILE *file = fopen(filepath, "wb");
    if (file == NULL)
    {
        printf("Gagal membuat file pengguna.\n");
        return;
    }

    // Simpan data pengguna ke file
    fwrite(&newUser, sizeof(Admin), 1, file);
    fclose(file);

    printf("Pendaftaran berhasil! Anda dapat login sekarang.\n");
}

int adminUnik(const char *username)
{
    char filepath[100];
    sprintf(filepath, "../db/admin/%s.dat", username);

    FILE *file = fopen(filepath, "rb");
    if (file != NULL)
    {
        fclose(file); // Jika file ada, berarti username sudah terdaftar
        return 0;
    }
    return 1; // Username unik
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/user.h"

// Fungsi untuk registrasi user baru
void registrasiUser()
{
    char username[50], password[50], confirmPassword[50];

    printf("Masukkan username baru: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Hapus newline

    // Pengecekan apakah username sudah terdaftar
    if (cekUsernameUnik(username) == 0)
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
    User newUser;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    newUser.numReservations = 0; // Inisialisasi jumlah pemesanan

    // Tentukan path untuk file .dat
    char filepath[100];
    sprintf(filepath, "../db/users/%s.dat", username);

    FILE *file = fopen(filepath, "wb");
    if (file == NULL)
    {
        printf("Gagal membuat file pengguna.\n");
        return;
    }

    // Simpan data pengguna ke file
    fwrite(&newUser, sizeof(User), 1, file);
    fclose(file);

    printf("Pendaftaran berhasil! Anda dapat login sekarang.\n");
}

// Fungsi untuk login sebagai user
void loginUser()
{
    char username[50], password[50];

    printf("Masukkan username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Hapus newline
    printf("Masukkan password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Hapus newline

    // Cek apakah username dan password valid
    if (login(username, password))
    {
        printf("Login berhasil sebagai user.\n");
        // Akses menu user (misalnya, memesan atau melihat riwayat)
    }
    else
    {
        printf("Username atau password salah.\n");
    }
}

// Fungsi untuk login dan verifikasi username serta password
int login(const char *username, const char *password)
{
    char filepath[100];
    sprintf(filepath, "../db/users/%s.dat", username); // Lokasi file pengguna

    FILE *file = fopen(filepath, "rb");
    if (file == NULL)
    {
        printf("Username tidak ditemukan.\n");
        return 0; // Username tidak ditemukan
    }

    User user;
    fread(&user, sizeof(User), 1, file);
    fclose(file);

    if (strcmp(user.password, password) == 0)
    {
        return 1; // Login berhasil
    }
    return 0; // Password salah
}

// Fungsi untuk mengecek apakah username sudah terdaftar
int cekUsernameUnik(const char *username)
{
    char filepath[100];
    sprintf(filepath, "../db/users/%s.dat", username);

    FILE *file = fopen(filepath, "rb");
    if (file != NULL)
    {
        fclose(file); // Jika file ada, berarti username sudah terdaftar
        return 0;
    }
    return 1; // Username unik
}

// Fungsi untuk menambahkan pemesanan
void tambahPemesanan(const char *username, const Reservation *reservation)
{
    char filepath[100];
    sprintf(filepath, "../db/users/%s.dat", username);

    FILE *file = fopen(filepath, "r+b");
    if (file == NULL)
    {
        printf("Gagal membuka file pengguna.\n");
        return;
    }

    User user;
    fread(&user, sizeof(User), 1, file);
    fseek(file, 0, SEEK_SET); // Pindahkan pointer ke awal file

    user.reservations[user.numReservations++] = *reservation;

    fwrite(&user, sizeof(User), 1, file);
    fclose(file);
}

#ifndef USER_H
#define USER_H

// Struktur untuk menyimpan informasi pemesanan
typedef struct {
    char date[20];      // Tanggal pemesanan
    char table[10];     // Nomor meja
} Reservation;

// Struktur untuk menyimpan informasi pengguna
typedef struct {
    char username[50];
    char password[50];
    Reservation reservations[100];  // Maksimal 100 pemesanan
    int numReservations;
} User;

void loginUser();
// Fungsi untuk login
int login(const char *username, const char *password);

// Fungsi untuk mengecek apakah username sudah unik
int cekUsernameUnik(const char *username);

// Fungsi untuk menambahkan pemesanan
void tambahPemesanan(const char *username, const Reservation *reservation);
// Fungsi untuk registrasi user baru
void registrasiUser();

#endif

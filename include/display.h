#ifndef DISPLAY_H
#define DISPLAY_H

#include "user.h"

// Fungsi untuk menampilkan menu berdasarkan role pengguna
void showMenuu(User loggedInUser);

// Fungsi untuk menampilkan pesan selamat datang
void showWelcomeMessage();

// Fungsi untuk menampilkan pesan kesalahan
void showError(const char *message);

// Fungsi untuk menampilkan data tabel
void displayTable(const char *headers[], const char *rows[][10], int rowCount, int columnCount);

#endif

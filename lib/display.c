#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "display.h"

// ANSI Escape Codes for Colors and Styles


// Fungsi menampilkan pesan selamat datang dengan animasi
void showWelcomeMessage()
{
    const char *welcomeText = "Selamat Datang di Bioskop";
    printf("\n");
    printf(WHITE BOLD "===============================\n" RESET);
    for (int i = 0; welcomeText[i] != '\0'; i++)
    {
        printf(BOLD YELLOW "%c" RESET, welcomeText[i]);
        fflush(stdout);
        usleep(100000); // Animasi karakter per karakter
    }
    printf("\n");
    printf(WHITE BOLD "===============================\n\n" RESET);
}

// Fungsi menampilkan menu berdasarkan role
void showMenuu(User loggedInUser)
{
    printf("\nHallo, " BOLD GREEN "%s" RESET "! (" CYAN "%s" RESET ")\n", loggedInUser.username, (loggedInUser.role == ADMIN ? "admin" : loggedInUser.role == PETUGAS ? "kasir"
                                                                                                                                                                      : "client"));

    if (loggedInUser.role == ADMIN)
    {
        printf(BOLD BLUE "1." RESET " Kelola Film\n");
        printf(BOLD BLUE "2." RESET " Kelola Jadwal\n");
        printf(BOLD BLUE "3." RESET " Kelola Bioskop\n");
        printf(BOLD BLUE "4." RESET " Lihat Semua Transaksi\n");
    }
    else if (loggedInUser.role == PETUGAS)
    {
        printf(BOLD MAGENTA "1." RESET " Proses Pemesanan Offline\n");
        printf(BOLD MAGENTA "2." RESET " Lihat Transaksi\n");
    }
    else if (loggedInUser.role == CLIENT)
    {
        printf(BOLD GREEN "1." RESET " Pesan Tiket\n");
        printf(BOLD GREEN "2." RESET " Tiket Saya\n");
        printf(BOLD GREEN "3." RESET " Profil\n");
    }
    printf(BOLD RED "0." RESET " Keluar\n");
}

// Fungsi untuk menampilkan pesan kesalahan dengan warna merah
void showError(const char *message)
{
    printf(RED BOLD "[ERROR]" RESET " %s\n", message);
}

// Fungsi untuk menampilkan data dalam bentuk tabel dengan warna
void displayTable(const char *headers[], const char *rows[][10], int rowCount, int columnCount)
{
    printf("\n");

    // Print headers
    printf(BG_CYAN BOLD);
    for (int i = 0; i < columnCount; i++)
    {
        printf("%-20s", headers[i]);
    }
    printf(RESET "\n");

    // Print separator
    printf(BG_CYAN);
    for (int i = 0; i < columnCount; i++)
    {
        printf("--------------------");
    }
    printf(RESET "\n");

    // Print rows
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            if (i % 2 == 0)
            {
                printf(GREEN "%-20s" RESET, rows[i][j]);
            }
            else
            {
                printf(CYAN "%-20s" RESET, rows[i][j]);
            }
        }
        printf("\n");
    }
}

#include <stdio.h>
#include <string.h>
#include "all.h"

// // Fungsi login sederhana
// int loginAsAdmin()
// {
//     char username[50], password[50];

//     printf("Username: ");
//     scanf("%s", username);
//     printf("Password: ");
//     scanf("%s", password);

//     // Simulasi admin login
//     if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0)
//     {
//         printf("\nLogin berhasil! Selamat datang, Admin.\n");
//         return 1; // Login berhasil
//     }

//     printf("\nLogin gagal. Username atau password salah.\n");
//     return 0; // Login gagal
// }

// // Menu utama setelah login sebagai admin
// void adminMenu()
// {
//     int choice;

//     do
//     {
//         printf("\n=== Menu Admin ===\n");
//         printf("1. Tampilkan Data Kota\n");
//         printf("2. Tampilkan Data Bioskop\n");
//         printf("3. Tampilkan Data Studio\n");
//         printf("4. Tampilkan Data Film\n");
//         printf("5. Tambah Data Film\n");
//         printf("0. Logout\n");
//         printf("Pilihan Anda: ");
//         scanf("%d", &choice);

//         switch (choice)
//         {
//         case 1:
//             displayKotaFromFile();
//             break;
//         case 2:
//             displayBioskopFromFile();
//             break;
//         case 3:
//             displayStudioFromFile();
//             break;
//         case 4:
//             displayFilmFromFile();
//             break;
//         case 0:
//             printf("Logout berhasil. Sampai jumpa!\n");
//             break;
//         case 9:
//             break;

//         default:
//             printf("Pilihan tidak valid.\n");
//         }
//     } while (choice != 0);
// }

// int main()
// {
//             // registerUser();

//     printf("=== Sistem Manajemen Bioskop ===\n");

//     if (loginAsAdmin())
//     {
//         adminMenu();
//     }
//     else
//     {
//         printf("Akses ditolak. Program akan keluar.\n");
//     }

//     return 0;
// }

// Fungsi utama
int main() {
    User *currentUser = NULL;
    
    while (1) {
        handleMenu(&currentUser);
    }
    
    return 0;
}

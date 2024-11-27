#include <stdio.h>
#include <string.h>
#include "kota.h"
#include "bioskop.h"
#include "studio.h"
#include "film.h"

// Fungsi login sederhana
int loginAsAdmin()
{
    char username[50], password[50];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // Simulasi admin login
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0)
    {
        printf("\nLogin berhasil! Selamat datang, Admin.\n");
        return 1; // Login berhasil
    }

    printf("\nLogin gagal. Username atau password salah.\n");
    return 0; // Login gagal
}

// Menu utama setelah login sebagai admin
void adminMenu()
{
    int choice;

    do
    {
        printf("\n=== Menu Admin ===\n");
        printf("1. Tampilkan Data Kota\n");
        printf("2. Tampilkan Data Bioskop\n");
        printf("3. Tampilkan Data Studio\n");
        printf("4. Tampilkan Data Film\n");
        printf("5. Tambah Data Film\n");
        printf("0. Logout\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayKotaFromFile();
            break;
        case 2:
            displayBioskopFromFile();
            break;
        case 3:
            displayStudioFromFile();
            break;
        case 4:
            displayFilmFromFile();
            break;
        case 5:
        {
            Film filmList[MAX_FILM];
            int filmCount = 0;

            if (!loadFilm(filmList, &filmCount))
            {
                printf("Gagal memuat data film.\n");
                break;
            }

            int bioskop_id, durasi, tersedia;
            char kode_film[10], judul[MAX_FILM_TITLE], genre[MAX_GENRE];

            printf("Masukkan ID Bioskop: ");
            scanf("%d", &bioskop_id);
            printf("Masukkan Kode Film: ");
            scanf("%s", kode_film);
            printf("Masukkan Judul Film: ");
            scanf(" %[^\n]", judul);
            printf("Masukkan Genre Film: ");
            scanf("%s", genre);
            printf("Masukkan Durasi Film (menit): ");
            scanf("%d", &durasi);
            printf("Film Tersedia? (1: Ya, 0: Tidak): ");
            scanf("%d", &tersedia);

            if (addFilm(filmList, &filmCount, bioskop_id, kode_film, judul, genre, durasi, tersedia))
            {
                printf("Film berhasil ditambahkan.\n");
                saveFilm(filmList, filmCount);
            }
            else
            {
                printf("Gagal menambahkan film.\n");
            }
            break;
        }
        case 0:
            printf("Logout berhasil. Sampai jumpa!\n");
            break;
        case 9:
            break;

        default:
            printf("Pilihan tidak valid.\n");
        }
    } while (choice != 0);
}

int main()
{
    printf("=== Sistem Manajemen Bioskop ===\n");

    if (loginAsAdmin())
    {
        adminMenu();
    }
    else
    {
        printf("Akses ditolak. Program akan keluar.\n");
    }

    return 0;
}

// Fungsi utama
// int main()
// {

// User currentUser = {1, "rief", "admin@example.com", "08123456789", "1234567890123456", "hashed_password", ADMIN, NULL};
// showWelcomeMessage();
// showMenuu(currentUser);
// User *user = NULL;
// char *menu[10]; // Pastikan cukup besar untuk menyimpan semua menu
// int menuCount = 0;
// int selection = -1;
// char menuMessage[512] = "Selamat datang di aplikasi bioskop";

// while (1)
// {
//     if (user)
//     {
//         char *newMenu[] = {
//             "Tiket ku",
//             "Pesan Tiket",
//             "Profil",
//             "Logout",
//         };

//         menuCount = 4;
//         sprintf(menuMessage, "Hallo, %s", user->name);
//         setMenu(menu, newMenu, menuCount);

//         selection = showMenu(menu, menuCount, menuMessage);

//         switch (selection)
//         {
//         case 1:
//             printf("Tiket ku\n");
//             break;
//         case 2:
//             printf("Pesan Tiket\n");
//             break;
//         case 3:
//             printf("Profil\n");
//             break;
//         case 4:
//             printf("Logout berhasil!\n");
//             free(user);
//             user = NULL;
//             break;
//         default:
//             printf("Pilihan tidak valid.\n");
//         }
//     }
//     else
//     {
//         // Menu untuk user yang belum login
//         char *newMenu[] = {
//             "Login",
//             "Register",
//             "Keluar",
//         };

//         menuCount = 3;
//         strcpy(menuMessage, "Selamat datang di aplikasi bioskop");
//         setMenu(menu, newMenu, menuCount);

//         selection = showMenu(menu, menuCount, menuMessage);

//         switch (selection)
//         {
//         case 1:
//             user = newUser();
//             loginUser(user);
//             break;
//         case 2:
//             registerUser();
//             break;
//         case 3:
//             printf("Selamat tinggal.\n");
//             exit(0);
//         default:
//             printf("Pilihan tidak valid. Coba lagi.\n");
//         }
//     }
// }

//     return 0;
// }
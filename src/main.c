#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "all.h"

// Fungsi utama halaman admin
void adminMenu(); // Halaman utama admin

// Submenu untuk setiap entitas
void kelolaKota();    // Kelola data kota
void kelolaBioskop(); // Kelola data bioskop
void kelolaStudio();  // Kelola data studio
void kelolaFilm();    // Kelola data film
void kelolaJadwal();  // Kelola data jadwal
void adminMenu()
{
    int choice;
    do
    {
        printf("\n=== HALAMAN ADMIN ===\n");
        printf("1. Kelola Kota\n");
        printf("2. Kelola Bioskop\n");
        printf("3. Kelola Studio\n");
        printf("4. Kelola Film\n");
        printf("5. Kelola Jadwal\n");
        printf("6. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            kelolaKota();
            break;
        case 2:
            kelolaBioskop();
            break;
        case 3:
            kelolaStudio();
            break;
        case 4:
            kelolaFilm();
            break;
        case 5:
            kelolaJadwal();
            break;
        case 6:
            printf("Keluar dari halaman admin.\n");
            break;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 6);
}

// Submenu untuk Kelola Kota
void kelolaKota()
{
    int choice;
    do
    {
        printf("\n--- KELOLA KOTA ---\n");
        printf("1. Tambah Kota\n");
        printf("2. Tampilkan Semua Kota\n");
        printf("3. Kembali\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addKota();
            break;
        case 2:
            displayKotaFromFile();
            break;
        case 3:
            return;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 3);
}

// Submenu untuk Kelola Bioskop
void kelolaBioskop()
{
    int choice;
    do
    {
        printf("\n--- KELOLA BIOSKOP ---\n");
        printf("1. Tambah Bioskop\n");
        printf("2. Tampilkan Semua Bioskop\n");
        printf("3. Kembali\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBioskop();
            break;
        case 2:
            displayBioskopFromFile();
            break;
        case 3:
            return;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 3);
}

// Submenu untuk Kelola Studio
void kelolaStudio()
{
    int choice;
    do
    {
        printf("\n--- KELOLA STUDIO ---\n");
        printf("1. Tambah Studio\n");
        printf("2. Tampilkan Semua Studio\n");
        printf("3. Kembali\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudio();
            break;
        case 2:
            displayStudioFromFile();
            break;
        case 3:
            return;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 3);
}

// Submenu untuk Kelola Film
void kelolaFilm()
{
    int choice;
    do
    {
        printf("\n--- KELOLA FILM ---\n");
        printf("1. Tambah Film\n");
        printf("2. Tampilkan Semua Film\n");
        printf("3. Kembali\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addFilm();
            break;
        case 2:
            displayFilmFromFile();
            break;
        case 3:
            return;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 3);
}

// Submenu untuk Kelola Jadwal
void kelolaJadwal()
{
    int choice;
    do
    {
        printf("\n--- KELOLA JADWAL ---\n");
        printf("1. Tambah Jadwal\n");
        printf("2. Tampilkan Semua Jadwal\n");
        printf("3. Tambah Jeda ke Jadwal\n");
        printf("4. Filter Jadwal Berdasarkan Film\n");
        printf("5. Filter Jadwal Berdasarkan Studio\n");
        printf("6. Kembali\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addJadwal();
            break;
        case 2:
            displayJadwal();
            break;
        case 3:
        {
            int jeda;
            printf("Masukkan jeda (menit): ");
            scanf("%d", &jeda);
            tambahJeda(jeda);
            break;
        }
        case 4:
        {
            int film_id;
            printf("Masukkan ID Film: ");
            scanf("%d", &film_id);
            displayJadwalByFilm(film_id);
            break;
        }
        case 5:
        {
            int studio_id;
            printf("Masukkan ID Studio: ");
            scanf("%d", &studio_id);
            displayJadwalByStudio(studio_id);
            break;
        }
        case 6:
            return;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 6);
}

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
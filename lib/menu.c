#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "all.h"

// ================================== core ================================== //

void guestMenu()
{
    int selection;

    char *menu[] = {
        "Login",
        "Register",
        "Keluar",
    };

    char *header[] = {
        GREEN "====================================================\n",
        "      Selamat datang di Sistem Pemesanan Tiket!     \n",
        "====================================================\n" RESET,
        NULL,
    };

    while (1)
    {
        selection = showMenu(menu, 3, header);

        if (selection == 1)
        {
            loginUser();
        }
        else if (selection == 2)
        {
            registerUser();
        }
        else if (selection == 3)
        {
            printf("Terima kasih telah menggunakan aplikasi ini!\n");
            exit(0);
        }

        if (isLogin())
        {
            break;
        }
    }
}

void userMenu()
{
    int selection;

    char *menu[] = {
        "Tiket ku",
        "Pesan Tiket",
        "Profil",
        "Logout",
    };

    char *header[] = {
        "====================================================\n",
        BOLD BLUE "      Selamat datang di Sistem Pemesanan Tiket!     \n" RESET,
        "====================================================\n",
        NULL};

    while (1)
    {
        selection = showMenu(menu, 4, header);

        switch (selection)
        {
        case 1:
            printf("Menampilkan tiket Anda...\n");

            break;
        case 2:
            printf("Halaman pemesanan tiket...\n");

            break;
        case 3:
            printf("Menampilkan profil...\n");

            break;
        case 4:
            clearSession();
            printf("Berhasil logout!\n");

            return;
        default:
        }
    }
}

void superAdminMenu()
{
    int selection;
    char *menu[] = {
        "Kelola Pengguna",
        "Kelola Kota",
        "Kelola Bioskop",
        "Laporan Penjualan",
        "Logout",
    };

    char *header[] = {
        "====================================================\n",
        "      Selamat datang di Sistem Pemesanan Tiket!      \n",
        "====================================================\n" RESET,
        NULL,
    };

    while (1)
    {
        selection = showMenu(menu, 5, header);

        switch (selection)
        {
        case 1:
            printf("Menampilkan Kelola Pengguna...\n");
            menuUser();
            break;
        case 2:
            printf("Menampilkan Kelola Kota...\n");
            menuKota();
            break;
        case 3:
            printf("Menampilkan Kelola Bioskop...\n");
            menuBioskop();
            break;
        case 8:
            printf("Menampilkan Laporan Penjualan...\n");
            // salesReport();
            break;
        case 10:
            clearSession();
            printf("Berhasil logout!\n");
            return;
        default:
            printf(RED "Pilihan tidak valid!\n" RESET);
        }
    }
}

void managerMenu()
{
    int selection;
    char *menu[] = {
        "Kelola Studio",
        "Kelola Film",
        "Kelola Jadwal",
        "Laporan Penjualan",
        "Logout",
    };

    char *header[] = {
        "====================================================\n",
        "      Selamat datang di Sistem Pemesanan Tiket!      \n",
        "====================================================\n" RESET,
        NULL,
    };

    while (1)
    {
        selection = showMenu(menu, 5, header);

        switch (selection)
        {
        case 1:
            printf("Menampilkan Kelola Studio...\n");
            menuStudio();
            break;
        case 2:
            printf("Menampilkan Kelola Film...\n");
            menuFilm();
            break;
        case 3:
            printf("Menampilkan Kelola Jadwal...\n");
            menuJadwal();
            break;
        case 4:
            printf("Menampilkan Laporan Penjualan...\n");
            // salesReport();
            break;
        case 5:
            clearSession();
            printf("Berhasil logout!\n");
            return;
        default:
            printf(RED "Pilihan tidak valid!\n" RESET);
        }
    }
}

void petugasMenu()
{
    int selection;
    char *menu[] = {
        "Lihat Studio",
        "Lihat Film",
        "Lihat Jadwal",
<<<<<<< HEAD
        "Transaksi",
=======
        "Transaksi"
>>>>>>> c2d71e003e9e9cb8a98cb2794d88546dc23a81ea
        "Laporan Penjualan",
        "Logout",
    };

    char *header[] = {
        "====================================================\n",
        "      Selamat datang di Sistem Pemesanan Tiket!      \n",
        "====================================================\n" RESET,
        NULL,
    };

    while (1)
    {
<<<<<<< HEAD
        selection = showMenu(menu, 6, header);
=======
        selection = showMenu(menu, 5, header);
>>>>>>> c2d71e003e9e9cb8a98cb2794d88546dc23a81ea

        switch (selection)
        {
        case 1:
            printf("Menampilkan Kelola Studio...\n");
<<<<<<< HEAD
            petugasLihatStudio();
            break;
        case 2:
            printf("Menampilkan Kelola Film...\n");
            petugasLihatFilm();
            break;
        case 3:
            printf("Menampilkan Kelola Jadwal...\n");
            petugasLihatJadwal();
            break;
        case 4:
            printf("Menampilkan Menu Penjualan...\n");
            petugasTransaksi();
            break;
        case 5:
            printf("Menampilkan Laporan Penjualan...\n");
            // salesReport();
            break;
        case 6:
=======
            menuStudio();
            break;
        case 2:
            printf("Menampilkan Kelola Film...\n");
            menuFilm();
            break;
        case 3:
            printf("Menampilkan Kelola Jadwal...\n");
            menuJadwal();
            break;
        case 4:
            printf("Menampilkan Laporan Penjualan...\n");
            // salesReport();
            break;
        case 5:
>>>>>>> c2d71e003e9e9cb8a98cb2794d88546dc23a81ea
            clearSession();
            printf("Berhasil logout!\n");
            return;
        default:
            printf(RED "Pilihan tidak valid!\n" RESET);
        }
    }
}

void handleMenu()
{
    while (1)
    {
        if (!isLogin())
        {
            guestMenu();
        }
        else
        {
            User *user = getCurrentUser();
            if (user->role == SUPER_ADMIN)
            {
                superAdminMenu();
            }
            else if (user->role == MANAGER)
            {
                managerMenu();
            }
            else if (user->role == PETUGAS)
            {
                petugasMenu();
            }
            else
            {
                userMenu();
            }
        }
    }
}

int showMenu(char *menu[], int menuLength, char **header)
{
    int key = 0;
    int selected = 0;

    while (1)
    {
        system("cls");

        for (int i = 0; header[i] != NULL; i++)
        {
            printf("%s", header[i]);
        }

        for (int i = 0; i < menuLength; i++)
        {
            if (selected == i)
            {
                printf(BLUE BOLD "  -> %s\n" RESET, menu[i]);
            }
            else
            {
                printf("     %s\n", menu[i]);
            }
        }

        printf("\nGunakan panah atas/bawah untuk memilih dan Enter untuk memilih\n");

        key = getch();

        if (key == 224)
        {
            key = getch();
            if (key == 72 && selected > 0)
            {
                selected--;
            }
            else if (key == 80 && selected < menuLength - 1)
            {
                selected++;
            }
        }
        else if (key == 13)
        {
            break;
        }
    }

    return selected + 1;
}
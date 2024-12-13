#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "user.h"
#include "auth.h"

// ================================== core ================================== //

void guestMenu()
{
    int selection;
    char *menu[] = {
        "Login",
        "Register",
        "Keluar"};

    while (1)
    {
        selection = showMenu(menu, 3, "=== Menu Tamu ===");

        switch (selection)
        {
        case 1:
            loginUser();
            break;
        case 2:
            registerUser();
            break;
        case 3:
            printf("Terima kasih telah menggunakan aplikasi ini!\n");
            exit(0);
        default:
            printf("Pilihan tidak valid!\n");
            getch();
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
        "Logout"};

    while (1)
    {
        selection = showMenu(menu, 4, "=== Menu Pengguna ===");

        switch (selection)
        {
        case 1:
            printf("Menampilkan tiket Anda...\n");
            getch();
            break;
        case 2:
            printf("Halaman pemesanan tiket...\n");
            getch();
            break;
        case 3:
            printf("Menampilkan profil...\n");
            getch();
            break;
        case 4:
            clearSession();
            printf("Berhasil logout!\n");
            getch();
            return;
        default:
            printf("Pilihan tidak valid!\n");
            getch();
        }
    }
}

void adminMenu()
{
    int selection;
    char *menu[] = {
        "Kelola Pengguna",
        "Kelola Tiket",
        "Laporan Penjualan",
        "Profil Admin",
        "Logout"};

    while (1)
    {
        selection = showMenu(menu, 5, "=== Menu Admin ===");

        switch (selection)
        {
        case 1:
            printf("Menampilkan kelola pengguna...\n");
            getch();
            break;
        case 2:
            printf("Menampilkan kelola tiket...\n");
            getch();
            break;
        case 3:
            printf("Menampilkan laporan penjualan...\n");
            getch();
            break;
        case 4:
            printf("Menampilkan profil admin...\n");
            getch();
            break;
        case 5:
            clearSession();
            printf("Berhasil logout!\n");
            getch();
            return;
        default:
            printf("Pilihan tidak valid!\n");
            getch();
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
            if (user->role == ADMIN)
            {
                adminMenu();
            }
            else
            {
                userMenu();
            }
        }
    }
}

int showMenu(char *menu[], int menuLength, char *menuMessage)
{
    int key = 0;
    int selected = 0;

    while (1)
    {
        system("cls");
        printf("\n%s\n\n", menuMessage);

        for (int i = 0; i < menuLength; i++)
        {
            if (selected == i)
            {
                printf("  -> %s\n", menu[i]);
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
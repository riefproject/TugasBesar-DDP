#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "user.h"
#include "auth.h"
#include "menu.h"

// Fungsi utama
int main()
{
    User *user = NULL;
    char *menu[10]; // Pastikan cukup besar untuk menyimpan semua menu
    int menuCount = 0;
    int selection = -1;
    char menuMessage[512] = "Selamat datang di aplikasi bioskop";

    while (1)
    {
        if (user)
        {
            char *newMenu[] = {
                "Tiket ku",
                "Pesan Tiket",
                "Profil",
                "Logout",
            };

            menuCount = 4;
            sprintf(menuMessage, "Hallo, %s", user->name);
            setMenu(menu, newMenu, menuCount);

            selection = showMenu(menu, menuCount, menuMessage);

            switch (selection)
            {
            case 1:
                printf("Tiket ku\n");
                break;
            case 2:
                printf("Pesan Tiket\n");
                break;
            case 3:
                printf("Profil\n");
                break;
            case 4:
                printf("Logout berhasil!\n");
                free(user);
                user = NULL;
                break;
            default:
                printf("Pilihan tidak valid.\n");
            }
        }
        else
        {
            // Menu untuk user yang belum login
            char *newMenu[] = {
                "Login",
                "Register",
                "Keluar",
            };

            menuCount = 3;
            strcpy(menuMessage, "Selamat datang di aplikasi bioskop");
            setMenu(menu, newMenu, menuCount);

            selection = showMenu(menu, menuCount, menuMessage);

            switch (selection)
            {
            case 1:
                user = newUser();
                loginUser(user);
                break;
            case 2:
                registerUser();
                break;
            case 3:
                printf("Selamat tinggal.\n");
                exit(0);
            default:
                printf("Pilihan tidak valid. Coba lagi.\n");
            }
        }
    }

    return 0;
}
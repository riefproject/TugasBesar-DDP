#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>

#include "menu.h"
#include "display.h"

int main()
{
    system("cls");
    puts(
        "                                                                                                               \n"
        "                                                           ____  _           _               _                 \n"
        "                                                          | __ )(_) ___  ___| | _____  _ __ | | ___   _        \n"
        "                                                          |  _ \\| |/ _ \\/ __| |/ / _ \\| '_ \\| |/ / | | |   \n"
        "                                                          | |_) | | (_) \\__ \\   < (_) | |_) |   <| |_| |     \n"
        "                                                          |____/|_|\\___/|___/_|\\_\\___/| .__/|_|\\_\\\\__,_| \n"
        "                                                                                      |_|                      \n"
        "                                                                                                               \n"
        "                                                             Selamat datang di Sistem Pemesanan Tiket!         \n");

    const int total = 40;
    const char spinner[] = "|/-\\";
    int spinner_index = 0;

    for (int i = 0; i <= total; i++)
    {
        printf("\r                                                          [");
        for (int j = 0; j < i; j++)
        {
            printf(BLUE BOLD "#");
        }
        for (int j = i; j < total; j++)
        {
            printf(" ");
        }
        printf("] %c", spinner[spinner_index]);

        fflush(stdout);
        spinner_index = (spinner_index + 1) % 4;
        usleep(100000);
    }

    handleMenu();

    return 0;
}
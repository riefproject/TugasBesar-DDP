#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"

// Fungsi untuk menampilkan menu utama
void tampilkanMenu()
{
    printf("1. Login sebagai Admin\n");
    printf("2. Login sebagai User\n");
    printf("3. Registrasi User Baru\n");
    printf("4. Exit\n");
}

int main()
{
    User user;
    int pilihan;
    printf("Selamat datang di Sistem Reservasi Hotel!\n");

    while (1)
    {
        tampilkanMenu();
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar(); // untuk menghapus newline setelah input

        switch (pilihan)
        {
        case 1:
            // authAdmin();
            break;
        case 2:
            authUser(&user);
            break;
        case 3:
            addUser();
            break;
        case 4:
            printf("Keluar dari program.\n");
            exit(0);
        default:
            printf("Pilihan tidak valid. Coba lagi.\n");
        }
    }
    return 0;
}

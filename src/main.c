#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "all.h"

void printTable(User *users, int count, int page, int perPage, int selection)
{
    int idWidth = 2, usernameWidth = 8, nameWidth = 4;
    int emailWidth = 5, notelpWidth = 6, roleWidth = 4;

    int start = (page - 1) * perPage;
    int end = start + perPage;
    if (end > count)
        end = count;

    for (int i = start; i < end; i++)
    {
        int idLen = snprintf(NULL, 0, "%d", users[i].id);
        if (idLen > idWidth)
            idWidth = idLen;
        if ((int)strlen(users[i].username) > usernameWidth)
            usernameWidth = strlen(users[i].username);
        if ((int)strlen(users[i].name) > nameWidth)
            nameWidth = strlen(users[i].name);
        if ((int)strlen(users[i].email) > emailWidth)
            emailWidth = strlen(users[i].email);
        if ((int)strlen(users[i].notelp) > notelpWidth)
            notelpWidth = strlen(users[i].notelp);
    }

    // Lebar total tabel
    int tableWidth = idWidth + usernameWidth + nameWidth +
                     emailWidth + notelpWidth + roleWidth + 20;

    // Cetak garis atas tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak header tabel
    printf("[*]| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           idWidth, "ID",
           usernameWidth, "Username",
           nameWidth, "Name",
           emailWidth, "Email",
           notelpWidth, "Notelp",
           roleWidth, "Role");

    // Cetak garis bawah header
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    for (int i = start; i < end; i++)
    {
        if (selection == i + 1)
        {
            printf("[*]| %-*d | %-*s | %-*s | %-*s | %-*s | %-*d |\n",
                   idWidth, users[i].id,
                   usernameWidth, users[i].username,
                   nameWidth, users[i].name,
                   emailWidth, users[i].email,
                   notelpWidth, users[i].notelp,
                   roleWidth, users[i].role);
        }
        else
        {
            printf("[ ]| %-*d | %-*s | %-*s | %-*s | %-*s | %-*d |\n",
                   idWidth, users[i].id,
                   usernameWidth, users[i].username,
                   nameWidth, users[i].name,
                   emailWidth, users[i].email,
                   notelpWidth, users[i].notelp,
                   roleWidth, users[i].role);
        }
    }

    // Cetak garis bawah tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Informasi halaman
    printf("Page %d of %d\n", page, (count + perPage - 1) / perPage);
}

// int main()
// {
//     FILE *file = fopen(USER_DATABASE_NAME, "r");
//     if (!file)
//     {
//         printf("File gagal dibuka.\n");
//         return 1;
//     }

//     int count = 0;
//     int i = 0;

//     User user;

//     while (fscanf(file, USER_GETTER_FORMAT,
//                   &user.id,
//                   user.username,
//                   user.password,
//                   user.name,
//                   user.email,
//                   user.notelp,
//                   &user.role) != EOF)
//     {
//         count++;
//     }

//     rewind(file);

//     User users[count];

//     while (fscanf(file, USER_GETTER_FORMAT,
//                   &users[i].id,
//                   users[i].username,
//                   users[i].password,
//                   users[i].name,
//                   users[i].email,
//                   users[i].notelp,
//                   &users[i].role) != EOF)
//     {
//         i++;
//     }

//     int page = 1, perPage = 10, selection = 1, pointer = 1;
//     int command;

//     while (1)
//     {
//         system("cls");
//         // Cetak tabel
//         selection = (page - 1) * perPage + pointer;

//         printf("%d/n", selection);

//         printTable(users, count, page, perPage, selection);

//         // Navigasi
//         printf("\n[Arrow >] Next Page | [Arrow <] Previous Page | [E] Exit: ");
//         // scanf(" %c", &command);

//         command = getch();

//         // printf("%d", command);

//         if (command == 224)
//         {
//             command = getch();
//             // printf("%d", command);

//             if (command == 77)
//             {
//                 pointer = 1;
//                 if (page * perPage < count)
//                     page++;
//                 else
//                     printf("Sudah di halaman terakhir.\n");
//             }
//             else if (command == 75)
//             {
//                 pointer = 1;
//                 if (page > 1)
//                     page--;
//                 else
//                     printf("Sudah di halaman pertama.\n");
//             }
//             else if (command == 72)
//             {
//                 if (pointer > 1)
//                 {
//                     pointer--;
//                 }
//             }
//             else if (command == 80)
//             {
//                 if (pointer < perPage)
//                 {
//                     pointer++;
//                 }
//             }
//         }
//         else if (command == 32)
//         {
//             printf("data terpilih %d", selection);
//             break;
//         }
//         else if (command == 'E' || command == 'e')
//         {
//             break;
//         }
//         else
//         {
//             printf("perintah tidak ditemukan");
//         }
//     }

//     fclose(file);
//     return 0;
// }

int main()
{
    // Inisialisasi sistem, jika diperlukan
    printf("Selamat datang di Sistem Pemesanan Tiket!\n\n");
    
    // Jalankan menu utama
    handleMenu();

    return 0;
}

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "display.h"
#include "studio.h"
#include "film.h"
#include "jadwal.h"

void petugasLihatStudio()
{
    Studio *studioList;
    int count = loadStudio(&studioList);

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        system("cls");
        selection = (page - 1) * perPage + pointer;

        printStudioTable(studioList, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page\n");
        printf("[Arrow /\\] | [Arrow \\/] Arrow Up/Down To Selecting\n");
        printf(BG_RED WHITE "[E] Exit" RESET "\n" RESET);

        command = getch();

        if (command == 224)
        {
            command = getch();

            if (command == 77)
            {
                pointer = 1;
                if (page * perPage < count)
                    page++;
                else
                {
                    printf("Sudah di halaman terakhir.\n");
                    sleep(1);
                }
            }
            else if (command == 75)
            {
                pointer = 1;
                if (page > 1)
                    page--;
                else
                {
                    printf("Sudah di halaman pertama.\n");
                    sleep(1);
                }
            }
            else if (command == 72)
            {
                if (pointer > 1)
                {
                    pointer--;
                }
            }
            else if (command == 80)
            {
                if (pointer < perPage && (page - 1) * perPage + pointer < count)
                {
                    pointer++;
                }
            }
        }
        else if (command == 'E' || command == 'e')
        {
            free(studioList);
            break;
        }
        else
        {
            printf(YELLOW BOLD "Command not found\n" RESET);
            sleep(1);
        }
    }
}

int petugasLihatFilm()
{
    Film *films;
    int count = loadFilm(&films);

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        system("cls");
        selection = (page - 1) * perPage + pointer;

        printFilmTable(films, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page");
        printf("[Arrow /\\] | [Arrow \\/] Arrow Up/Down To Selecting\n");
        printf(BG_RED WHITE "[E] Exit\n" RESET);

        command = getch();

        if (command == 224)
        {
            command = getch();

            if (command == 77)
            {
                pointer = 1;
                if (page * perPage < count)
                    page++;
                else
                {
                    printf("Sudah di halaman terakhir.\n");
                    sleep(1);
                }
            }
            else if (command == 75)
            {
                pointer = 1;
                if (page > 1)
                    page--;
                else
                {
                    printf("Sudah di halaman pertama.\n");
                    sleep(1);
                }
            }
            else if (command == 72)
            {
                if (pointer > 1)
                {
                    pointer--;
                }
            }
            else if (command == 80)
            {
                if (pointer < perPage && (page - 1) * perPage + pointer < count)
                {
                    pointer++;
                }
            }
        }
        else if (command == 'E' || command == 'e')
        {
            free(films);
            break;
        }
        else
        {
            printf(YELLOW BOLD "Perintah tidak ditemukan\n" RESET);
            sleep(1);
        }
    }
}

int petugasLihatJadwal()
{
    Jadwal *jadwals;
    int count = loadJadwal(&jadwals);

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        system("cls");
        selection = (page - 1) * perPage + pointer;

        printf(GREEN "====================================================\n");
        printf("             Menu Management Jadwal                 \n");
        printf("====================================================\n" RESET);

        printJadwalTable(jadwals, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page");
        printf("[Arrow /\\] | [Arrow \\/] Arrow Up/Down To Selecting\n");
        printf(GREEN "[ENTER]: Enter To Select Studio\n\n" RESET);

        command = getch();

        if (command == 224)
        {
            command = getch();

            if (command == 77) // Arrow Right -> Next Page
            {
                pointer = 1;
                if (page * perPage < count)
                    page++;
                else
                {
                    printf(BLUE "Sudah di halaman terakhir.\n");
                    sleep(1);
                }
            }
            else if (command == 75) // Arrow Left -> Previous Page
            {
                pointer = 1;
                if (page > 1)
                    page--;
                else
                {
                    printf(BLUE "Sudah di halaman pertama.\n");
                    sleep(1);
                }
            }
            else if (command == 72) // Arrow Up -> Move up in list
            {
                if (pointer > 1)
                {
                    pointer--;
                }
            }
            else if (command == 80) // Arrow Down -> Move down in list
            {
                if (pointer < perPage && (page - 1) * perPage + pointer < count)
                {
                    pointer++;
                }
            }
        }
        else if (command == 'E' || command == 'e') // Exit
        {
            free(jadwals);
            break;
        }
        else
        {
            printf(YELLOW BOLD "Perintah tidak ditemukan\n" RESET);
            sleep(1);
        }
    }
}

int petugasTransaksi()
{
    int filmID = 0;
    Film *films;
    int count = loadFilm(&films);

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        system("cls");
        selection = (page - 1) * perPage + pointer;

        printFilmTable(films, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page");
        printf("[Arrow /\\] | [Arrow \\/] Arrow Up/Down To Selecting\n");

        command = getch();

        if (command == 224)
        {
            command = getch();

            if (command == 77)
            {
                pointer = 1;
                if (page * perPage < count)
                    page++;
                else
                {
                    printf("Sudah di halaman terakhir.\n");
                    sleep(1);
                }
            }
            else if (command == 75)
            {
                pointer = 1;
                if (page > 1)
                    page--;
                else
                {
                    printf("Sudah di halaman pertama.\n");
                    sleep(1);
                }
            }
            else if (command == 72)
            {
                if (pointer > 1)
                {
                    pointer--;
                }
            }
            else if (command == 80)
            {
                if (pointer < perPage && (page - 1) * perPage + pointer < count)
                {
                    pointer++;
                }
            }
        }
        else if (command == 13)
        {
            filmID = films[selection - 1].id;
            free(films);
            break;
        }
        else
        {
            printf(YELLOW BOLD "Perintah tidak ditemukan\n" RESET);
            sleep(1);
        }
    }

    int jadwalID = 0;
    Jadwal *jadwals;
    int count = loadJadwalIsHasFilmId(&jadwals, filmID);

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        system("cls");
        selection = (page - 1) * perPage + pointer;

        printJadwalTable(jadwals, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page");
        printf("[Arrow /\\] | [Arrow \\/] Arrow Up/Down To Selecting\n");
        printf(GREEN "[ENTER]: Enter To Select Studio\n\n" RESET);

        command = getch();

        if (command == 224)
        {
            command = getch();

            if (command == 77) // Arrow Right -> Next Page
            {
                pointer = 1;
                if (page * perPage < count)
                    page++;
                else
                {
                    printf(BLUE "Sudah di halaman terakhir.\n");
                    sleep(1);
                }
            }
            else if (command == 75) // Arrow Left -> Previous Page
            {
                pointer = 1;
                if (page > 1)
                    page--;
                else
                {
                    printf(BLUE "Sudah di halaman pertama.\n");
                    sleep(1);
                }
            }
            else if (command == 72) // Arrow Up -> Move up in list
            {
                if (pointer > 1)
                {
                    pointer--;
                }
            }
            else if (command == 80) // Arrow Down -> Move down in list
            {
                if (pointer < perPage && (page - 1) * perPage + pointer < count)
                {
                    pointer++;
                }
            }
        }
        else if (command == 13)
        {
            int jadwalID = jadwals[selection - 1].id;
            free(jadwals);
            return jadwalID;
        }
        else
        {
            printf(YELLOW BOLD "Perintah tidak ditemukan\n" RESET);
            sleep(1);
        }
    }

    
}
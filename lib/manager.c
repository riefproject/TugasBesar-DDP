#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "display.h"
#include "studio.h"
#include "film.h"
#include "jadwal.h"
#include "auth.h"
#include "transaksi.h"
#include "manager.h"

int managerMenuTransaksi()
{
    Transaksi *transaksis;
    int count = loadTransaksiKota(&transaksis);

    if (count < 0)
    {
        printf(RED "Gagal memuat data transaksi.\n" RESET);
        return -1;
    }

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        system("cls");
        selection = (page - 1) * perPage + pointer;

        printf(GREEN "====================================================\n");
        printf("             Menu Management Transaksi              \n");
        printf("====================================================\n" RESET);

        printTransaksiTable(transaksis, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page");
        printf(BG_RED WHITE "[E] Exit" RESET "\n" RESET);

        command = getch();

        if (command == 224)
        {
            command = getch();

            if (command == 77) // Arrow Right
            {
                pointer = 1;
                if (page * perPage < count)
                    page++;
                else
                {
                    printf(BLUE "Sudah di halaman terakhir.\n" RESET);
                    sleep(1);
                }
            }
            else if (command == 75) // Arrow Left
            {
                pointer = 1;
                if (page > 1)
                    page--;
                else
                {
                    printf(BLUE "Sudah di halaman pertama.\n" RESET);
                    sleep(1);
                }
            }
            else if (command == 72) // Arrow Up
            {
                if (pointer > 1)
                {
                    pointer--;
                }
            }
            else if (command == 80) // Arrow Down
            {
                if (pointer < perPage && (page - 1) * perPage + pointer < count)
                {
                    pointer++;
                }
            }
        }
        else if (command == 'E' || command == 'e') // Exit
        {
            free(transaksis);
            return 0;
        }
        else
        {
            printf(YELLOW BOLD "Perintah tidak ditemukan\n" RESET);
            sleep(1);
        }
    }
}

int loadTransaksiKota(Transaksi **transaksis)
{
    FILE *file = fopen(TRANSAKSI_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int count = countTransaksiData();
    if (count <= 0)
    {
        fclose(file);
        return count;
    }

    *transaksis = (Transaksi *)malloc(count * sizeof(Transaksi));
    if (*transaksis == NULL)
    {
        printf("Gagal mengalokasi memori.\n");
        fclose(file);
        return -1;
    }

    Transaksi temp;
    int i = 0;
    while (fscanf(file, TRANSAKSI_GETTER_FORMAT,
                  temp.id,
                  temp.user_id,
                  temp.jadwal_id,
                  temp.harga,
                  temp.bayar,
                  temp.kembali,
                  (int *)temp.jenisPembelian) != EOF)
    {
        Jadwal *jadwal = findJadwalById(temp.jadwal_id);
        if (jadwal == NULL)
        {
            continue;
        }

        Studio *studio = findStudioById(jadwal->studio_id);
        if (studio == NULL)
        {
            continue;
        }

        Bioskop *bioskop = findStudioById(studio->bioskop_id);
        if (bioskop == NULL)
        {
            continue;
        }

        User *user = getCurrentUser();

        if (bioskop->manager_id == user->id)
        {
            (*transaksis)[i] = temp;
            i++;
        }
    }

    fclose(file);
    return count;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>

#include "display.h"
#include "transaksi.h"

// ================================== Main Menu ================================ //

int menuTransaksi()
{
    Transaksi *transaksis;
    int count = loadTransaksi(&transaksis);

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

// ================================== Action ================================== //

int countTicketsSold(int jadwal_id)
{
    FILE *file = fopen(TRANSAKSI_DATABASE_NAME, "r");
    if (!file)
    {
        printf("Error membuka file transaksi.\n");
        return -1;
    }

    Transaksi transaksi;
    int count = 0;

    while (fscanf(file, TRANSAKSI_GETTER_FORMAT,
                  &transaksi.id, &transaksi.user_id, &transaksi.jadwal_id,
                  &transaksi.harga, &transaksi.bayar, &transaksi.kembali,
                  &transaksi.jenisPembelian) == 7)
    {
        if (transaksi.jadwal_id == jadwal_id)
        {
            count++; // Tiket terjual bertambah
        }
    }

    fclose(file);
    return count;
}

Transaksi *createTransaksi(int user_id, int jadwal_id, int harga, int bayar, JenisPembelian jenisPembelian)
{
    Transaksi *transaksi = malloc(sizeof(Transaksi));
    if (!transaksi)
    {
        printf("Alokasi memori gagal, lokasi: createTransaksi\n");
        return NULL;
    }

    transaksi->id = getLastAvailableID(TRANSAKSI_DATABASE_NAME);
    transaksi->user_id = user_id;
    transaksi->jadwal_id = jadwal_id;
    transaksi->harga = harga;
    transaksi->bayar = bayar;
    transaksi->kembali = bayar - harga;
    transaksi->jenisPembelian = jenisPembelian;

    FILE *file = fopen(TRANSAKSI_DATABASE_NAME, "a");
    if (!file)
    {
        printf("Gagal membuka file database transaksi.\n");
        free(transaksi);
        return NULL;
    }

    fprintf(file, TRANSAKSI_SETTER_FORMAT,
            transaksi->id,
            transaksi->user_id,
            transaksi->jadwal_id,
            transaksi->harga,
            transaksi->bayar,
            transaksi->kembali,
            transaksi->jenisPembelian);

    fclose(file);

    return transaksi;
}

// ================================== Utils ================================== //

int countTransaksiData()
{
    FILE *file = fopen(TRANSAKSI_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int count = 0;
    Transaksi transaksi;
    while (fscanf(file, TRANSAKSI_GETTER_FORMAT,
                  &transaksi.id,
                  &transaksi.user_id,
                  &transaksi.jadwal_id,
                  &transaksi.harga,
                  &transaksi.bayar,
                  &transaksi.kembali,
                  (int *)&transaksi.jenisPembelian) != EOF)
    {
        count++;
    }
    fclose(file);
    return count;
}

int loadTransaksi(Transaksi **transaksis)
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

    rewind(file);
    int i = 0;
    while (fscanf(file, TRANSAKSI_GETTER_FORMAT,
                  &(*transaksis)[i].id,
                  &(*transaksis)[i].user_id,
                  &(*transaksis)[i].jadwal_id,
                  &(*transaksis)[i].harga,
                  &(*transaksis)[i].bayar,
                  &(*transaksis)[i].kembali,
                  (int *)&(*transaksis)[i].jenisPembelian) != EOF)
    {
        i++;
    }

    fclose(file);
    return count;
}

void printTransaksiTable(Transaksi *transaksis, int count, int page, int perPage, int selection)
{
    int idWidth = 2, userWidth = 6, jadwalWidth = 6, hargaWidth = 5;
    int bayarWidth = 5, kembaliWidth = 7, jenisWidth = 12;

    int start = (page - 1) * perPage;
    int end = start + perPage;
    if (end > count)
        end = count;

    // Hitung panjang kolom terpanjang
    for (int i = start; i < end; i++)
    {
        int idLen = snprintf(NULL, 0, "%d", transaksis[i].id);
        if (idLen > idWidth)
            idWidth = idLen;

        int userLen = snprintf(NULL, 0, "%d", transaksis[i].user_id);
        if (userLen > userWidth)
            userWidth = userLen;

        int jadwalLen = snprintf(NULL, 0, "%d", transaksis[i].jadwal_id);
        if (jadwalLen > jadwalWidth)
            jadwalWidth = jadwalLen;

        int hargaLen = snprintf(NULL, 0, "%d", transaksis[i].harga);
        if (hargaLen > hargaWidth)
            hargaWidth = hargaLen;

        int bayarLen = snprintf(NULL, 0, "%d", transaksis[i].bayar);
        if (bayarLen > bayarWidth)
            bayarWidth = bayarLen;

        int kembaliLen = snprintf(NULL, 0, "%d", transaksis[i].kembali);
        if (kembaliLen > kembaliWidth)
            kembaliWidth = kembaliLen;
    }

    int tableWidth = snprintf(NULL, 0,
                              "[ * ]| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
                              idWidth, "ID",
                              userWidth, "User",
                              jadwalWidth, "Jadwal",
                              hargaWidth, "Harga",
                              bayarWidth, "Bayar",
                              kembaliWidth, "Kembali",
                              jenisWidth, "Jenis Pembelian");

    // Cetak garis atas tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak header tabel
    printf("[ * ]| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           idWidth, "ID",
           userWidth, "User",
           jadwalWidth, "Jadwal",
           hargaWidth, "Harga",
           bayarWidth, "Bayar",
           kembaliWidth, "Kembali",
           jenisWidth, "Jenis Pembelian");

    // Cetak garis bawah header
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak isi tabel
    for (int i = start; i < end; i++)
    {
        const char *jenisString = (transaksis[i].jenisPembelian == ONLINE) ? "Online" : "Offline";

        if (selection == i + 1)
        {
            printf(BLUE BOLD "[ * ]| %-*d | %-*d | %-*d | %-*d | %-*d | %-*d | %-*s |\n" RESET,
                   idWidth, transaksis[i].id,
                   userWidth, transaksis[i].user_id,
                   jadwalWidth, transaksis[i].jadwal_id,
                   hargaWidth, transaksis[i].harga,
                   bayarWidth, transaksis[i].bayar,
                   kembaliWidth, transaksis[i].kembali,
                   jenisWidth, jenisString);
        }
        else
        {
            printf("[   ]| %-*d | %-*d | %-*d | %-*d | %-*d | %-*d | %-*s |\n",
                   idWidth, transaksis[i].id,
                   userWidth, transaksis[i].user_id,
                   jadwalWidth, transaksis[i].jadwal_id,
                   hargaWidth, transaksis[i].harga,
                   bayarWidth, transaksis[i].bayar,
                   kembaliWidth, transaksis[i].kembali,
                   jenisWidth, jenisString);
        }
    }

    // Cetak garis bawah tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Informasi halaman
    printf("Page %d of %d\n", page, (count + perPage - 1) / perPage);
}

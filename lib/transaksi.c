#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>

#include "display.h"
#include "transaksi.h"

Transaksi *createTransaksi(int user_id, int jadwal_id, int harga, int bayar)
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

    FILE *file = fopen(TRANSAKSI_DATABASE_NAME, "a");
    if (!file)
    {
        printf("Gagal membuka file database transaksi.\n");
        free(transaksi);
        return NULL;
    }

    fprintf(file, "%d,%d,%d,%d,%d,%d\n",
            transaksi->id,
            transaksi->user_id,
            transaksi->jadwal_id,
            transaksi->harga,
            transaksi->bayar,
            transaksi->kembali);

    fclose(file);

    return transaksi;
}

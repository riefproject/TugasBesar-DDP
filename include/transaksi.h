#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#define TRANSAKSI_SETTER_FORMAT "%d,%d,%d,%d,%d,%d,%d\n"
#define TRANSAKSI_GETTER_FORMAT "%d,%d,%d,%d,%d,%d,%d\n"
#define TRANSAKSI_DATABASE_NAME "db/transaksi.csv"

#include "db.h"

typedef enum
{
    ONLINE = 1,
    OFFLINE = 2
} JenisPembelian;
typedef struct
{
    int id;
    int user_id;
    int jadwal_id;
    int harga;
    int bayar;
    int kembali;
    JenisPembelian jenisPembelian;
} Transaksi;

// ================================== Main Menu ================================ //



// ================================== Action ================================== //

int countTicketsSold(int jadwal_id);

Transaksi *createTransaksi(int user_id, int jadwal_id, int harga, int bayar, JenisPembelian jenisPembelian);

// ================================== Utils ================================== //

int countTransaksiData();

int loadTransaksi(Transaksi **transaksis);

void printTransaksiTable(Transaksi *transaksis, int count, int page, int perPage, int selection);

#endif
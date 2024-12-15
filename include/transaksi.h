#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#define TRANSAKSI_SETTER_FORMAT "%d,%d,%d,%d,%d,%d\n"
#define TRANSAKSI_GETTER_FORMAT "%d,%d,%d,%d,%d,%d\n"
#define TRANSAKSI_DATABASE_NAME "db/transaksi.csv"

#include "db.h"
typedef struct
{
    int id;
    int user_id;
    int jadwal_id;
    int harga;
    int bayar;
    int kembali;
} Transaksi;



#endif
#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include "db.h"
typedef struct
{
    int id;
    int userID;
    int noTiket;
    int totalBayar;
    char pembayaran[10];

} Transaksi;

#endif
#ifndef CLIENT_H
#define CLIENT_H

#include "jadwal.h"

int clientMenuTransaksi();

int clientTransaksi();

int loadJadwalIsHasFilmId(Jadwal **jadwals, int id);

int clientLoadTransaksi(Transaksi **transaksis);

#endif
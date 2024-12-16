#ifndef PETUGAS_H
#define PETUGAS_H

#include "db.h"

int petugasMenuFilm();

int petugasMenuJadwal();

int petugasTransaksi();

int loadJadwalHariIni(Jadwal **jadwals, int film_id);

#endif
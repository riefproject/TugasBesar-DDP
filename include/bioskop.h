#ifndef BIOSKOP_H
#define BIOSKOP_H

#include "kota.h"
#define MAX_BIOSKOP_NAME 50
#define MAX_MANAGER_NAME 50
#define MAX_BIOSKOP 100
#define BIOSKOP_CSV_FILE "db/bioskop.csv" // Nama file statis untuk bioskop

typedef struct
{
    int id;
    int kota_id; // Foreign key ke tabel Kota
    char nama[MAX_BIOSKOP_NAME];
    char manager[MAX_MANAGER_NAME];
} Bioskop;

// Constructor
Bioskop createBioskop(int id, int kota_id, const char *nama, const char *manager);

// Getter
int getBioskopId(const Bioskop *bioskop);
int getBioskopKotaId(const Bioskop *bioskop);
const char *getBioskopNama(const Bioskop *bioskop);
const char *getBioskopManager(const Bioskop *bioskop);

// Setter
void setBioskopId(Bioskop *bioskop, int id);
void setBioskopKotaId(Bioskop *bioskop, int kota_id);
void setBioskopNama(Bioskop *bioskop, const char *nama);
void setBioskopManager(Bioskop *bioskop, const char *manager);

// Fungsi untuk menambahkan bioskop
int addBioskop();

// Fungsi untuk menampilkan daftar bioskop langsung dari file
void displayBioskopFromFile();

#endif

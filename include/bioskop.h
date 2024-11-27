#ifndef BIOSKOP_H
#define BIOSKOP_H

#include "kota.h"

#define MAX_BIOSKOP_NAME 50
#define MAX_MANAGER_NAME 50
#define MAX_BIOSKOP 100
#define BIOSKOP_CSV_FILE "bioskop.csv" // Nama file statis untuk bioskop

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

// Fungsi untuk membaca data bioskop dari file CSV
int loadBioskop(Bioskop bioskopList[], int *count);

// Fungsi untuk menyimpan data bioskop ke file CSV
int saveBioskop(const Bioskop bioskopList[], int count);

// Fungsi untuk menampilkan daftar bioskop
void displayBioskop(const Bioskop bioskopList[], int count, const Kota kotaList[], int kotaCount);

// Fungsi untuk mencari bioskop berdasarkan ID
Bioskop *findBioskopById(const Bioskop bioskopList[], int count, int id);

// Fungsi untuk menambah bioskop baru
int addBioskop(Bioskop bioskopList[], int *count, int kota_id, const char *nama, const char *manager);

// Validasi unik untuk nama bioskop (case insensitive)
int isBioskopNamaUnique(const Bioskop bioskopList[], int count, const char *nama);

void displayBioskopFromFile();
#endif

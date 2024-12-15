#ifndef BIOSKOP_H
#define BIOSKOP_H

#include "kota.h"
#include "user.h"

#define MAX_BIOSKOP_NAME 50
#define MAX_BIOSKOP 100
#define MAX_BIOSKOP_ALAMAT 200
#define BIOSKOP_SETTER_FORMAT "%d,%d,%s,%d,%s\n"
#define BIOSKOP_GETTER_FORMAT "%d,%d,%[^,],%d,%[^\n]\n"
#define BIOSKOP_DATABASE_NAME "db/bioskop.csv"

typedef struct
{
    int id;
    int kota_id;
    char nama[MAX_BIOSKOP_NAME];
    int manager_id;
    char alamat[MAX_BIOSKOP_ALAMAT];
} Bioskop;

typedef struct
{
    int id;
    int kota_id;
    char kota_nama[MAX_KOTA_NAME];
    char nama[MAX_BIOSKOP_NAME];
    int manager_id;
    char manager_name[MAX_USER_NAME];
    char alamat[MAX_BIOSKOP_ALAMAT];
    int jumlahStudio;
    int jumlahFilm;
    int jumlahTransaksi;
    int pendapatan;
} BioskopFullData;

// ================================== Main Menu =================================== //

int menuBioskop();
void createBioskopMenu();
void updateBioskopMenu(Bioskop bioskop);

// ================================== Getter ================================== //

int getBioskopId(const Bioskop *bioskop);
int getBioskopKotaId(const Bioskop *bioskop);
const char *getBioskopNama(const Bioskop *bioskop);
int getBioskopManagerId(const Bioskop *bioskop);

// ================================== Setter ================================== //

void setBioskopId(Bioskop *bioskop, int id);
void setBioskopKotaId(Bioskop *bioskop, int kota_id);
void setBioskopNama(Bioskop *bioskop, const char *nama);
void setBioskopManagerId(Bioskop *bioskop, int manager_id);

// ================================= Action =================================== //

Bioskop *findBioskopById(const int id);
Bioskop *findBioskopByNama(const char *nama);
Bioskop *findBioskopByManagerId(int manager_id);
Bioskop *createBioskop(const char *nama, const char *alamat, int kota_id, int manager_id);
Bioskop *updateBioskop(int id, const char *nama, const char *alamat, int kota_id, int manager_id);
int deleteBioskop(Bioskop bioskop);

// ================================== Utils ================================== //

int selectKota();
int selectManager();
int countBioskopData();
int loadBioskop(Bioskop **bioskop);
void printBioskopTable(Bioskop *bioskop, int count, int page, int perPage, int selection);

#endif

#ifndef KOTA_H
#define KOTA_H

#define MAX_NAME_KOTA_LENGTH 50
#define MAX_KOTA 100
#define TEMP_KOTA_FILE "temp/temp_kota.csv"
#define KOTA_SETTER_FORMAT "%d,%s\n"
#define KOTA_GETTER_FORMAT "%d,%s\n"
#define KOTA_DATABASE_NAME "db/kota.csv"

typedef struct
{
    int id;
    char nama[MAX_NAME_KOTA_LENGTH];
} Kota;

// ==================================== Other ================================== //

// Membandingkan string tanpa memperhatikan huruf besar/kecil
int caseInsensitiveCompare(const char *str1, const char *str2);

// ================================== Main Menu ================================ //

int menuKota();
void createKotaMenu();
void updateKotaMenu(Kota kota);

// ================================== Action ================================== //

Kota *findKota(int id);
Kota *findKotaByName(const char *nama);
Kota *createKota(const char *nama);
Kota *updateKota(const int id, const char *nama);
int deleteKota(Kota kota);

// ================================== Utils ================================== //

int countKotaData();
int loadKota(Kota **kotaList);
void printKotaTable(Kota *kotaList, int count, int page, int perPage, int selection);

#endif

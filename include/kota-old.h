#ifndef KOTA_H
#define KOTA_H

#define MAX_NAME_KOTA_LENGTH 50
#define MAX_KOTA 100
#define TEMP_KOTA_FILE "temp/temp_kota.csv"
#define KOTA_DATABASE_NAME "db/kota.csv"
#define KOTA_SETTER_FORMAT "%d,%s\n"
#define KOTA_GETTER_FORMAT "%d,%[^,]\n"

typedef struct
{
    int id;
    char nama[MAX_NAME_KOTA_LENGTH];
} Kota;

// Constructor
Kota createKota(int id, const char *nama);

// Getter
int getKotaId(const Kota *kota);
const char *getKotaNama(const Kota *kota);

// Setter
void setKotaId(Kota *kota, int id);
void setKotaNama(Kota *kota, const char *nama);

// Fungsi untuk menambahkan kota
int addKota();

// Fungsi untuk menampilkan daftar kota langsung dari file
void displayKotaFromFile();

// Fungsi untuk update daftar kota langsung dari file
int updateKota();

// Fungsi untuk delete daftar kota langsung dari file
int deleteKota();

// Fungsi untuk mencari kota berdasarkan ID
void findKotaById(int id);

// Fungsi untuk membuat backup file kota
void saveKotaBackup();

// Membandingkan string tanpa memperhatikan huruf besar/kecil
int caseInsensitiveCompare(const char *str1, const char *str2);

#endif
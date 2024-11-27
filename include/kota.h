#ifndef KOTA_H
#define KOTA_H

#define MAX_NAME_KOTA_LENGTH 50
#define MAX_KOTA 100
#define KOTA_CSV_FILE "kota.csv"

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

// Fungsi untuk membaca data kota dari file CSV
int loadKota(Kota kotaList[], int *count);

// Fungsi untuk menampilkan daftar kota
void displayKota(const Kota kotaList[], int count);

// Fungsi untuk mencari kota berdasarkan ID
Kota *findKotaById(const Kota kotaList[], int count, int id);

// Fungsi untuk menambah kota baru
int addKota(Kota kotaList[], int *count, const char *nama);

// Fungsi untuk menyimpan data kota ke file CSV
int saveKota(const Kota kotaList[], int count);

// Validasi nama kota unik
int isKotaNamaUnique(const Kota kotaList[], int count, const char *nama);

// Membandingkan string tanpa memperhatikan huruf besar/kecil
int caseInsensitiveCompare(const char *str1, const char *str2);

void displayKotaFromFile();

#endif

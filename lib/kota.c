#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "kota.h"

// Constructor
Kota createKota(int id, const char *nama)
{
    Kota kota;
    kota.id = id;
    strncpy(kota.nama, nama, MAX_NAME_KOTA_LENGTH - 1);
    kota.nama[MAX_NAME_KOTA_LENGTH - 1] = '\0';
    return kota;
}

// Getter
int getKotaId(const Kota *kota)
{
    return kota->id;
}

const char *getKotaNama(const Kota *kota)
{
    return kota->nama;
}

// Setter
void setKotaId(Kota *kota, int id)
{
    kota->id = id;
}

void setKotaNama(Kota *kota, const char *nama)
{
    strncpy(kota->nama, nama, MAX_NAME_KOTA_LENGTH - 1);
    kota->nama[MAX_NAME_KOTA_LENGTH - 1] = '\0';
}

// Membaca data kota dari file CSV
int loadKota(Kota kotaList[], int *count)
{
    FILE *file = fopen(KOTA_CSV_FILE, "r");
    if (!file)
    {
        perror("Gagal membuka file");
        return 0;
    }

    char line[256];
    *count = 0;

    // Lewati header
    fgets(line, sizeof(line), file);

    // Baca data
    while (fgets(line, sizeof(line), file))
    {
        int id;
        char nama[MAX_NAME_KOTA_LENGTH];
        sscanf(line, "%d,%49[^\n]", &id, nama);
        kotaList[*count] = createKota(id, nama);
        (*count)++;
    }

    fclose(file);
    return 1;
}

// Menampilkan daftar kota
void displayKota(const Kota kotaList[], int count)
{
    printf("\nDaftar Kota:\n");
    printf("==========================\n");
    printf("%-5s %-20s\n", "ID", "Nama");
    printf("==========================\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-5d %-20s\n", getKotaId(&kotaList[i]), getKotaNama(&kotaList[i]));
    }
    printf("==========================\n");
}

// Mencari kota berdasarkan ID
Kota *findKotaById(const Kota kotaList[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (getKotaId(&kotaList[i]) == id)
        {
            return &kotaList[i];
        }
    }
    return NULL;
}

// Menambah kota baru
int addKota(Kota kotaList[], int *count, const char *nama)
{
    if (*count >= MAX_KOTA)
    {
        printf("Gagal menambah kota: kapasitas penuh.\n");
        return 0;
    }

    // Validasi nama kota unik
    if (!isKotaNamaUnique(kotaList, *count, nama))
    {
        printf("Gagal menambah kota: nama kota '%s' sudah ada.\n", nama);
        return 0;
    }

    // Buat ID baru
    int newId = *count > 0 ? getKotaId(&kotaList[*count - 1]) + 1 : 1;

    kotaList[*count] = createKota(newId, nama);
    (*count)++;

    return 1;
}

// Menyimpan data kota ke file CSV
int saveKota(const Kota kotaList[], int count)
{
    FILE *file = fopen(KOTA_CSV_FILE, "w");
    if (!file)
    {
        perror("Gagal membuka file");
        return 0;
    }

    fprintf(file, "id,nama\n");
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d,%s\n", getKotaId(&kotaList[i]), getKotaNama(&kotaList[i]));
    }

    fclose(file);
    return 1;
}

// Membandingkan string tanpa memperhatikan huruf besar/kecil
int caseInsensitiveCompare(const char *str1, const char *str2)
{
    while (*str1 && *str2)
    {
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2))
        {
            return 0;
        }
        str1++;
        str2++;
    }
    return *str1 == '\0' && *str2 == '\0';
}

// Memeriksa apakah nama kota unik (case insensitive)
int isKotaNamaUnique(const Kota kotaList[], int count, const char *nama)
{
    for (int i = 0; i < count; i++)
    {
        if (caseInsensitiveCompare(kotaList[i].nama, nama))
        {
            return 0; // Nama kota sudah ada
        }
    }
    return 1; // Nama kota unik
}

void displayKotaFromFile()
{
    Kota kotaList[MAX_KOTA];
    int kotaCount = 0;

    // Load data kota
    if (!loadKota(kotaList, &kotaCount))
    {
        printf("Gagal memuat data kota.\n");
        return;
    }

    // Tampilkan daftar kota
    printf("\nDaftar Kota:\n");
    printf("==========================\n");
    printf("%-5s %-20s\n", "ID", "Nama");
    printf("==========================\n");

    for (int i = 0; i < kotaCount; i++)
    {
        printf("%-5d %-20s\n", getKotaId(&kotaList[i]), getKotaNama(&kotaList[i]));
    }
    printf("==========================\n");
}

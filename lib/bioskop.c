#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "bioskop.h"

// Constructor
Bioskop createBioskop(int id, int kota_id, const char *nama, const char *manager)
{
    Bioskop bioskop;
    bioskop.id = id;
    bioskop.kota_id = kota_id;
    strncpy(bioskop.nama, nama, MAX_BIOSKOP_NAME - 1);
    bioskop.nama[MAX_BIOSKOP_NAME - 1] = '\0';
    strncpy(bioskop.manager, manager, MAX_MANAGER_NAME - 1);
    bioskop.manager[MAX_MANAGER_NAME - 1] = '\0';
    return bioskop;
}

// Getter
int getBioskopId(const Bioskop *bioskop)
{
    return bioskop->id;
}
int getBioskopKotaId(const Bioskop *bioskop)
{
    return bioskop->kota_id;
}
const char *getBioskopNama(const Bioskop *bioskop)
{
    return bioskop->nama;
}
const char *getBioskopManager(const Bioskop *bioskop)
{
    return bioskop->manager;
}

// Setter
void setBioskopId(Bioskop *bioskop, int id)
{
    bioskop->id = id;
}
void setBioskopKotaId(Bioskop *bioskop, int kota_id)
{
    bioskop->kota_id = kota_id;
}
void setBioskopNama(Bioskop *bioskop, const char *nama)
{
    strncpy(bioskop->nama, nama, MAX_BIOSKOP_NAME - 1);
    bioskop->nama[MAX_BIOSKOP_NAME - 1] = '\0';
}
void setBioskopManager(Bioskop *bioskop, const char *manager)
{
    strncpy(bioskop->manager, manager, MAX_MANAGER_NAME - 1);
    bioskop->manager[MAX_MANAGER_NAME - 1] = '\0';
}

// Validasi nama bioskop unik
int isBioskopNamaUnique(const Bioskop bioskopList[], int count, const char *nama)
{
    for (int i = 0; i < count; i++)
    {
        if (caseInsensitiveCompare(bioskopList[i].nama, nama))
        {
            return 0; // Nama bioskop sudah ada
        }
    }
    return 1; // Nama bioskop unik
}

// Membaca data bioskop dari file CSV
int loadBioskop(Bioskop bioskopList[], int *count)
{
    FILE *file = fopen(BIOSKOP_CSV_FILE, "r");
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
        int id, kota_id;
        char nama[MAX_BIOSKOP_NAME], manager[MAX_MANAGER_NAME];
        sscanf(line, "%d,%d,%49[^,],%49[^\n]", &id, &kota_id, nama, manager);
        bioskopList[*count] = createBioskop(id, kota_id, nama, manager);
        (*count)++;
    }

    fclose(file);
    return 1;
}

// Menyimpan data bioskop ke file CSV
int saveBioskop(const Bioskop bioskopList[], int count)
{
    FILE *file = fopen(BIOSKOP_CSV_FILE, "w");
    if (!file)
    {
        perror("Gagal membuka file");
        return 0;
    }

    fprintf(file, "id,kota_id,nama,manager\n");
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d,%d,%s,%s\n",
                getBioskopId(&bioskopList[i]),
                getBioskopKotaId(&bioskopList[i]),
                getBioskopNama(&bioskopList[i]),
                getBioskopManager(&bioskopList[i]));
    }

    fclose(file);
    return 1;
}

// Menampilkan daftar bioskop
void displayBioskop(const Bioskop bioskopList[], int count, const Kota kotaList[], int kotaCount)
{
    printf("\nDaftar Bioskop:\n");
    printf("=======================================================\n");
    printf("%-5s %-20s %-15s %-20s\n", "ID", "Nama", "Kota", "Manager");
    printf("=======================================================\n");

    for (int i = 0; i < count; i++)
    {
        const char *kotaNama = "Tidak Ditemukan";
        for (int j = 0; j < kotaCount; j++)
        {
            if (getKotaId(&kotaList[j]) == getBioskopKotaId(&bioskopList[i]))
            {
                kotaNama = getKotaNama(&kotaList[j]);
                break;
            }
        }
        printf("%-5d %-20s %-15s %-20s\n",
               getBioskopId(&bioskopList[i]),
               getBioskopNama(&bioskopList[i]),
               kotaNama,
               getBioskopManager(&bioskopList[i]));
    }
    printf("=======================================================\n");
}

// Menambah bioskop baru
int addBioskop(Bioskop bioskopList[], int *count, int kota_id, const char *nama, const char *manager)
{
    if (*count >= MAX_BIOSKOP)
    {
        printf("Gagal menambah bioskop: kapasitas penuh.\n");
        return 0;
    }

    if (!isBioskopNamaUnique(bioskopList, *count, nama))
    {
        printf("Gagal menambah bioskop: nama bioskop '%s' sudah ada.\n", nama);
        return 0;
    }

    int newId = *count > 0 ? getBioskopId(&bioskopList[*count - 1]) + 1 : 1;

    bioskopList[*count] = createBioskop(newId, kota_id, nama, manager);
    (*count)++;

    return 1;
}

void displayBioskopFromFile()
{
    Bioskop bioskopList[MAX_BIOSKOP];
    Kota kotaList[MAX_KOTA];
    int bioskopCount = 0, kotaCount = 0;

    // Load data kota
    if (!loadKota(kotaList, &kotaCount))
    {
        printf("Gagal memuat data kota.\n");
        return;
    }

    // Load data bioskop
    if (!loadBioskop(bioskopList, &bioskopCount))
    {
        printf("Gagal memuat data bioskop.\n");
        return;
    }

    // Tampilkan daftar bioskop
    printf("\nDaftar Bioskop:\n");
    printf("===================================================\n");
    printf("%-5s %-20s %-15s %-20s\n", "ID", "Nama", "Kota", "Manager");
    printf("===================================================\n");

    for (int i = 0; i < bioskopCount; i++)
    {
        const char *kotaNama = "Tidak Ditemukan";
        for (int j = 0; j < kotaCount; j++)
        {
            if (getKotaId(&kotaList[j]) == getBioskopKotaId(&bioskopList[i]))
            {
                kotaNama = getKotaNama(&kotaList[j]);
                break;
            }
        }
        printf("%-5d %-20s %-15s %-20s\n",
               getBioskopId(&bioskopList[i]),
               getBioskopNama(&bioskopList[i]),
               kotaNama,
               getBioskopManager(&bioskopList[i]));
    }
    printf("===================================================\n");
}

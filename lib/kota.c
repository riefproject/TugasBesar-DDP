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

// Menambahkan kota baru
int addKota()
{
    FILE *file = fopen(KOTA_CSV_FILE, "r+"); // Buka file untuk membaca dan menulis
    if (!file)
    {
        // Jika file tidak ada, buat file baru
        file = fopen(KOTA_CSV_FILE, "w+");
        if (!file)
        {
            perror("Gagal membuka atau membuat file kota.");
            return 0;
        }
        // Tulis header ke file baru
        fprintf(file, "id,nama\n");
    }

    // Buffer untuk membaca file
    char line[256];
    int id = 0;
    char nama[MAX_NAME_KOTA_LENGTH];
    int isUnique = 1;

    // Dapatkan input nama kota dari admin
    printf("Masukkan nama kota baru: ");
    scanf(" %[^\n]", nama);

    // Skip header
    fgets(line, sizeof(line), file);

    // Cek apakah nama sudah ada di file
    while (fgets(line, sizeof(line), file))
    {
        int existingId;
        char existingNama[MAX_NAME_KOTA_LENGTH];
        sscanf(line, "%d,%49[^\n]", &existingId, existingNama);
        id = existingId; // Simpan ID terakhir
        if (caseInsensitiveCompare(existingNama, nama))
        {
            isUnique = 0;
            break;
        }
    }

    if (!isUnique)
    {
        printf("Gagal menambah kota: nama kota '%s' sudah ada.\n", nama);
        fclose(file);
        return 0;
    }

    // Tambahkan kota baru
    id++; // Increment ID
    fprintf(file, "%d,%s\n", id, nama);

    fclose(file);
    printf("Kota '%s' berhasil ditambahkan dengan ID %d.\n", nama, id);
    return 1;
}

// Menampilkan daftar kota langsung dari file
void displayKotaFromFile()
{
    FILE *file = fopen(KOTA_CSV_FILE, "r");
    if (!file)
    {
        printf("File kota.csv tidak ditemukan.\n");
        return;
    }

    char line[256];
    // Skip header
    fgets(line, sizeof(line), file);

    printf("\nDaftar Kota:\n");
    printf("==========================\n");
    printf("%-5s %-20s\n", "ID", "Nama");
    printf("==========================\n");

    while (fgets(line, sizeof(line), file))
    {
        int id;
        char nama[MAX_NAME_KOTA_LENGTH];
        sscanf(line, "%d,%49[^\n]", &id, nama);
        printf("%-5d %-20s\n", id, nama);
    }

    printf("==========================\n");
    fclose(file);
}

// Mencari kota berdasarkan ID di file
void findKotaById(int id)
{
    FILE *file = fopen(KOTA_CSV_FILE, "r");
    if (!file)
    {
        printf("File kota.csv tidak ditemukan.\n");
        return;
    }

    char line[256];
    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        int existingId;
        char nama[MAX_NAME_KOTA_LENGTH];
        sscanf(line, "%d,%49[^\n]", &existingId, nama);
        if (existingId == id)
        {
            printf("Kota ditemukan: ID: %d, Nama: %s\n", existingId, nama);
            fclose(file);
            return;
        }
    }

    printf("Kota dengan ID %d tidak ditemukan.\n", id);
    fclose(file);
}

// Menyimpan ulang data kota (jika perlu, sebagai backup)
void saveKotaBackup()
{
    FILE *file = fopen(KOTA_CSV_FILE, "r");
    if (!file)
    {
        printf("File kota.csv tidak ditemukan.\n");
        return;
    }

    FILE *backup = fopen("kota_backup.csv", "w");
    if (!backup)
    {
        perror("Gagal membuat file backup.");
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        fputs(line, backup);
    }

    fclose(file);
    fclose(backup);
    printf("Backup file kota.csv berhasil dibuat sebagai kota_backup.csv.\n");
}

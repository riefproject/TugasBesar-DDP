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

int updateKota()
{
    FILE *file = fopen(KOTA_CSV_FILE, "r");
    if (!file)
    {
        printf("File kota.csv tidak ditemukan.\n");
        return 0;
    }

    FILE *tempFile = fopen(TEMP_KOTA_FILE, "w");
    if (!tempFile)
    {
        perror("Gagal membuat file sementara.");
        fclose(file);
        return 0;
    }

    int id;
    char namaBaru[MAX_NAME_KOTA_LENGTH];

    printf("Masukkan ID Kota yang ingin diperbarui: ");
    scanf("%d", &id);
    printf("Masukkan Nama Baru: ");
    scanf(" %[^\n]", namaBaru);

    char line[256];
    int found = 0;
    int isUnique = 1;

    // Salin header
    fgets(line, sizeof(line), file);
    fputs(line, tempFile);

    // Proses baris data
    while (fgets(line, sizeof(line), file))
    {
        int existingId;
        char nama[MAX_NAME_KOTA_LENGTH];
        sscanf(line, "%d,%49[^\n]", &existingId, nama);

        if (strcmp(nama, namaBaru) == 0 && existingId != id)
        {
            isUnique = 0;
        }

        if (existingId == id)
        {
            fprintf(tempFile, "%d,%s\n", id, namaBaru);
            found = 1;
        }
        else
        {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!isUnique)
    {
        printf("Gagal memperbarui: Nama kota '%s' sudah ada.\n", namaBaru);
        remove(TEMP_KOTA_FILE);
        return 0;
    }

    if (found)
    {
        remove(KOTA_CSV_FILE);
        rename(TEMP_KOTA_FILE, KOTA_CSV_FILE);
        printf("Kota dengan ID %d berhasil diperbarui.\n", id);
    }
    else
    {
        remove(TEMP_KOTA_FILE);
        printf("Kota dengan ID %d tidak ditemukan.\n", id);
    }

    return found;
}

int deleteKota()
{
    FILE *file = fopen(KOTA_CSV_FILE, "r");
    if (!file)
    {
        printf("File kota.csv tidak ditemukan.\n");
        return 0;
    }

    FILE *tempFile = fopen(TEMP_KOTA_FILE, "w");
    if (!tempFile)
    {
        perror("Gagal membuat file sementara.");
        fclose(file);
        return 0;
    }

    int id;
    printf("Masukkan ID Kota yang ingin dihapus: ");
    scanf("%d", &id);

    char line[256];
    int found = 0;

    // Salin header
    fgets(line, sizeof(line), file);
    fputs(line, tempFile);

    // Proses baris data
    while (fgets(line, sizeof(line), file))
    {
        int existingId;
        char nama[MAX_NAME_KOTA_LENGTH];
        sscanf(line, "%d,%49[^\n]", &existingId, nama);

        if (existingId == id)
        {
            printf("\nApakah Anda yakin ingin menghapus data berikut?\n");
            printf("ID Kota: %d\nNama Kota: %s\n", existingId, nama);
            printf("Ketik 'y' untuk menghapus atau 'n' untuk membatalkan: ");
            char confirm;
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y')
            {
                printf("Data dengan ID %d berhasil dihapus.\n", id);
                found = 1; // Jangan salin baris ini ke file temporary
            }
            else
            {
                printf("Penghapusan dibatalkan.\n");
                fputs(line, tempFile); // Salin kembali data jika dibatalkan
            }
        }
        else
        {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove(KOTA_CSV_FILE);
        rename(TEMP_KOTA_FILE, KOTA_CSV_FILE);
    }
    else
    {
        remove(TEMP_KOTA_FILE);
        printf("Kota dengan ID %d tidak ditemukan.\n", id);
    }

    return found;
}

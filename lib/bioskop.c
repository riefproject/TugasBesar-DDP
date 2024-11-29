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

int addBioskop()
{
    FILE *file = fopen(BIOSKOP_CSV_FILE, "r+"); // Buka file untuk membaca dan menulis
    if (!file)
    {
        // Jika file tidak ada, buat file baru
        file = fopen(BIOSKOP_CSV_FILE, "w+");
        if (!file)
        {
            perror("Gagal membuka atau membuat file bioskop.");
            return 0;
        }
        // Tulis header ke file baru
        fprintf(file, "id,kota_id,nama,manager\n");
    }

    char line[256];
    int id = 0, kota_id;
    char nama[MAX_BIOSKOP_NAME], manager[MAX_MANAGER_NAME];
    int isUnique = 1;

    // Skip header
    fgets(line, sizeof(line), file);

    // Cek apakah nama sudah ada di file
    while (fgets(line, sizeof(line), file))
    {
        int existingId;
        char existingNama[MAX_BIOSKOP_NAME];
        sscanf(line, "%d,%*d,%49[^,],%*s", &existingId, existingNama);
        id = existingId; // Simpan ID terakhir
        if (caseInsensitiveCompare(existingNama, nama))
        {
            isUnique = 0;
            break;
        }
    }

    if (!isUnique)
    {
        printf("Gagal menambah bioskop: nama bioskop '%s' sudah ada.\n", nama);
        fclose(file);
        return 0;
    }

    // Ambil input dari admin
    printf("Masukkan ID Kota: ");
    scanf("%d", &kota_id);
    printf("Masukkan Nama Bioskop: ");
    scanf(" %[^\n]", nama);
    printf("Masukkan Nama Manager: ");
    scanf(" %[^\n]", manager);

    // Tambahkan bioskop baru
    id++; // Increment ID terakhir
    fprintf(file, "%d,%d,%s,%s\n", id, kota_id, nama, manager);

    fclose(file);
    printf("Bioskop '%s' berhasil ditambahkan dengan ID %d.\n", nama, id);
    return 1;
}

void displayBioskopFromFile()
{
    FILE *bioskopFile = fopen(BIOSKOP_CSV_FILE, "r");
    FILE *kotaFile = fopen(KOTA_CSV_FILE, "r");

    if (!bioskopFile)
    {
        printf("File bioskop.csv tidak ditemukan.\n");
        return;
    }
    if (!kotaFile)
    {
        printf("File kota.csv tidak ditemukan.\n");
        fclose(bioskopFile);
        return;
    }

    char bioskopLine[256], kotaLine[256];
    printf("\nDaftar Bioskop:\n");
    printf("===================================================\n");
    printf("%-5s %-20s %-15s %-20s\n", "ID", "Nama", "Kota", "Manager");
    printf("===================================================\n");

    // Lewati header kota
    fgets(kotaLine, sizeof(kotaLine), kotaFile);

    // Lewati header bioskop
    fgets(bioskopLine, sizeof(bioskopLine), bioskopFile);

    // Tampilkan data bioskop
    while (fgets(bioskopLine, sizeof(bioskopLine), bioskopFile))
    {
        int id, kota_id;
        char nama[MAX_BIOSKOP_NAME], manager[MAX_MANAGER_NAME];
        char kotaNama[MAX_NAME_KOTA_LENGTH] = "Tidak Ditemukan";

        sscanf(bioskopLine, "%d,%d,%49[^,],%49[^\n]", &id, &kota_id, nama, manager);

        // Cari nama kota berdasarkan kota_id
        rewind(kotaFile);                            // Kembali ke awal file kota
        fgets(kotaLine, sizeof(kotaLine), kotaFile); // Lewati header
        while (fgets(kotaLine, sizeof(kotaLine), kotaFile))
        {
            int kotaId;
            char namaKota[MAX_NAME_KOTA_LENGTH];
            sscanf(kotaLine, "%d,%49[^\n]", &kotaId, namaKota);
            if (kotaId == kota_id)
            {
                strncpy(kotaNama, namaKota, MAX_NAME_KOTA_LENGTH);
                break;
            }
        }

        printf("%-5d %-20s %-15s %-20s\n", id, nama, kotaNama, manager);
    }

    printf("===================================================\n");

    fclose(bioskopFile);
    fclose(kotaFile);
}

int updateBioskop()
{
    FILE *file = fopen(BIOSKOP_CSV_FILE, "r");
    if (!file)
    {
        printf("File bioskop.csv tidak ditemukan.\n");
        return 0;
    }

    FILE *tempFile = fopen(TEMP_BIOSKOP_FILE, "w");
    if (!tempFile)
    {
        perror("Gagal membuat file sementara.");
        fclose(file);
        return 0;
    }

    int id;
    char namaBaru[MAX_BIOSKOP_NAME];
    char managerBaru[MAX_MANAGER_NAME];

    printf("Masukkan ID Bioskop yang ingin diperbarui: ");
    scanf("%d", &id);
    printf("Masukkan Nama Baru: ");
    scanf(" %[^\n]", namaBaru);
    printf("Masukkan Manager Baru: ");
    scanf(" %[^\n]", managerBaru);

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
        char nama[MAX_BIOSKOP_NAME], manager[MAX_MANAGER_NAME];
        sscanf(line, "%d,%*d,%49[^,],%49[^\n]", &existingId, nama, manager);

        // Validasi unik untuk nama bioskop
        if (strcmp(nama, namaBaru) == 0 && existingId != id)
        {
            isUnique = 0;
        }

        if (existingId == id)
        {
            fprintf(tempFile, "%d,%d,%s,%s\n", id, 0, namaBaru, managerBaru); // 0 sebagai placeholder kota_id
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
        printf("Gagal memperbarui: Nama bioskop '%s' sudah ada.\n", namaBaru);
        remove(TEMP_BIOSKOP_FILE);
        return 0;
    }

    if (found)
    {
        remove(BIOSKOP_CSV_FILE);
        rename(TEMP_BIOSKOP_FILE, BIOSKOP_CSV_FILE);
        printf("Bioskop dengan ID %d berhasil diperbarui.\n", id);
    }
    else
    {
        remove(TEMP_BIOSKOP_FILE);
        printf("Bioskop dengan ID %d tidak ditemukan.\n", id);
    }

    return found;
}

int deleteBioskop()
{
    FILE *file = fopen(BIOSKOP_CSV_FILE, "r");
    if (!file)
    {
        printf("File bioskop.csv tidak ditemukan.\n");
        return 0;
    }

    FILE *tempFile = fopen(TEMP_BIOSKOP_FILE, "w");
    if (!tempFile)
    {
        perror("Gagal membuat file sementara.");
        fclose(file);
        return 0;
    }

    int id;
    printf("Masukkan ID Bioskop yang ingin dihapus: ");
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
        char nama[MAX_BIOSKOP_NAME], manager[MAX_MANAGER_NAME];
        sscanf(line, "%d,%*d,%49[^,],%49[^\n]", &existingId, nama, manager);

        if (existingId == id)
        {
            printf("\nApakah Anda yakin ingin menghapus data berikut?\n");
            printf("ID Bioskop: %d\nNama Bioskop: %s\nManager: %s\n", existingId, nama, manager);
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
        remove(BIOSKOP_CSV_FILE);
        rename(TEMP_BIOSKOP_FILE, BIOSKOP_CSV_FILE);
    }
    else
    {
        remove(TEMP_BIOSKOP_FILE);
        printf("Bioskop dengan ID %d tidak ditemukan.\n", id);
    }

    return found;
}

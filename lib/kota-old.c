#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>

#include "display.h"
#include "kota.h"

// Constructor
Kota createKota(int id, const char *nama)
{
    Kota kota;
    kota.id = id;
    strncpy(kota.nama, nama, MAX_KOTA_NAME - 1);
    kota.nama[MAX_KOTA_NAME - 1] = '\0';
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
    strncpy(kota->nama, nama, MAX_KOTA_NAME - 1);
    kota->nama[MAX_KOTA_NAME - 1] = '\0';
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
    FILE *file = fopen(KOTA_DATABASE_NAME, "r+"); // Buka file untuk membaca dan menulis
    if (!file)
    {
        // Jika file tidak ada, buat file baru
        file = fopen(KOTA_DATABASE_NAME, "w+");
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
    char nama[MAX_KOTA_NAME];
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
        char existingNama[MAX_KOTA_NAME];
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
    FILE *file = fopen(KOTA_DATABASE_NAME, "r");
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
        char nama[MAX_KOTA_NAME];
        sscanf(line, "%d,%49[^\n]", &id, nama);
        printf("%-5d %-20s\n", id, nama);
    }

    printf("==========================\n");
    fclose(file);
}

// Mencari kota berdasarkan ID di file
void findKotaById(int id)
{
    FILE *file = fopen(KOTA_DATABASE_NAME, "r");
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
        char nama[MAX_KOTA_NAME];
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
    FILE *file = fopen(KOTA_DATABASE_NAME, "r");
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

void updateKotaMenu(Kota kota)
{
    printf(YELLOW "====================================================\n");
    printf("                 Menu Edit Kota                     \n");
    printf("====================================================\n" RESET);

    char nama[MAX_KOTA_NAME];
    int id = kota.id;

    while (1)
    {
        printf("Masukkan nama kota\t: ");
        fgets(nama, sizeof(nama), stdin);
        nama[strcspn(nama, "\n")] = 0;

        if (strcmp(nama, "") == 0)
        {
            printf(RED BOLD "Nama kota tidak boleh kosong.\n" RESET);
            sleep(1);
            continue;
        }
        break;
    }

    Kota *updatedKota = updateKota(id, nama);
    if (!updatedKota)
    {
        printf(RED BOLD "Gagal mengubah kota. Harap coba lagi!\n" RESET);
        return;
    }

    printf(GREEN BOLD "Berhasil mengubah kota!\n" RESET);
    sleep(2);
    free(updatedKota);
}

Kota *updateKota(const int id, const char *nama)
{
    Kota *updatedKota = malloc(sizeof(Kota));
    if (!updatedKota)
    {
        printf("Alokasi memori gagal, location: updateKota");
        return NULL;
    }

    // Set the updated values for kota
    strncpy(updatedKota->nama, nama, MAX_KOTA_NAME);
    updatedKota->id = id;

    FILE *fromFile = fopen(KOTA_DATABASE_NAME, "r");
    if (!fromFile)
    {
        free(updatedKota);
        return NULL;
    }

    int count = countKotaData();
    if (count == -1)
    {
        printf("Penghitungan data kota gagal, location: updateKota");
        return NULL;
    }

    int i = 0;

    Kota kotaList[count];

    while (fscanf(fromFile, KOTA_GETTER_FORMAT,
                  &kotaList[i].id,
                  kotaList[i].nama) != EOF)
    {
        if (kotaList[i].id == id)
        {
            kotaList[i] = *updatedKota;
        }
        i++;
    }
    fclose(fromFile);

    FILE *toFile = fopen(KOTA_DATABASE_NAME, "w");
    i = 0;
    while (i < count)
    {
        fprintf(toFile, KOTA_SETTER_FORMAT,
                kotaList[i].id,
                kotaList[i].nama);
        i++;
    }

    fclose(toFile);
    return updatedKota;
}

int deleteKota(Kota kota)
{
    // Buat pesan konfirmasi
    int len = snprintf(NULL, 0, "Apakah Anda yakin ingin menghapus data kota dengan nama '%s'?\n", kota.nama) + 1;
    char *head = malloc(len);
    if (!head)
    {
        printf(RED "Gagal mengalokasikan memori.\n" RESET);
        sleep(1);

        return -1;
    }
    snprintf(head, len, "Apakah Anda yakin ingin menghapus data kota dengan nama '%s'?\n", kota.nama);

    char *menu[] = {
        "Tidak, Batalkan",
        "Ya, Hapus",
    };

    char *header[] = {
        RED BOLD "====================================================\n",
        "                Konfirmasi Hapus Kota               \n",
        "====================================================\n\n" RESET,
        head,
        NULL};

    int selection = showMenu(menu, 2, header);
    free(head);

    if (selection == 1)
    {
        return 1;
    }

    // cadangkan data
    FILE *fromFile = fopen(KOTA_DATABASE_NAME, "r");
    if (!fromFile)
    {
        printf(RED "Gagal membuka file, lokasi: deleteKota.\n" RESET);
        sleep(1);
        return -1;
    }

    int count = countKotaData();
    if (count == -1)
    {
        printf(RED "Penghitungan data kota gagal, lokasi: deleteKota.\n" RESET);
        fclose(fromFile);
        return -1;
    }

    Kota users[count], temp;
    int i = 0;
    while (fscanf(fromFile, KOTA_GETTER_FORMAT,
                  &temp.id,
                  temp.nama) != EOF)
    {
        if (temp.id != kota.id)
        {
            users[i] = temp;
            i++;
        }
    }
    fclose(fromFile);

    // menulis ulang file dengan data pengguna yang diperbarui
    FILE *toFile = fopen(KOTA_DATABASE_NAME, "w");
    if (!toFile)
    {
        printf(RED "Gagal membuka file untuk ditulis, lokasi: deleteKota.\n" RESET);
        return -1;
    }

    i = 0;
    while (i < count - 1)
    {
        fprintf(toFile, KOTA_SETTER_FORMAT,
                users[i].id,
                users[i].nama);
        sleep(10);
        i++;
    }

    fclose(toFile);

    return 1;
}

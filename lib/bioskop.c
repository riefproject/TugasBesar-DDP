#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>

#include "display.h"
#include "menu.h"
#include "security.h"
#include "bioskop.h"
#include "user.h"
#include "film.h"
#include "studio.h"
#include "kota.h"
#include "db.h"

// ================================== Getter ================================== //

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
    return findUserByID(bioskop->manager_id)->name;
}
const char *getBioskopKota(const Bioskop *bioskop)
{
    char *temp = findKotaByID(bioskop->kota_id)->nama;
    temp[strcspn(temp, "\n")] = 0;
    return temp;
}

// ================================== Setter ================================== //

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
void setBioskopAlamat(Bioskop *bioskop, const char *alamat)
{
    strncpy(bioskop->alamat, alamat, MAX_BIOSKOP_ALAMAT - 1);
    bioskop->alamat[MAX_BIOSKOP_ALAMAT - 1] = '\0';
}
void setBioskopManagerId(Bioskop *bioskop, int manager_id)
{
    bioskop->manager_id = manager_id;
}

// ================================== Main Menu =================================== //

int menuBioskop()
{
    Bioskop *bioskops;
    int count = loadBioskop(&bioskops);

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        system("cls");

        selection = (page - 1) * perPage + pointer;

        printf(GREEN "====================================================\n");
        printf("                 Daftar Bioskop                     \n");
        printf("====================================================\n" RESET);

        printBioskopTable(bioskops, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page");
        printf(GREEN "\n[C]: Create" RESET " | " YELLOW "[U]: Update" RESET " | " RED "[D]: Delete" RESET " | " BG_RED WHITE "[E] Exit\n" RESET);

        command = getch();

        if (command == 224)
        {
            command = getch();

            if (command == 77 && page * perPage < count)
            {
                pointer = 1;
                page++;
            }
            else if (command == 75 && page > 1)
            {
                pointer = 1;
                page--;
            }
            else if (command == 72 && pointer > 1)
            {
                pointer--;
            }
            else if (command == 80 && pointer < perPage && (page - 1) * perPage + pointer < count)
            {
                pointer++;
            }
        }
        else if (command == 'C' || command == 'c')
        {
            createBioskopMenu();
            // free(bioskops);
            count = loadBioskop(&bioskops);
            pointer = 1;
        }
        else if (command == 'U' || command == 'u')
        {
            updateBioskopMenu(bioskops[selection - 1]);
            // free(bioskops);
            count = loadBioskop(&bioskops);
            pointer = 1;
        }
        else if (command == 'D' || command == 'd')
        {
            deleteBioskop(bioskops[selection - 1]);
            // free(bioskops);
            count = loadBioskop(&bioskops);
            pointer = 1;
        }
        else if (command == 'E' || command == 'e')
        {
            break;
        }
        else
        {
            printf(YELLOW BOLD "Perintah tidak valid!\n" RESET);
            sleep(1);
        }
    }
}

int selectKota()
{
    Kota *kotaList;
    int count = loadKota(&kotaList);

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        selection = (page - 1) * perPage + pointer;

        printKotaTable(kotaList, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page\n");
        printf("[Arrow /\\] | [Arrow \\/] Arrow Up/Down To Selecting\n");
        printf(GREEN "[ENTER]: Enter To Select Kota\n" RESET);

        command = getch();

        if (command == 224)
        {
            command = getch();

            if (command == 77)
            {
                pointer = 1;
                if (page * perPage < count)
                    page++;
                else
                {
                    printf("Sudah di halaman terakhir.\n");
                    sleep(1);
                }
            }
            else if (command == 75)
            {
                pointer = 1;
                if (page > 1)
                    page--;
                else
                {
                    printf("Sudah di halaman pertama.\n");
                    sleep(1);
                }
            }
            else if (command == 72)
            {
                if (pointer > 1)
                {
                    pointer--;
                }
            }
            else if (command == 80)
            {
                if (pointer < perPage && (page - 1) * perPage + pointer < count)
                {
                    pointer++;
                }
            }
        }
        else if (command == 13)
        {
            printf("Kota " GREEN "%s" RESET " dipilih\n" RESET, kotaList[selection - 1].nama);

            int kotaID = kotaList[selection - 1].id;

            free(kotaList);

            return kotaID;
        }
        else
        {
            printf(YELLOW BOLD "Command not found\n" RESET);
            sleep(1);
        }
    }
}

int selectManager()
{
    User *users;
    int count = loadUser(&users);

    count = filterUserByRole(&users, MANAGER);

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        selection = (page - 1) * perPage + pointer;

        printUserTable(users, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page \n");
        printf("[Arrow /\\] | [Arrow \\/] Arrow Up/Down To Selecting \n");
        printf(GREEN "[ENTER]: Enter To Select Manager \n" RESET);

        command = getch();

        if (command == 224)
        {
            command = getch();

            if (command == 77)
            {
                pointer = 1;
                if (page * perPage < count)
                    page++;
                else
                {
                    printf("Sudah di halaman terakhir.\n");
                    sleep(1);
                }
            }
            else if (command == 75)
            {
                pointer = 1;
                if (page > 1)
                    page--;
                else
                {
                    printf("Sudah di halaman pertama.\n");
                    sleep(1);
                }
            }
            else if (command == 72)
            {
                if (pointer > 1)
                {
                    pointer--;
                }
            }
            else if (command == 80)
            {
                if (pointer < perPage && (page - 1) * perPage + pointer < count)
                {
                    pointer++;
                }
            }
        }
        else if (command == 13)
        {
            printf("Manager dengan nama" GREEN " %s \n" RESET, users[selection - 1].name);
            free(users);
            return users[selection - 1].id;
        }
        else
        {
            printf(YELLOW BOLD "perintah tidak ditemukan\n" RESET);
            sleep(1);
        }
    }
}

void createBioskopMenu()
{
    system("cls");

    printf(GREEN "====================================================\n");
    printf("                 Menu Tambah Bioskop                 \n");
    printf("====================================================\n" RESET);

    char nama[MAX_BIOSKOP_NAME], alamat[MAX_BIOSKOP_ALAMAT];
    int kota_id, manager_id;

    while (1)
    {
        printf("Masukkan nama bioskop: ");
        fgets(nama, sizeof(nama), stdin);
        nama[strcspn(nama, "\n")] = 0; // Hapus newline

        if (strlen(nama) < 3)
        {
            printf(RED "Nama bioskop harus memiliki minimal 3 karakter.\n" RESET);
            continue;
        }

        Bioskop *bioskop = findBioskopByNama(nama);
        if (bioskop != NULL)
        {
            printf(RED "Nama bioskop sudah terdaftar, silakan gunakan nama lain.\n" RESET);
            free(bioskop); // Pastikan pointer dilepas jika perlu
            continue;
        }
        break;
    }

    printf("Masukkan alamat bioskop: ");
    fgets(alamat, sizeof(alamat), stdin);
    alamat[strcspn(alamat, "\n")] = 0;

    printf("Pilih Kota: \n");
    kota_id = selectKota();
    printf("Pilih manager: \n");
    manager_id = selectManager();

    Bioskop *newBioskop = createBioskop(nama, alamat, kota_id, manager_id);
    if (!newBioskop)
    {
        printf(RED "Gagal menambahkan bioskop baru.\n" RESET);
        return;
    }

    printf(GREEN "Berhasil menambah bioskop!\n" RESET);
    free(newBioskop);
}

void updateBioskopMenu(Bioskop bioskop)
{
    printf(YELLOW "====================================================\n");
    printf("                 Menu Edit Bioskop                   \n");
    printf("====================================================\n" RESET);

    char nama[MAX_BIOSKOP_NAME], alamat[MAX_BIOSKOP_ALAMAT];
    int kota_id, manager_id;

    while (1)
    {
        printf("Masukkan nama bioskop: ");
        fgets(nama, sizeof(nama), stdin);
        nama[strcspn(nama, "\n")] = 0; // Hapus newline

        if (strlen(nama) < 3)
        {
            printf(RED "Nama bioskop harus memiliki minimal 3 karakter.\n" RESET);
            continue;
        }

        Bioskop *bioskop = findBioskopByNama(nama);
        if (bioskop != NULL)
        {
            printf(RED "Nama bioskop sudah terdaftar, silakan gunakan nama lain.\n" RESET);
            free(bioskop); // Pastikan pointer dilepas jika perlu
            continue;
        }
        break;
    }

    printf("Masukkan alamat bioskop: ");
    fgets(alamat, sizeof(alamat), stdin);
    alamat[strcspn(alamat, "\n")] = 0;

    printf("Pilih Kota: \n");
    kota_id = selectKota();
    printf("Pilih manager: \n");
    manager_id = selectManager();

    Bioskop *newBioskop = updateBioskop(bioskop.id, nama, alamat, kota_id, manager_id);
    if (!newBioskop)
    {
        printf(RED "Gagal menambahkan bioskop baru.\n" RESET);
        return;
    }

    printf(GREEN "Berhasil menambah bioskop!\n" RESET);
    free(newBioskop);
}

// ================================= Action =================================== //
Bioskop *findBioskopById(const int id)
{
    FILE *file = fopen(BIOSKOP_DATABASE_NAME, "r");
    if (!file)
    {
        printf("Gagal membuka file database bioskop.\n");
        return NULL;
    }

    Bioskop *bioskop = NULL;

    while (1)
    {
        Bioskop temp;

        if (fscanf(file, BIOSKOP_GETTER_FORMAT,
                   &temp.id,
                   &temp.kota_id,
                   temp.nama,
                   &temp.manager_id,
                   temp.alamat) != 5)
        {
            break;
        }

        if (temp.id == id)
        {
            bioskop = malloc(sizeof(Bioskop));
            if (!bioskop)
            {
                printf("Gagal mengalokasikan memori untuk Bioskop.\n");
                break;
            }
            *bioskop = temp;
            break;
        }
    }

    fclose(file);
    return bioskop;
}

Bioskop *findBioskopByNama(const char *nama)
{
    FILE *file = fopen(BIOSKOP_DATABASE_NAME, "r");
    if (!file)
    {
        return NULL;
    }

    Bioskop *bioskop = malloc(sizeof(Bioskop));
    if (!bioskop)
    {
        fclose(file);
        return NULL;
    }

    while (fscanf(file, "%d,%[^,]", &bioskop->id, bioskop->nama) == 2)
    {
        if (strcmp(bioskop->nama, nama) == 0)
        {
            fclose(file);
            return bioskop;
        }
    }

    fclose(file);
    free(bioskop);
    return NULL;
}

Bioskop *findBioskopByManagerId(int manager_id)
{
    FILE *file = fopen(BIOSKOP_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return NULL;
    }

    Bioskop *bioskop = malloc(sizeof(Bioskop));
    Bioskop *selectedBioskop = NULL;

    int i = 0;

    // Membaca semua data dari file dan memfilter berdasarkan manager_id
    while (fscanf(file, BIOSKOP_GETTER_FORMAT,
                  &bioskop->id,
                  &bioskop->kota_id,
                  bioskop->nama,
                  &bioskop->manager_id,
                  bioskop->alamat) != EOF)
    {

        if (bioskop->manager_id == manager_id)
        {
            selectedBioskop = bioskop;
            break;
        }
        i++;
    }

    fclose(file);
    free(bioskop);
    return selectedBioskop;
}

Bioskop *createBioskop(const char *nama, const char *alamat, const int kota_id, const int manager_id)
{
    Bioskop *bioskop = malloc(sizeof(Bioskop));
    if (!bioskop)
    {
        printf("Alokasi memori gagal, lokasi: createBioskop\n");
        return NULL;
    }

    setBioskopNama(bioskop, nama);
    setBioskopAlamat(bioskop, alamat);
    setBioskopKotaId(bioskop, kota_id);
    setBioskopId(bioskop, getLastAvailableID(BIOSKOP_DATABASE_NAME));
    setBioskopManagerId(bioskop, manager_id);

    FILE *file = fopen(BIOSKOP_DATABASE_NAME, "a");
    if (!file)
    {
        printf("Gagal membuka file untuk menulis data bioskop\n");
        free(bioskop);
        return NULL;
    }

    fprintf(file, BIOSKOP_SETTER_FORMAT,
            bioskop->id,
            bioskop->kota_id,
            bioskop->nama,
            bioskop->manager_id,
            bioskop->alamat);

    fclose(file);
    return bioskop;
}

Bioskop *updateBioskop(const int id, const char *nama, const char *alamat, const int kota_id, const int manager_id)
{
    Bioskop *updatedBioskop = malloc(sizeof(Bioskop));
    if (!updatedBioskop)
    {
        printf("Alokasi memori gagal, lokasi: updateBioskop\n");
        return NULL;
    }

    // Mengisi data baru menggunakan setter
    setBioskopId(updatedBioskop, id);
    setBioskopNama(updatedBioskop, nama);
    setBioskopAlamat(updatedBioskop, alamat);
    setBioskopKotaId(updatedBioskop, kota_id);
    setBioskopManagerId(updatedBioskop, manager_id);

    // Membuka file database untuk membaca data
    FILE *fromFile = fopen(BIOSKOP_DATABASE_NAME, "r");
    if (!fromFile)
    {
        printf("Gagal membuka file untuk membaca data, lokasi: updateBioskop\n");
        free(updatedBioskop);
        return NULL;
    }

    int count = countBioskopData();
    if (count == -1)
    {
        printf("Penghitungan data bioskop gagal, lokasi: updateBioskop\n");
        fclose(fromFile);
        free(updatedBioskop);
        return NULL;
    }

    int i = 0;
    Bioskop bioskops[count];

    // Membaca semua data dari file ke array bioskops
    while (fscanf(fromFile, BIOSKOP_GETTER_FORMAT,
                  &bioskops[i].id,
                  &bioskops[i].kota_id,
                  bioskops[i].nama,
                  &bioskops[i].manager_id,
                  bioskops[i].alamat) != EOF)
    {
        // Memperbarui data jika ID cocok
        if (bioskops[i].id == id)
        {
            bioskops[i] = *updatedBioskop;
        }
        i++;
    }
    fclose(fromFile);

    // Membuka file database untuk menulis ulang data
    FILE *toFile = fopen(BIOSKOP_DATABASE_NAME, "w");
    if (!toFile)
    {
        printf("Gagal membuka file untuk menulis data, lokasi: updateBioskop\n");
        free(updatedBioskop);
        return NULL;
    }

    // Menulis kembali data bioskop ke file
    for (i = 0; i < count; i++)
    {
        fprintf(toFile, BIOSKOP_SETTER_FORMAT,
                bioskops[i].id,
                bioskops[i].kota_id,
                bioskops[i].nama,
                bioskops[i].manager_id,
                bioskops[i].alamat);
    }

    fclose(toFile);
    return updatedBioskop;
}

int deleteBioskop(Bioskop bioskop)
{
    // Buat pesan konfirmasi
    int len = snprintf(NULL, 0, "Apakah Anda yakin ingin menghapus data bioskop dengan nama '%s'?\n", bioskop.nama) + 1;
    char *head = malloc(len);
    if (!head)
    {
        printf(RED "Gagal mengalokasikan memori.\n" RESET);
        sleep(1);
        return -1;
    }
    snprintf(head, len, "Apakah Anda yakin ingin menghapus data bioskop dengan nama '%s'?\n", bioskop.nama);

    char *menu[] = {
        "Tidak, Batalkan",
        "Ya, Hapus",
    };

    char *header[] = {
        RED BOLD "====================================================\n",
        "             Konfirmasi Hapus Bioskop               \n",
        "====================================================\n\n" RESET,
        head,
        NULL};

    int selection = showMenu(menu, 2, header);
    free(head);

    if (selection == 1)
    {
        return 1; // Pembatalan oleh pengguna
    }

    // Cadangkan data bioskop
    FILE *fromFile = fopen(BIOSKOP_DATABASE_NAME, "r");
    if (!fromFile)
    {
        printf(RED "Gagal membuka file, lokasi: deleteBioskop.\n" RESET);
        sleep(1);
        return -1;
    }

    int count = countBioskopData();
    if (count == -1)
    {
        printf(RED "Penghitungan data bioskop gagal, lokasi: deleteBioskop.\n" RESET);
        fclose(fromFile);
        return -1;
    }

    Bioskop bioskops[count], temp;
    int i = 0;

    while (fscanf(fromFile, BIOSKOP_GETTER_FORMAT,
                  &temp.id,
                  &temp.kota_id,
                  temp.nama,
                  &temp.manager_id,
                  temp.alamat) != EOF)
    {
        if (temp.id != bioskop.id)
        {
            bioskops[i] = temp;
            i++;
        }
    }
    fclose(fromFile);

    // Menulis ulang file dengan data bioskop yang diperbarui
    FILE *toFile = fopen(BIOSKOP_DATABASE_NAME, "w");
    if (!toFile)
    {
        printf(RED "Gagal membuka file untuk ditulis, lokasi: deleteBioskop.\n" RESET);
        return -1;
    }

    for (int j = 0; j < i; j++)
    {
        fprintf(toFile, BIOSKOP_SETTER_FORMAT,
                bioskops[j].id,
                bioskops[j].kota_id,
                bioskops[j].nama,
                bioskops[j].manager_id,
                bioskops[j].alamat);
    }

    fclose(toFile);

    return 1; // Berhasil
}

// ================================== Utils ================================== //

int countBioskopData()
{
    FILE *file = fopen(BIOSKOP_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    Bioskop bioskop;
    int count = 0;

    if (file == NULL)
    {
        printf("Error: File tidak dapat dibuka\n");
        return 1;
    }

    while (fscanf(file, BIOSKOP_GETTER_FORMAT,
                  &bioskop.id,
                  &bioskop.kota_id,
                  bioskop.nama,
                  &bioskop.manager_id,
                  bioskop.alamat) != EOF)
    {
        count++;
    }

    fclose(file);
    return count;
}

int loadBioskop(Bioskop **bioskops)
{

    FILE *file = fopen(BIOSKOP_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int count = countBioskopData();

    *bioskops = (Bioskop *)malloc(count * sizeof(Bioskop));
    if (*bioskops == NULL)
    {
        printf("Gagal mengalokasi memori.\n");
        fclose(file);
        return -1;
    }

    rewind(file);

    int i = 0;

    while (fscanf(file, BIOSKOP_GETTER_FORMAT,
                  &(*bioskops)[i].id,
                  &(*bioskops)[i].kota_id,
                  (*bioskops)[i].nama,
                  &(*bioskops)[i].manager_id,
                  (*bioskops)[i].alamat) != EOF)
    {
        i++;
    }

    fclose(file);
    return count;
}

void printBioskopTable(Bioskop *bioskops, int count, int page, int perPage, int selection)
{
    int idWidth = 2, kotaWidth = 7, namaWidth = 12, managerWidth = 7;

    int start = (page - 1) * perPage;
    int end = start + perPage;
    if (end > count)
        end = count;
    // Hitung panjang kolom terpanjang
    for (int i = start; i < end; i++)
    {
        int idLen = snprintf(NULL, 0, "%d", bioskops[i].id);
        if (idLen > idWidth)
            idWidth = idLen;

        if ((int)strlen(bioskops[i].nama) > namaWidth)
            namaWidth = strlen(bioskops[i].nama);

        const char *manager = getBioskopManager(&bioskops[i]);

        if ((int)strlen(manager) > managerWidth)
            managerWidth = strlen(manager);

        const char *kota = getBioskopKota(&bioskops[i]);

        if ((int)strlen(kota) > kotaWidth)
            kotaWidth = strlen(kota);
    }

    int tableWidth = snprintf(NULL, 0,
                              "[ * ]| %-*s | %-*s | %-*s | %-*s |\n",
                              idWidth, "ID",
                              kotaWidth, "Kota",
                              namaWidth, "Nama Bioskop",
                              managerWidth, "Manager");

    // Cetak garis atas tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak header tabel
    printf("[ * ]| %-*s | %-*s | %-*s | %-*s |\n",
           idWidth, "ID",
           kotaWidth, "Kota",
           namaWidth, "Nama Bioskop",
           managerWidth, "Manager");

    // Cetak garis bawah header
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak isi tabel
    for (int i = start; i < end; i++)
    {
        if (selection == i + 1)
        {
            printf(BLUE BOLD "[ * ]| %-*d | %-*s | %-*s | %-*s |\n" RESET,
                   idWidth, bioskops[i].id,
                   kotaWidth, getBioskopKota(&bioskops[i]),
                   namaWidth, bioskops[i].nama,
                   managerWidth, getBioskopManager(&bioskops[i]));
        }
        else
        {
            printf("[   ]| %-*d | %-*s | %-*s | %-*s |\n",
                   idWidth, bioskops[i].id,
                   kotaWidth, getBioskopKota(&bioskops[i]),
                   namaWidth, bioskops[i].nama,
                   managerWidth, getBioskopManager(&bioskops[i]));
        }
    }

    // Cetak garis bawah tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Informasi halaman
    printf("Page %d of %d\n", page, (count + perPage - 1) / perPage);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>

#include "display.h"
#include "kota.h"
#include "menu.h"
#include "db.h"

// ==================================== Other ================================== //

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

// ================================== Main Menu ================================ //

int menuKota()
{
    Kota *kotaList;
    int count = loadKota(&kotaList);

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        system("cls");
        selection = (page - 1) * perPage + pointer;

        printf("====================================================\n");
        printf("               Menu Management Kota                 \n");
        printf("====================================================\n");

        printKotaTable(kotaList, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page");
        printf(GREEN "\n[C]: Create" RESET " | " YELLOW "[U]: Update" RESET " | " RED "[D]: Delete" RESET " | " BG_RED WHITE "[E] Exit\n" RESET);

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
                    sleep(500);
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
                    sleep(500);
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
        else if (command == 32)
        {
            printf("City selected: %d\n", selection);
            free(kotaList);
            return 0;
        }
        else if (command == 'C' || command == 'c')
        {
            createKotaMenu();

            free(kotaList);
            count = loadKota(&kotaList);
            pointer = 1;
        }
        else if (command == 'U' || command == 'u')
        {
            updateKotaMenu(kotaList[selection - 1]);

            free(kotaList);
            count = loadKota(&kotaList);
            pointer = 1;
        }
        else if (command == 'D' || command == 'd')
        {
            deleteKota(kotaList[selection - 1]);

            free(kotaList);
            count = loadKota(&kotaList);
            pointer = 1;
        }
        else if (command == 'E' || command == 'e')
        {
            free(kotaList);
            return 0;
        }
        else
        {
            printf(YELLOW BOLD "Command not found\n" RESET);
            sleep(500);
        }
    }
}

void createKotaMenu()
{
    system("cls");

    printf(GREEN "====================================================\n");
    printf("                Menu Tambah Kota                    \n");
    printf("====================================================\n" RESET);

    char nama[MAX_KOTA_NAME];

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

    Kota *newKota = createKota(nama);
    if (!newKota)
    {
        printf(RED BOLD "Gagal menambah kota. Harap coba lagi!\n" RESET);
        return;
    }

    printf(GREEN BOLD "Berhasil menambah kota!.\n" RESET);
    sleep(2);
    free(newKota);
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

// ================================== Action ================================== //

Kota *findKotaByID(int id)
{
    FILE *file = fopen(KOTA_DATABASE_NAME, "r");

    if (!file)
    {
        return NULL;
    }

    Kota *kota = malloc(sizeof(Kota));
    if (!kota)
    {
        fclose(file);
        return NULL;
    }

    while (fscanf(file, "%d,%[^,]", &kota->id, kota->nama) == 2)
    {
        if (kota->id == id)
        {
            fclose(file);
            return kota;
        }
    }

    fclose(file);
    free(kota);
    return NULL;
}

Kota *findKotaByName(const char *nama)
{
    FILE *file = fopen(KOTA_DATABASE_NAME, "r");
    if (!file)
    {
        return NULL;
    }

    Kota *kota = malloc(sizeof(Kota));
    if (!kota)
    {
        fclose(file);
        return NULL;
    }

    while (fscanf(file, "%d,%[^,]", &kota->id, kota->nama) == 2)
    {
        if (strcmp(kota->nama, nama) == 0)
        {
            fclose(file);
            return kota;
        }
    }

    fclose(file);
    free(kota);
    return NULL;
}

Kota *createKota(const char *nama)
{
    Kota *kota = malloc(sizeof(Kota));
    if (!kota)
    {
        printf("Alokasi memori gagal, lokasi: createKota\n");
        return NULL;
    }

    strncpy(kota->nama, nama, MAX_KOTA_NAME);
    kota->nama[MAX_KOTA_NAME - 1] = '\0';

    FILE *file = fopen(KOTA_DATABASE_NAME, "a");
    if (!file)
    {
        free(kota);
        printf("Gagal membuka file.\n");
        return NULL;
    }

    int id = getLastAvailableID(KOTA_DATABASE_NAME);
    kota->id = id;

    fprintf(file, KOTA_SETTER_FORMAT,
            kota->id,
            kota->nama);

    fclose(file);
    return kota;
}

Kota *updateKota(const int id, const char *nama)
{
    Kota *updatedKota = malloc(sizeof(Kota));
    if (!updatedKota)
    {
        printf("Alokasi memori gagal, location: updateKota");
        return NULL;
    }

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

// ================================== Utils ================================== //

int countKotaData()
{
    FILE *file = fopen(KOTA_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int count = 0;
    Kota kota;

    while (fscanf(file, KOTA_GETTER_FORMAT, &kota.id, kota.nama) != EOF)
    {
        count++;
    }
    fclose(file);
    return count;
}

int loadKota(Kota **kotaList)
{
    FILE *file = fopen(KOTA_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int count = countKotaData();

    *kotaList = (Kota *)malloc(count * sizeof(Kota));
    if (*kotaList == NULL)
    {
        printf("Gagal mengalokasi memori.\n");
        fclose(file);
        return -1;
    }

    rewind(file);
    int i = 0;

    while (fscanf(file, KOTA_GETTER_FORMAT, &(*kotaList)[i].id, (*kotaList)[i].nama) != EOF)
    {
        i++;
    }

    fclose(file);
    return count;
}

void printKotaTable(const Kota *kotaList, int count, int page, int perPage, int selection)
{
    int start = (page - 1) * perPage;
    int end = start + perPage;
    if (end > count)
        end = count;

    int idWidth = 2, namaWidth = 12;

    for (int i = start; i < end; i++)
    {
        int idWidthC = snprintf(NULL, 0, "%d", kotaList[i].id);
        if (idWidthC > idWidth)
            idWidth = idWidthC;

        if ((int)strlen(kotaList[i].nama) > namaWidth)
            namaWidth = strlen(kotaList[i].nama);
    }

    int tableWidth = snprintf(NULL, 0,
                              "[ * ]| %-*s | %-*s |\n",
                              idWidth, "ID",
                              namaWidth, "Nama Kota");

    // Print table header
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    printf("[ * ]| %-*s | %-*s |\n", idWidth, "ID", namaWidth, "Nama Kota");

    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Print table rows
    for (int i = start; i < end; i++)
    {
        // Display selected row with a marker
        if (selection == i + 1)
        {
            printf(BLUE BOLD "[ * ]| %-*d | %-*s |\n" RESET, idWidth, kotaList[i].id, namaWidth, kotaList[i].nama);
        }
        else
        {
            printf("[   ]| %-*d | %-*s |\n", idWidth, kotaList[i].id, namaWidth, kotaList[i].nama);
        }
    }

    // Print table footer
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Display pagination info
    printf("Page %d of %d\n", page, (count + perPage - 1) / perPage);
}

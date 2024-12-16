#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>

#include "display.h"
#include "menu.h"
#include "auth.h"
#include "bioskop.h"
#include "user.h"
#include "studio.h"
#include "db.h"

// ================================== setter ================================== //

void setStudioBioskopId(Studio *studio, int bioskop_id)
{
    studio->bioskop_id = bioskop_id;
}

void setNama(Studio *studio, const char *nama)
{
    strncpy(studio->nama, nama, MAX_STUDIO_NAME - 1);
    studio->nama[MAX_STUDIO_NAME - 1] = '\0'; // Ensures null-termination
}

void setJumlahKursi(Studio *studio, int jumlah_kursi)
{
    studio->jumlah_kursi = jumlah_kursi;
}

void setAdditionalFee(Studio *studio, int additionalFee)
{
    studio->additionalFee = additionalFee;
}

// ==================================== getter ==================================== //

int getStudioBioskopId(const Studio *studio)
{
    return studio->bioskop_id;
}

const char *getNama(const Studio *studio)
{
    return studio->nama;
}

int getJumlahKursi(const Studio *studio)
{
    return studio->jumlah_kursi;
}

int getAdditionalFee(const Studio *studio)
{
    return studio->additionalFee;
}

// ==================================== Main Menu =================================//

int menuStudio()
{
    Studio *studios;
    int count = loadStudio(&studios);

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {

        system("cls");
        selection = (page - 1) * perPage + pointer;

        printf(GREEN "====================================================\n");
        printf("             Menu Manajemen Studio                  \n");
        printf("====================================================\n" RESET);

        printStudioTable(studios, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page");
        printf(GREEN "\n[C]: Create" RESET " | " YELLOW "[U]: Update" RESET " | " RED "[D]: Delete" RESET " | " BG_RED WHITE "[E] Exit" RESET "\n" RESET);

        command = getch();

        if (command == 224)
        {
            command = getch();

            if (command == 77) // Right arrow
            {
                pointer = 1;
                if (page * perPage < count)
                    page++;
                else
                {
                    printf(BLUE "Sudah di halaman terakhir.\n");
                    sleep(1);
                }
            }
            else if (command == 75) // Left arrow
            {
                pointer = 1;
                if (page > 1)
                    page--;
                else
                {
                    printf(BLUE "Sudah di halaman pertama.\n");
                    sleep(1);
                }
            }
            else if (command == 72) // Up arrow
            {
                if (pointer > 1)
                {
                    pointer--;
                }
            }
            else if (command == 80) // Down arrow
            {
                if (pointer < perPage && (page - 1) * perPage + pointer < count)
                {
                    pointer++;
                }
            }
        }
        else if (command == 32)
        {
            printf("Data terpilih %d\n", selection);
            free(studios);
            return 0;
        }
        else if (command == 'C' || command == 'c')
        {
            createStudioMenu();

            free(studios);
            count = loadStudio(&studios);
        }
        else if (command == 'U' || command == 'u')
        {
            updateStudioMenu(studios[selection - 1]);

            free(studios);
            count = loadStudio(&studios);
        }
        else if (command == 'D' || command == 'd')
        {
            deleteStudio(studios[selection - 1]);

            free(studios);
            count = loadStudio(&studios);
        }
        else if (command == 'E' || command == 'e')
        {
            free(studios);
            return 0;
        }
        else
        {
            printf(YELLOW BOLD "Perintah tidak ditemukan\n" RESET);
            sleep(1);
        }
    }
}

void createStudioMenu()
{
    system("cls");

    printf(GREEN "====================================================\n");
    printf("                Menu Tambah Studio                  \n");
    printf("====================================================\n" RESET);

    char nama[MAX_STUDIO_NAME];
    int jumlah_kursi = 0;
    int additionalFee = 0;

    while (1)
    {
        printf("Masukkan nama studio\t: ");
        fgets(nama, sizeof(nama), stdin);
        nama[strcspn(nama, "\n")] = 0;

        if (strcmp(nama, "") == 0)
        {
            printf(RED BOLD "Nama studio tidak boleh kosong.\n" RESET);
            sleep(1);
            continue;
        }
        break;
    }

    while (1)
    {
        printf("Masukkan jumlah kursi\t: ");
        scanf("%d", &jumlah_kursi);

        if (jumlah_kursi <= 0)
        {
            printf(RED BOLD "Jumlah kursi tidak valid.\n" RESET);
            sleep(1);
            continue;
        }
        break;
    }

    while (1)
    {
        printf("Masukkan additionalFee\t: ");
        scanf("%d", &additionalFee);

        if (additionalFee < 0)
        {
            printf(RED BOLD "AdditionalFee tidak valid.\n" RESET);
            sleep(1);
            continue;
        }
        break;
    }

    Studio *newStudio = createStudio(nama, jumlah_kursi, additionalFee);
    if (!newStudio)
    {
        printf(RED BOLD "Gagal menambah studio. Harap Coba Lagi!\n" RESET);
        return;
    }

    printf(GREEN BOLD "Berhasil menambah studio!.\n" RESET);
    sleep(2);
    free(newStudio);
}

void updateStudioMenu(Studio studio)
{
    printf(YELLOW "====================================================\n");
    printf("                 Menu Edit Studio                   \n");
    printf("====================================================\n" RESET);

    char nama[MAX_STUDIO_NAME];
    int jumlah_kursi = 0;
    int additionalFee = 0;

    while (1)
    {
        printf("Masukkan nama studio\t: ");
        fgets(nama, sizeof(nama), stdin);
        nama[strcspn(nama, "\n")] = 0;

        if (strcmp(nama, "") == 0)
        {
            printf(RED BOLD "Nama studio tidak boleh kosong.\n" RESET);
            sleep(1);
            continue;
        }
        break;
    }

    while (1)
    {
        printf("Masukkan jumlah kursi\t: ");
        scanf("%d", &jumlah_kursi);

        if (jumlah_kursi <= 0)
        {
            printf(RED BOLD "Jumlah kursi tidak valid.\n" RESET);
            sleep(1);
            continue;
        }
        break;
    }

    while (1)
    {
        printf("Masukkan additionalFee\t: ");
        scanf("%d", &additionalFee);

        if (additionalFee < 0)
        {
            printf(RED BOLD "AdditionalFee tidak valid.\n" RESET);
            sleep(1);
            continue;
        }
        break;
    }

    Studio *updatedStudio = updateStudio(studio.id, nama, jumlah_kursi, additionalFee);
    if (!updatedStudio)
    {
        printf(RED BOLD "Gagal mengubah studio. Harap Coba Lagi!\n" RESET);
        return;
    }

    printf(GREEN BOLD "Berhasil mengubah studio!.\n" RESET);
    sleep(2);
    free(updatedStudio);
}

// ==================================== Action ====================================//

Studio *findStudioById(int studio_id)
{
    FILE *file = fopen(STUDIO_DATABASE_NAME, "r");
    if (!file)
    {
        printf("Error membuka file studio.\n");
        return NULL;
    }

    Studio *studio = malloc(sizeof(Studio));
    if (!studio)
    {
        printf("Gagal mengalokasikan memori.\n");
        fclose(file);
        return NULL;
    }

    while (fscanf(file, STUDIO_GETTER_FORMAT,
                  &studio->id, studio->nama, &studio->bioskop_id,
                  &studio->jumlah_kursi, &studio->additionalFee) == 5)
    {
        if (studio->id == studio_id)
        {
            fclose(file);
            return studio;
        }
    }

    free(studio);
    fclose(file);
    return NULL;
}

int findStudioCapacityById(int studio_id)
{
    FILE *file = fopen(STUDIO_DATABASE_NAME, "r");
    if (!file)
    {
        printf("Error membuka file studio.\n");
        return -1;
    }

    Studio studio;
    while (fscanf(file, STUDIO_GETTER_FORMAT,
                  &studio.id, studio.nama, &studio.bioskop_id,
                  &studio.jumlah_kursi, &studio.additionalFee) == 5)
    {
        if (studio.id == studio_id)
        {
            fclose(file);
            return studio.jumlah_kursi; // Kapasitas studio
        }
    }

    fclose(file);
    return -1; // Studio tidak ditemukan
}

Studio *createStudio(const char *nama, int jumlah_kursi, int additionalFee)
{
    Studio *studio = malloc(sizeof(Studio));
    if (!studio)
    {
        printf("Alokasi memori gagal, lokasi: createStudio.\n");
        return NULL;
    }

    User *user = getCurrentUser();

    int bioskop_id = findBioskopByManagerId(user->id)->id;

    setStudioBioskopId(studio, bioskop_id);
    setNama(studio, nama);
    setJumlahKursi(studio, jumlah_kursi);
    setAdditionalFee(studio, additionalFee);

    FILE *file = fopen(STUDIO_DATABASE_NAME, "a");
    if (!file)
    {
        free(studio);
        return NULL;
    }

    int id = getLastAvailableID(STUDIO_DATABASE_NAME);
    studio->id = id;

    fprintf(file, STUDIO_SETTER_FORMAT,
            studio->id,
            getNama(studio),
            getStudioBioskopId(studio),
            getJumlahKursi(studio),
            getAdditionalFee(studio));

    fclose(file);
    return studio;
}

Studio *updateStudio(const int id, const char *nama, int jumlah_kursi, int additionalFee)
{
    Studio *updatedStudio = malloc(sizeof(Studio));
    if (!updatedStudio)
    {
        printf("Alokasi memori gagal, lokasi: updateStudio.\n");
        return NULL;
    }

    updatedStudio->id = id;
    setNama(updatedStudio, nama);
    setJumlahKursi(updatedStudio, jumlah_kursi);
    setAdditionalFee(updatedStudio, additionalFee);

    FILE *fromFile = fopen(STUDIO_DATABASE_NAME, "r");
    if (!fromFile)
    {
        free(updatedStudio);
        return NULL;
    }

    int count = countStudioData();
    if (count == -1)
    {
        fclose(fromFile);
        free(updatedStudio);
        return NULL;
    }

    Studio studios[count];
    int i = 0;

    while (fscanf(fromFile, STUDIO_GETTER_FORMAT,
                  &studios[i].id,
                  studios[i].nama,
                  &studios[i].bioskop_id,
                  &studios[i].jumlah_kursi,
                  &studios[i].additionalFee) != EOF)
    {
        if (studios[i].id == id)
        {
            setStudioBioskopId(updatedStudio, studios[i].bioskop_id);
            studios[i] = *updatedStudio;
        }
        i++;
    }
    fclose(fromFile);

    FILE *toFile = fopen(STUDIO_DATABASE_NAME, "w");
    for (i = 0; i < count; i++)
    {
        fprintf(toFile, STUDIO_SETTER_FORMAT,
                studios[i].id,
                studios[i].nama,
                studios[i].bioskop_id,
                studios[i].jumlah_kursi,
                studios[i].additionalFee);
    }
    fclose(toFile);

    return updatedStudio;
}

int deleteStudio(Studio studio)
{
    int len = snprintf(NULL, 0, "Apakah Anda yakin ingin menghapus data studio dengan ID '%d'?\n", studio.id) + 1;
    char *head = malloc(len);
    if (!head)
    {
        printf(RED "Gagal mengalokasikan memori.\n" RESET);
        sleep(1);

        return -1;
    }
    snprintf(head, len, "Apakah Anda yakin ingin menghapus data studio dengan ID '%d'?\n", studio.id);

    char *menu[] = {
        "Tidak, Batalkan",
        "Ya, Hapus",
    };

    char *header[] = {
        RED BOLD "====================================================\n",
        "             Konfirmasi Hapus Studio                \n",
        "====================================================\n\n" RESET,
        head,
        NULL};

    int selection = showMenu(menu, 2, header);
    free(head);

    if (selection == 1)
    {
        return 1;
    }

    FILE *fromFile = fopen(STUDIO_DATABASE_NAME, "r");
    if (!fromFile)
    {
        printf(RED "Gagal membuka file, lokasi: deleteStudio.\n" RESET);
        sleep(1);
        return -1;
    }

    int count = countStudioData();
    if (count == -1)
    {
        printf(RED "Penghitungan data studio gagal, lokasi: deleteStudio.\n" RESET);
        fclose(fromFile);
        return -1;
    }

    Studio studios[count], temp;
    int i = 0;
    while (fscanf(fromFile, STUDIO_GETTER_FORMAT,
                  &temp.id,
                  temp.nama,
                  &temp.bioskop_id,
                  &temp.jumlah_kursi,
                  &temp.additionalFee) != EOF)
    {
        if (temp.id != studio.id)
        {
            studios[i] = temp;
            i++;
        }
    }
    fclose(fromFile);

    FILE *toFile = fopen(STUDIO_DATABASE_NAME, "w");
    if (!toFile)
    {
        printf(RED "Gagal membuka file untuk ditulis, lokasi: deleteStudio.\n" RESET);
        return -1;
    }

    i = 0;
    while (i < count - 1)
    {
        fprintf(toFile, STUDIO_SETTER_FORMAT,
                studios[i].id,
                studios[i].nama,
                studios[i].bioskop_id,
                studios[i].jumlah_kursi,
                studios[i].additionalFee);
        i++;
    }

    fclose(toFile);

    return 1;
}

// ==================================== Utils ====================================//

int countStudioData()
{
    FILE *file = fopen(STUDIO_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int count = 0;
    Studio studio;

    // Menggunakan format yang sesuai dengan struktur Studio
    while (fscanf(file, STUDIO_GETTER_FORMAT,
                  &studio.id,
                  studio.nama,
                  &studio.bioskop_id,
                  &studio.jumlah_kursi,
                  &studio.additionalFee) != EOF)
    {
        count++;
    }
    fclose(file);
    return count;
}

int loadStudio(Studio **studios)
{
    FILE *file = fopen(STUDIO_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int count = countStudioData();
    if (count == -1)
    {
        fclose(file);
        return -1;
    }

    *studios = (Studio *)malloc(count * sizeof(Studio));
    if (*studios == NULL)
    {
        printf("Gagal mengalokasi memori.\n");
        fclose(file);
        return -1;
    }

    rewind(file);
    int i = 0;

    // Membaca data dari file dan menyimpannya ke dalam array studios
    while (fscanf(file, STUDIO_GETTER_FORMAT,
                  &(*studios)[i].id,
                  (*studios)[i].nama,
                  &(*studios)[i].bioskop_id,
                  &(*studios)[i].jumlah_kursi,
                  &(*studios)[i].additionalFee) != EOF)
    {
        i++;
    }

    fclose(file);
    return count;
}

void printStudioTable(Studio *studios, int count, int page, int perPage, int selection)
{
    int idWidth = 2, namaWidth = 4, jumlahKursiWidth = 12, additionalFeeWidth = 13;

    int start = (page - 1) * perPage;
    int end = start + perPage;
    if (end > count)
        end = count;

    // Hitung panjang kolom terpanjang
    for (int i = start; i < end; i++)
    {
        int idLen = snprintf(NULL, 0, "%d", studios[i].id);
        if (idLen > idWidth)
            idWidth = idLen;

        if ((int)strlen(studios[i].nama) > namaWidth)
            namaWidth = strlen(studios[i].nama);

        int kursiLen = snprintf(NULL, 0, "%d", studios[i].jumlah_kursi);
        if (kursiLen > jumlahKursiWidth)
            jumlahKursiWidth = kursiLen;

        int additionalFeeLen = snprintf(NULL, 0, "%d", studios[i].additionalFee);
        if (additionalFeeLen > additionalFeeWidth)
            additionalFeeWidth = additionalFeeLen;
    }

    int tableWidth = snprintf(NULL, 0,
                              "[ * ]| %-*s | %-*s | %-*s | %-*s |\n",
                              idWidth, "ID",
                              namaWidth, "Nama",
                              jumlahKursiWidth, "Jumlah Kursi",
                              additionalFeeWidth, "AdditionalFee");

    // Cetak garis atas tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak header tabel
    printf("[ * ]| %-*s | %-*s | %-*s | %-*s |\n",
           idWidth, "ID",
           namaWidth, "Nama",
           jumlahKursiWidth, "Jumlah Kursi",
           additionalFeeWidth, "AdditionalFee");

    // Cetak garis bawah header
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak isi tabel
    for (int i = start; i < end; i++)
    {
        // Tampilkan dengan penanda jika dipilih
        if (selection == i + 1)
        {
            printf(BLUE BOLD "[ * ]| %-*d | %-*s | %-*d | %-*d |\n" RESET,
                   idWidth, studios[i].id,
                   namaWidth, studios[i].nama,
                   jumlahKursiWidth, studios[i].jumlah_kursi,
                   additionalFeeWidth, studios[i].additionalFee);
        }
        else
        {
            printf("[   ]| %-*d | %-*s | %-*d | %-*d |\n",
                   idWidth, studios[i].id,
                   namaWidth, studios[i].nama,
                   jumlahKursiWidth, studios[i].jumlah_kursi,
                   additionalFeeWidth, studios[i].additionalFee);
        }
    }

    // Cetak garis bawah tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Informasi halaman
    printf("Page %d of %d\n", page, (count + perPage - 1) / perPage);
}

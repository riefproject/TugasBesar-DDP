#include <stdio.h>
#include <string.h>
#include "studio.h"

// Constructor
Studio createStudio(int id, int bioskop_id, int jumlah_kursi, float additional_fee)
{
    Studio studio;
    studio.id = id;
    studio.bioskop_id = bioskop_id;
    studio.jumlah_kursi = jumlah_kursi;
    studio.additional_fee = additional_fee;
    return studio;
}

// Getter
int getStudioId(const Studio *studio)
{
    return studio->id;
}

int getStudioBioskopId(const Studio *studio)
{
    return studio->bioskop_id;
}

int getStudioJumlahKursi(const Studio *studio)
{
    return studio->jumlah_kursi;
}

float getStudioAdditionalFee(const Studio *studio)
{
    return studio->additional_fee;
}

// Setter
void setStudioId(Studio *studio, int id)
{
    studio->id = id;
}

void setStudioBioskopId(Studio *studio, int bioskop_id)
{
    studio->bioskop_id = bioskop_id;
}

void setStudioJumlahKursi(Studio *studio, int jumlah_kursi)
{
    studio->jumlah_kursi = jumlah_kursi;
}

void setStudioAdditionalFee(Studio *studio, float additional_fee)
{
    studio->additional_fee = additional_fee;
}

// Membaca data studio dari file CSV
int loadStudio(Studio studioList[], int *count)
{
    FILE *file = fopen(STUDIO_CSV_FILE, "r");
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
        int id, bioskop_id, jumlah_kursi;
        float additional_fee;
        sscanf(line, "%d,%d,%d,%f", &id, &bioskop_id, &jumlah_kursi, &additional_fee);
        studioList[*count] = createStudio(id, bioskop_id, jumlah_kursi, additional_fee);
        (*count)++;
    }

    fclose(file);
    return 1;
}

// Menyimpan data studio ke file CSV
int saveStudio(const Studio studioList[], int count)
{
    FILE *file = fopen(STUDIO_CSV_FILE, "w");
    if (!file)
    {
        perror("Gagal membuka file");
        return 0;
    }

    fprintf(file, "id,bioskop_id,jumlah_kursi,additional_fee\n");
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d,%d,%d,%.2f\n",
                getStudioId(&studioList[i]),
                getStudioBioskopId(&studioList[i]),
                getStudioJumlahKursi(&studioList[i]),
                getStudioAdditionalFee(&studioList[i]));
    }

    fclose(file);
    return 1;
}

// Menampilkan daftar studio
void displayStudio(const Studio studioList[], int count, const Bioskop bioskopList[], int bioskopCount)
{
    printf("\nDaftar Studio:\n");
    printf("=====================================================\n");
    printf("%-5s %-20s %-15s %-15s\n", "ID", "Bioskop", "Jumlah Kursi", "Additional Fee");
    printf("=====================================================\n");

    for (int i = 0; i < count; i++)
    {
        const char *bioskopNama = "Tidak Ditemukan";
        for (int j = 0; j < bioskopCount; j++)
        {
            if (getBioskopId(&bioskopList[j]) == getStudioBioskopId(&studioList[i]))
            {
                bioskopNama = getBioskopNama(&bioskopList[j]);
                break;
            }
        }
        printf("%-5d %-20s %-15d %-15.2f\n",
               getStudioId(&studioList[i]),
               bioskopNama,
               getStudioJumlahKursi(&studioList[i]),
               getStudioAdditionalFee(&studioList[i]));
    }
    printf("=====================================================\n");
}

// Menambah studio baru
int addStudio(Studio studioList[], int *count, int bioskop_id, int jumlah_kursi, float additional_fee)
{
    if (*count >= MAX_STUDIO)
    {
        printf("Gagal menambah studio: kapasitas penuh.\n");
        return 0;
    }

    int newId = *count > 0 ? getStudioId(&studioList[*count - 1]) + 1 : 1;

    studioList[*count] = createStudio(newId, bioskop_id, jumlah_kursi, additional_fee);
    (*count)++;

    return 1;
}

// Mencari studio berdasarkan ID
Studio *findStudioById(const Studio studioList[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (getStudioId(&studioList[i]) == id)
        {
            return &studioList[i];
        }
    }
    return NULL;
}

void displayStudioFromFile()
{
    Studio studioList[MAX_STUDIO];
    Bioskop bioskopList[MAX_BIOSKOP];
    int studioCount = 0, bioskopCount = 0;

    // Load data bioskop
    if (!loadBioskop(bioskopList, &bioskopCount))
    {
        printf("Gagal memuat data bioskop.\n");
        return;
    }

    // Load data studio
    if (!loadStudio(studioList, &studioCount))
    {
        printf("Gagal memuat data studio.\n");
        return;
    }

    // Tampilkan daftar studio
    printf("\nDaftar Studio:\n");
    printf("=====================================================\n");
    printf("%-5s %-20s %-15s %-15s\n", "ID", "Bioskop", "Jumlah Kursi", "Additional Fee");
    printf("=====================================================\n");

    for (int i = 0; i < studioCount; i++)
    {
        const char *bioskopNama = "Tidak Ditemukan";
        for (int j = 0; j < bioskopCount; j++)
        {
            if (getBioskopId(&bioskopList[j]) == getStudioBioskopId(&studioList[i]))
            {
                bioskopNama = getBioskopNama(&bioskopList[j]);
                break;
            }
        }
        printf("%-5d %-20s %-15d %-15.2f\n",
               getStudioId(&studioList[i]),
               bioskopNama,
               getStudioJumlahKursi(&studioList[i]),
               getStudioAdditionalFee(&studioList[i]));
    }
    printf("=====================================================\n");
}

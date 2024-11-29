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

int addStudio()
{
    FILE *file = fopen(STUDIO_CSV_FILE, "r+"); // Buka file untuk membaca dan menulis
    if (!file)
    {
        // Jika file tidak ada, buat file baru
        file = fopen(STUDIO_CSV_FILE, "w+");
        if (!file)
        {
            perror("Gagal membuka atau membuat file studio.");
            return 0;
        }
        // Tulis header ke file baru
        fprintf(file, "id,bioskop_id,jumlah_kursi,additional_fee\n");
    }

    char line[256];
    int id = 0, bioskop_id, jumlah_kursi;
    float additional_fee;

    // Skip header
    fgets(line, sizeof(line), file);

    // Cari ID terakhir
    while (fgets(line, sizeof(line), file))
    {
        int existingId;
        sscanf(line, "%d,%*d,%*d,%*f", &existingId);
        id = existingId; // Simpan ID terakhir
    }

    // Ambil input dari admin
    printf("Masukkan ID Bioskop: ");
    scanf("%d", &bioskop_id);
    printf("Masukkan Jumlah Kursi: ");
    scanf("%d", &jumlah_kursi);
    printf("Masukkan Biaya Tambahan: ");
    scanf("%f", &additional_fee);

    // Tambahkan studio baru
    id++; // Increment ID terakhir
    fprintf(file, "%d,%d,%d,%.2f\n", id, bioskop_id, jumlah_kursi, additional_fee);

    fclose(file);
    printf("Studio berhasil ditambahkan dengan ID %d.\n", id);
    return 1;
}

void findStudioById(int id)
{
    FILE *file = fopen(STUDIO_CSV_FILE, "r");
    if (!file)
    {
        printf("File studio.csv tidak ditemukan.\n");
        return;
    }

    char line[256];
    // Skip header
    fgets(line, sizeof(line), file);

    // Cari studio berdasarkan ID
    while (fgets(line, sizeof(line), file))
    {
        int existingId, bioskop_id, jumlah_kursi;
        float additional_fee;

        sscanf(line, "%d,%d,%d,%f", &existingId, &bioskop_id, &jumlah_kursi, &additional_fee);

        if (existingId == id)
        {
            printf("Studio ditemukan:\n");
            printf("ID: %d\n", existingId);
            printf("Bioskop ID: %d\n", bioskop_id);
            printf("Jumlah Kursi: %d\n", jumlah_kursi);
            printf("Biaya Tambahan: %.2f\n", additional_fee);
            fclose(file);
            return;
        }
    }

    printf("Studio dengan ID %d tidak ditemukan.\n", id);
    fclose(file);
}

void displayStudioFromFile()
{
    FILE *studioFile = fopen(STUDIO_CSV_FILE, "r");
    FILE *bioskopFile = fopen(BIOSKOP_CSV_FILE, "r");

    if (!studioFile)
    {
        printf("File studio.csv tidak ditemukan.\n");
        return;
    }
    if (!bioskopFile)
    {
        printf("File bioskop.csv tidak ditemukan.\n");
        fclose(studioFile);
        return;
    }

    char studioLine[256], bioskopLine[256];
    printf("\nDaftar Studio:\n");
    printf("=====================================================\n");
    printf("%-5s %-20s %-15s %-15s\n", "ID", "Bioskop", "Jumlah Kursi", "Additional Fee");
    printf("=====================================================\n");

    // Lewati header bioskop
    fgets(bioskopLine, sizeof(bioskopLine), bioskopFile);

    // Lewati header studio
    fgets(studioLine, sizeof(studioLine), studioFile);

    // Tampilkan data studio
    while (fgets(studioLine, sizeof(studioLine), studioFile))
    {
        int id, bioskop_id, jumlah_kursi;
        float additional_fee;
        char bioskopNama[MAX_BIOSKOP_NAME] = "Tidak Ditemukan";

        sscanf(studioLine, "%d,%d,%d,%f", &id, &bioskop_id, &jumlah_kursi, &additional_fee);

        // Cari nama bioskop berdasarkan bioskop_id
        rewind(bioskopFile);                                  // Kembali ke awal file bioskop
        fgets(bioskopLine, sizeof(bioskopLine), bioskopFile); // Lewati header
        while (fgets(bioskopLine, sizeof(bioskopLine), bioskopFile))
        {
            int existingBioskopId;
            char namaBioskop[MAX_BIOSKOP_NAME];
            sscanf(bioskopLine, "%d,%*d,%49[^,],%*s", &existingBioskopId, namaBioskop);
            if (existingBioskopId == bioskop_id)
            {
                strncpy(bioskopNama, namaBioskop, MAX_BIOSKOP_NAME);
                break;
            }
        }

        printf("%-5d %-20s %-15d %-15.2f\n", id, bioskopNama, jumlah_kursi, additional_fee);
    }

    printf("=====================================================\n");

    fclose(studioFile);
    fclose(bioskopFile);
}

int updateStudio()
{
    FILE *file = fopen(STUDIO_CSV_FILE, "r");
    if (!file)
    {
        printf("File studio.csv tidak ditemukan.\n");
        return 0;
    }

    FILE *tempFile = fopen(TEMP_STUDIO_FILE, "w");
    if (!tempFile)
    {
        perror("Gagal membuat file sementara.");
        fclose(file);
        return 0;
    }

    int id;
    int jumlahKursiBaru;
    float additionalFeeBaru;

    printf("Masukkan ID Studio yang ingin diperbarui: ");
    scanf("%d", &id);
    printf("Masukkan Jumlah Kursi Baru: ");
    scanf("%d", &jumlahKursiBaru);
    printf("Masukkan Additional Fee Baru: ");
    scanf("%f", &additionalFeeBaru);

    char line[256];
    int found = 0;

    // Salin header
    fgets(line, sizeof(line), file);
    fputs(line, tempFile);

    // Proses baris data
    while (fgets(line, sizeof(line), file))
    {
        int existingId, bioskopId, jumlahKursi;
        float additionalFee;
        sscanf(line, "%d,%d,%d,%f", &existingId, &bioskopId, &jumlahKursi, &additionalFee);

        if (existingId == id)
        {
            fprintf(tempFile, "%d,%d,%d,%.2f\n", id, bioskopId, jumlahKursiBaru, additionalFeeBaru);
            found = 1;
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
        remove(STUDIO_CSV_FILE);
        rename(TEMP_STUDIO_FILE, STUDIO_CSV_FILE);
        printf("Studio dengan ID %d berhasil diperbarui.\n", id);
    }
    else
    {
        remove(TEMP_STUDIO_FILE);
        printf("Studio dengan ID %d tidak ditemukan.\n", id);
    }

    return found;
}

int deleteStudio()
{
    FILE *file = fopen(STUDIO_CSV_FILE, "r");
    if (!file)
    {
        printf("File studio.csv tidak ditemukan.\n");
        return 0;
    }

    FILE *tempFile = fopen(TEMP_STUDIO_FILE, "w");
    if (!tempFile)
    {
        perror("Gagal membuat file sementara.");
        fclose(file);
        return 0;
    }

    int id;
    printf("Masukkan ID Studio yang ingin dihapus: ");
    scanf("%d", &id);

    char line[256];
    int found = 0;

    // Salin header
    fgets(line, sizeof(line), file);
    fputs(line, tempFile);

    // Proses baris data
    while (fgets(line, sizeof(line), file))
    {
        int existingId, bioskopId, jumlahKursi;
        float additionalFee;
        sscanf(line, "%d,%d,%d,%f", &existingId, &bioskopId, &jumlahKursi, &additionalFee);

        if (existingId == id)
        {
            printf("\nApakah Anda yakin ingin menghapus data berikut?\n");
            printf("ID Studio: %d\nID Bioskop: %d\nJumlah Kursi: %d\nAdditional Fee: %.2f\n",
                   existingId, bioskopId, jumlahKursi, additionalFee);
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
        remove(STUDIO_CSV_FILE);
        rename(TEMP_STUDIO_FILE, STUDIO_CSV_FILE);
    }
    else
    {
        remove(TEMP_STUDIO_FILE);
        printf("Studio dengan ID %d tidak ditemukan.\n", id);
    }

    return found;
}

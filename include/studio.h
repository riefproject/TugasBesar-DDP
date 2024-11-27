#ifndef STUDIO_H
#define STUDIO_H

#include "bioskop.h"

#define MAX_STUDIO 100
#define STUDIO_CSV_FILE "studio.csv"

typedef struct
{
    int id;
    int bioskop_id; // Foreign key ke tabel Bioskop
    int jumlah_kursi;
    float additional_fee;
} Studio;

// Constructor
Studio createStudio(int id, int bioskop_id, int jumlah_kursi, float additional_fee);

// Getter
int getStudioId(const Studio *studio);
int getStudioBioskopId(const Studio *studio);
int getStudioJumlahKursi(const Studio *studio);
float getStudioAdditionalFee(const Studio *studio);

// Setter
void setStudioId(Studio *studio, int id);
void setStudioBioskopId(Studio *studio, int bioskop_id);
void setStudioJumlahKursi(Studio *studio, int jumlah_kursi);
void setStudioAdditionalFee(Studio *studio, float additional_fee);

// Fungsi untuk membaca data studio dari file CSV
int loadStudio(Studio studioList[], int *count);

// Fungsi untuk menyimpan data studio ke file CSV
int saveStudio(const Studio studioList[], int count);

// Fungsi untuk menampilkan daftar studio
void displayStudio(const Studio studioList[], int count, const Bioskop bioskopList[], int bioskopCount);

// Fungsi untuk mencari studio berdasarkan ID
Studio *findStudioById(const Studio studioList[], int count, int id);

// Fungsi untuk menambah studio baru
int addStudio(Studio studioList[], int *count, int bioskop_id, int jumlah_kursi, float additional_fee);

// Fungsi untuk menampilkan daftar studio dari db
void displayStudioFromFile();

#endif

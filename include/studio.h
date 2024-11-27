#ifndef STUDIO_H
#define STUDIO_H

#include "bioskop.h"

#define MAX_STUDIO 100
#define STUDIO_CSV_FILE "db/studio.csv"

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

// Fungsi untuk menambahkan studio baru
int addStudio();

// Fungsi untuk mencari studio berdasarkan ID
void findStudioById(int id);

// Fungsi untuk menampilkan daftar studio dari file
void displayStudioFromFile();

#endif

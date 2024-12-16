#ifndef STUDIO_H
#define STUDIO_H

#define MAX_STUDIO_NAME 100
#define STUDIO_SETTER_FORMAT "%d,%s,%d,%d,%d\n"
#define STUDIO_GETTER_FORMAT "%d,%[^,],%d,%d,%d\n"
#define STUDIO_DATABASE_NAME "db/studio.csv"

// ================================== type definition ================================== //

typedef struct
{
    int id;
    char nama[MAX_STUDIO_NAME];
    int bioskop_id; // Foreign key ke tabel Bioskop
    int jumlah_kursi;
    int additionalFee;
} Studio;

// ================================== setter ================================== //

void setNamaStudio(Studio *studio, const char *nama);
void setStudioBioskopId(Studio *studio, int bioskop_id);
void setJumlahKursi(Studio *studio, int jumlah_kursi);
void setHarga(Studio *studio, int additionalFee);

// ================================== getter ================================== //

const char *getNamaStudio(const Studio *studio);
int getStudioBioskopId(const Studio *studio);
int getJumlahKursi(const Studio *studio);
int getHarga(const Studio *studio);

// ================================== Main Menu ================================ //

int menuStudio();
void createStudioMenu();
void updateStudioMenu(Studio studio);

// ================================== Action ================================== //

Studio *findStudioById(int id);
int findStudioCapacityById(int studio_id);
Studio *createStudio(const char *nama, int jumlah_kursi, int additionalFee);
Studio *updateStudio(const int id, const char *nama, int jumlah_kursi, int additionalFee);
int deleteStudio(Studio studio);

// ================================== Utils ================================== //

int countStudioData();
int loadStudio(Studio **studios);
int filterStudioByBioskop(Studio **studios, int bioskop_id);
void printStudioTable(Studio *studios, int count, int page, int perPage, int selection);

#endif

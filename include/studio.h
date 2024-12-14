#ifndef STUDIO_H
#define STUDIO_H

#include "bioskop.h"

#define MAX_STUDIO 100
#define STUDIO_CSV_FILE "db/studio.csv"
#define TEMP_STUDIO_FILE "temp_studio.csv"
#define STUDIO_SETTER_FORMAT "%d,%d,%d,%f\n"
#define STUDIO_GETTER_FORMAT "%d,%d,%d,%f\n"
#define STUDIO_DATABASE_NAME "db/users.csv"

typedef struct
{
    int id;
    int bioskop_id; // Foreign key ke tabel Bioskop
    int jumlah_kursi;
    float additional_fee;
} Studio;


#endif

#ifndef FILM_H
#define FILM_H

#include "bioskop.h"

#define MAX_FILM_TITLE 100
#define MAX_GENRE 50
#define MAX_FILM 100
#define FILM_DATABASE_NAME "db/film.csv"
#define TEMP_FILM_FILE "temp/temp_film.csv"
#define FILM_SETTER_FORMAT "%d,%d,%s,%s,%s,%d,%d\n"

typedef struct
{
    int id;
    int bioskop_id; // Foreign key ke tabel Bioskop
    char kode_film[10];
    char judul[MAX_FILM_TITLE];
    char genre[MAX_GENRE];
    int durasi;   // Durasi dalam menit
    int tersedia; // Status ketersediaan (1: tersedia, 0: tidak tersedia)
} Film;

// Constructor
Film createFilm(int id, int bioskop_id, const char *kode_film, const char *judul, const char *genre, int durasi, int tersedia);

// Getter
int getFilmId(const Film *film);
int getFilmBioskopId(const Film *film);
const char *getFilmKode(const Film *film);
const char *getFilmJudul(const Film *film);
const char *getFilmGenre(const Film *film);
int getFilmDurasi(const Film *film);
int isFilmTersedia(const Film *film);
int getFilmDurasiById(int film_id);

// Setter
void setFilmId(Film *film, int id);
void setFilmBioskopId(Film *film, int bioskop_id);
void setFilmKode(Film *film, const char *kode_film);
void setFilmJudul(Film *film, const char *judul);
void setFilmGenre(Film *film, const char *genre);
void setFilmDurasi(Film *film, int durasi);
void setFilmTersedia(Film *film, int tersedia);

// Prosedur untuk menampilkan daftar film langsung dari file
void displayFilmFromFile();

// Fungsi untuk menambah film baru
int addFilm();

// Fungsi untuk update film
int updateFilm();

// Fungsi untuk delete film
int deleteFilm();

#endif
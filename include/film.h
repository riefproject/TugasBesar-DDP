#ifndef FILM_H
#define FILM_H

#include "bioskop.h"

#define MAX_FILM_TITLE 100
#define MAX_GENRE 50
#define MAX_FILM 100
#define FILM_SETTER_FORMAT "%d,%d,%s,%s,%s,%d,%d\n"
#define FILM_GETTER_FORMAT "%d,%d,%[^,],%[^,],%[^,],%d,%d\n"
#define FILM_DATABASE_NAME "db/film.csv"
typedef struct
{
    int id;
    int bioskop_id;
    char kode_film[10];
    char judul[MAX_FILM_TITLE];
    char genre[MAX_GENRE];
    int durasi;
    int tersedia;
} Film;

// ================================== Setter ================================== //

int getFilmId(const Film *film);
int getFilmBioskopId(const Film *film);
const char *getFilmKode(const Film *film);
const char *getFilmJudul(const Film *film);
const char *getFilmGenre(const Film *film);
int getFilmDurasi(const Film *film);
int isFilmTersedia(const Film *film);
int getFilmDurasiById(int film_id);

// ================================== Getter ================================== //

void setFilmId(Film *film, int id);
void setFilmBioskopId(Film *film, int bioskop_id);
void setFilmKode(Film *film, const char *kode_film);
void setFilmJudul(Film *film, const char *judul);
void setFilmGenre(Film *film, const char *genre);
void setFilmDurasi(Film *film, int durasi);
void setFilmTersedia(Film *film, int tersedia);

// ================================== Main Menu ================================ //

int menuFilm();
void createFilmMenu();
void updateFilmMenu(Film film);

// ================================== Action ================================== //

Film *findFilmByKode(const char *kode_film);
Film *createFilm(const char *kode_film, const char *judul, const char *genre, int durasi, int tersedia);
Film *updateFilm(int id, const char *kode_film, const char *judul, const char *genre, int durasi, int tersedia);
int deleteFilm(Film film);

// ================================== Utils ================================== //

int countFilmData();
int loadFilm(Film **films);
void printFilmTable(Film *films, int count, int page, int perPage, int selection);

#endif

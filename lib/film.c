#include <stdio.h>
#include <string.h>
#include "film.h"

// Constructor
Film createFilm(int id, int bioskop_id, const char *kode_film, const char *judul, const char *genre, int durasi, int tersedia)
{
    Film film;
    film.id = id;
    film.bioskop_id = bioskop_id;
    strncpy(film.kode_film, kode_film, sizeof(film.kode_film) - 1);
    film.kode_film[sizeof(film.kode_film) - 1] = '\0';
    strncpy(film.judul, judul, MAX_FILM_TITLE - 1);
    film.judul[MAX_FILM_TITLE - 1] = '\0';
    strncpy(film.genre, genre, MAX_GENRE - 1);
    film.genre[MAX_GENRE - 1] = '\0';
    film.durasi = durasi;
    film.tersedia = tersedia;
    return film;
}

// Getter
int getFilmId(const Film *film) { return film->id; }
int getFilmBioskopId(const Film *film) { return film->bioskop_id; }
const char *getFilmKode(const Film *film) { return film->kode_film; }
const char *getFilmJudul(const Film *film) { return film->judul; }
const char *getFilmGenre(const Film *film) { return film->genre; }
int getFilmDurasi(const Film *film) { return film->durasi; }
int isFilmTersedia(const Film *film) { return film->tersedia; }

// Setter
void setFilmId(Film *film, int id) { film->id = id; }
void setFilmBioskopId(Film *film, int bioskop_id) { film->bioskop_id = bioskop_id; }
void setFilmKode(Film *film, const char *kode_film)
{
    strncpy(film->kode_film, kode_film, sizeof(film->kode_film) - 1);
    film->kode_film[sizeof(film->kode_film) - 1] = '\0';
}
void setFilmJudul(Film *film, const char *judul)
{
    strncpy(film->judul, judul, MAX_FILM_TITLE - 1);
    film->judul[MAX_FILM_TITLE - 1] = '\0';
}
void setFilmGenre(Film *film, const char *genre)
{
    strncpy(film->genre, genre, MAX_GENRE - 1);
    film->genre[MAX_GENRE - 1] = '\0';
}
void setFilmDurasi(Film *film, int durasi) { film->durasi = durasi; }
void setFilmTersedia(Film *film, int tersedia) { film->tersedia = tersedia; }

// Membaca data film dari file CSV
int loadFilm(Film filmList[], int *count)
{
    FILE *file = fopen(FILM_CSV_FILE, "r");
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
        int id, bioskop_id, durasi, tersedia;
        char kode_film[10], judul[MAX_FILM_TITLE], genre[MAX_GENRE];
        sscanf(line, "%d,%d,%9[^,],%99[^,],%49[^,],%d,%d", &id, &bioskop_id, kode_film, judul, genre, &durasi, &tersedia);
        filmList[*count] = createFilm(id, bioskop_id, kode_film, judul, genre, durasi, tersedia);
        (*count)++;
    }

    fclose(file);
    return 1;
}

// Menyimpan data film ke file CSV
int saveFilm(const Film filmList[], int count)
{
    FILE *file = fopen(FILM_CSV_FILE, "w");
    if (!file)
    {
        perror("Gagal membuka file");
        return 0;
    }

    fprintf(file, "id,bioskop_id,kode_film,judul,genre,durasi,tersedia\n");
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d,%d,%s,%s,%s,%d,%d\n",
                getFilmId(&filmList[i]),
                getFilmBioskopId(&filmList[i]),
                getFilmKode(&filmList[i]),
                getFilmJudul(&filmList[i]),
                getFilmGenre(&filmList[i]),
                getFilmDurasi(&filmList[i]),
                isFilmTersedia(&filmList[i]));
    }

    fclose(file);
    return 1;
}

// Menampilkan daftar film
void displayFilm(const Film filmList[], int count, const Bioskop bioskopList[], int bioskopCount)
{
    printf("\nDaftar Film:\n");
    printf("===============================================================\n");
    printf("%-5s %-20s %-15s %-15s %-10s\n", "ID", "Judul", "Bioskop", "Genre", "Durasi");
    printf("===============================================================\n");

    for (int i = 0; i < count; i++)
    {
        const char *bioskopNama = "Tidak Ditemukan";
        for (int j = 0; j < bioskopCount; j++)
        {
            if (getBioskopId(&bioskopList[j]) == getFilmBioskopId(&filmList[i]))
            {
                bioskopNama = getBioskopNama(&bioskopList[j]);
                break;
            }
        }
        printf("%-5d %-20s %-15s %-15s %-10d\n",
               getFilmId(&filmList[i]),
               getFilmJudul(&filmList[i]),
               bioskopNama,
               getFilmGenre(&filmList[i]),
               getFilmDurasi(&filmList[i]));
    }
    printf("===============================================================\n");
}

// Prosedur untuk menampilkan daftar film langsung dari file
void displayFilmFromFile()
{
    Film filmList[MAX_FILM];
    Bioskop bioskopList[MAX_BIOSKOP];
    int filmCount = 0, bioskopCount = 0;

    // Load data bioskop
    if (!loadBioskop(bioskopList, &bioskopCount))
    {
        printf("Gagal memuat data bioskop.\n");
        return;
    }

    // Load data film
    if (!loadFilm(filmList, &filmCount))
    {
        printf("Gagal memuat data film.\n");
        return;
    }

    // Tampilkan daftar film
    displayFilm(filmList, filmCount, bioskopList, bioskopCount);
}

// Menambah film baru
int addFilm(Film filmList[], int *count, int bioskop_id, const char *kode_film, const char *judul, const char *genre, int durasi, int tersedia)
{
    if (*count >= MAX_FILM)
    {
        printf("Gagal menambah film: kapasitas penuh.\n");
        return 0;
    }
}

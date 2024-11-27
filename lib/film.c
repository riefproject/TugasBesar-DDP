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

// Prosedur untuk menampilkan daftar film langsung dari file
void displayFilmFromFile()
{
    FILE *filmFile = fopen(FILM_CSV_FILE, "r");
    FILE *bioskopFile = fopen(BIOSKOP_CSV_FILE, "r");

    if (!filmFile)
    {
        printf("File film.csv tidak ditemukan.\n");
        return;
    }
    if (!bioskopFile)
    {
        printf("File bioskop.csv tidak ditemukan.\n");
        fclose(filmFile);
        return;
    }

    char filmLine[256], bioskopLine[256];
    printf("\nDaftar Film:\n");
    printf("===============================================================\n");
    printf("%-5s %-20s %-15s %-15s %-10s\n", "ID", "Judul", "Bioskop", "Genre", "Durasi");
    printf("===============================================================\n");

    // Lewati header bioskop
    fgets(bioskopLine, sizeof(bioskopLine), bioskopFile);

    // Lewati header film
    fgets(filmLine, sizeof(filmLine), filmFile);

    // Tampilkan data film
    while (fgets(filmLine, sizeof(filmLine), filmFile))
    {
        int id, bioskop_id, durasi, tersedia;
        char kode_film[10], judul[MAX_FILM_TITLE], genre[MAX_GENRE];
        char bioskopNama[MAX_BIOSKOP_NAME] = "Tidak Ditemukan";

        sscanf(filmLine, "%d,%d,%9[^,],%99[^,],%49[^,],%d,%d",
               &id, &bioskop_id, kode_film, judul, genre, &durasi, &tersedia);

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

        printf("%-5d %-20s %-15s %-15s %-10d\n", id, judul, bioskopNama, genre, durasi);
    }

    printf("===============================================================\n");

    fclose(filmFile);
    fclose(bioskopFile);
}

void findFilmById(int id)
{
    FILE *file = fopen(FILM_CSV_FILE, "r");
    if (!file)
    {
        printf("File film.csv tidak ditemukan.\n");
        return;
    }

    char line[256];
    // Lewati header
    fgets(line, sizeof(line), file);

    // Cari film berdasarkan ID
    while (fgets(line, sizeof(line), file))
    {
        int existingId, bioskop_id, durasi, tersedia;
        char kode_film[10], judul[MAX_FILM_TITLE], genre[MAX_GENRE];

        sscanf(line, "%d,%d,%9[^,],%99[^,],%49[^,],%d,%d",
               &existingId, &bioskop_id, kode_film, judul, genre, &durasi, &tersedia);

        if (existingId == id)
        {
            printf("Film ditemukan:\n");
            printf("ID: %d\n", existingId);
            printf("Bioskop ID: %d\n", bioskop_id);
            printf("Kode Film: %s\n", kode_film);
            printf("Judul: %s\n", judul);
            printf("Genre: %s\n", genre);
            printf("Durasi: %d menit\n", durasi);
            printf("Tersedia: %s\n", tersedia ? "Ya" : "Tidak");
            fclose(file);
            return;
        }
    }

    printf("Film dengan ID %d tidak ditemukan.\n", id);
    fclose(file);
}

// Menambah film baru
int addFilm()
{
    FILE *file = fopen(FILM_CSV_FILE, "r+"); // Buka file untuk membaca dan menulis
    if (!file)
    {
        // Jika file tidak ada, buat file baru
        file = fopen(FILM_CSV_FILE, "w+");
        if (!file)
        {
            perror("Gagal membuka atau membuat file film.");
            return 0;
        }
        // Tulis header ke file baru
        fprintf(file, "id,bioskop_id,kode_film,judul,genre,durasi,tersedia\n");
    }

    char line[256];
    int id = 0, bioskop_id, durasi, tersedia;
    char kode_film[10], judul[MAX_FILM_TITLE], genre[MAX_GENRE];

    // Skip header
    fgets(line, sizeof(line), file);

    // Cari ID terakhir
    while (fgets(line, sizeof(line), file))
    {
        int existingId;
        sscanf(line, "%d,%*d,%*[^,],%*[^,],%*[^,],%*d,%*d", &existingId);
        id = existingId; // Simpan ID terakhir
    }

    // Ambil input dari admin
    printf("Masukkan ID Bioskop: ");
    scanf("%d", &bioskop_id);
    printf("Masukkan Kode Film: ");
    scanf("%s", kode_film);
    printf("Masukkan Judul Film: ");
    scanf(" %[^\n]", judul);
    printf("Masukkan Genre Film: ");
    scanf("%s", genre);
    printf("Masukkan Durasi Film (menit): ");
    scanf("%d", &durasi);
    printf("Film Tersedia? (1: Ya, 0: Tidak): ");
    scanf("%d", &tersedia);

    // Tambahkan film baru
    id++; // Increment ID terakhir
    fprintf(file, "%d,%d,%s,%s,%s,%d,%d\n", id, bioskop_id, kode_film, judul, genre, durasi, tersedia);

    fclose(file);
    printf("Film '%s' berhasil ditambahkan dengan ID %d.\n", judul, id);
    return 1;
}

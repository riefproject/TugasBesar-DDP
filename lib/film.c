#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>

#include "display.h"
#include "menu.h"
#include "security.h"
#include "film.h"
#include "db.h"

// ================================== setter ================================== //

int getFilmId(const Film *film) { return film->id; }
int getFilmBioskopId(const Film *film) { return film->bioskop_id; }
const char *getFilmKode(const Film *film) { return film->kode_film; }
const char *getFilmJudul(const Film *film) { return film->judul; }
const char *getFilmGenre(const Film *film) { return film->genre; }
int getFilmDurasi(const Film *film) { return film->durasi; }
int isFilmTersedia(const Film *film) { return film->tersedia; }
int getFilmDurasiById(int film_id)
{
    FILE *file = fopen(FILM_DATABASE_NAME, "r");
    if (!file)
    {
        perror("Gagal membuka file film.csv");
        return 0; // Gagal membaca file
    }

    char line[256];
    int id, durasi;
    char kode_film[10], judul[MAX_FILM_TITLE], genre[MAX_GENRE];

    // Lewati header
    fgets(line, sizeof(line), file);

    // Baca setiap baris dan cari berdasarkan ID film
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%d,%*d,%9[^,],%99[^,],%49[^,],%d,%*d",
               &id, kode_film, judul, genre, &durasi);

        if (id == film_id)
        {
            fclose(file);
            return durasi; // Kembalikan durasi jika ID cocok
        }
    }

    fclose(file);
    return 0; // Film dengan ID tersebut tidak ditemukan
}

// ==================================== getter ==================================== //

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

// ==================================== Main Menu =================================//

int menuFilm()
{
    Film *films;
    int count = loadFilm(&films);

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        system("cls");
        selection = (page - 1) * perPage + pointer;

        printFilmTable(films, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page");
        printf(GREEN "\n[C]: Create" RESET " | " YELLOW "[U]: Update" RESET " | " RED "[D]: Delete" RESET " | " BG_RED WHITE "[E] Exit\n" RESET);

        command = getch();

        if (command == 224)
        {
            command = getch();

            if (command == 77)
            {
                pointer = 1;
                if (page * perPage < count)
                    page++;
                else
                {
                    printf("Sudah di halaman terakhir.\n");
                    sleep(500);
                }
            }
            else if (command == 75)
            {
                pointer = 1;
                if (page > 1)
                    page--;
                else
                {
                    printf("Sudah di halaman pertama.\n");
                    sleep(500);
                }
            }
            else if (command == 72)
            {
                if (pointer > 1)
                {
                    pointer--;
                }
            }
            else if (command == 80)
            {
                if (pointer < perPage && (page - 1) * perPage + pointer < count)
                {
                    pointer++;
                }
            }
        }
        else if (command == 32)
        {
            printf("Film terpilih %d", selection);
            free(films);
            return 0;
        }
        else if (command == 'C' || command == 'c')
        {
            createFilmMenu();

            free(films);
            count = loadFilm(&films);
            pointer = 1;
        }
        else if (command == 'U' || command == 'u')
        {
            updateFilmMenu(films[selection - 1]);

            free(films);
            count = loadFilm(&films);
            pointer = 1;
        }
        else if (command == 'D' || command == 'd')
        {
            deleteFilm(films[selection - 1]);

            free(films);
            count = loadFilm(&films);
            pointer = 1;
        }
        else if (command == 'E' || command == 'e')
        {
            free(films);
            return 0;
        }
        else
        {
            printf(YELLOW BOLD "Perintah tidak ditemukan\n" RESET);
            sleep(500);
        }
    }
}

void createFilmMenu()
{
    system("cls");

    printf(GREEN "====================================================\n");
    printf("                Menu Tambah Film                    \n");
    printf("====================================================\n" RESET);

    char kode_film[10], judul[MAX_FILM_TITLE], genre[MAX_GENRE];
    int durasi, tersedia;

    while (1)
    {
        printf("Masukkan kode film\t: ");
        fgets(kode_film, sizeof(kode_film), stdin);
        kode_film[strcspn(kode_film, "\n")] = 0;

        Film *find = findFilmByKode(kode_film);

        if (find != NULL)
        {
            printf(RED BOLD "Kode film sudah terdaftar. Silakan pilih kode lain.\n" RESET);
            sleep(1);
            continue;
        }

        if (strcmp(kode_film, "") == 0)
        {
            printf(RED BOLD "Kode film tidak boleh kosong.\n" RESET);
            sleep(1);
            continue;
        }

        break;
    }

    printf("Masukkan judul film\t: ");
    fgets(judul, sizeof(judul), stdin);
    judul[strcspn(judul, "\n")] = 0;

    printf("Masukkan genre film\t: ");
    fgets(genre, sizeof(genre), stdin);
    genre[strcspn(genre, "\n")] = 0;

    printf("Masukkan durasi film (menit)\t: ");
    scanf("%d", &durasi);

    printf("Masukkan status aktif (1 untuk tersedia, 0 untuk tidak)\t: ");
    scanf("%d", &tersedia);

    Film *newFilm = createFilm(kode_film, judul, genre, durasi, tersedia);
    if (!newFilm)
    {
        printf(RED BOLD "Gagal menambah film. Harap coba lagi!\n" RESET);
        return;
    }

    printf(GREEN BOLD "Berhasil menambah film!\n" RESET);
    sleep(2);
    free(newFilm);
}

void updateFilmMenu(Film film)
{
    printf(YELLOW "====================================================\n");
    printf("                 Menu Edit Film                     \n");
    printf("====================================================\n" RESET);

    char kode_film[10], judul[MAX_FILM_TITLE], genre[MAX_GENRE];
    int durasi, tersedia;

    while (1)
    {
        printf("Masukkan kode film\t: ");
        fgets(kode_film, sizeof(kode_film), stdin);
        kode_film[strcspn(kode_film, "\n")] = 0;

        Film *find = findFilmByKode(kode_film);

        if (find != NULL && film.id != find->id)
        {
            printf(RED BOLD "Kode film sudah terdaftar. Silakan pilih kode lain.\n" RESET);
            sleep(1);
            continue;
        }

        if (strcmp(kode_film, "") == 0)
        {
            printf(RED BOLD "Kode film tidak boleh kosong.\n" RESET);
            sleep(1);
            continue;
        }

        break;
    }

    printf("Masukkan judul film\t: ");
    fgets(judul, sizeof(judul), stdin);
    judul[strcspn(judul, "\n")] = 0;

    printf("Masukkan genre film\t: ");
    fgets(genre, sizeof(genre), stdin);
    genre[strcspn(genre, "\n")] = 0;

    printf("Masukkan durasi film (menit)\t: ");
    scanf("%d", &durasi);

    printf("Masukkan status ketersediaan (1 untuk tersedia, 0 untuk tidak)\t: ");
    scanf("%d", &tersedia);

    Film *updatedFilm = updateFilm(film.id, kode_film, judul, genre, durasi, tersedia);
    if (!updatedFilm)
    {
        printf(RED BOLD "Gagal mengubah film. Harap coba lagi!\n" RESET);
        return;
    }

    printf(GREEN BOLD "Berhasil mengubah film!\n" RESET);
    sleep(2);
    free(updatedFilm);
}

// ==================================== Action ====================================//

Film *findFilmByKode(const char *kode_film)
{
    FILE *file = fopen(FILM_DATABASE_NAME, "r");
    if (!file)
    {
        return NULL;
    }

    Film *film = malloc(sizeof(Film));
    while (fscanf(file, FILM_GETTER_FORMAT,
                  &film->id,
                  film->kode_film,
                  film->judul,
                  film->genre,
                  &film->durasi,
                  &film->tersedia,
                  &film->bioskop_id) != EOF)
    {
        if (film->kode_film == kode_film)
        {
            fclose(file);
            return film;
        }
    }

    fclose(file);
    free(film);
    return NULL;
}

Film *createFilm(const char *kode_film, const char *judul, const char *genre, int durasi, int tersedia)
{
    Film *film = malloc(sizeof(Film));
    if (!film)
    {
        printf("Alokasi memori gagal, location: createFilm\n");
        sleep(2);
        return NULL;
    }

    User *user = getCurrentUser();
    Bioskop *bioskop = findBioskopByManagerId(user->id);
    if (bioskop == NULL)
    {
        printf(YELLOW BOLD "Bioskop Tidak di temukan wait until redirect..., Message location: createFilm" RESET);
        sleep(2);
        return NULL;
    }

    int bioskop_id = bioskop->id;

    // Set film properties using setters
    setFilmKode(film, kode_film);
    setFilmJudul(film, judul);
    setFilmGenre(film, genre);
    setFilmDurasi(film, durasi);
    setFilmTersedia(film, tersedia);
    setFilmBioskopId(film, bioskop_id);

    FILE *file = fopen(FILM_DATABASE_NAME, "a");
    if (!file)
    {
        printf(YELLOW BOLD "File tidak dapat dibuka, Message location: createFilm" RESET);
        free(film);
        return NULL;
    }

    int id = getLastAvailableID(FILM_DATABASE_NAME);
    setFilmId(film, id);

    fprintf(file, FILM_SETTER_FORMAT,
            film->id,
            film->bioskop_id,
            film->kode_film,
            film->judul,
            film->genre,
            film->durasi,
            film->tersedia);

    fclose(file);
    return film;
}

Film *updateFilm(int id, const char *kode_film, const char *judul, const char *genre, int durasi, int tersedia)
{
    Film *updatedFilm = malloc(sizeof(Film));
    if (!updatedFilm)
    {
        printf("Alokasi memori gagal, location: updateFilm\n");
        return NULL;
    }

    setFilmId(updatedFilm, id);
    setFilmKode(updatedFilm, kode_film);
    setFilmJudul(updatedFilm, judul);
    setFilmGenre(updatedFilm, genre);
    setFilmDurasi(updatedFilm, durasi);
    setFilmTersedia(updatedFilm, tersedia);

    FILE *fromFile = fopen(FILM_DATABASE_NAME, "r");
    if (!fromFile)
    {
        free(updatedFilm);
        return NULL;
    }

    int count = countFilmData();
    if (count == -1)
    {
        printf("Penghitungan data film gagal, location: updateFilm\n");
        fclose(fromFile);
        return NULL;
    }

    int i = 0;
    Film films[count];
    while (fscanf(fromFile, FILM_GETTER_FORMAT,
                  &films[i].id,
                  films[i].kode_film,
                  films[i].judul,
                  films[i].genre,
                  &films[i].durasi,
                  &films[i].tersedia,
                  &films[i].bioskop_id) != EOF)
    {
        if (films[i].id == id)
        {
            setFilmBioskopId(updatedFilm, films[i].bioskop_id);

            films[i] = *updatedFilm;
        }
        i++;
    }
    fclose(fromFile);

    FILE *toFile = fopen(FILM_DATABASE_NAME, "w");
    i = 0;
    while (i < count)
    {
        fprintf(toFile, FILM_SETTER_FORMAT,
                films[i].id,
                films[i].bioskop_id,
                films[i].kode_film,
                films[i].judul,
                films[i].genre,
                films[i].durasi,
                films[i].tersedia);
        i++;
    }

    fclose(toFile);
    return updatedFilm;
}

int deleteFilm(Film film)
{
    // Buat pesan konfirmasi
    int len = snprintf(NULL, 0, "Apakah Anda yakin ingin menghapus film dengan kode '%s'?\n", getFilmKode(&film)) + 1;
    char *head = malloc(len);
    if (!head)
    {
        printf("Gagal mengalokasikan memori.\n");
        return -1;
    }
    snprintf(head, len, "Apakah Anda yakin ingin menghapus film dengan kode '%s'?\n", getFilmKode(&film));

    char *menu[] = {
        "Tidak, Batalkan",
        "Ya, Hapus",
    };

    char *header[] = {
        RED BOLD "====================================================\n",
        "             Konfirmasi Hapus Film                  \n",
        "====================================================\n\n" RESET,
        head,
        NULL};

    int selection = showMenu(menu, 2, header);
    free(head);

    if (selection == 1)
    {
        return 1;
    }

    // Cadangkan data
    FILE *fromFile = fopen(FILM_DATABASE_NAME, "r");
    if (!fromFile)
    {
        printf(RED "Gagal membuka file, lokasi: deleteFilm.\n" RESET);
        return -1;
    }

    int count = countFilmData();
    if (count == -1)
    {
        printf(RED "Penghitungan data film gagal, lokasi: deleteFilm.\n" RESET);
        fclose(fromFile);
        return -1;
    }

    Film films[count], temp;
    int i = 0;
    while (fscanf(fromFile, FILM_GETTER_FORMAT,
                  &temp.id,
                  temp.kode_film,
                  temp.judul,
                  temp.genre,
                  &temp.durasi,
                  &temp.tersedia,
                  &temp.bioskop_id) != EOF)
    {
        if (temp.id != getFilmId(&film))
        {
            films[i] = temp;
            i++;
        }
    }
    fclose(fromFile);

    // Menulis ulang file dengan data film yang diperbarui
    FILE *toFile = fopen(FILM_DATABASE_NAME, "w");
    if (!toFile)
    {
        printf(RED "Gagal membuka file untuk ditulis, lokasi: deleteFilm.\n" RESET);
        return -1;
    }

    i = 0;
    while (i < count - 1)
    {
        fprintf(toFile, FILM_SETTER_FORMAT,
                getFilmId(&films[i]),
                getFilmKode(&films[i]),
                getFilmJudul(&films[i]),
                getFilmGenre(&films[i]),
                getFilmDurasi(&films[i]),
                isFilmTersedia(&films[i]),
                getFilmBioskopId(&films[i]));
        i++;
    }

    fclose(toFile);

    return 1;
}

// ==================================== Utils ====================================//

int countFilmData()
{
    FILE *file = fopen(FILM_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int count = 0;
    Film film;

    while (fscanf(file, FILM_GETTER_FORMAT,
                  &film.id,
                  &film.bioskop_id,
                  film.kode_film,
                  film.judul,
                  film.genre,
                  &film.durasi,
                  &film.tersedia) != EOF)
    {
        count++;
    }
    fclose(file);
    return count;
}

int loadFilm(Film **films)
{
    FILE *file = fopen(FILM_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int count = countFilmData();

    *films = (Film *)malloc(count * sizeof(Film));
    if (*films == NULL)
    {
        printf("Gagal mengalokasi memori.\n");
        fclose(file);
        return -1;
    }

    rewind(file);
    int i = 0;

    while (fscanf(file, FILM_GETTER_FORMAT,
                  &(*films)[i].id,
                  &(*films)[i].bioskop_id,
                  (*films)[i].kode_film,
                  (*films)[i].judul,
                  (*films)[i].genre,
                  &(*films)[i].durasi,
                  &(*films)[i].tersedia) != EOF)
    {
        i++;
    }

    fclose(file);
    return count;
}

void printFilmTable(Film *films, int count, int page, int perPage, int selection)
{
    printf(GREEN "====================================================\n");
    printf("              Menu Management Film                  \n");
    printf("====================================================\n" RESET);

    int idWidth = 2, kodeWidth = 9, judulWidth = 4;
    int genreWidth = 5, durasiWidth = 14, tersediaWidth = 8;

    int start = (page - 1) * perPage;
    int end = start + perPage;
    if (end > count)
        end = count;

    // Hitung panjang kolom terpanjang
    for (int i = start; i < end; i++)
    {
        int idLen = snprintf(NULL, 0, "%d", films[i].id);
        if (idLen > idWidth)
            idWidth = idLen;
        if ((int)strlen(films[i].kode_film) > kodeWidth)
            kodeWidth = strlen(films[i].kode_film);
        if ((int)strlen(films[i].judul) > judulWidth)
            judulWidth = strlen(films[i].judul);
        if ((int)strlen(films[i].genre) > genreWidth)
            genreWidth = strlen(films[i].genre);
    }

    int tableWidth = snprintf(NULL, 0,
                              "[ * ]| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
                              idWidth, "ID",
                              kodeWidth, "Kode Film",
                              judulWidth, "Judul",
                              genreWidth, "Genre",
                              durasiWidth, "Durasi (menit)",
                              tersediaWidth, "Tersedia");

    // Cetak garis atas tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak header tabel
    printf("[ * ]| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           idWidth, "ID",
           kodeWidth, "Kode Film",
           judulWidth, "Judul",
           genreWidth, "Genre",
           durasiWidth, "Durasi (menit)",
           tersediaWidth, "Tersedia");

    // Cetak garis bawah header
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak isi tabel
    for (int i = start; i < end; i++)
    {
        // Tampilkan dengan penanda jika dipilih
        if (selection == i + 1)
        {
            printf(BLUE BOLD "[ * ]| %-*d | %-*s | %-*s | %-*s | %-*d | %-*d |\n" RESET,
                   idWidth, films[i].id,
                   kodeWidth, films[i].kode_film,
                   judulWidth, films[i].judul,
                   genreWidth, films[i].genre,
                   durasiWidth, films[i].durasi,
                   tersediaWidth, films[i].tersedia);
        }
        else
        {
            printf("[   ]| %-*d | %-*s | %-*s | %-*s | %-*d | %-*d |\n",
                   idWidth, films[i].id,
                   kodeWidth, films[i].kode_film,
                   judulWidth, films[i].judul,
                   genreWidth, films[i].genre,
                   durasiWidth, films[i].durasi,
                   tersediaWidth, films[i].tersedia);
        }
    }

    // Cetak garis bawah tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Informasi halaman
    printf("Page %d of %d\n", page, (count + perPage - 1) / perPage);
}

#ifndef JADWAL_H
#define JADWAL_H

#include <time.h> // Library untuk struct tm dan fungsi terkait

#define MAX_TIME_LENGTH 20
#define JADWAL_SETTER_FORMAT "%d,%d,%d,%d:%d,%d:%d,%d-%d-%d,%d\n"
#define JADWAL_GETTER_FORMAT "%d,%d,%d,%02d:%02d,%02d:%02d,%d-%02d-%02d,%d\n"
#define JADWAL_DATABASE_NAME "db/jadwal.csv"

// Alias untuk struct tm (tm:= struct waktu bawaan time.h)
typedef struct tm Waktu;

// Struktur Data Jadwal
typedef struct
{
    int id;
    int studio_id;
    int film_id;
    Waktu waktu_awal_tayang;
    Waktu waktu_akhir_tayang;
    Waktu tersedia_sampai;
    int harga_tiket;
} Jadwal;

// ================================ Main Menu ================================= //

int menuJadwal();
int selectStudioJadwal();
int selectFilmJadwal();
void createJadwalMenu();
void updateJadwalMenu(Jadwal jadwal);

// ================================= Action =================================== //

int isValidTime(int hour, int minute);
int isValidDate(int year, int month, int day);
Jadwal *cekKonflikJadwalStudio(int studio_id);
void *createJadwal(int studio_id, int film_id, Waktu waktu_awal_tayang, Waktu waktu_akhir_tayang, Waktu tersedia_sampai, int harga_tiket);
void *updateJadwal(int id, int studio_id, int film_id, Waktu waktu_awal_tayang, Waktu waktu_akhir_tayang, Waktu tersedia_sampai, int harga_tiket);
int deleteJadwal(Jadwal jadwal);

// ================================== Utils ================================== //

int countJadwalData();
int loadJadwal(Jadwal **jadwals);
void printJadwalTable(Jadwal *jadwal, int count, int page, int perPage, int selection);

#endif

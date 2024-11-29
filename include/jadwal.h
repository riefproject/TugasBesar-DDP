#ifndef JADWAL_H
#define JADWAL_H

#include <time.h> // Library untuk struct tm dan fungsi terkait

#define JADWAL_CSV_FILE "db/jadwal.csv"    // Lokasi file jadwal
#define TEMP_JADWAL_FILE "temp_jadwal.csv" // Lokasi file temporary
#define MAX_TIME_LENGTH 20                 // Panjang string waktu (YYYY-MM-DD HH:MM)
#define JEDA_STANDAR 30                    // Jeda antar film (menit)

// Alias untuk struct tm (tm:= struct waktu bawaan time.h)
typedef struct tm Waktu;

// Struktur Data Jadwal
typedef struct
{
    int id;             // ID Jadwal
    int studio_id;      // ID Studio
    int film_id;        // ID Film
    Waktu waktu_tayang; // Waktu Tayang
    int status;         // Status Jadwal (dinamis: 0=Belum Dimulai, 1=Berlangsung, 2=Selesai)
} Jadwal;

// Constructor
Jadwal createJadwal(int id, int studio_id, int film_id, Waktu waktu_tayang);

// Getter
int getJadwalId(const Jadwal *jadwal);
int getJadwalStudioId(const Jadwal *jadwal);
int getJadwalFilmId(const Jadwal *jadwal);
Waktu getJadwalWaktuTayang(const Jadwal *jadwal);
int getJadwalStatus(const Jadwal *jadwal);

// Setter
void setJadwalId(Jadwal *jadwal, int id);
void setJadwalStudioId(Jadwal *jadwal, int studio_id);
void setJadwalFilmId(Jadwal *jadwal, int film_id);
void setJadwalWaktuTayang(Jadwal *jadwal, Waktu waktu_tayang);
void setJadwalStatus(Jadwal *jadwal, int status);

// Fungsi CRUD
int addJadwal();      // Menambahkan jadwal baru
void displayJadwal(); // Menampilkan semua jadwal
int updateJadwal();   // Memperbarui jadwal
int deleteJadwal();   // Menghapus atau menonaktifkan jadwal

// Validasi Konflik Waktu
int validateTime(const char *timeStr, Waktu *waktu);
int isTimeConflict(int studio_id, const Waktu *waktu_baru, int durasi_baru, int jeda);

// Filtering Jadwal
void displayJadwalByFilm(int film_id);     // Filter berdasarkan ID Film
void displayJadwalByStudio(int studio_id); // Filter berdasarkan ID Studio

// Fitur Tambahan
int tambahJeda(int jeda);                                  // Menambahkan jeda ke jadwal hari ini
int getStatusJadwal(const Jadwal *jadwal, int durasiFilm); // Hitung status dinamis

#endif

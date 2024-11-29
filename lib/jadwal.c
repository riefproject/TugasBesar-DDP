#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jadwal.h"
#include "film.h"

// Custom strptime untuk kompatibilitas Windows
char *strptime(const char *s, const char *format, struct tm *tm)
{
    memset(tm, 0, sizeof(*tm));
    if (sscanf(s, "%d-%d-%d %d:%d",
               &tm->tm_year, &tm->tm_mon, &tm->tm_mday,
               &tm->tm_hour, &tm->tm_min) != 5)
    {
        return NULL;
    }
    tm->tm_year -= 1900;
    tm->tm_mon -= 1;
    return (char *)(s + strlen(s));
}

// Constructor
Jadwal createJadwal(int id, int studio_id, int film_id, Waktu waktu_tayang)
{
    Jadwal jadwal;
    jadwal.id = id;
    jadwal.studio_id = studio_id;
    jadwal.film_id = film_id;
    jadwal.waktu_tayang = waktu_tayang;
    jadwal.status = 0; // Default: Belum dimulai
    return jadwal;
}

// Getter
int getJadwalId(const Jadwal *jadwal) { return jadwal->id; }
int getJadwalStudioId(const Jadwal *jadwal) { return jadwal->studio_id; }
int getJadwalFilmId(const Jadwal *jadwal) { return jadwal->film_id; }
Waktu getJadwalWaktuTayang(const Jadwal *jadwal) { return jadwal->waktu_tayang; }
int getJadwalStatus(const Jadwal *jadwal) { return jadwal->status; }

// Setter
void setJadwalId(Jadwal *jadwal, int id) { jadwal->id = id; }
void setJadwalStudioId(Jadwal *jadwal, int studio_id) { jadwal->studio_id = studio_id; }
void setJadwalFilmId(Jadwal *jadwal, int film_id) { jadwal->film_id = film_id; }
void setJadwalWaktuTayang(Jadwal *jadwal, Waktu waktu_tayang) { jadwal->waktu_tayang = waktu_tayang; }
void setJadwalStatus(Jadwal *jadwal, int status) { jadwal->status = status; }

// Validasi waktu
int validateTime(const char *timeStr, Waktu *waktu)
{
    if (strptime(timeStr, "%Y-%m-%d %H:%M", waktu) == NULL)
    {
        return 0;
    }
    return 1;
}

// Menambahkan jadwal baru
int addJadwal()
{
    FILE *file = fopen(JADWAL_CSV_FILE, "a");
    if (!file)
    {
        perror("Gagal membuka file jadwal.csv");
        return 0;
    }

    Jadwal jadwal;
    char waktu_input[MAX_TIME_LENGTH];
    Waktu waktu_baru;
    int durasi_baru;

    printf("Masukkan ID Studio: ");
    scanf("%d", &jadwal.studio_id);
    printf("Masukkan ID Film: ");
    scanf("%d", &jadwal.film_id);
    printf("Masukkan Waktu Tayang (YYYY-MM-DD HH:MM): ");
    scanf(" %[^\n]", waktu_input);

    if (!validateTime(waktu_input, &waktu_baru))
    {
        printf("Waktu tidak valid.\n");
        fclose(file);
        return 0;
    }

    durasi_baru = getFilmDurasiById(jadwal.film_id); // Ambil durasi dari film
    if (durasi_baru <= 0)
    {
        printf("Film tidak ditemukan atau durasi tidak valid.\n");
        fclose(file);
        return 0;
    }

    if (isTimeConflict(jadwal.studio_id, &waktu_baru, durasi_baru, JEDA_STANDAR))
    {
        printf("Gagal menambahkan jadwal. Konflik waktu.\n");
        fclose(file);
        return 0;
    }

    jadwal.waktu_tayang = waktu_baru;
    jadwal.id = time(NULL) % 1000000; // ID unik
    jadwal.status = getStatusJadwal(&jadwal, durasi_baru);

    fprintf(file, "%d,%d,%d,%d-%02d-%02d %02d:%02d,%d\n",
            jadwal.id, jadwal.studio_id, jadwal.film_id,
            jadwal.waktu_tayang.tm_year + 1900,
            jadwal.waktu_tayang.tm_mon + 1,
            jadwal.waktu_tayang.tm_mday,
            jadwal.waktu_tayang.tm_hour,
            jadwal.waktu_tayang.tm_min,
            jadwal.status);

    fclose(file);
    printf("Jadwal berhasil ditambahkan.\n");
    return 1;
}

// Menampilkan semua jadwal
void displayJadwal()
{
    FILE *file = fopen(JADWAL_CSV_FILE, "r");
    if (!file)
    {
        perror("Gagal membuka file jadwal.csv");
        return;
    }

    char line[256];
    printf("===========================================================\n");
    printf("%-5s %-10s %-10s %-20s %-15s\n", "ID", "Studio", "Film", "Waktu", "Status");
    printf("===========================================================\n");

    while (fgets(line, sizeof(line), file))
    {
        Jadwal jadwal;
        char waktu_str[MAX_TIME_LENGTH];

        sscanf(line, "%d,%d,%d,%19[^,],%d",
               &jadwal.id, &jadwal.studio_id, &jadwal.film_id, waktu_str, &jadwal.status);

        strptime(waktu_str, "%Y-%m-%d %H:%M", &jadwal.waktu_tayang);
        int durasiFilm = getFilmDurasiById(jadwal.film_id);
        jadwal.status = getStatusJadwal(&jadwal, durasiFilm);

        char waktu_formatted[MAX_TIME_LENGTH];
        strftime(waktu_formatted, sizeof(waktu_formatted), "%Y-%m-%d %H:%M", &jadwal.waktu_tayang);

        const char *statusDesc = (jadwal.status == 0) ? "Belum Dimulai" : (jadwal.status == 1) ? "Sedang Berlangsung"
                                                                                               : "Selesai";

        printf("%-5d %-10d %-10d %-20s %-15s\n",
               jadwal.id, jadwal.studio_id, jadwal.film_id, waktu_formatted, statusDesc);
    }

    fclose(file);
}

// Validasi konflik waktu
int isTimeConflict(int studio_id, const Waktu *waktu_baru, int durasi_baru, int jeda)
{
    FILE *file = fopen(JADWAL_CSV_FILE, "r");
    if (!file)
    {
        perror("Gagal membuka file jadwal.csv");
        return 1; // Anggap ada konflik
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        Jadwal jadwal;
        char waktu_str[MAX_TIME_LENGTH];

        sscanf(line, "%*d,%d,%*d,%19[^,],%*d", &jadwal.studio_id, waktu_str);

        if (jadwal.studio_id != studio_id)
            continue;

        strptime(waktu_str, "%Y-%m-%d %H:%M", &jadwal.waktu_tayang);
        time_t start_baru = mktime((struct tm *)waktu_baru);
        time_t start_lama = mktime(&jadwal.waktu_tayang);
        time_t end_lama = start_lama + (durasi_baru * 60) + (jeda * 60);

        if (difftime(start_baru, end_lama) < 0 && difftime(start_baru, start_lama) >= 0)
        {
            fclose(file);
            return 1; // Konflik
        }
    }

    fclose(file);
    return 0; // Tidak ada konflik
}

// Menghitung status jadwal dinamis
int getStatusJadwal(const Jadwal *jadwal, int durasiFilm)
{
    time_t now = time(NULL); // Waktu saat ini
    time_t waktuTayang = mktime((struct tm *)&jadwal->waktu_tayang);
    time_t waktuSelesai = waktuTayang + (durasiFilm * 60);

    if (difftime(now, waktuTayang) < 0)
        return 0; // Belum dimulai
    else if (difftime(now, waktuSelesai) < 0)
        return 1; // Sedang berlangsung
    else
        return 2; // Selesai
}

void displayJadwalByFilm(int film_id)
{
    FILE *file = fopen(JADWAL_CSV_FILE, "r");
    if (!file)
    {
        perror("Gagal membuka file jadwal.csv");
        return;
    }

    char line[256];
    printf("Jadwal untuk Film ID %d:\n", film_id);
    printf("===========================================================\n");
    printf("%-5s %-10s %-20s %-15s\n", "ID", "Studio", "Waktu", "Status");
    printf("===========================================================\n");

    while (fgets(line, sizeof(line), file))
    {
        Jadwal jadwal;
        char waktu_str[MAX_TIME_LENGTH];
        int durasiFilm;

        sscanf(line, "%d,%d,%d,%19[^,],%d",
               &jadwal.id, &jadwal.studio_id, &jadwal.film_id, waktu_str, &jadwal.status);

        // Lewati jika bukan film yang dimaksud
        if (jadwal.film_id != film_id)
            continue;

        // Konversi waktu dan validasi status
        strptime(waktu_str, "%Y-%m-%d %H:%M", &jadwal.waktu_tayang);
        durasiFilm = getFilmDurasiById(jadwal.film_id);
        jadwal.status = getStatusJadwal(&jadwal, durasiFilm);

        const char *statusDesc = (jadwal.status == 0) ? "Belum Dimulai" : (jadwal.status == 1) ? "Sedang Berlangsung"
                                                                                               : "Selesai";

        printf("%-5d %-10d %-20s %-15s\n",
               jadwal.id, jadwal.studio_id, waktu_str, statusDesc);
    }

    fclose(file);
}

void displayJadwalByStudio(int studio_id)
{
    FILE *file = fopen(JADWAL_CSV_FILE, "r");
    if (!file)
    {
        perror("Gagal membuka file jadwal.csv");
        return;
    }

    char line[256];
    printf("Jadwal untuk Studio ID %d:\n", studio_id);
    printf("===========================================================\n");
    printf("%-5s %-10s %-20s %-15s\n", "ID", "Film", "Waktu", "Status");
    printf("===========================================================\n");

    while (fgets(line, sizeof(line), file))
    {
        Jadwal jadwal;
        char waktu_str[MAX_TIME_LENGTH];
        int durasiFilm;

        sscanf(line, "%d,%d,%d,%19[^,],%d",
               &jadwal.id, &jadwal.studio_id, &jadwal.film_id, waktu_str, &jadwal.status);

        // Lewati jika bukan studio yang dimaksud
        if (jadwal.studio_id != studio_id)
            continue;

        // Konversi waktu dan validasi status
        strptime(waktu_str, "%Y-%m-%d %H:%M", &jadwal.waktu_tayang);
        durasiFilm = getFilmDurasiById(jadwal.film_id);
        jadwal.status = getStatusJadwal(&jadwal, durasiFilm);

        const char *statusDesc = (jadwal.status == 0) ? "Belum Dimulai" : (jadwal.status == 1) ? "Sedang Berlangsung"
                                                                                               : "Selesai";

        printf("%-5d %-10d %-20s %-15s\n",
               jadwal.id, jadwal.film_id, waktu_str, statusDesc);
    }

    fclose(file);
}

int tambahJeda(int jeda)
{
    FILE *file = fopen(JADWAL_CSV_FILE, "r");
    if (!file)
    {
        perror("Gagal membuka file jadwal.csv");
        return 0;
    }

    FILE *tempFile = fopen(TEMP_JADWAL_FILE, "w");
    if (!tempFile)
    {
        perror("Gagal membuat file sementara.");
        fclose(file);
        return 0;
    }

    char line[256];
    time_t now = time(NULL);
    struct tm waktuSekarang = *localtime(&now);

    // Salin header
    fgets(line, sizeof(line), file);
    fputs(line, tempFile);

    // Proses setiap jadwal
    while (fgets(line, sizeof(line), file))
    {
        Jadwal jadwal;
        char waktu_str[MAX_TIME_LENGTH];

        sscanf(line, "%d,%d,%d,%19[^,],%d",
               &jadwal.id, &jadwal.studio_id, &jadwal.film_id, waktu_str, &jadwal.status);

        // Konversi string waktu ke struct tm
        strptime(waktu_str, "%Y-%m-%d %H:%M", &jadwal.waktu_tayang);

        // Tambah jeda jika jadwal pada hari ini dan >= waktu sekarang
        if (jadwal.waktu_tayang.tm_year == waktuSekarang.tm_year &&
            jadwal.waktu_tayang.tm_yday == waktuSekarang.tm_yday &&
            difftime(mktime(&jadwal.waktu_tayang), now) >= 0)
        {
            jadwal.waktu_tayang.tm_min += jeda;
            mktime(&jadwal.waktu_tayang); // Normalisasi waktu
        }

        fprintf(tempFile, "%d,%d,%d,%d-%02d-%02d %02d:%02d,%d\n",
                jadwal.id, jadwal.studio_id, jadwal.film_id,
                jadwal.waktu_tayang.tm_year + 1900,
                jadwal.waktu_tayang.tm_mon + 1,
                jadwal.waktu_tayang.tm_mday,
                jadwal.waktu_tayang.tm_hour,
                jadwal.waktu_tayang.tm_min,
                jadwal.status);
    }

    fclose(file);
    fclose(tempFile);

    // Ganti file asli dengan file sementara
    remove(JADWAL_CSV_FILE);
    rename(TEMP_JADWAL_FILE, JADWAL_CSV_FILE);

    printf("Jeda %d menit berhasil ditambahkan pada jadwal hari ini.\n", jeda);
    return 1;
}
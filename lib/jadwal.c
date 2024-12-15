#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>

#include "display.h"
#include "jadwal.h"
#include "film.h"
#include "studio.h"
#include "db.h"

// ================================== Getter ================================== //

// ================================== Setter ================================== //

// ================================ Main Menu ================================= //

int menuJadwal()
{
    Jadwal *jadwals;
    int count = loadJadwal(&jadwals);

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        system("cls");
        selection = (page - 1) * perPage + pointer;

        printf(GREEN "====================================================\n");
        printf("             Menu Management Jadwal                 \n");
        printf("====================================================\n" RESET);

        printJadwalTable(jadwals, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page");
        printf(GREEN "\n[C]: Create" RESET " | " YELLOW "[U]: Update" RESET " | " RED "[D]: Delete" RESET " | " BG_RED WHITE "[E] Exit" RESET "\n" RESET);

        command = getch();

        if (command == 224)
        {
            command = getch();

            if (command == 77) // Arrow Right -> Next Page
            {
                pointer = 1;
                if (page * perPage < count)
                    page++;
                else
                {
                    printf(BLUE "Sudah di halaman terakhir.\n");
                    sleep(1);
                }
            }
            else if (command == 75) // Arrow Left -> Previous Page
            {
                pointer = 1;
                if (page > 1)
                    page--;
                else
                {
                    printf(BLUE "Sudah di halaman pertama.\n");
                    sleep(1);
                }
            }
            else if (command == 72) // Arrow Up -> Move up in list
            {
                if (pointer > 1)
                {
                    pointer--;
                }
            }
            else if (command == 80) // Arrow Down -> Move down in list
            {
                if (pointer < perPage && (page - 1) * perPage + pointer < count)
                {
                    pointer++;
                }
            }
        }
        else if (command == 32) // Space Bar -> Select item
        {
            printf("Jadwal terpilih ID: %d\n", jadwals[selection - 1].id);
            free(jadwals);
            return 0;
        }
        else if (command == 'C' || command == 'c') // Create new Jadwal
        {
            createJadwalMenu();

            free(jadwals);
            count = loadJadwal(&jadwals);
            pointer = 1;
        }
        else if (command == 'U' || command == 'u') // Update selected Jadwal
        {
            updateJadwalMenu(jadwals[selection - 1]);

            free(jadwals);
            count = loadJadwal(&jadwals);
            pointer = 1;
        }
        else if (command == 'D' || command == 'd') // Delete selected Jadwal
        {
            deleteJadwal(jadwals[selection - 1]);

            free(jadwals);
            count = loadJadwal(&jadwals);
            pointer = 1;
        }
        else if (command == 'E' || command == 'e') // Exit
        {
            free(jadwals);
            return 0;
        }
        else
        {
            printf(YELLOW BOLD "Perintah tidak ditemukan\n" RESET);
            sleep(1);
        }
    }
}

int selectStudioJadwal()
{
    Studio *studioList;
    int count = loadStudio(&studioList);

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        selection = (page - 1) * perPage + pointer;

        printStudioTable(studioList, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page\n");
        printf("[Arrow /\\] | [Arrow \\/] Arrow Up/Down To Selecting\n");
        printf(GREEN "[ENTER]: Enter To Select Studio\n\n" RESET);

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
                    sleep(1);
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
                    sleep(1);
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
        else if (command == 13)
        {
            Jadwal *jadwal = cekKonflikJadwalStudio(studioList[selection - 1].id);
            if (jadwal != NULL)
            {
                printf("Studio ini sedang memutar film lain dalam ");
                continue;
            }

            printf("Studio " GREEN "%s" RESET " dipilih\n", studioList[selection - 1].nama);

            int studioID = studioList[selection - 1].id;

            free(studioList);

            return studioID;
        }
        else
        {
            printf(YELLOW BOLD "Command not found\n" RESET);
            sleep(1);
        }
    }
}

int selectFilmJadwal()
{
    Film *filmList;
    int count = loadFilm(&filmList);

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        selection = (page - 1) * perPage + pointer;

        printFilmTable(filmList, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page\n");
        printf("[Arrow /\\] | [Arrow \\/] Arrow Up/Down To Selecting\n");
        printf(GREEN "[ENTER]: Enter To Select Film\n\n" RESET);

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
                    sleep(1);
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
                    sleep(1);
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
        else if (command == 13)
        {
            printf("Film " GREEN "%s" RESET " dipilih\n", filmList[selection - 1].judul);

            int filmID = filmList[selection - 1].id;

            free(filmList);

            return filmID;
        }
        else
        {
            printf(YELLOW BOLD "Command not found\n" RESET);
            sleep(1);
        }
    }
}

void createJadwalMenu()
{
    system("cls");

    printf(GREEN "====================================================\n");
    printf("              Menu Tambah Jadwal (tiket)            \n");
    printf("====================================================\n" RESET);

    Jadwal newJadwal;
    char input[MAX_TIME_LENGTH];
    int harga_tiket;

    // Pilih Studio
    printf("Pilih Studio: \n");
    newJadwal.studio_id = selectStudioJadwal();

    // Pilih Film
    printf("Pilih Film: \n");
    newJadwal.film_id = selectFilmJadwal();

    printf("Masukan harga tiket: ");
    scanf("%d", &harga_tiket);
    printf("\n");

    int valid = 0;
    while (!valid)
    {
        printf("Masukkan Waktu Awal Tayang (hh:mm): ");
        fgets(input, sizeof(input), stdin); // untuk membersihkan buffer
        sscanf(input, "%d:%d", &newJadwal.waktu_akhir_tayang.tm_hour, &newJadwal.waktu_akhir_tayang.tm_min);

        valid = isValidTime(newJadwal.waktu_akhir_tayang.tm_hour, newJadwal.waktu_akhir_tayang.tm_min);
        if (!valid)
        {
            printf("Waktu tidak valid! Pastikan jam (0-23) dan menit (0-59).\n");
        }
    }

    // Input Waktu Akhir Tayang
    valid = 0;
    while (!valid)
    {
        printf("Masukkan Waktu Akhir Tayang (hh:mm): ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d:%d", &newJadwal.waktu_akhir_tayang.tm_hour, &newJadwal.waktu_akhir_tayang.tm_min);

        valid = isValidTime(newJadwal.waktu_akhir_tayang.tm_hour, newJadwal.waktu_akhir_tayang.tm_min);
        if (!valid)
        {
            printf("Waktu tidak valid! Pastikan jam (0-23) dan menit (0-59).\n");
        }
    }

    // Input Tanggal Tersedia Sampai
    valid = 0;
    while (!valid)
    {
        printf("Masukkan Tanggal Tersedia Sampai (yyyy-mm-dd): ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d-%d-%d", &newJadwal.tersedia_sampai.tm_year, &newJadwal.tersedia_sampai.tm_mon, &newJadwal.tersedia_sampai.tm_mday);

        newJadwal.tersedia_sampai.tm_year -= 1900; // tm_year mulai dari 1900
        newJadwal.tersedia_sampai.tm_mon -= 1;     // tm_mon mulai dari 0 (Januari)

        valid = isValidDate(newJadwal.tersedia_sampai.tm_year, newJadwal.tersedia_sampai.tm_mon + 1, newJadwal.tersedia_sampai.tm_mday);
        if (!valid)
        {
            printf("Tanggal tidak valid! Pastikan format dan rentang tanggalnya benar.\n");
        }
    }

    Jadwal *createdJadwal = createJadwal(
        newJadwal.studio_id,
        newJadwal.film_id,
        newJadwal.waktu_awal_tayang,
        newJadwal.waktu_akhir_tayang,
        newJadwal.tersedia_sampai,
        harga_tiket);

    if (createdJadwal == NULL)
    {
        printf(RED BOLD "Gagal menambah jadwal. Harap coba lagi.\n" RESET);
        return;
    }

    printf(GREEN BOLD "Berhasil menambah jadwal!.\n" RESET);
    sleep(2);
    free(createdJadwal);
}

void updateJadwalMenu(Jadwal jadwal)
{
    printf(YELLOW "====================================================\n");
    printf("              Menu Edit Jadwal (tiket)              \n");
    printf("====================================================\n" RESET);

    Jadwal updatedJadwal;
    char input[MAX_TIME_LENGTH];
    int harga_tiket;

    // Pilih Studio
    printf("Pilih Studio: \n");
    updatedJadwal.studio_id = selectStudioJadwal();

    // Pilih Film
    printf("Pilih Film: \n");
    updatedJadwal.film_id = selectFilmJadwal();

    printf("Masukan harga tiket: ");
    scanf("%d", &harga_tiket);
    printf("\n");

    int valid = 0;
    while (!valid)
    {
        printf("Masukkan Waktu Awal Tayang (hh:mm): ");
        fgets(input, sizeof(input), stdin); // untuk membersihkan buffer
        sscanf(input, "%d:%d", &updatedJadwal.waktu_akhir_tayang.tm_hour, &updatedJadwal.waktu_akhir_tayang.tm_min);

        valid = isValidTime(updatedJadwal.waktu_akhir_tayang.tm_hour, updatedJadwal.waktu_akhir_tayang.tm_min);
        if (!valid)
        {
            printf("Waktu tidak valid! Pastikan jam (0-23) dan menit (0-59).\n");
        }
    }

    // Input Waktu Akhir Tayang
    valid = 0;
    while (!valid)
    {
        printf("Masukkan Waktu Akhir Tayang (hh:mm): ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d:%d", &updatedJadwal.waktu_akhir_tayang.tm_hour, &updatedJadwal.waktu_akhir_tayang.tm_min);

        valid = isValidTime(updatedJadwal.waktu_akhir_tayang.tm_hour, updatedJadwal.waktu_akhir_tayang.tm_min);
        if (!valid)
        {
            printf("Waktu tidak valid! Pastikan jam (0-23) dan menit (0-59).\n");
        }
    }

    // Input Tanggal Tersedia Sampai
    valid = 0;
    while (!valid)
    {
        printf("Masukkan Tanggal Tersedia Sampai (yyyy-mm-dd): ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d-%d-%d", &updatedJadwal.tersedia_sampai.tm_year, &updatedJadwal.tersedia_sampai.tm_mon, &updatedJadwal.tersedia_sampai.tm_mday);

        updatedJadwal.tersedia_sampai.tm_year -= 1900; // tm_year mulai dari 1900
        updatedJadwal.tersedia_sampai.tm_mon -= 1;     // tm_mon mulai dari 0 (Januari)

        valid = isValidDate(updatedJadwal.tersedia_sampai.tm_year, updatedJadwal.tersedia_sampai.tm_mon + 1, updatedJadwal.tersedia_sampai.tm_mday);
        if (!valid)
        {
            printf("Tanggal tidak valid! Pastikan format dan rentang tanggalnya benar.\n");
        }
    }

    // Menyimpan perubahan jadwal ke database
    updatedJadwal.id = jadwal.id; // Memastikan ID tetap sama dengan ID jadwal yang diupdate
    Jadwal *newJadwal = updateJadwal(
        jadwal.id,
        updatedJadwal.studio_id,
        updatedJadwal.film_id,
        updatedJadwal.waktu_awal_tayang,
        updatedJadwal.waktu_akhir_tayang,
        updatedJadwal.tersedia_sampai,
        harga_tiket);

    if (newJadwal == NULL)
    {
        printf(RED BOLD "Gagal mengubah jadwal. Harap coba lagi.\n" RESET);
        return;
    }

    printf(GREEN BOLD "Berhasil mengubah jadwal!.\n" RESET);
    sleep(2);
    return newJadwal;
}

// ================================= Action =================================== //
int isValidTime(int hour, int minute)
{
    return (hour >= 0 && hour < 24 && minute >= 0 && minute < 60);
}

int isValidDate(int year, int month, int day)
{
    if (month < 1 || month > 12)
        return 0;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        daysInMonth[1] = 29;
    }

    return (day >= 1 && day <= daysInMonth[month - 1]);
}

Jadwal *cekKonflikJadwalStudio(int studio_id)
{
    Jadwal *jadwalList;
    int count = loadJadwal(&jadwalList);

    time_t sekarang = time(NULL);
    struct tm *hari_ini = localtime(&sekarang);
    int i = 0;

    while (i < count)
    {
        if (jadwalList[i].studio_id == studio_id)
        {
            // Periksa jika ada film dengan tersedia_sampai > hari ini
            if (difftime(mktime(&jadwalList[i].tersedia_sampai), mktime(hari_ini)) > 0)
            {
                return &jadwalList[i]; // Konflik ditemukan karena studio sudah terpakai
            }
        }
        i++;
    }

    return NULL; // Tidak ada konflik
}

Jadwal *createJadwal(int studio_id, int film_id, Waktu waktu_awal_tayang, Waktu waktu_akhir_tayang, Waktu tersedia_sampai, int harga_tiket)
{
    Jadwal *jadwal = malloc(sizeof(Jadwal));
    if (!jadwal)
    {
        printf("Alokasi memori gagal, lokasi: createJadwal\n");
        return NULL;
    }

    jadwal->id = getLastAvailableID(JADWAL_DATABASE_NAME);
    jadwal->studio_id = studio_id;
    jadwal->film_id = film_id;
    jadwal->waktu_awal_tayang.tm_hour = waktu_awal_tayang.tm_hour;
    jadwal->waktu_awal_tayang.tm_min = waktu_awal_tayang.tm_min;
    jadwal->waktu_akhir_tayang.tm_hour = waktu_akhir_tayang.tm_hour;
    jadwal->waktu_akhir_tayang.tm_min = waktu_akhir_tayang.tm_min;
    jadwal->tersedia_sampai = tersedia_sampai;
    jadwal->harga_tiket = harga_tiket;

    FILE *file = fopen(JADWAL_DATABASE_NAME, "a");
    if (!file)
    {
        printf("Gagal membuka file untuk menulis data jadwal\n");
        free(jadwal);
        return NULL;
    }

    fprintf(file, JADWAL_SETTER_FORMAT,
            jadwal->id,
            jadwal->studio_id,
            jadwal->film_id,
            jadwal->waktu_awal_tayang.tm_hour, jadwal->waktu_awal_tayang.tm_min,
            jadwal->waktu_akhir_tayang.tm_hour, jadwal->waktu_akhir_tayang.tm_min,
            jadwal->tersedia_sampai.tm_year + 1900, jadwal->tersedia_sampai.tm_mon + 1, jadwal->tersedia_sampai.tm_mday,
            jadwal->harga_tiket);

    fclose(file);
    return jadwal;
}

Jadwal *updateJadwal(int id, int studio_id, int film_id, Waktu waktu_awal_tayang, Waktu waktu_akhir_tayang, Waktu tersedia_sampai, int harga_tiket)
{
    FILE *fromFile = fopen(JADWAL_DATABASE_NAME, "r");
    if (!fromFile)
    {
        printf("Gagal membuka file untuk membaca data jadwal\n");
        return NULL;
    }

    int count = countJadwalData();
    Jadwal jadwals[count];
    int i = 0;

    while (fscanf(fromFile, JADWAL_GETTER_FORMAT,
                  &jadwals[i].id,
                  &jadwals[i].studio_id,
                  &jadwals[i].film_id,
                  &jadwals[i].waktu_awal_tayang.tm_hour, &jadwals[i].waktu_awal_tayang.tm_min,
                  &jadwals[i].waktu_akhir_tayang.tm_hour, &jadwals[i].waktu_akhir_tayang.tm_min,
                  &jadwals[i].tersedia_sampai.tm_year, &jadwals[i].tersedia_sampai.tm_mon, &jadwals[i].tersedia_sampai.tm_mday,
                  &jadwals[i].harga_tiket) != EOF)
    {
        if (jadwals[i].id == id)
        {
            jadwals[i].studio_id = studio_id;
            jadwals[i].film_id = film_id;
            jadwals[i].waktu_awal_tayang.tm_hour = waktu_awal_tayang.tm_hour;
            jadwals[i].waktu_awal_tayang.tm_min = waktu_awal_tayang.tm_min;
            jadwals[i].waktu_akhir_tayang.tm_hour = waktu_akhir_tayang.tm_hour;
            jadwals[i].waktu_akhir_tayang.tm_min = waktu_akhir_tayang.tm_min;
            jadwals[i].tersedia_sampai = tersedia_sampai;
            jadwals[i].harga_tiket = harga_tiket;
            id = i;
        }
        i++;
    }
    fclose(fromFile);

    FILE *toFile = fopen(JADWAL_DATABASE_NAME, "w");
    if (!toFile)
    {
        printf("Gagal membuka file untuk menulis data jadwal\n");
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        fprintf(toFile, JADWAL_SETTER_FORMAT,
                jadwals[i].id,
                jadwals[i].studio_id,
                jadwals[i].film_id,
                jadwals[i].waktu_awal_tayang.tm_hour, jadwals[i].waktu_awal_tayang.tm_min,
                jadwals[i].waktu_akhir_tayang.tm_hour, jadwals[i].waktu_akhir_tayang.tm_min,
                jadwals[i].tersedia_sampai.tm_year + 1900, jadwals[i].tersedia_sampai.tm_mon + 1, jadwals[i].tersedia_sampai.tm_mday,
                &jadwals[i].harga_tiket);
    }

    fclose(toFile);
    return &jadwals[id];
}

int deleteJadwal(Jadwal jadwal)
{
    // Buat pesan konfirmasi
    int len = snprintf(NULL, 0, "Apakah Anda yakin ingin menghapus jadwal dengan ID '%d'?\n", jadwal.id) + 1;
    char *head = malloc(len);
    if (!head)
    {
        printf(RED "Gagal mengalokasikan memori.\n" RESET);
        sleep(1);
        return -1;
    }
    snprintf(head, len, "Apakah Anda yakin ingin menghapus jadwal dengan ID '%d'?\n", jadwal.id);

    char *menu[] = {
        "Tidak, Batalkan",
        "Ya, Hapus",
    };

    char *header[] = {
        RED BOLD "====================================================\n",
        "             Konfirmasi Hapus Jadwal               \n",
        "====================================================\n\n" RESET,
        head,
        NULL};

    int selection = showMenu(menu, 2, header);
    free(head);

    if (selection == 1)
    {
        printf("Penghapusan dibatalkan.\n");
        return 0; // Penghapusan dibatalkan
    }

    // Buka file untuk membaca jadwal
    FILE *fromFile = fopen(JADWAL_DATABASE_NAME, "r");
    if (!fromFile)
    {
        printf("Gagal membuka file untuk membaca data jadwal\n");
        return -1;
    }

    int count = countJadwalData();
    if (count == 0)
    {
        printf("Tidak ada data jadwal untuk dihapus\n");
        fclose(fromFile);
        return -1;
    }

    Jadwal jadwals[count];
    int i = 0;

    Jadwal temp;
    // Membaca data jadwal dari file dan menyaring yang akan dihapus
    while (fscanf(fromFile, JADWAL_GETTER_FORMAT,
                  &temp.id,
                  &temp.studio_id,
                  &temp.film_id,
                  &temp.waktu_awal_tayang.tm_hour, &temp.waktu_awal_tayang.tm_min,
                  &temp.waktu_akhir_tayang.tm_hour, &temp.waktu_akhir_tayang.tm_min,
                  &temp.tersedia_sampai.tm_year, &temp.tersedia_sampai.tm_mon, &temp.tersedia_sampai.tm_mday,
                  &temp.harga_tiket) != EOF)
    {
        printf("Membaca jadwal ID: %d\n", temp.id); // Debug log
        if (temp.id != jadwal.id)
        {
            jadwals[i] = temp;
            i++;
        }
    }
    fclose(fromFile);

    // Jika jadwal tidak ditemukan
    if (i == count)
    {
        printf("Jadwal dengan ID %d tidak ditemukan\n", jadwal.id);
        return -1;
    }

    // Menulis ulang data jadwal ke file tanpa yang dihapus
    FILE *toFile = fopen(JADWAL_DATABASE_NAME, "w");
    if (!toFile)
    {
        printf("Gagal membuka file untuk menulis data jadwal\n");
        return -1;
    }

    for (int j = 0; j < i; j++)
    {
        printf("Menulis ulang jadwal ID: %d\n", jadwals[j].id); // Debug log
        fprintf(toFile, JADWAL_SETTER_FORMAT,
                jadwals[j].id,
                jadwals[j].studio_id,
                jadwals[j].film_id,
                jadwals[j].waktu_awal_tayang.tm_hour, jadwals[j].waktu_awal_tayang.tm_min,
                jadwals[j].waktu_akhir_tayang.tm_hour, jadwals[j].waktu_akhir_tayang.tm_min,
                jadwals[j].tersedia_sampai.tm_year + 1900, jadwals[j].tersedia_sampai.tm_mon + 1, jadwals[j].tersedia_sampai.tm_mday,
                jadwals[j].harga_tiket);
    }

    fclose(toFile);
    printf("Jadwal dengan ID %d berhasil dihapus.\n", jadwal.id);
    return 1; // Berhasil menghapus jadwal
}

// ================================== Utils ================================== //
int countJadwalData()
{
    FILE *file = fopen(JADWAL_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int count = 0;
    Jadwal jadwal;

    while (fscanf(file, JADWAL_GETTER_FORMAT,
                  &jadwal.id,
                  &jadwal.studio_id,
                  &jadwal.film_id,
                  &jadwal.waktu_awal_tayang.tm_hour,
                  &jadwal.waktu_awal_tayang.tm_min,
                  &jadwal.waktu_akhir_tayang.tm_hour,
                  &jadwal.waktu_akhir_tayang.tm_min,
                  &jadwal.tersedia_sampai.tm_year,
                  &jadwal.tersedia_sampai.tm_mon,
                  &jadwal.tersedia_sampai.tm_mday,
                  &jadwal.harga_tiket) == 11) // 11 elemen harus berhasil dibaca
    {

        count++;
    }

    fclose(file);
    return count;
}

int loadJadwal(Jadwal **jadwals)
{
    FILE *file = fopen(JADWAL_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int count = countJadwalData();
    if (count <= 0)
    {
        fclose(file);
        return count;
    }

    *jadwals = (Jadwal *)malloc(count * sizeof(Jadwal));
    if (*jadwals == NULL)
    {
        printf("Gagal mengalokasi memori.\n");
        fclose(file);
        return -1;
    }

    rewind(file);
    int i = 0;
    while (fscanf(file, JADWAL_GETTER_FORMAT,
                  &(*jadwals)[i].id,
                  &(*jadwals)[i].studio_id,
                  &(*jadwals)[i].film_id,
                  &(*jadwals)[i].waktu_awal_tayang.tm_hour,
                  &(*jadwals)[i].waktu_awal_tayang.tm_min,
                  &(*jadwals)[i].waktu_akhir_tayang.tm_hour,
                  &(*jadwals)[i].waktu_akhir_tayang.tm_min,
                  &(*jadwals)[i].tersedia_sampai.tm_year,
                  &(*jadwals)[i].tersedia_sampai.tm_mon,
                  &(*jadwals)[i].tersedia_sampai.tm_mday,
                  &(*jadwals)[i].harga_tiket) == 11) // Validasi jumlah elemen
    {
        i++;
    }
    // printf("%d\n", (*jadwals)[0].tersedia_sampai.tm_year);
    // sleep(10);
    fclose(file);
    return count;
}

void printJadwalTable(Jadwal *jadwal, int count, int page, int perPage, int selection)
{
    int idWidth = 2, studioWidth = 6, filmWidth = 6;
    int waktuWidth = 11, tersediaWidth = 18; // waktuWidth untuk waktu awal dan akhir

    int start = (page - 1) * perPage;
    int end = start + perPage;
    if (end > count)
        end = count;

    // Hitung panjang kolom terpanjang
    for (int i = start; i < end; i++)
    {
        int idLen = snprintf(NULL, 0, "%d", jadwal[i].id);
        if (idLen > idWidth)
            idWidth = idLen;

        int studioLen = snprintf(NULL, 0, "%d", jadwal[i].studio_id);
        if (studioLen > studioWidth)
            studioWidth = studioLen;

        int filmLen = snprintf(NULL, 0, "%d", jadwal[i].film_id);
        if (filmLen > filmWidth)
            filmWidth = filmLen;
    }

    // Hitung panjang tabel
    int tableWidth = 6 + idWidth + 3 + studioWidth + 3 + filmWidth + 3 + waktuWidth + 3 + waktuWidth + 3 + tersediaWidth + 3;

    // Cetak garis atas tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak header tabel
    printf("[ * ]| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           idWidth, "ID",
           studioWidth, "Studio",
           filmWidth, "Film",
           waktuWidth, "Waktu Awal",
           waktuWidth, "Waktu Akhir",
           tersediaWidth, "Tersedia Sampai");

    // Cetak garis bawah header
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak isi tabel
    for (int i = start; i < end; i++)
    {

        char waktuAwal[20], waktuAkhir[20], tersedia[20];

        // Format waktu
        strftime(waktuAwal, sizeof(waktuAwal), "%H:%M", &jadwal[i].waktu_awal_tayang);
        strftime(waktuAkhir, sizeof(waktuAkhir), "%H:%M", &jadwal[i].waktu_akhir_tayang);
        snprintf(tersedia, sizeof(tersedia), "%d-%d-%d", jadwal[i].tersedia_sampai.tm_mday, jadwal[i].tersedia_sampai.tm_mon, jadwal[i].tersedia_sampai.tm_year);

        // Tampilkan baris
        if (selection == i + 1)
        {
            printf(BLUE BOLD "[ * ]| %-*d | %-*d | %-*d | %-*s | %-*s | %-*s |\n" RESET,
                   idWidth, jadwal[i].id,
                   studioWidth, jadwal[i].studio_id,
                   filmWidth, jadwal[i].film_id,
                   waktuWidth, waktuAwal,
                   waktuWidth, waktuAkhir,
                   tersediaWidth, tersedia);
        }
        else
        {
            printf("[   ]| %-*d | %-*d | %-*d | %-*s | %-*s | %-*s |\n",
                   idWidth, jadwal[i].id,
                   studioWidth, jadwal[i].studio_id,
                   filmWidth, jadwal[i].film_id,
                   waktuWidth, waktuAwal,
                   waktuWidth, waktuAkhir,
                   tersediaWidth, tersedia);
        }
    }

    // Cetak garis bawah tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Informasi halaman
    printf("Page %d of %d\n", page, (count + perPage - 1) / perPage);
}

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
#include "menu.h"
#include "db.h"
#include "transaksi.h"

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
        printf(GREEN "\n[C]: Create" RESET " | " RED "[D]: Delete" RESET " | " BG_RED WHITE "[E] Exit" RESET "\n" RESET);

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
        else if (command == 'D' || command == 'd') // Delete selected Jadwal
        {
            deleteJadwal(jadwals[selection - 1]);

            free(jadwals);
            count = loadJadwal(&jadwals);
            pointer = 1;
        }
        else if (command == 'E' || command == 'e') // Exit
        {
            printf(YELLOW BOLD "Keluar ...\n" RESET);
            break;
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
                sleep(2);
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

    printf("Pilih Studio: \n");
    newJadwal.studio_id = selectStudioJadwal();

    printf("Pilih Film: \n");
    newJadwal.film_id = selectFilmJadwal();

    printf("Masukkan harga tiket: ");
    scanf("%d", &harga_tiket);
    getchar(); // Clear the newline character from the input buffer

    int valid = 0;
    int hour, minute;
    while (!valid)
    {
        printf("Masukkan Waktu Awal Tayang (hh:mm): ");
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            input[strcspn(input, "\n")] = 0;
            if (sscanf(input, "%02d:%02d", &hour, &minute) == 2)
            {
                if (isValidTime(hour, minute))
                {
                    newJadwal.waktu_awal_tayang.tm_hour = hour;
                    newJadwal.waktu_awal_tayang.tm_min = minute;
                    valid = 1;
                }
                else
                {
                    printf("Waktu tidak valid! Jam harus 0-23 dan menit 0-59.\n");
                }
            }
            else
            {
                printf("Format tidak valid! Gunakan format hh:mm (contoh: 07:00)\n");
            }
        }
    }

    valid = 0;
    while (!valid)
    {
        printf("Masukkan Waktu Akhir Tayang (hh:mm): ");
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            input[strcspn(input, "\n")] = 0;
            if (sscanf(input, "%02d:%02d", &hour, &minute) == 2)
            {
                if (isValidTime(hour, minute))
                {
                    newJadwal.waktu_akhir_tayang.tm_hour = hour;
                    newJadwal.waktu_akhir_tayang.tm_min = minute;
                    valid = 1;
                }
                else
                {
                    printf("Waktu tidak valid! Jam harus 0-23 dan menit 0-59.\n");
                }
            }
            else
            {
                printf("Format tidak valid! Gunakan format hh:mm (contoh: 07:00)\n");
            }
        }
    }

    valid = 0;
    while (!valid)
    {
        printf("Masukkan Tanggal Tersedia Sampai (yyyy-mm-dd): ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d-%d-%d", &newJadwal.tersedia_sampai.tm_year, &newJadwal.tersedia_sampai.tm_mon, &newJadwal.tersedia_sampai.tm_mday);

        newJadwal.tersedia_sampai.tm_year -= 1900;
        newJadwal.tersedia_sampai.tm_mon -= 1;

        valid = isValidDate(newJadwal.tersedia_sampai.tm_year, newJadwal.tersedia_sampai.tm_mon + 1, newJadwal.tersedia_sampai.tm_mday);
        if (!valid)
        {
            printf("Tanggal tidak valid! Pastikan format dan rentang tanggalnya benar.\n");
        }
    }

    // printf("\nInformasi Jadwal yang Dimasukkan:\n");
    // printf("==============================\n");
    // printf("Studio ID: %d\n", newJadwal.studio_id);
    // printf("Film ID: %d\n", newJadwal.film_id);
    // printf("Harga Tiket: %d\n", newJadwal.harga_tiket);
    // printf("Waktu Awal Tayang: %02d:%02d\n", newJadwal.waktu_awal_tayang.tm_hour, newJadwal.waktu_awal_tayang.tm_min);
    // printf("Waktu Akhir Tayang: %02d:%02d\n", newJadwal.waktu_akhir_tayang.tm_hour, newJadwal.waktu_akhir_tayang.tm_min);
    // printf("Tanggal Tersedia Sampai: %04d-%02d-%02d\n", newJadwal.tersedia_sampai.tm_year + 1900, newJadwal.tersedia_sampai.tm_mon + 1, newJadwal.tersedia_sampai.tm_mday);
    // printf("==============================\n");

    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);

    // // Menampilkan waktu saat ini
    // printf("Tanggal Hari Ini: %d-%02d-%02d\n", currentTime->tm_year + 1900, currentTime->tm_mon + 1, currentTime->tm_mday);
    // printf("Waktu Saat Ini: %02d:%02d\n", currentTime->tm_hour, currentTime->tm_min);
    // sleep(100);

    Waktu waktu_awal_tayang = {0};
    waktu_awal_tayang.tm_year = currentTime->tm_year;
    waktu_awal_tayang.tm_mon = currentTime->tm_mon;
    waktu_awal_tayang.tm_mday = currentTime->tm_mday;
    waktu_awal_tayang.tm_hour = newJadwal.waktu_awal_tayang.tm_hour;
    waktu_awal_tayang.tm_min = newJadwal.waktu_awal_tayang.tm_min;
    waktu_awal_tayang.tm_sec = 0;

    Waktu waktu_akhir_tayang = {0};
    waktu_akhir_tayang.tm_hour = newJadwal.waktu_akhir_tayang.tm_hour;
    waktu_akhir_tayang.tm_min = newJadwal.waktu_akhir_tayang.tm_min;

    Waktu tersedia_sampai = {0};
    tersedia_sampai.tm_year = newJadwal.tersedia_sampai.tm_year;
    tersedia_sampai.tm_mon = newJadwal.tersedia_sampai.tm_mon;
    tersedia_sampai.tm_mday = newJadwal.tersedia_sampai.tm_mday;

    createJadwal(newJadwal.studio_id, newJadwal.film_id, waktu_awal_tayang, waktu_akhir_tayang, tersedia_sampai, harga_tiket);

    printf(GREEN BOLD "Berhasil menambah jadwal!\n" RESET);
    sleep(2);
}

// ================================= Action =================================== //

Jadwal *findJadwalById(int jadwal_id)
{
    FILE *file = fopen(JADWAL_DATABASE_NAME, "r");
    if (!file)
    {
        printf("Error membuka file jadwal.\n");
        return NULL;
    }

    // Alokasi memori untuk hasil pencarian
    Jadwal *targetJadwal = malloc(sizeof(Jadwal));
    if (!targetJadwal)
    {
        printf("Gagal mengalokasikan memori.\n");
        fclose(file);
        return NULL;
    }

    // Cari jadwal berdasarkan ID
    while (fscanf(file, JADWAL_GETTER_FORMAT,
                  &targetJadwal->id, &targetJadwal->studio_id, &targetJadwal->film_id,
                  &targetJadwal->waktu_awal_tayang.tm_hour, &targetJadwal->waktu_awal_tayang.tm_min,
                  &targetJadwal->waktu_akhir_tayang.tm_hour, &targetJadwal->waktu_akhir_tayang.tm_min,
                  &targetJadwal->tersedia_sampai.tm_year, &targetJadwal->tersedia_sampai.tm_mon, &targetJadwal->tersedia_sampai.tm_mday,
                  &targetJadwal->harga_tiket) == 11)
    {
        if (targetJadwal->id == jadwal_id)
        {
            fclose(file);
            return targetJadwal; // Kembalikan hasil jika ditemukan
        }
    }

    // Jika tidak ditemukan, bebaskan memori dan kembalikan NULL
    free(targetJadwal);
    fclose(file);
    return NULL;
}

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

int isStudioFull(int jadwal_id)
{
    FILE *file = fopen(JADWAL_DATABASE_NAME, "r");
    if (!file)
    {
        printf("Error membuka file jadwal.\n");
        return -1;
    }

    Jadwal *targetJadwal = findJadwalById(jadwal_id);
    if (targetJadwal == NULL)
    {
        printf("Jadwal ID %d tidak ditemukan.\n", jadwal_id);
        fclose(file);
        return -1;
    }

    // Dapatkan kapasitas studio
    Studio *std = findStudioById(targetJadwal->studio_id);
    if (std == NULL)
    {
        printf("Studio tidak ditemukan.\n");
        fclose(file);
        return -1;
    }

    int capacity = std->jumlah_kursi;
    int totalTickets = countTicketsSold(jadwal_id);

    fclose(file);

    // Bandingkan total tiket dengan kapasitas studio
    if (totalTickets >= capacity)
    {
        // printf("Studio penuh! Total tiket terjual: %d / %d\n", totalTickets, capacity);
        return 1;
    }
    else
    {
        // printf("Studio masih tersedia. Total tiket terjual: %d / %d\n", totalTickets, capacity);
        return 0;
    }
}

void *createJadwal(int studio_id, int film_id, Waktu waktu_awal_tayang, Waktu waktu_akhir_tayang, Waktu tersedia_sampai, int harga_tiket)
{
    // // Print parameter lainnya
    // printf("Studio ID: %d\n", studio_id);
    // printf("Film ID: %d\n", film_id);

    // printf("=== Waktu Awal Tayang ===\n");
    // printf("Tahun: %d\n", waktu_awal_tayang.tm_year);  // Menambahkan 1900 ke tm_year
    // printf("Bulan: %02d\n", waktu_awal_tayang.tm_mon); // Menambahkan 1 ke tm_mon (indeks mulai dari 0)
    // printf("Tanggal: %02d\n", waktu_awal_tayang.tm_mday);
    // printf("Jam: %02d\n", waktu_awal_tayang.tm_hour);
    // printf("Menit: %02d\n", waktu_awal_tayang.tm_min);
    // printf("Detik: %02d\n", waktu_awal_tayang.tm_sec);

    // printf("\n=== Waktu Akhir Tayang ===\n");
    // printf("Tahun: %d\n", waktu_akhir_tayang.tm_year);  // Menambahkan 1900 ke tm_year
    // printf("Bulan: %02d\n", waktu_akhir_tayang.tm_mon); // Menambahkan 1 ke tm_mon (indeks mulai dari 0)
    // printf("Tanggal: %02d\n", waktu_akhir_tayang.tm_mday);
    // printf("Jam: %02d\n", waktu_akhir_tayang.tm_hour);
    // printf("Menit: %02d\n", waktu_akhir_tayang.tm_min);
    // printf("Detik: %02d\n", waktu_akhir_tayang.tm_sec);

    // printf("\n=== Tersedia Sampai ===\n");
    // printf("Tahun: %d\n", tersedia_sampai.tm_year);  // Menambahkan 1900 ke tm_year
    // printf("Bulan: %02d\n", tersedia_sampai.tm_mon); // Menambahkan 1 ke tm_mon (indeks mulai dari 0)
    // printf("Tanggal: %02d\n", tersedia_sampai.tm_mday);
    // printf("Jam: %02d\n", tersedia_sampai.tm_hour);
    // printf("Menit: %02d\n", tersedia_sampai.tm_min);
    // printf("Detik: %02d\n", tersedia_sampai.tm_sec);

    // // Print harga_tiket
    // printf("Harga Tiket: %d\n", harga_tiket);
    // sleep(10);

    // Alokasi memori untuk objek Jadwal
    Jadwal *jadwal = malloc(sizeof(Jadwal));
    if (!jadwal)
    {
        printf("Alokasi memori gagal, lokasi: createJadwal2\n");
        return NULL;
    }

    // Inisialisasi atribut Jadwal
    jadwal->id = getLastAvailableID(JADWAL_DATABASE_NAME);
    jadwal->studio_id = studio_id;
    jadwal->film_id = film_id;
    jadwal->waktu_awal_tayang = waktu_awal_tayang;
    jadwal->waktu_akhir_tayang = waktu_akhir_tayang;
    jadwal->tersedia_sampai = tersedia_sampai;
    jadwal->harga_tiket = harga_tiket;

    // Buka file database jadwal
    FILE *file = fopen(JADWAL_DATABASE_NAME, "a");
    if (!file)
    {
        printf("Gagal membuka file untuk menulis data jadwal\n");
        free(jadwal);
        return NULL;
    }

    // Hitung menit awal dan akhir
    int menitAwal = waktu_awal_tayang.tm_hour * 60 + waktu_awal_tayang.tm_min;
    int menitAkhir = waktu_akhir_tayang.tm_hour * 60 + waktu_akhir_tayang.tm_min;

    // Ambil durasi film dan jeda antar film
    Film *film = findFilmByID(film_id);
    if (!film)
    {
        printf("Film dengan ID %d tidak ditemukan\n", film_id);
        fclose(file);
        free(jadwal);
        return NULL;
    }
    int durasi = film->durasi; // Durasi film dalam menit
    int jeda = 30;             // Jeda antar film dalam menit

    // Mulai dari hari ini hingga tersedia_sampai
    Waktu currentDate = waktu_awal_tayang;
    currentDate.tm_hour = 0; // Reset jam ke awal hari
    currentDate.tm_min = 0;
    currentDate.tm_sec = 0;

    int jadwalID = jadwal->id;

    // Loop selama tanggal currentDate <= tersedia_sampai
    while (mktime(&currentDate) <= mktime(&tersedia_sampai))
    {
        int currentStart = menitAwal;
        // Loop untuk membuat jadwal dalam satu hari
        while (currentStart + durasi <= menitAkhir)
        {
            // Hitung waktu mulai dan selesai untuk jadwal saat ini
            int currentEnd = currentStart + durasi;

            // Konversi waktu mulai ke jam dan menit
            int startHour = currentStart / 60;
            int startMin = currentStart % 60;

            // Konversi waktu selesai ke jam dan menit
            int endHour = currentEnd / 60;
            int endMin = currentEnd % 60;

            // Tulis jadwal ke file
            fprintf(file, JADWAL_SETTER_FORMAT,
                    jadwalID++,
                    studio_id,
                    film_id,
                    startHour, startMin,
                    endHour, endMin,
                    currentDate.tm_year + 1900, currentDate.tm_mon + 1, currentDate.tm_mday,
                    harga_tiket);

            // Tambahkan jeda waktu setelah film selesai
            currentStart = currentEnd + jeda;
        }

        // Tambahkan satu hari ke tanggal
        currentDate.tm_mday++;
        mktime(&currentDate); // Normalisasi tanggal (untuk menangani akhir bulan, dst.)
    }

    fclose(file);
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
        "              Konfirmasi Hapus Jadwal               \n",
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

void printJadwalTableFull(Jadwal *jadwal, int count, int page, int perPage, int selection)
{
    int idWidth = 2, studioWidth = 6, soldWidth = 10, filmWidth = 6;
    int waktuWidth = 11, tersediaWidth = 18;
    int bioskopNamaWidth = 14, bioskopAlamatWidth = 20;

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

        int soldLen = snprintf(NULL, 0, "%d/%d",
                               countTicketsSold(jadwal[i].id),
                               findStudioById(jadwal[i].studio_id)->jumlah_kursi);

        if (soldLen > soldWidth)
            soldWidth = soldLen;

        int filmLen = snprintf(NULL, 0, "%d", jadwal[i].film_id);
        if (filmLen > filmWidth)
            filmWidth = filmLen;

        Bioskop *bioskop = findBioskopById(jadwal[i].studio_id);
        if (bioskop)
        {
            int namaLen = strlen(bioskop->nama);
            if (namaLen > bioskopNamaWidth)
                bioskopNamaWidth = namaLen;

            int alamatLen = strlen(bioskop->alamat);
            if (alamatLen > bioskopAlamatWidth)
                bioskopAlamatWidth = alamatLen;

            free(bioskop); // Bebaskan memori
        }
    }

    // Hitung panjang tabel
    int tableWidth = 6 + idWidth + 3 + studioWidth + 3 + soldWidth + 3 + filmWidth + 3 +
                     waktuWidth + 3 + waktuWidth + 3 + tersediaWidth + 3 +
                     bioskopNamaWidth + 3 + bioskopAlamatWidth + 5;

    // Cetak garis atas tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak header tabel
    printf("[ * ]| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           idWidth, "ID",
           studioWidth, "Studio",
           soldWidth, "Terjual/Kap.",
           filmWidth, "Film",
           waktuWidth, "Waktu Awal",
           waktuWidth, "Waktu Akhir",
           tersediaWidth, "Tersedia Sampai",
           bioskopNamaWidth, "Nama Bioskop",
           bioskopAlamatWidth, "Alamat Bioskop");

    // Cetak garis bawah header
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Cetak isi tabel
    for (int i = start; i < end; i++)
    {
        char waktuAwal[20], waktuAkhir[20], tersedia[20];
        Bioskop *bioskop = findBioskopById(jadwal[i].studio_id);
        Studio *studio = findStudioById(jadwal[i].studio_id);

        // Format waktu
        strftime(waktuAwal, sizeof(waktuAwal), "%H:%M", &jadwal[i].waktu_awal_tayang);
        strftime(waktuAkhir, sizeof(waktuAkhir), "%H:%M", &jadwal[i].waktu_akhir_tayang);
        snprintf(tersedia, sizeof(tersedia), "%02d-%02d-%d",
                 jadwal[i].tersedia_sampai.tm_mday,
                 jadwal[i].tersedia_sampai.tm_mon,
                 jadwal[i].tersedia_sampai.tm_year);

        // Ambil data studio
        int ticketsSold = countTicketsSold(jadwal[i].id);
        int kapasitas = studio ? studio->jumlah_kursi : 0;

        // Ambil data bioskop
        const char *bioskopNama = bioskop ? bioskop->nama : "Tidak Ditemukan";
        const char *bioskopAlamat = bioskop ? bioskop->alamat : "Tidak Ditemukan";

        // Tampilkan baris
        if (selection == i + 1)
        {
            printf(BLUE BOLD "[ * ]| %-*d | %-*d | %-*d/%-*d | %-*d | %-*s | %-*s | %-*s | %-*s | %-*s |\n" RESET,
                   idWidth, jadwal[i].id,
                   studioWidth, jadwal[i].studio_id,
                   soldWidth / 2, ticketsSold, soldWidth / 2 + 1, kapasitas,
                   filmWidth, jadwal[i].film_id,
                   waktuWidth, waktuAwal,
                   waktuWidth, waktuAkhir,
                   tersediaWidth, tersedia,
                   bioskopNamaWidth, bioskopNama,
                   bioskopAlamatWidth, bioskopAlamat);
        }
        else
        {
            printf("[   ]| %-*d | %-*d | %-*d/%-*d | %-*d | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
                   idWidth, jadwal[i].id,
                   studioWidth, jadwal[i].studio_id,
                   soldWidth / 2, ticketsSold, soldWidth / 2 + 1, kapasitas,
                   filmWidth, jadwal[i].film_id,
                   waktuWidth, waktuAwal,
                   waktuWidth, waktuAkhir,
                   tersediaWidth, tersedia,
                   bioskopNamaWidth, bioskopNama,
                   bioskopAlamatWidth, bioskopAlamat);
        }

        // Bebaskan memori
        if (bioskop)
            free(bioskop);
        if (studio)
            free(studio);
    }

    // Cetak garis bawah tabel
    for (int i = 0; i < tableWidth; i++)
        printf("=");
    printf("\n");

    // Informasi halaman
    printf("Page %d of %d\n", page, (count + perPage - 1) / perPage);
}

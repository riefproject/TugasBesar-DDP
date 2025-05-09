#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "display.h"
#include "studio.h"
#include "film.h"
#include "jadwal.h"
#include "auth.h"
#include "transaksi.h"
#include "client.h"

int clientMenuTransaksi()
{
    Transaksi *transaksis;
    int count = clientLoadTransaksi(&transaksis);

    if (count < 0)
    {
        printf(RED "Gagal memuat data transaksi.\n" RESET);
        return -1;
    }

    int page = 1, perPage = 10, selection = 1, pointer = 1;
    int command;

    while (1)
    {
        system("cls");
        selection = (page - 1) * perPage + pointer;

        printf(GREEN "====================================================\n");
        printf("             Menu Management Transaksi              \n");
        printf("====================================================\n" RESET);

        printTransaksiTable(transaksis, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page");
        printf(BG_RED WHITE "[E] Exit" RESET "\n" RESET);

        command = getch();

        if (command == 224)
        {
            command = getch();

            if (command == 77) // Arrow Right
            {
                pointer = 1;
                if (page * perPage < count)
                    page++;
                else
                {
                    printf(BLUE "Sudah di halaman terakhir.\n" RESET);
                    sleep(1);
                }
            }
            else if (command == 75) // Arrow Left
            {
                pointer = 1;
                if (page > 1)
                    page--;
                else
                {
                    printf(BLUE "Sudah di halaman pertama.\n" RESET);
                    sleep(1);
                }
            }
            else if (command == 72) // Arrow Up
            {
                if (pointer > 1)
                {
                    pointer--;
                }
            }
            else if (command == 80) // Arrow Down
            {
                if (pointer < perPage && (page - 1) * perPage + pointer < count)
                {
                    pointer++;
                }
            }
        }
        else if (command == 'E' || command == 'e') // Exit
        {
            return 0;
        }
        else
        {
            printf(YELLOW BOLD "Perintah tidak ditemukan\n" RESET);
            sleep(1);
        }
    }
}

int clientTransaksi()
{
    int filmID = 0;
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
        printf("[Arrow /\\] | [Arrow \\/] Arrow Up/Down To Selecting\n");
        printf(GREEN "[ENTER]: Enter To Select Studio" RESET " | " BG_RED WHITE "[E] Exit" RESET "\n" RESET RESET);

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
            filmID = films[selection - 1].id;
            free(films);
            break;
        }
        else if (command == 'E' || command == 'e') // Exit
        {
            printf(YELLOW BOLD "Keluar ...\n" RESET);
            sleep(2);
            return 0;
        }
        else
        {
            printf(YELLOW BOLD "Perintah tidak ditemukan\n" RESET);
            sleep(1);
        }
    }

    int jadwalID = 0;
    int studioID = 0;
    Jadwal *jadwals;
    count = loadJadwalIsHasFilmId(&jadwals, filmID);

    page = 1;
    perPage = 10;
    selection = 1;
    pointer = 1;

    while (1)
    {
        system("cls");
        selection = (page - 1) * perPage + pointer;

        printJadwalTableFull(jadwals, count, page, perPage, selection);

        printf("[Arrow >] Next Page | [Arrow <] Previous Page");
        printf("[Arrow /\\] | [Arrow \\/] Arrow Up/Down To Selecting\n");
        printf(GREEN "[ENTER]: Enter To Select Studio" RESET " | " BG_RED WHITE "[E] Exit" RESET "\n" RESET RESET);

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
        else if (command == 13)
        {
            jadwalID = jadwals[selection - 1].id;
            studioID = jadwals[selection - 1].studio_id;
            free(jadwals);
            break;
        }
        else if (command == 'E' || command == 'e') // Exit
        {
            printf(YELLOW BOLD "Keluar ...\n" RESET);
            sleep(2);
            return 0;
        }
        else
        {
            printf(YELLOW BOLD "Perintah tidak ditemukan\n" RESET);
            sleep(1);
        }
    }

    Studio *studio = findStudioById(studioID);
    int additionalFee = 0;
    if (studio != NULL)
    {
        additionalFee = studio->additionalFee;
    }

    int harga = jadwals[selection - 1].harga_tiket + additionalFee;
    int bayar, kembali;

    while (1)
    {
        printf("Harga tiket: %d\n", harga);

        printf("Masukkan jumlah uang yang dibayarkan: ");
        scanf("%d", &bayar);

        if (bayar < harga)
        {
            printf("Uang yang dibayarkan tidak cukup. Silakan coba lagi.\n\n");
        }
        else
        {
            kembali = bayar - harga;
            break;
        }
    }

    // Tampilkan rincian transaksi
    printf("\n========== Rincian Transaksi ==========\n");
    printf("Harga Tiket : %d\n", harga);
    printf("Bayar       : %d\n", bayar);
    printf("Kembali     : %d\n", kembali);
    printf("========================================\n");

    printf(BLUE "Mempreoses transaksi...\n" RESET);
    sleep(5);

    // Buat transaksi baru
    Transaksi *trans = createTransaksi(getCurrentUser()->id, jadwalID, harga, bayar, ONLINE);

    if (trans)
    {
        printf(GREEN "Transaksi berhasil disimpan!\n");
        printf("ID Transaksi: %d\n" RESET, trans->id);
        sleep(2);
    }
    else
    {
        printf(RED "Gagal menyimpan transaksi.\n" RESET);
        sleep(2);
    }
}

int loadJadwalIsHasFilmId(Jadwal **jadwals, int film_id)
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
        return 0;
    }

    *jadwals = (Jadwal *)malloc(count * sizeof(Jadwal));
    if (*jadwals == NULL)
    {
        printf("Gagal mengalokasi memori.\n");
        fclose(file);
        return -1;
    }

    // Ambil tanggal hari ini
    time_t now = time(NULL);
    struct tm *today = localtime(&now);

    int i = 0;
    Jadwal temp;

    while (fscanf(file, JADWAL_GETTER_FORMAT,
                  &temp.id,
                  &temp.studio_id,
                  &temp.film_id,
                  &temp.waktu_awal_tayang.tm_hour,
                  &temp.waktu_awal_tayang.tm_min,
                  &temp.waktu_akhir_tayang.tm_hour,
                  &temp.waktu_akhir_tayang.tm_min,
                  &temp.tersedia_sampai.tm_year,
                  &temp.tersedia_sampai.tm_mon,
                  &temp.tersedia_sampai.tm_mday,
                  &temp.harga_tiket) == 11)
    {
        // Sesuaikan tahun dan bulan (data .tm_year dimulai dari 1900, .tm_mon dari 0)
        if (temp.tersedia_sampai.tm_year >= (today->tm_year + 1900) &&
            temp.tersedia_sampai.tm_mon >= (today->tm_mon + 1) &&
            temp.tersedia_sampai.tm_mday >= today->tm_mday &&
            temp.film_id == film_id)
        {
            (*jadwals)[i] = temp;
            i++;
        }
    }

    fclose(file);

    if (i == 0)
    {
        free(*jadwals);
        *jadwals = NULL;
    }

    return i;
}

int clientLoadTransaksi(Transaksi **transaksis)
{
    FILE *file = fopen(TRANSAKSI_DATABASE_NAME, "r");
    if (!file)
    {
        printf("File gagal dibuka.\n");
        return -1;
    }

    int totalTransaksiCount = countTransaksiData();
    if (totalTransaksiCount <= 0)
    {
        fclose(file);
        return totalTransaksiCount;
    }

    // Ambil user saat ini
    User *currentUser = getCurrentUser();
    if (!currentUser)
    {
        printf("User saat ini tidak valid.\n");
        fclose(file);
        return -1;
    }

    // Hitung jumlah transaksi yang sesuai user_id
    Transaksi temp;
    int validTransaksiCount = 0;
    while (fscanf(file, TRANSAKSI_GETTER_FORMAT,
                  &temp.id,
                  &temp.user_id,
                  &temp.jadwal_id,
                  &temp.harga,
                  &temp.bayar,
                  &temp.kembali,
                  (int *)&temp.jenisPembelian) != EOF)
    {
        if (temp.user_id == currentUser->id)
        {
            validTransaksiCount++;
        }
    }

    // Reset posisi file pointer untuk membaca ulang
    rewind(file);

    if (validTransaksiCount == 0)
    {
        fclose(file);
        return 0;
    }

    // Alokasikan memori untuk transaksi yang valid
    *transaksis = (Transaksi *)malloc(validTransaksiCount * sizeof(Transaksi));
    if (*transaksis == NULL)
    {
        printf("Gagal mengalokasi memori.\n");
        fclose(file);
        return -1;
    }

    // Membaca dan menyimpan transaksi yang valid
    int i = 0;
    while (fscanf(file, TRANSAKSI_GETTER_FORMAT,
                  &temp.id,
                  &temp.user_id,
                  &temp.jadwal_id,
                  &temp.harga,
                  &temp.bayar,
                  &temp.kembali,
                  (int *)&temp.jenisPembelian) != EOF)
    {
        if (temp.user_id == currentUser->id)
        {
            (*transaksis)[i] = temp;
            i++;
        }
    }

    fclose(file);
    return validTransaksiCount;
}

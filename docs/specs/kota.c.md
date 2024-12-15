<style>
    body{
        font-family:"Times New Roman";
        font-size: 11pt;
        color: black;
        margin: 0;
    }
    code,
    pre code{
        font-family: "Courier New";
        font-size:10pt;
        color: black;
    }
    table,
    tr,
    td,
    th{
        border: 1pt solid black;
    }
    h3{
        font-size:12pt;
    }
</style>

| Nama Modul               | Menu Kota                                                                                     |
| ------------------------ | --------------------------------------------------------------------------------------------- |
| Deskripsi                | Menampilkan daftar kota dengan navigasi untuk membuat, memperbarui, atau menghapus data kota. |
| I.S                      | Data kota tersedia di database.                                                               |
| F.S                      | Pengguna dapat membuat, memperbarui, atau menghapus data kota.                                |
| Modul yang Dipanggil     | loadKota, printKotaTable, createKotaMenu, updateKotaMenu, deleteKota.                         |
| Modul Pemanggil          | Menu utama aplikasi.                                                                          |
| Parameter Input/Keluaran | Input: Tidak ada. Output: Tidak ada.                                                          |

```
MODUL menuKota ()
DEKLARASI
    kotaList: POINTER TO Kota;
    count, page, perPage, selection, pointer, command: integer;
ALGORITMA
    count <- loadKota(&kotaList);
    page <- 1; perPage <- 10; pointer <- 1;

    WHILE TRUE DO
        CLEAR_SCREEN();
        selection <- (page - 1) * perPage + pointer;

        PRINT_HEADER("Menu Management Kota");
        printKotaTable(kotaList, count, page, perPage, selection);
        PRINT_NAVIGATION_MENU();

        command <- getch();
        IF command = 224 THEN
            command <- getch();
            HANDLE_ARROW_KEYS(command, page, perPage, pointer, count);
        ELSE IF command = 'C' OR command = 'c' THEN
            createKotaMenu();
            free(kotaList);
            count <- loadKota(&kotaList);
        ELSE IF command = 'U' OR command = 'u' THEN
            updateKotaMenu(kotaList[selection - 1]);
            free(kotaList);
            count <- loadKota(&kotaList);
        ELSE IF command = 'D' OR command = 'd' THEN
            deleteKota(kotaList[selection - 1]);
            free(kotaList);
            count <- loadKota(&kotaList);
        ELSE IF command = 'E' OR command = 'e' THEN
            free(kotaList);
            RETURN;
        ELSE
            PRINT_INVALID_COMMAND();
        ENDIF
    ENDWHILE
END MODUL
```

| Nama Modul               | Create Kota Menu                                                 |
| ------------------------ | ---------------------------------------------------------------- |
| Deskripsi                | Menu untuk menambahkan data kota baru, termasuk input nama kota. |
| I.S                      | Tidak ada input kota baru.                                       |
| F.S                      | Data kota baru berhasil ditambahkan ke database.                 |
| Modul yang Dipanggil     | createKota.                                                      |
| Modul Pemanggil          | menuKota.                                                        |
| Parameter Input/Keluaran | Input: Tidak ada. Output: Tidak ada.                             |

```
MODUL createKotaMenu ()
DEKLARASI
    nama: array [1..MAX_KOTA_NAME] OF char;
    newKota: POINTER TO Kota;
ALGORITMA
    CLEAR_SCREEN();
    PRINT_HEADER("Menu Tambah Kota");

    WHILE TRUE DO
        PRINT "Masukkan nama kota\t: ";
        READ_LINE(nama);

        IF nama = "" THEN
            PRINT_ERROR("Nama kota tidak boleh kosong.");
            CONTINUE;
        ENDIF

        BREAK;
    ENDWHILE

    newKota <- createKota(nama);
    IF newKota = NULL THEN
        PRINT_ERROR("Gagal menambah kota.");
        RETURN;
    ENDIF

    PRINT_SUCCESS("Berhasil menambah kota!");
    free(newKota);
END MODUL
```

| Nama Modul               | Update Kota Menu                                                          |
| ------------------------ | ------------------------------------------------------------------------- |
| Deskripsi                | Menu untuk memperbarui data kota yang ada, termasuk input nama kota baru. |
| I.S                      | Data kota tersedia untuk diperbarui.                                      |
| F.S                      | Data kota yang diperbarui berhasil disimpan ke database.                  |
| Modul yang Dipanggil     | updateKota.                                                               |
| Modul Pemanggil          | menuKota.                                                                 |
| Parameter Input/Keluaran | Input: Kota yang akan diperbarui. Output: Tidak ada.                      |

```
MODUL updateKotaMenu (Input: kota: Kota)
DEKLARASI
    nama: array [1..MAX_KOTA_NAME] OF char;
    updatedKota: POINTER TO Kota;
ALGORITMA
    PRINT_HEADER("Menu Edit Kota");

    WHILE TRUE DO
        PRINT "Masukkan nama kota\t: ";
        READ_LINE(nama);

        IF nama = "" THEN
            PRINT_ERROR("Nama kota tidak boleh kosong.");
            CONTINUE;
        ENDIF

        BREAK;
    ENDWHILE

    updatedKota <- updateKota(kota.id, nama);
    IF updatedKota = NULL THEN
        PRINT_ERROR("Gagal mengubah kota.");
        RETURN;
    ENDIF

    PRINT_SUCCESS("Berhasil mengubah kota!");
    free(updatedKota);
END MODUL
```

| Nama Modul               | Case Insensitive Compare                                            |
| ------------------------ | ------------------------------------------------------------------- |
| Deskripsi                | Membandingkan dua string tanpa memperhatikan huruf besar dan kecil. |
| I.S                      | Dua string diberikan.                                               |
| F.S                      | Mengembalikan 1 jika string sama, 0 jika berbeda.                   |
| Modul yang Dipanggil     | Tidak ada.                                                          |
| Modul Pemanggil          | Fungsi lain yang membutuhkan perbandingan case-insensitive string.  |
| Parameter Input/Keluaran | Input: str1 (string), str2 (string). Output: Integer (1 atau 0).    |

```
MODUL caseInsensitiveCompare (Input: str1: string, str2: string; Output: result: integer)
DEKLARASI
    result: integer;
ALGORITMA
    WHILE *str1 != '\0' AND *str2 != '\0' DO
        IF tolower((unsigned char) *str1) != tolower((unsigned char) *str2) THEN
            RETURN 0;
        ENDIF
        str1 <- str1 + 1;
        str2 <- str2 + 1;
    ENDWHILE

    RETURN (*str1 = '\0' AND *str2 = '\0');
END MODUL
```

| Nama Modul               | Find Kota by ID                                                                            |
| ------------------------ | ------------------------------------------------------------------------------------------ |
| Deskripsi                | Mencari data kota berdasarkan ID yang diberikan.                                           |
| I.S                      | ID kota diberikan.                                                                         |
| F.S                      | Data kota ditemukan dan dikembalikan dalam bentuk pointer, atau NULL jika tidak ditemukan. |
| Modul yang Dipanggil     | Tidak ada.                                                                                 |
| Modul Pemanggil          | Modul lain yang memerlukan pencarian kota berdasarkan ID.                                  |
| Parameter Input/Keluaran | Input: id (integer). Output: Pointer ke Kota atau NULL.                                    |

```
MODUL findKotaByID (Input: id: integer; Output: kota: POINTER TO Kota)
DEKLARASI
    file: FILE POINTER;
    kota: POINTER TO Kota;
ALGORITMA
    file <- fopen(KOTA_DATABASE_NAME, "r");
    IF file = NULL THEN
        RETURN NULL;
    ENDIF

    kota <- malloc(sizeof(Kota));
    IF kota = NULL THEN
        fclose(file);
        RETURN NULL;
    ENDIF

    WHILE fscanf(file, "%d,%[^"]", &kota->id, kota->nama) = 2 DO
        IF kota->id = id THEN
            fclose(file);
            RETURN kota;
        ENDIF
    ENDWHILE

    fclose(file);
    free(kota);
    RETURN NULL;
END MODUL
```

| Nama Modul               | Find Kota by Name                                                                          |
| ------------------------ | ------------------------------------------------------------------------------------------ |
| Deskripsi                | Mencari data kota berdasarkan nama kota yang diberikan.                                    |
| I.S                      | Nama kota diberikan.                                                                       |
| F.S                      | Data kota ditemukan dan dikembalikan dalam bentuk pointer, atau NULL jika tidak ditemukan. |
| Modul yang Dipanggil     | Tidak ada.                                                                                 |
| Modul Pemanggil          | Modul lain yang memerlukan pencarian kota berdasarkan nama.                                |
| Parameter Input/Keluaran | Input: nama (string). Output: Pointer ke Kota atau NULL.                                   |

```
MODUL findKotaByName (Input: nama: string; Output: kota: POINTER TO Kota)
DEKLARASI
    file: FILE POINTER;
    kota: POINTER TO Kota;
ALGORITMA
    file <- fopen(KOTA_DATABASE_NAME, "r");
    IF file = NULL THEN
        RETURN NULL;
    ENDIF

    kota <- malloc(sizeof(Kota));
    IF kota = NULL THEN
        fclose(file);
        RETURN NULL;
    ENDIF

    WHILE fscanf(file, "%d,%[^"]", &kota->id, kota->nama) = 2 DO
        IF strcmp(kota->nama, nama) = 0 THEN
            fclose(file);
            RETURN kota;
        ENDIF
    ENDWHILE

    fclose(file);
    free(kota);
    RETURN NULL;
END MODUL
```

| Nama Modul               | Create Kota                                                              |
| ------------------------ | ------------------------------------------------------------------------ |
| Deskripsi                | Membuat data kota baru berdasarkan input pengguna.                       |
| I.S                      | Tidak ada data kota baru yang ditambahkan.                               |
| F.S                      | Data kota baru berhasil disimpan ke database.                            |
| Modul yang Dipanggil     | Tidak ada.                                                               |
| Modul Pemanggil          | Modul lain yang memerlukan penambahan data kota.                         |
| Parameter Input/Keluaran | Input: nama (string). Output: Pointer ke Kota baru atau NULL jika gagal. |

```
MODUL createKota (Input: nama: string; Output: kota: POINTER TO Kota)
DEKLARASI
    kota: POINTER TO Kota;
    file: FILE POINTER;
    id: integer;
ALGORITMA
    kota <- malloc(sizeof(Kota));
    IF kota = NULL THEN
        PRINT("Alokasi memori gagal.");
        RETURN NULL;
    ENDIF

    strncpy(kota->nama, nama, MAX_KOTA_NAME);
    kota->nama[MAX_KOTA_NAME - 1] <- '\0';

    file <- fopen(KOTA_DATABASE_NAME, "a");
    IF file = NULL THEN
        free(kota);
        PRINT("Gagal membuka file.");
        RETURN NULL;
    ENDIF

    id <- getLastAvailableID(KOTA_DATABASE_NAME);
    kota->id <- id;

    fprintf(file, KOTA_SETTER_FORMAT,
            kota->id,
            kota->nama);

    fclose(file);
    RETURN kota;
END MODUL
```

| Nama Modul               | Update Kota                                                                                       |
| ------------------------ | ------------------------------------------------------------------------------------------------- |
| Deskripsi                | Memperbarui data kota yang ada dengan input baru.                                                 |
| I.S                      | Data kota tersedia di database.                                                                   |
| F.S                      | Data kota diperbarui sesuai dengan input baru.                                                    |
| Modul yang Dipanggil     | Tidak ada.                                                                                        |
| Modul Pemanggil          | Modul lain yang memerlukan pembaruan data kota.                                                   |
| Parameter Input/Keluaran | Input: id (integer), nama (string). Output: Pointer ke Kota yang diperbarui atau NULL jika gagal. |

```
MODUL updateKota (Input: id: integer, nama: string; Output: updatedKota: POINTER TO Kota)
DEKLARASI
    updatedKota: POINTER TO Kota;
    fromFile, toFile: FILE POINTER;
    kotaList: array OF Kota;
    count, i: integer;
ALGORITMA
    updatedKota <- malloc(sizeof(Kota));
    IF updatedKota = NULL THEN
        PRINT("Alokasi memori gagal.");
        RETURN NULL;
    ENDIF

    strncpy(updatedKota->nama, nama, MAX_KOTA_NAME);
    updatedKota->id <- id;

    fromFile <- fopen(KOTA_DATABASE_NAME, "r");
    IF fromFile = NULL THEN
        free(updatedKota);
        RETURN NULL;
    ENDIF

    count <- countKotaData();
    IF count = -1 THEN
        fclose(fromFile);
        RETURN NULL;
    ENDIF

    FOR i <- 0 TO count - 1 DO
        IF kotaList[i].id = id THEN
            kotaList[i] <- *updatedKota;
        ENDIF
    ENDFOR
    fclose(fromFile);

    toFile <- fopen(KOTA_DATABASE_NAME, "w");
    IF toFile = NULL THEN
        free(updatedKota);
        RETURN NULL;
    ENDIF

    FOR i <- 0 TO count - 1 DO
        fprintf(toFile, KOTA_SETTER_FORMAT,
                kotaList[i].id,
                kotaList[i].nama);
    ENDFOR
    fclose(toFile);

    RETURN updatedKota;
END MODUL
```

| Nama Modul               | Delete Kota                                                                  |
| ------------------------ | ---------------------------------------------------------------------------- |
| Deskripsi                | Menghapus data kota dari database berdasarkan ID kota.                       |
| I.S                      | Data kota tersedia di database.                                              |
| F.S                      | Data kota berhasil dihapus dari database.                                    |
| Modul yang Dipanggil     | Tidak ada.                                                                   |
| Modul Pemanggil          | Modul lain yang memerlukan penghapusan data kota.                            |
| Parameter Input/Keluaran | Input: kota (struct Kota). Output: Integer (1 jika berhasil, -1 jika gagal). |

```
MODUL deleteKota (Input: kota: Kota; Output: result: integer)
DEKLARASI
    fromFile, toFile: FILE POINTER;
    kotaList: array OF Kota;
    count, i, j: integer;
ALGORITMA
    fromFile <- fopen(KOTA_DATABASE_NAME, "r");
    IF fromFile = NULL THEN
        PRINT("Gagal membuka file.");
        RETURN -1;
    ENDIF

    count <- countKotaData();
    IF count = -1 THEN
        fclose(fromFile);
        RETURN -1;
    ENDIF

    j <- 0;
    FOR i <- 0 TO count - 1 DO
        IF kotaList[i].id != kota.id THEN
            kotaList[j] <- kotaList[i];
            j <- j + 1;
        ENDIF
    ENDFOR
    fclose(fromFile);

    toFile <- fopen(KOTA_DATABASE_NAME, "w");
    IF toFile = NULL THEN
        RETURN -1;
    ENDIF

    FOR i <- 0 TO j - 1 DO
        fprintf(toFile, KOTA_SETTER_FORMAT,
                kotaList[i].id,
                kotaList[i].nama);
    ENDFOR
    fclose(toFile);

    RETURN 1;
END MODUL
```

| Nama Modul               | Count Kota Data                                                      |
| ------------------------ | -------------------------------------------------------------------- |
| Deskripsi                | Menghitung jumlah data kota yang ada dalam database.                 |
| I.S                      | Database kota tersedia.                                              |
| F.S                      | Jumlah data kota dihitung dan dikembalikan.                          |
| Modul yang Dipanggil     | Tidak ada.                                                           |
| Modul Pemanggil          | Modul lain yang memerlukan informasi jumlah data kota.               |
| Parameter Input/Keluaran | Input: Tidak ada. Output: Integer (jumlah data kota, -1 jika gagal). |

```
MODUL countKotaData ()
DEKLARASI
    file: FILE POINTER;
    kota: Kota;
    count: integer;
ALGORITMA
    file <- fopen(KOTA_DATABASE_NAME, "r");
    IF file = NULL THEN
        PRINT("File gagal dibuka.");
        RETURN -1;
    ENDIF

    count <- 0;
    WHILE fscanf(file, KOTA_GETTER_FORMAT, &kota.id, kota.nama) != EOF DO
        count <- count + 1;
    ENDWHILE

    fclose(file);
    RETURN count;
END MODUL
```

| Nama Modul               | Load Kota                                                                               |
| ------------------------ | --------------------------------------------------------------------------------------- |
| Deskripsi                | Memuat semua data kota dari database ke dalam memori.                                   |
| I.S                      | Database kota tersedia.                                                                 |
| F.S                      | Semua data kota dimuat ke dalam array.                                                  |
| Modul yang Dipanggil     | countKotaData.                                                                          |
| Modul Pemanggil          | Modul lain yang memerlukan data kota.                                                   |
| Parameter Input/Keluaran | Input: Pointer ke array kota. Output: Integer (jumlah data yang dimuat, -1 jika gagal). |

```
MODUL loadKota (Output: kotaList: POINTER TO Kota; Output: count: integer)
DEKLARASI
    file: FILE POINTER;
    count: integer;
    i: integer;
ALGORITMA
    file <- fopen(KOTA_DATABASE_NAME, "r");
    IF file = NULL THEN
        PRINT("File gagal dibuka.");
        RETURN -1;
    ENDIF

    count <- countKotaData();
    kotaList <- malloc(count * sizeof(Kota));
    IF kotaList = NULL THEN
        PRINT("Gagal mengalokasi memori.");
        fclose(file);
        RETURN -1;
    ENDIF

    rewind(file);
    FOR i <- 0 TO count - 1 DO
        fscanf(file, KOTA_GETTER_FORMAT, &kotaList[i].id, kotaList[i].nama);
    ENDFOR

    fclose(file);
    RETURN count;
END MODUL
```

| Nama Modul               | Print Kota Table                                                                                  |
| ------------------------ | ------------------------------------------------------------------------------------------------- |
| Deskripsi                | Menampilkan data kota dalam bentuk tabel pada terminal.                                           |
| I.S                      | Data kota tersedia di memori.                                                                     |
| F.S                      | Tabel data kota ditampilkan di terminal.                                                          |
| Modul yang Dipanggil     | Tidak ada.                                                                                        |
| Modul Pemanggil          | Modul lain yang membutuhkan tampilan tabel data kota.                                             |
| Parameter Input/Keluaran | Input: Array kota, jumlah data, halaman, jumlah per halaman, pilihan saat ini. Output: Tidak ada. |

```
MODUL printKotaTable (Input: kotaList: POINTER TO Kota, count: integer, page: integer, perPage: integer, selection: integer)
DEKLARASI
    idWidth, namaWidth, start, end, i: integer;
    tableWidth: integer;
ALGORITMA
    idWidth <- 2; namaWidth <- 12;
    start <- (page - 1) * perPage;
    end <- start + perPage;
    IF end > count THEN
        end <- count;
    ENDIF

    FOR i <- start TO end - 1 DO
        idWidth <- MAX(idWidth, LENGTH(TO_STRING(kotaList[i].id)));
        namaWidth <- MAX(namaWidth, LENGTH(kotaList[i].nama));
    ENDFOR

    tableWidth <- LENGTH(FORMAT("[ * ]| %-*s | %-*s |",
                               idWidth, "ID",
                               namaWidth, "Nama Kota"));

    PRINT_HEADER(tableWidth);
    PRINT_ROW(idWidth, namaWidth);
    PRINT_DIVIDER(tableWidth);

    FOR i <- start TO end - 1 DO
        IF selection = i + 1 THEN
            PRINT_SELECTED_ROW(kotaList[i]);
        ELSE
            PRINT_ROW(kotaList[i]);
        ENDIF
    ENDFOR

    PRINT_DIVIDER(tableWidth);
    PRINT_PAGE_INFO(page, count, perPage);
END MODUL
```

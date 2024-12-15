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

### Modul Bioskop

| Nama Modul               | Getter dan Setter Bioskop                                                                                                        |
| ------------------------ | -------------------------------------------------------------------------------------------------------------------------------- |
| Deskripsi                | Modul untuk mengakses (getter) atau mengubah (setter) properti dari objek Bioskop seperti ID, Nama, Kota, Manager, dan Alamat.   |
| I.S                      | Objek Bioskop sudah diinisialisasi.                                                                                              |
| F.S                      | Properti dari objek Bioskop berhasil diakses atau diperbarui.                                                                    |
| Modul yang Dipanggil     | Tidak ada.                                                                                                                       |
| Modul Pemanggil          | Fungsi lain yang memerlukan akses ke properti Bioskop.                                                                           |
| Parameter Input/Keluaran | Input: Objek Bioskop dan properti yang diakses atau diubah. Output: Nilai properti (getter) atau objek yang diperbarui (setter). |

```
MODUL getBioskopId (Input: bioskop: POINTER TO Bioskop; Output: id: integer)
ALGORITMA
    RETURN bioskop->id;
END MODUL

MODUL setBioskopId (Input: bioskop: POINTER TO Bioskop, id: integer)
ALGORITMA
    bioskop->id <- id;
END MODUL

MODUL getBioskopNama (Input: bioskop: POINTER TO Bioskop; Output: nama: string)
ALGORITMA
    RETURN bioskop->nama;
END MODUL

MODUL setBioskopNama (Input: bioskop: POINTER TO Bioskop, nama: string)
ALGORITMA
    strncpy(bioskop->nama, nama, MAX_BIOSKOP_NAME - 1);
    bioskop->nama[MAX_BIOSKOP_NAME - 1] <- '\0';
END MODUL

MODUL getBioskopKota (Input: bioskop: POINTER TO Bioskop; Output: kota: string)
ALGORITMA
    kota <- findKotaByID(bioskop->kota_id);
    RETURN kota->nama;
END MODUL

MODUL setBioskopKotaId (Input: bioskop: POINTER TO Bioskop, kota_id: integer)
ALGORITMA
    bioskop->kota_id <- kota_id;
END MODUL
```

| Nama Modul               | Menu Bioskop                                                                                        |
| ------------------------ | --------------------------------------------------------------------------------------------------- |
| Deskripsi                | Menampilkan daftar bioskop dengan navigasi untuk membuat, memperbarui, atau menghapus data bioskop. |
| I.S                      | Data bioskop tersedia di database.                                                                  |
| F.S                      | Pengguna dapat membuat, memperbarui, atau menghapus data bioskop.                                   |
| Modul yang Dipanggil     | loadBioskop, printBioskopTable, createBioskopMenu, updateBioskopMenu, deleteBioskop.                |
| Modul Pemanggil          | Menu utama aplikasi.                                                                                |
| Parameter Input/Keluaran | Input: Tidak ada. Output: Tidak ada.                                                                |

```
MODUL menuBioskop ()
DEKLARASI
    bioskops: POINTER TO Bioskop;
    count, page, perPage, selection, pointer, command: integer;
ALGORITMA
    count <- loadBioskop(&bioskops);
    page <- 1; perPage <- 10; pointer <- 1;

    WHILE TRUE DO
        system("cls");
        selection <- (page - 1) * perPage + pointer;

        PRINT_HEADER();
        printBioskopTable(bioskops, count, page, perPage, selection);
        PRINT_NAVIGATION_MENU();

        command <- getch();
        IF command = 224 THEN
            command <- getch();
            HANDLE_ARROW_KEYS(command, page, perPage, pointer, count);
        ELSE IF command = 'C' OR command = 'c' THEN
            createBioskopMenu();
            free(bioskops);
            count <- loadBioskop(&bioskops);
        ELSE IF command = 'U' OR command = 'u' THEN
            updateBioskopMenu(bioskops[selection - 1]);
            free(bioskops);
            count <- loadBioskop(&bioskops);
        ELSE IF command = 'D' OR command = 'd' THEN
            deleteBioskop(bioskops[selection - 1]);
            free(bioskops);
            count <- loadBioskop(&bioskops);
        ELSE IF command = 'E' OR command = 'e' THEN
            free(bioskops);
            RETURN;
        ELSE
            PRINT_INVALID_COMMAND();
        ENDIF
    ENDWHILE
END MODUL
```

| Nama Modul               | Select Kota                                                          |
| ------------------------ | -------------------------------------------------------------------- |
| Deskripsi                | Menampilkan daftar kota untuk dipilih oleh pengguna dengan navigasi. |
| I.S                      | Data kota tersedia di database.                                      |
| F.S                      | Kota yang dipilih oleh pengguna dikembalikan dalam bentuk ID kota.   |
| Modul yang Dipanggil     | loadKota, printKotaTable.                                            |
| Modul Pemanggil          | createBioskopMenu, updateBioskopMenu.                                |
| Parameter Input/Keluaran | Input: Tidak ada. Output: ID kota yang dipilih.                      |

```
MODUL selectKota ()
DEKLARASI
    kotaList: POINTER TO Kota;
    count, page, perPage, selection, pointer, command, kotaID: integer;
ALGORITMA
    count <- loadKota(&kotaList);
    page <- 1; perPage <- 10; pointer <- 1;

    WHILE TRUE DO
        selection <- (page - 1) * perPage + pointer;

        printKotaTable(kotaList, count, page, perPage, selection);
        PRINT_NAVIGATION_PROMPT();

        command <- getch();
        IF command = 224 THEN
            command <- getch();
            HANDLE_ARROW_KEYS(command, page, perPage, pointer, count);
        ELSE IF command = 13 THEN
            kotaID <- kotaList[selection - 1].id;
            free(kotaList);
            RETURN kotaID;
        ELSE
            PRINT_INVALID_COMMAND();
        ENDIF
    ENDWHILE
END MODUL
```

| Nama Modul               | Select Manager                                                           |
| ------------------------ | ------------------------------------------------------------------------ |
| Deskripsi                | Menampilkan daftar manajer untuk dipilih pengguna.                       |
| I.S                      | Data manajer tersedia di database.                                       |
| F.S                      | Manajer yang dipilih oleh pengguna dikembalikan dalam bentuk ID manajer. |
| Modul yang Dipanggil     | loadUser, filterUserByRole, printUserTable.                              |
| Modul Pemanggil          | createBioskopMenu, updateBioskopMenu.                                    |
| Parameter Input/Keluaran | Input: Tidak ada. Output: ID manajer yang dipilih.                       |

```
MODUL selectManager ()
DEKLARASI
    users: POINTER TO User;
    count, page, perPage, selection, pointer, command, managerID: integer;
ALGORITMA
    count <- loadUser(&users);
    count <- filterUserByRole(&users, MANAGER);
    page <- 1; perPage <- 10; pointer <- 1;

    WHILE TRUE DO
        selection <- (page - 1) * perPage + pointer;

        printUserTable(users, count, page, perPage, selection);
        PRINT_NAVIGATION_PROMPT();

        command <- getch();
        IF command = 224 THEN
            command <- getch();
            HANDLE_ARROW_KEYS(command, page, perPage, pointer, count);
        ELSE IF command = 13 THEN
            managerID <- users[selection - 1].id;
            free(users);
            RETURN managerID;
        ELSE
            PRINT_INVALID_COMMAND();
        ENDIF
    ENDWHILE
END MODUL
```

| Nama Modul               | Create Bioskop Menu                                                                       |
| ------------------------ | ----------------------------------------------------------------------------------------- |
| Deskripsi                | Menu untuk menambahkan data bioskop baru, termasuk input nama, alamat, kota, dan manajer. |
| I.S                      | Tidak ada input bioskop baru.                                                             |
| F.S                      | Data bioskop baru berhasil ditambahkan ke database.                                       |
| Modul yang Dipanggil     | findBioskopByNama, selectKota, selectManager, createBioskop.                              |
| Modul Pemanggil          | menuBioskop.                                                                              |
| Parameter Input/Keluaran | Input: Tidak ada. Output: Tidak ada.                                                      |

```
MODUL createBioskopMenu ()
DEKLARASI
    nama: array [1..MAX_BIOSKOP_NAME] OF char;
    alamat: array [1..MAX_BIOSKOP_ALAMAT] OF char;
    kota_id, manager_id: integer;
    newBioskop: POINTER TO Bioskop;
ALGORITMA
    CLEAR_SCREEN();
    PRINT_HEADER("Menu Tambah Bioskop");

    WHILE TRUE DO
        PRINT "Masukkan nama bioskop: ";
        READ_LINE(nama);
        IF LENGTH(nama) < 3 THEN
            PRINT_ERROR("Nama bioskop harus memiliki minimal 3 karakter.");
            CONTINUE;
        ENDIF

        IF findBioskopByNama(nama) != NULL THEN
            PRINT_ERROR("Nama bioskop sudah terdaftar.");
            CONTINUE;
        ENDIF
        BREAK;
    ENDWHILE

    PRINT "Masukkan alamat bioskop: ";
    READ_LINE(alamat);

    PRINT "Pilih Kota: ";
    kota_id <- selectKota();

    PRINT "Pilih Manager: ";
    manager_id <- selectManager();

    newBioskop <- createBioskop(nama, alamat, kota_id, manager_id);
    IF newBioskop = NULL THEN
        PRINT_ERROR("Gagal menambahkan bioskop baru.");
        RETURN;
    ENDIF

    PRINT_SUCCESS("Berhasil menambah bioskop!");
    free(newBioskop);
END MODUL
```

| Nama Modul               | Update Bioskop Menu                                                                                |
| ------------------------ | -------------------------------------------------------------------------------------------------- |
| Deskripsi                | Menu untuk memperbarui data bioskop yang ada, termasuk input nama, alamat, kota, dan manajer baru. |
| I.S                      | Data bioskop tersedia untuk diperbarui.                                                            |
| F.S                      | Data bioskop yang diperbarui berhasil disimpan ke database.                                        |
| Modul yang Dipanggil     | findBioskopByNama, selectKota, selectManager, updateBioskop.                                       |
| Modul Pemanggil          | menuBioskop.                                                                                       |
| Parameter Input/Keluaran | Input: Bioskop yang akan diperbarui. Output: Tidak ada.                                            |

```
MODUL updateBioskopMenu (Input: bioskop: Bioskop)
DEKLARASI
    nama: array [1..MAX_BIOSKOP_NAME] OF char;
    alamat: array [1..MAX_BIOSKOP_ALAMAT] OF char;
    kota_id, manager_id: integer;
    updatedBioskop: POINTER TO Bioskop;
ALGORITMA
    PRINT_HEADER("Menu Edit Bioskop");

    WHILE TRUE DO
        PRINT "Masukkan nama bioskop: ";
        READ_LINE(nama);
        IF LENGTH(nama) < 3 THEN
            PRINT_ERROR("Nama bioskop harus memiliki minimal 3 karakter.");
            CONTINUE;
        ENDIF

        IF findBioskopByNama(nama) != NULL THEN
            PRINT_ERROR("Nama bioskop sudah terdaftar.");
            CONTINUE;
        ENDIF
        BREAK;
    ENDWHILE

    PRINT "Masukkan alamat bioskop: ";
    READ_LINE(alamat);

    PRINT "Pilih Kota: ";
    kota_id <- selectKota();

    PRINT "Pilih Manager: ";
    manager_id <- selectManager();

    updatedBioskop <- updateBioskop(bioskop.id, nama, alamat, kota_id, manager_id);
    IF updatedBioskop = NULL THEN
        PRINT_ERROR("Gagal memperbarui bioskop.");
        RETURN;
    ENDIF

    PRINT_SUCCESS("Berhasil memperbarui bioskop!");
    free(updatedBioskop);
END MODUL
```

| Nama Modul               | Find Bioskop by Name                                                                          |
| ------------------------ | --------------------------------------------------------------------------------------------- |
| Deskripsi                | Mencari data bioskop berdasarkan nama yang diberikan.                                         |
| I.S                      | Nama bioskop diberikan.                                                                       |
| F.S                      | Data bioskop ditemukan dan dikembalikan dalam bentuk pointer, atau NULL jika tidak ditemukan. |
| Modul yang Dipanggil     | Tidak ada.                                                                                    |
| Modul Pemanggil          | Modul lain yang memerlukan pencarian bioskop berdasarkan nama.                                |
| Parameter Input/Keluaran | Input: nama (string). Output: Pointer ke Bioskop atau NULL.                                   |

```
MODUL findBioskopByNama (Input: nama: string; Output: bioskop: POINTER TO Bioskop)
DEKLARASI
    file: FILE POINTER;
    bioskop: POINTER TO Bioskop;
ALGORITMA
    file <- fopen(BIOSKOP_DATABASE_NAME, "r");
    IF file = NULL THEN
        RETURN NULL;
    ENDIF

    bioskop <- malloc(sizeof(Bioskop));
    IF bioskop = NULL THEN
        fclose(file);
        RETURN NULL;
    ENDIF

    WHILE fscanf(file, "%d,%[^,]", &bioskop->id, bioskop->nama) = 2 DO
        IF strcmp(bioskop->nama, nama) = 0 THEN
            fclose(file);
            RETURN bioskop;
        ENDIF
    ENDWHILE

    fclose(file);
    free(bioskop);
    RETURN NULL;
END MODUL
```

| Nama Modul               | Create Bioskop                                                                                  |
| ------------------------ | ----------------------------------------------------------------------------------------------- |
| Deskripsi                | Membuat data bioskop baru berdasarkan input pengguna.                                           |
| I.S                      | Tidak ada data bioskop baru yang ditambahkan.                                                   |
| F.S                      | Data bioskop baru berhasil disimpan ke database.                                                |
| Modul yang Dipanggil     | setBioskopNama, setBioskopAlamat, setBioskopKotaId, setBioskopId, setBioskopManagerId.          |
| Modul Pemanggil          | Modul lain yang memerlukan penambahan data bioskop.                                             |
| Parameter Input/Keluaran | Input: nama, alamat, kota_id, manager_id. Output: Pointer ke Bioskop baru atau NULL jika gagal. |

```
MODUL createBioskop (Input: nama: string, alamat: string, kota_id: integer, manager_id: integer; Output: bioskop: POINTER TO Bioskop)
DEKLARASI
    bioskop: POINTER TO Bioskop;
    file: FILE POINTER;
ALGORITMA
    bioskop <- malloc(sizeof(Bioskop));
    IF bioskop = NULL THEN
        PRINT("Alokasi memori gagal.");
        RETURN NULL;
    ENDIF

    setBioskopNama(bioskop, nama);
    setBioskopAlamat(bioskop, alamat);
    setBioskopKotaId(bioskop, kota_id);
    setBioskopId(bioskop, getLastAvailableID(BIOSKOP_DATABASE_NAME));
    setBioskopManagerId(bioskop, manager_id);

    file <- fopen(BIOSKOP_DATABASE_NAME, "a");
    IF file = NULL THEN
        PRINT("Gagal membuka file.");
        free(bioskop);
        RETURN NULL;
    ENDIF

    fprintf(file, BIOSKOP_SETTER_FORMAT,
            bioskop->id,
            bioskop->kota_id,
            bioskop->nama,
            bioskop->manager_id,
            bioskop->alamat);
    fclose(file);

    RETURN bioskop;
END MODUL
```

| Nama Modul               | Update Bioskop                                                                                                 |
| ------------------------ | -------------------------------------------------------------------------------------------------------------- |
| Deskripsi                | Memperbarui data bioskop yang ada dengan input baru.                                                           |
| I.S                      | Data bioskop tersedia di database.                                                                             |
| F.S                      | Data bioskop diperbarui sesuai dengan input baru.                                                              |
| Modul yang Dipanggil     | setBioskopNama, setBioskopAlamat, setBioskopKotaId, setBioskopId, setBioskopManagerId.                         |
| Modul Pemanggil          | Modul lain yang memerlukan pembaruan data bioskop.                                                             |
| Parameter Input/Keluaran | Input: id, nama, alamat, kota_id, manager_id. Output: Pointer ke Bioskop yang diperbarui atau NULL jika gagal. |

```
MODUL updateBioskop (Input: id: integer, nama: string, alamat: string, kota_id: integer, manager_id: integer; Output: updatedBioskop: POINTER TO Bioskop)
DEKLARASI
    updatedBioskop: POINTER TO Bioskop;
    fromFile, toFile: FILE POINTER;
    bioskops: array OF Bioskop;
    count, i: integer;
ALGORITMA
    updatedBioskop <- malloc(sizeof(Bioskop));
    IF updatedBioskop = NULL THEN
        PRINT("Alokasi memori gagal.");
        RETURN NULL;
    ENDIF

    setBioskopId(updatedBioskop, id);
    setBioskopNama(updatedBioskop, nama);
    setBioskopAlamat(updatedBioskop, alamat);
    setBioskopKotaId(updatedBioskop, kota_id);
    setBioskopManagerId(updatedBioskop, manager_id);

    fromFile <- fopen(BIOSKOP_DATABASE_NAME, "r");
    IF fromFile = NULL THEN
        PRINT("Gagal membuka file.");
        free(updatedBioskop);
        RETURN NULL;
    ENDIF

    count <- countBioskopData();
    IF count = -1 THEN
        PRINT("Gagal menghitung data.");
        fclose(fromFile);
        free(updatedBioskop);
        RETURN NULL;
    ENDIF

    FOR i <- 0 TO count - 1 DO
        IF bioskops[i].id = id THEN
            bioskops[i] <- *updatedBioskop;
        ENDIF
    ENDFOR
    fclose(fromFile);

    toFile <- fopen(BIOSKOP_DATABASE_NAME, "w");
    IF toFile = NULL THEN
        PRINT("Gagal membuka file untuk menulis.");
        free(updatedBioskop);
        RETURN NULL;
    ENDIF

    FOR i <- 0 TO count - 1 DO
        fprintf(toFile, BIOSKOP_SETTER_FORMAT,
                bioskops[i].id,
                bioskops[i].kota_id,
                bioskops[i].nama,
                bioskops[i].manager_id,
                bioskops[i].alamat);
    ENDFOR
    fclose(toFile);

    RETURN updatedBioskop;
END MODUL
```

| Nama Modul               | Delete Bioskop                                                                     |
| ------------------------ | ---------------------------------------------------------------------------------- |
| Deskripsi                | Menghapus data bioskop dari database berdasarkan ID.                               |
| I.S                      | Data bioskop tersedia di database.                                                 |
| F.S                      | Data bioskop berhasil dihapus dari database.                                       |
| Modul yang Dipanggil     | Tidak ada.                                                                         |
| Modul Pemanggil          | Modul lain yang memerlukan penghapusan data bioskop.                               |
| Parameter Input/Keluaran | Input: bioskop (struct Bioskop). Output: Integer (1 jika berhasil, -1 jika gagal). |

```
MODUL deleteBioskop (Input: bioskop: Bioskop; Output: result: integer)
DEKLARASI
    fromFile, toFile: FILE POINTER;
    bioskops: array OF Bioskop;
    count, i, j: integer;
ALGORITMA
    fromFile <- fopen(BIOSKOP_DATABASE_NAME, "r");
    IF fromFile = NULL THEN
        PRINT("Gagal membuka file.");
        RETURN -1;
    ENDIF

    count <- countBioskopData();
    IF count = -1 THEN
        PRINT("Gagal menghitung data.");
        fclose(fromFile);
        RETURN -1;
    ENDIF

    j <- 0;
    FOR i <- 0 TO count - 1 DO
        IF bioskops[i].id != bioskop.id THEN
            bioskops[j] <- bioskops[i];
            j <- j + 1;
        ENDIF
    ENDFOR
    fclose(fromFile);

    toFile <- fopen(BIOSKOP_DATABASE_NAME, "w");
    IF toFile = NULL THEN
        PRINT("Gagal membuka file untuk menulis.");
        RETURN -1;
    ENDIF

    FOR i <- 0 TO j - 1 DO
        fprintf(toFile, BIOSKOP_SETTER_FORMAT,
                bioskops[i].id,
                bioskops[i].kota_id,
                bioskops[i].nama,
                bioskops[i].manager_id,
                bioskops[i].alamat);
    ENDFOR
    fclose(toFile);

    RETURN 1;
END MODUL
```

| Nama Modul               | Count Bioskop Data                                                      |
| ------------------------ | ----------------------------------------------------------------------- |
| Deskripsi                | Menghitung jumlah data bioskop yang ada dalam database.                 |
| I.S                      | Database bioskop tersedia.                                              |
| F.S                      | Jumlah data bioskop dihitung dan dikembalikan.                          |
| Modul yang Dipanggil     | Tidak ada.                                                              |
| Modul Pemanggil          | Modul lain yang memerlukan informasi jumlah data bioskop.               |
| Parameter Input/Keluaran | Input: Tidak ada. Output: Integer (jumlah data bioskop, -1 jika gagal). |

```
MODUL countBioskopData ()
DEKLARASI
    file: FILE POINTER;
    bioskop: Bioskop;
    count: integer;
ALGORITMA
    file <- fopen(BIOSKOP_DATABASE_NAME, "r");
    IF file = NULL THEN
        PRINT("File gagal dibuka.");
        RETURN -1;
    ENDIF

    count <- 0;
    WHILE fscanf(file, BIOSKOP_GETTER_FORMAT,
                 &bioskop.id,
                 &bioskop.kota_id,
                 bioskop.nama,
                 &bioskop.manager_id,
                 bioskop.alamat) != EOF DO
        count <- count + 1;
    ENDWHILE

    fclose(file);
    RETURN count;
END MODUL
```

| Nama Modul               | Load Bioskop                                                                               |
| ------------------------ | ------------------------------------------------------------------------------------------ |
| Deskripsi                | Memuat semua data bioskop dari database ke dalam memori.                                   |
| I.S                      | Database bioskop tersedia.                                                                 |
| F.S                      | Semua data bioskop dimuat ke dalam array.                                                  |
| Modul yang Dipanggil     | countBioskopData.                                                                          |
| Modul Pemanggil          | Modul lain yang memerlukan data bioskop.                                                   |
| Parameter Input/Keluaran | Input: Pointer ke array bioskop. Output: Integer (jumlah data yang dimuat, -1 jika gagal). |

```
MODUL loadBioskop (Output: bioskops: POINTER TO Bioskop; Output: count: integer)
DEKLARASI
    file: FILE POINTER;
    count: integer;
    i: integer;
ALGORITMA
    file <- fopen(BIOSKOP_DATABASE_NAME, "r");
    IF file = NULL THEN
        PRINT("File gagal dibuka.");
        RETURN -1;
    ENDIF

    count <- countBioskopData();
    bioskops <- malloc(count * sizeof(Bioskop));
    IF bioskops = NULL THEN
        PRINT("Gagal mengalokasi memori.");
        fclose(file);
        RETURN -1;
    ENDIF

    rewind(file);
    FOR i <- 0 TO count - 1 DO
        fscanf(file, BIOSKOP_GETTER_FORMAT,
               &bioskops[i].id,
               &bioskops[i].kota_id,
               bioskops[i].nama,
               &bioskops[i].manager_id,
               bioskops[i].alamat);
    ENDFOR

    fclose(file);
    RETURN count;
END MODUL
```

| Nama Modul               | Print Bioskop Table                                                                                  |
| ------------------------ | ---------------------------------------------------------------------------------------------------- |
| Deskripsi                | Menampilkan data bioskop dalam bentuk tabel pada terminal.                                           |
| I.S                      | Data bioskop tersedia di memori.                                                                     |
| F.S                      | Tabel data bioskop ditampilkan di terminal.                                                          |
| Modul yang Dipanggil     | getBioskopManager, getBioskopKota.                                                                   |
| Modul Pemanggil          | Modul lain yang membutuhkan tampilan tabel data bioskop.                                             |
| Parameter Input/Keluaran | Input: Array bioskop, jumlah data, halaman, jumlah per halaman, pilihan saat ini. Output: Tidak ada. |

```
MODUL printBioskopTable (Input: bioskops: POINTER TO Bioskop, count: integer, page: integer, perPage: integer, selection: integer)
DEKLARASI
    idWidth, kotaWidth, namaWidth, managerWidth, start, end, i: integer;
    tableWidth: integer;
ALGORITMA
    idWidth <- 2; kotaWidth <- 7; namaWidth <- 12; managerWidth <- 7;
    start <- (page - 1) * perPage;
    end <- start + perPage;
    IF end > count THEN
        end <- count;
    ENDIF

    FOR i <- start TO end - 1 DO
        idWidth <- MAX(idWidth, LENGTH(TO_STRING(bioskops[i].id)));
        kotaWidth <- MAX(kotaWidth, LENGTH(getBioskopKota(&bioskops[i])));
        namaWidth <- MAX(namaWidth, LENGTH(bioskops[i].nama));
        managerWidth <- MAX(managerWidth, LENGTH(getBioskopManager(&bioskops[i])));
    ENDFOR

    tableWidth <- LENGTH(FORMAT("[ * ]| %-*s | %-*s | %-*s | %-*s |",
                               idWidth, "ID",
                               kotaWidth, "Kota",
                               namaWidth, "Nama Bioskop",
                               managerWidth, "Manager"));

    PRINT_HEADER(tableWidth);
    PRINT_ROW(idWidth, kotaWidth, namaWidth, managerWidth);
    PRINT_DIVIDER(tableWidth);

    FOR i <- start TO end - 1 DO
        IF selection = i + 1 THEN
            PRINT_SELECTED_ROW(bioskops[i]);
        ELSE
            PRINT_ROW(bioskops[i]);
        ENDIF
    ENDFOR

    PRINT_DIVIDER(tableWidth);
    PRINT_PAGE_INFO(page, count, perPage);
END MODUL
```

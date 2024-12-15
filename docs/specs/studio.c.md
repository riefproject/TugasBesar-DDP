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

| Nama Modul               | Getter dan Setter Studio                                                                                                                     |
| ------------------------ | -------------------------------------------------------------------------------------------------------------------------------------------- |
| Deskripsi                | Modul untuk mengakses (getter) atau mengubah (setter) properti dari objek Studio seperti ID Bioskop, Nama, Jumlah Kursi, dan Additional Fee. |
| I.S                      | Objek Studio sudah diinisialisasi.                                                                                                           |
| F.S                      | Properti dari objek Studio berhasil diakses atau diperbarui.                                                                                 |
| Modul yang Dipanggil     | Tidak ada.                                                                                                                                   |
| Modul Pemanggil          | Fungsi lain yang memerlukan akses ke properti Studio.                                                                                        |
| Parameter Input/Keluaran | Input: Objek Studio dan properti yang diakses atau diubah. Output: Nilai properti (getter) atau objek yang diperbarui (setter).              |

```
MODUL setStudioBioskopId (Input: studio: POINTER TO Studio, bioskop_id: integer)
ALGORITMA
    studio->bioskop_id <- bioskop_id;
END MODUL

MODUL setNama (Input: studio: POINTER TO Studio, nama: string)
ALGORITMA
    strncpy(studio->nama, nama, MAX_STUDIO_NAME - 1);
    studio->nama[MAX_STUDIO_NAME - 1] <- '\0';
END MODUL

MODUL setJumlahKursi (Input: studio: POINTER TO Studio, jumlah_kursi: integer)
ALGORITMA
    studio->jumlah_kursi <- jumlah_kursi;
END MODUL

MODUL setAdditionalFee (Input: studio: POINTER TO Studio, additionalFee: float)
ALGORITMA
    studio->additionalFee <- additionalFee;
END MODUL

MODUL getStudioBioskopId (Input: studio: POINTER TO Studio; Output: bioskop_id: integer)
ALGORITMA
    RETURN studio->bioskop_id;
END MODUL

MODUL getNama (Input: studio: POINTER TO Studio; Output: nama: string)
ALGORITMA
    RETURN studio->nama;
END MODUL

MODUL getJumlahKursi (Input: studio: POINTER TO Studio; Output: jumlah_kursi: integer)
ALGORITMA
    RETURN studio->jumlah_kursi;
END MODUL

MODUL getAdditionalFee (Input: studio: POINTER TO Studio; Output: additionalFee: float)
ALGORITMA
    RETURN studio->additionalFee;
END MODUL
```

| Nama Modul               | Menu Studio                                                                                       |
| ------------------------ | ------------------------------------------------------------------------------------------------- |
| Deskripsi                | Menampilkan daftar studio dengan navigasi untuk membuat, memperbarui, atau menghapus data studio. |
| I.S                      | Data studio tersedia di database.                                                                 |
| F.S                      | Pengguna dapat membuat, memperbarui, atau menghapus data studio.                                  |
| Modul yang Dipanggil     | loadStudio, printStudioTable, createStudioMenu, updateStudioMenu, deleteStudio.                   |
| Modul Pemanggil          | Menu utama aplikasi.                                                                              |
| Parameter Input/Keluaran | Input: Tidak ada. Output: Tidak ada.                                                              |

```
MODUL menuStudio ()
DEKLARASI
    studios: POINTER TO Studio;
    count, page, perPage, selection, pointer, command: integer;
ALGORITMA
    count <- loadStudio(&studios);
    page <- 1; perPage <- 10; pointer <- 1;

    WHILE TRUE DO
        CLEAR_SCREEN();
        selection <- (page - 1) * perPage + pointer;

        PRINT_HEADER("Menu Manajemen Studio");
        printStudioTable(studios, count, page, perPage, selection);
        PRINT_NAVIGATION_MENU();

        command <- getch();
        IF command = 224 THEN
            command <- getch();
            HANDLE_ARROW_KEYS(command, page, perPage, pointer, count);
        ELSE IF command = 'C' OR command = 'c' THEN
            createStudioMenu();
            free(studios);
            count <- loadStudio(&studios);
        ELSE IF command = 'U' OR command = 'u' THEN
            updateStudioMenu(studios[selection - 1]);
            free(studios);
            count <- loadStudio(&studios);
        ELSE IF command = 'D' OR command = 'd' THEN
            deleteStudio(studios[selection - 1]);
            free(studios);
            count <- loadStudio(&studios);
        ELSE IF command = 'E' OR command = 'e' THEN
            free(studios);
            RETURN;
        ELSE
            PRINT_INVALID_COMMAND();
        ENDIF
    ENDWHILE
END MODUL
```

| Nama Modul               | Create Studio Menu                                                                              |
| ------------------------ | ----------------------------------------------------------------------------------------------- |
| Deskripsi                | Menu untuk menambahkan data studio baru, termasuk input nama, jumlah kursi, dan additional fee. |
| I.S                      | Tidak ada input studio baru.                                                                    |
| F.S                      | Data studio baru berhasil ditambahkan ke database.                                              |
| Modul yang Dipanggil     | createStudio.                                                                                   |
| Modul Pemanggil          | menuStudio.                                                                                     |
| Parameter Input/Keluaran | Input: Tidak ada. Output: Tidak ada.                                                            |

```
MODUL createStudioMenu ()
DEKLARASI
    nama: array [1..MAX_STUDIO_NAME] OF char;
    jumlah_kursi: integer;
    additionalFee: float;
    newStudio: POINTER TO Studio;
ALGORITMA
    CLEAR_SCREEN();
    PRINT_HEADER("Menu Tambah Studio");

    WHILE TRUE DO
        PRINT "Masukkan nama studio\t: ";
        READ_LINE(nama);

        IF nama = "" THEN
            PRINT_ERROR("Nama studio tidak boleh kosong.");
            CONTINUE;
        ENDIF

        BREAK;
    ENDWHILE

    WHILE TRUE DO
        PRINT "Masukkan jumlah kursi\t: ";
        READ_INTEGER(jumlah_kursi);

        IF jumlah_kursi <= 0 THEN
            PRINT_ERROR("Jumlah kursi tidak valid.");
            CONTINUE;
        ENDIF

        BREAK;
    ENDWHILE

    WHILE TRUE DO
        PRINT "Masukkan additionalFee\t: ";
        READ_FLOAT(additionalFee);

        IF additionalFee <= 0 THEN
            PRINT_ERROR("AdditionalFee tidak valid.");
            CONTINUE;
        ENDIF

        BREAK;
    ENDWHILE

    newStudio <- createStudio(nama, jumlah_kursi, additionalFee);
    IF newStudio = NULL THEN
        PRINT_ERROR("Gagal menambah studio.");
        RETURN;
    ENDIF

    PRINT_SUCCESS("Berhasil menambah studio!");
    free(newStudio);
END MODUL
```

| Nama Modul               | Update Studio Menu                                                                                  |
| ------------------------ | --------------------------------------------------------------------------------------------------- |
| Deskripsi                | Menu untuk memperbarui data studio yang ada, termasuk input nama, jumlah kursi, dan additional fee. |
| I.S                      | Data studio tersedia untuk diperbarui.                                                              |
| F.S                      | Data studio yang diperbarui berhasil disimpan ke database.                                          |
| Modul yang Dipanggil     | updateStudio.                                                                                       |
| Modul Pemanggil          | menuStudio.                                                                                         |
| Parameter Input/Keluaran | Input: Studio yang akan diperbarui. Output: Tidak ada.                                              |

```
MODUL updateStudioMenu (Input: studio: Studio)
DEKLARASI
    nama: array [1..MAX_STUDIO_NAME] OF char;
    jumlah_kursi: integer;
    additionalFee: float;
    updatedStudio: POINTER TO Studio;
ALGORITMA
    PRINT_HEADER("Menu Edit Studio");

    WHILE TRUE DO
        PRINT "Masukkan nama studio\t: ";
        READ_LINE(nama);

        IF nama = "" THEN
            PRINT_ERROR("Nama studio tidak boleh kosong.");
            CONTINUE;
        ENDIF

        BREAK;
    ENDWHILE

    WHILE TRUE DO
        PRINT "Masukkan jumlah kursi\t: ";
        READ_INTEGER(jumlah_kursi);

        IF jumlah_kursi <= 0 THEN
            PRINT_ERROR("Jumlah kursi tidak valid.");
            CONTINUE;
        ENDIF

        BREAK;
    ENDWHILE

    WHILE TRUE DO
        PRINT "Masukkan additionalFee\t: ";
        READ_FLOAT(additionalFee);

        IF additionalFee <= 0 THEN
            PRINT_ERROR("AdditionalFee tidak valid.");
            CONTINUE;
        ENDIF

        BREAK;
    ENDWHILE

    updatedStudio <- updateStudio(studio.id, nama, jumlah_kursi, additionalFee);
    IF updatedStudio = NULL THEN
        PRINT_ERROR("Gagal mengubah studio.");
        RETURN;
    ENDIF

    PRINT_SUCCESS("Berhasil mengubah studio!");
    free(updatedStudio);
END MODUL
```

| Nama Modul               | createStudio                                                                                                              |
| ------------------------ | ------------------------------------------------------------------------------------------------------------------------- |
| Deskripsi                | Membuat data studio baru dan menyimpannya dalam database.                                                                 |
| I.S                      | Data studio baru belum ada dalam database.                                                                                |
| F.S                      | Data studio baru ditambahkan ke database.                                                                                 |
| Modul yang Dipanggil     | getCurrentUser, findBioskopByManagerId, setStudioBioskopId, setNama, setJumlahKursi, setAdditionalFee, getLastAvailableID |
| Modul Pemanggil          | Menu manajemen studio.                                                                                                    |
| Parameter Input/Keluaran | Input: nama (string), jumlah_kursi (integer), additionalFee (float). Output: POINTER TO Studio.                           |

```
MODUL createStudio (Input: nama: string, jumlah_kursi: integer, additionalFee: float; Output: result: POINTER TO Studio)
DEKLARASI
    studio: POINTER TO Studio;
    user: POINTER TO User;
    bioskop_id: integer;
    id: integer;
    file: FILE POINTER;
ALGORITMA
    studio <- malloc(sizeof(Studio));
    IF studio = NULL THEN
        PRINT "Alokasi memori gagal, lokasi: createStudio.";
        RETURN NULL;
    ENDIF

    user <- getCurrentUser();
    bioskop_id <- findBioskopByManagerId(user->id)->id;

    setStudioBioskopId(studio, bioskop_id);
    setNama(studio, nama);
    setJumlahKursi(studio, jumlah_kursi);
    setAdditionalFee(studio, additionalFee);

    file <- fopen(STUDIO_DATABASE_NAME, "a");
    IF file = NULL THEN
        free(studio);
        RETURN NULL;
    ENDIF

    id <- getLastAvailableID(STUDIO_DATABASE_NAME);
    studio->id <- id;

    fprintf(file, STUDIO_SETTER_FORMAT, studio->id, getNama(studio), getStudioBioskopId(studio), getJumlahKursi(studio), getAdditionalFee(studio));
    fclose(file);
    RETURN studio;
END MODUL
```

| Nama Modul               | updateStudio                                                                                                  |
| ------------------------ | ------------------------------------------------------------------------------------------------------------- |
| Deskripsi                | Memperbarui data studio yang ada dalam database.                                                              |
| I.S                      | Data studio lama sudah ada dalam database.                                                                    |
| F.S                      | Data studio diperbarui sesuai dengan input baru.                                                              |
| Modul yang Dipanggil     | setNama, setJumlahKursi, setAdditionalFee, countStudioData, setStudioBioskopId                                |
| Modul Pemanggil          | Menu manajemen studio.                                                                                        |
| Parameter Input/Keluaran | Input: id (integer), nama (string), jumlah_kursi (integer), additionalFee (float). Output: POINTER TO Studio. |

```
MODUL updateStudio (Input: id: integer, nama: string, jumlah_kursi: integer, additionalFee: float; Output: result: POINTER TO Studio)
DEKLARASI
    updatedStudio: POINTER TO Studio;
    fromFile, toFile: FILE POINTER;
    count, i: integer;
    studios: array OF Studio;
ALGORITMA
    updatedStudio <- malloc(sizeof(Studio));
    IF updatedStudio = NULL THEN
        PRINT "Alokasi memori gagal, lokasi: updateStudio.";
        RETURN NULL;
    ENDIF

    updatedStudio->id <- id;
    setNama(updatedStudio, nama);
    setJumlahKursi(updatedStudio, jumlah_kursi);
    setAdditionalFee(updatedStudio, additionalFee);

    fromFile <- fopen(STUDIO_DATABASE_NAME, "r");
    IF fromFile = NULL THEN
        free(updatedStudio);
        RETURN NULL;
    ENDIF

    count <- countStudioData();
    IF count = -1 THEN
        fclose(fromFile);
        free(updatedStudio);
        RETURN NULL;
    ENDIF

    FOR i <- 0 TO count - 1 DO
        fscanf(fromFile, STUDIO_GETTER_FORMAT, &studios[i].id, studios[i].nama, &studios[i].bioskop_id, &studios[i].jumlah_kursi, &studios[i].additionalFee);
        IF studios[i].id = id THEN
            setStudioBioskopId(updatedStudio, studios[i].bioskop_id);
            studios[i] <- *updatedStudio;
        ENDIF
    ENDFOR
    fclose(fromFile);

    toFile <- fopen(STUDIO_DATABASE_NAME, "w");
    FOR i <- 0 TO count - 1 DO
        fprintf(toFile, STUDIO_SETTER_FORMAT, studios[i].id, studios[i].nama, studios[i].bioskop_id, studios[i].jumlah_kursi, studios[i].additionalFee);
    ENDFOR
    fclose(toFile);

    RETURN updatedStudio;
END MODUL
```

| Nama Modul               | deleteStudio                                                                   |
| ------------------------ | ------------------------------------------------------------------------------ |
| Deskripsi                | Menghapus data studio dari database.                                           |
| I.S                      | Data studio sudah ada dalam database.                                          |
| F.S                      | Data studio dihapus dari database jika konfirmasi pengguna valid.              |
| Modul yang Dipanggil     | countStudioData, showMenu                                                      |
| Modul Pemanggil          | Menu manajemen studio.                                                         |
| Parameter Input/Keluaran | Input: studio (Studio struct). Output: Integer 1 jika berhasil, -1 jika gagal. |

```
MODUL deleteStudio (Input: studio: Studio; Output: result: integer)
DEKLARASI
    fromFile, toFile: FILE POINTER;
    studios: array OF Studio;
    count, i: integer;
    temp: Studio;
    head: string;
ALGORITMA
    head <- sprintf("Apakah Anda yakin ingin menghapus data studio dengan ID '%d'?", studio.id);
    menu <- ["Tidak, Batalkan", "Ya, Hapus"];
    selection <- showMenu(menu, 2, head);

    IF selection = 1 THEN
        RETURN 1;
    ENDIF

    fromFile <- fopen(STUDIO_DATABASE_NAME, "r");
    IF fromFile = NULL THEN
        PRINT "File gagal dibuka, lokasi: deleteStudio.";
        RETURN -1;
    ENDIF

    count <- countStudioData();
    IF count = -1 THEN
        fclose(fromFile);
        RETURN -1;
    ENDIF

    FOR i <- 0 TO count - 1 DO
        fscanf(fromFile, STUDIO_GETTER_FORMAT, &temp.id, temp.nama, &temp.bioskop_id, &temp.jumlah_kursi, &temp.additionalFee);
        IF temp.id != studio.id THEN
            studios[i] <- temp;
        ENDIF
    ENDFOR
    fclose(fromFile);

    toFile <- fopen(STUDIO_DATABASE_NAME, "w");
    FOR i <- 0 TO count - 2 DO
        fprintf(toFile, STUDIO_SETTER_FORMAT, studios[i].id, studios[i].nama, studios[i].bioskop_id, studios[i].jumlah_kursi, studios[i].additionalFee);
    ENDFOR
    fclose(toFile);

    RETURN 1;
END MODUL
```

| Nama Modul               | countStudioData                                                       |
| ------------------------ | --------------------------------------------------------------------- |
| Deskripsi                | Menghitung jumlah data studio dalam database.                         |
| I.S                      | Database studio tersedia.                                             |
| F.S                      | Mengembalikan jumlah record studio dalam file database.               |
| Modul yang Dipanggil     | Tidak ada.                                                            |
| Modul Pemanggil          | Fungsi manajemen studio lainnya.                                      |
| Parameter Input/Keluaran | Input: Tidak ada. Output: Jumlah record (integer) atau -1 jika gagal. |

```
MODUL countStudioData (Output: count: integer)
DEKLARASI
    file: FILE POINTER;
    count: integer;
    studio: Studio;
ALGORITMA
    file <- fopen(STUDIO_DATABASE_NAME, "r");
    IF file = NULL THEN
        PRINT "File gagal dibuka.";
        RETURN -1;
    ENDIF

    count <- 0;
    WHILE fscanf(file, STUDIO_GETTER_FORMAT, &studio.id, studio.nama, &studio.bioskop_id, &studio.jumlah_kursi, &studio.additionalFee) != EOF DO
        count <- count + 1;
    ENDWHILE
    fclose(file);
    RETURN count;
END MODUL
```

| Nama Modul               | loadStudio                                                                                    |
| ------------------------ | --------------------------------------------------------------------------------------------- |
| Deskripsi                | Memuat data studio dari file database ke dalam array.                                         |
| I.S                      | Database studio tersedia.                                                                     |
| F.S                      | Data studio dimuat ke dalam array.                                                            |
| Modul yang Dipanggil     | countStudioData                                                                               |
| Modul Pemanggil          | Fungsi manajemen studio lainnya.                                                              |
| Parameter Input/Keluaran | Input: studios (POINTER TO Studio ARRAY). Output: Jumlah record (integer) atau -1 jika gagal. |

```
MODUL loadStudio (Output: studios: POINTER TO Studio ARRAY; result: integer)
DEKLARASI
    file: FILE POINTER;
    count, i: integer;
ALGORITMA
    file <- fopen(STUDIO_DATABASE_NAME, "r");
    IF file = NULL THEN
        PRINT "File gagal dibuka.";
        RETURN -1;
    ENDIF

    count <- countStudioData();
    IF count = -1 THEN
        fclose(file);
        RETURN -1;
    ENDIF

    studios <- malloc(count * sizeof(Studio));
    IF studios = NULL THEN
        PRINT "Gagal mengalokasi memori.";
        fclose(file);
        RETURN -1;
    ENDIF

    rewind(file);
    i <- 0;
    WHILE fscanf(file, STUDIO_GETTER_FORMAT, &studios[i].id, studios[i].nama, &studios[i].bioskop_id, &studios[i].jumlah_kursi, &studios[i].additionalFee) != EOF DO
        i <- i + 1;
    ENDWHILE
    fclose(file);
    RETURN count;
END MODUL
```

| Nama Modul               | printStudioTable                                                                                                           |
| ------------------------ | -------------------------------------------------------------------------------------------------------------------------- |
| Deskripsi                | Menampilkan tabel data studio dalam format yang rapi.                                                                      |
| I.S                      | Data studio tersedia dalam array.                                                                                          |
| F.S                      | Data studio ditampilkan dalam format tabel di konsol.                                                                      |
| Modul yang Dipanggil     | Tidak ada.                                                                                                                 |
| Modul Pemanggil          | Fungsi manajemen studio lainnya.                                                                                           |
| Parameter Input/Keluaran | Input: studios (Studio ARRAY), count (integer), page (integer), perPage (integer), selection (integer). Output: Tidak ada. |

```
MODUL printStudioTable (Input: studios: Studio ARRAY, count: integer, page: integer, perPage: integer, selection: integer)
DEKLARASI
    idWidth, namaWidth, jumlahKursiWidth, additionalFeeWidth, tableWidth, start, end, i: integer;
ALGORITMA
    idWidth <- 2;
    namaWidth <- 4;
    jumlahKursiWidth <- 12;
    additionalFeeWidth <- 13;

    start <- (page - 1) * perPage;
    end <- start + perPage;
    IF end > count THEN
        end <- count;
    ENDIF

    FOR i <- start TO end - 1 DO
        idWidth <- MAX(idWidth, LENGTH(studios[i].id));
        namaWidth <- MAX(namaWidth, LENGTH(studios[i].nama));
        jumlahKursiWidth <- MAX(jumlahKursiWidth, LENGTH(studios[i].jumlah_kursi));
        additionalFeeWidth <- MAX(additionalFeeWidth, LENGTH(studios[i].additionalFee));
    ENDFOR

    tableWidth <- FORMAT_WIDTH(idWidth, namaWidth, jumlahKursiWidth, additionalFeeWidth);
    PRINT HEADER_LINE(tableWidth);
    PRINT HEADER(idWidth, namaWidth, jumlahKursiWidth, additionalFeeWidth);
    PRINT HEADER_LINE(tableWidth);

    FOR i <- start TO end - 1 DO
        IF selection = i + 1 THEN
            PRINT SELECTED_ROW(studios[i], idWidth, namaWidth, jumlahKursiWidth, additionalFeeWidth);
        ELSE
            PRINT ROW(studios[i], idWidth, namaWidth, jumlahKursiWidth, additionalFeeWidth);
        ENDIF
    ENDFOR

    PRINT HEADER_LINE(tableWidth);
    PRINT PAGE_INFO(page, (count + perPage - 1) / perPage);
END MODUL
```

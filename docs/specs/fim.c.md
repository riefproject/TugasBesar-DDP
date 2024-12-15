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

| Nama Modul           | Getter dan Setter Film |
|---------------------|--------------------------|
| Deskripsi          | Modul untuk mengakses (getter) atau mengubah (setter) properti dari objek Film seperti ID, Kode Film, Judul, Genre, Durasi, dan Status Tersedia. |
| I.S                | Objek Film sudah diinisialisasi. |
| F.S                | Properti dari objek Film berhasil diakses atau diperbarui. |
| Modul yang Dipanggil | Tidak ada. |
| Modul Pemanggil    | Fungsi lain yang memerlukan akses ke properti Film. |
| Parameter Input/Keluaran | Input: Objek Film dan properti yang diakses atau diubah. Output: Nilai properti (getter) atau objek yang diperbarui (setter). |

```
MODUL getFilmId (Input: film: POINTER TO Film; Output: id: integer)
ALGORITMA
    RETURN film->id;
END MODUL

MODUL setFilmId (Input: film: POINTER TO Film, id: integer)
ALGORITMA
    film->id <- id;
END MODUL

MODUL getFilmKode (Input: film: POINTER TO Film; Output: kode_film: string)
ALGORITMA
    RETURN film->kode_film;
END MODUL

MODUL setFilmKode (Input: film: POINTER TO Film, kode_film: string)
ALGORITMA
    strncpy(film->kode_film, kode_film, sizeof(film->kode_film) - 1);
    film->kode_film[sizeof(film->kode_film) - 1] <- '\0';
END MODUL

MODUL getFilmJudul (Input: film: POINTER TO Film; Output: judul: string)
ALGORITMA
    RETURN film->judul;
END MODUL

MODUL setFilmJudul (Input: film: POINTER TO Film, judul: string)
ALGORITMA
    strncpy(film->judul, judul, MAX_FILM_TITLE - 1);
    film->judul[MAX_FILM_TITLE - 1] <- '\0';
END MODUL

MODUL getFilmDurasiById (Input: film_id: integer; Output: durasi: integer)
DEKLARASI
    file: FILE POINTER;
    line: array [1..256] OF char;
    id, durasi: integer;
    kode_film: array [1..10] OF char;
    judul: array [1..MAX_FILM_TITLE] OF char;
    genre: array [1..MAX_GENRE] OF char;
ALGORITMA
    file <- fopen(FILM_DATABASE_NAME, "r");
    IF file = NULL THEN
        PRINT_ERROR("Gagal membuka file film.csv");
        RETURN 0;
    ENDIF

    fgets(line, sizeof(line), file); // Skip header
    WHILE fgets(line, sizeof(line), file) != NULL DO
        sscanf(line, "%d,%*d,%9[^,],%99[^,],%49[^,],%d,%*d",
               &id, kode_film, judul, genre, &durasi);
        IF id = film_id THEN
            fclose(file);
            RETURN durasi;
        ENDIF
    ENDWHILE

    fclose(file);
    RETURN 0;
END MODUL
```
| Nama Modul           | Menu Film |
|---------------------|--------------------------|
| Deskripsi          | Menampilkan daftar film dengan navigasi untuk membuat, memperbarui, atau menghapus data film. |
| I.S                | Data film tersedia di database. |
| F.S                | Pengguna dapat membuat, memperbarui, atau menghapus data film. |
| Modul yang Dipanggil | loadFilm, printFilmTable, createFilmMenu, updateFilmMenu, deleteFilm. |
| Modul Pemanggil    | Menu utama aplikasi. |
| Parameter Input/Keluaran | Input: Tidak ada. Output: Tidak ada. |

```
MODUL menuFilm ()
DEKLARASI
    films: POINTER TO Film;
    count, page, perPage, selection, pointer, command: integer;
ALGORITMA
    count <- loadFilm(&films);
    page <- 1; perPage <- 10; pointer <- 1;

    WHILE TRUE DO
        CLEAR_SCREEN();
        selection <- (page - 1) * perPage + pointer;

        printFilmTable(films, count, page, perPage, selection);
        PRINT_NAVIGATION_MENU();

        command <- getch();
        IF command = 224 THEN
            command <- getch();
            HANDLE_ARROW_KEYS(command, page, perPage, pointer, count);
        ELSE IF command = 'C' OR command = 'c' THEN
            createFilmMenu();
            free(films);
            count <- loadFilm(&films);
        ELSE IF command = 'U' OR command = 'u' THEN
            updateFilmMenu(films[selection - 1]);
            free(films);
            count <- loadFilm(&films);
        ELSE IF command = 'D' OR command = 'd' THEN
            deleteFilm(films[selection - 1]);
            free(films);
            count <- loadFilm(&films);
        ELSE IF command = 'E' OR command = 'e' THEN
            free(films);
            RETURN;
        ELSE
            PRINT_INVALID_COMMAND();
        ENDIF
    ENDWHILE
END MODUL
```

| Nama Modul           | Create Film Menu |
|---------------------|--------------------------|
| Deskripsi          | Menu untuk menambahkan data film baru, termasuk input kode film, judul, genre, durasi, ketersediaan, dan ID bioskop. |
| I.S                | Tidak ada input film baru. |
| F.S                | Data film baru berhasil ditambahkan ke database. |
| Modul yang Dipanggil | findFilmByKode, createFilm. |
| Modul Pemanggil    | menuFilm. |
| Parameter Input/Keluaran | Input: Tidak ada. Output: Tidak ada. |

```
MODUL createFilmMenu ()
DEKLARASI
    kode_film: array [1..10] OF char;
    judul: array [1..MAX_FILM_TITLE] OF char;
    genre: array [1..MAX_GENRE] OF char;
    durasi, tersedia, bioskop_id: integer;
    newFilm: POINTER TO Film;
ALGORITMA
    CLEAR_SCREEN();
    PRINT_HEADER("Menu Tambah Film");

    WHILE TRUE DO
        PRINT "Masukkan kode film\t: ";
        READ_LINE(kode_film);

        IF findFilmByKode(kode_film) != NULL THEN
            PRINT_ERROR("Kode film sudah terdaftar.");
            CONTINUE;
        ENDIF

        IF kode_film = "" THEN
            PRINT_ERROR("Kode film tidak boleh kosong.");
            CONTINUE;
        ENDIF

        BREAK;
    ENDWHILE

    PRINT "Masukkan judul film\t: ";
    READ_LINE(judul);

    PRINT "Masukkan genre film\t: ";
    READ_LINE(genre);

    PRINT "Masukkan durasi film (menit)\t: ";
    READ_INTEGER(durasi);

    PRINT "Masukkan status ketersediaan (1 untuk tersedia, 0 untuk tidak)\t: ";
    READ_INTEGER(tersedia);

    PRINT "Masukkan ID bioskop\t: ";
    READ_INTEGER(bioskop_id);

    newFilm <- createFilm(kode_film, judul, genre, durasi, tersedia, bioskop_id);
    IF newFilm = NULL THEN
        PRINT_ERROR("Gagal menambah film.");
        RETURN;
    ENDIF

    PRINT_SUCCESS("Berhasil menambah film!");
    free(newFilm);
END MODUL
```

| Nama Modul           | Update Film Menu |
|---------------------|--------------------------|
| Deskripsi          | Menu untuk memperbarui data film yang ada, termasuk input kode film, judul, genre, durasi, ketersediaan, dan ID bioskop. |
| I.S                | Data film tersedia untuk diperbarui. |
| F.S                | Data film yang diperbarui berhasil disimpan ke database. |
| Modul yang Dipanggil | findFilmByKode, updateFilm. |
| Modul Pemanggil    | menuFilm. |
| Parameter Input/Keluaran | Input: Film yang akan diperbarui. Output: Tidak ada. |

```
MODUL updateFilmMenu (Input: film: Film)
DEKLARASI
    kode_film: array [1..10] OF char;
    judul: array [1..MAX_FILM_TITLE] OF char;
    genre: array [1..MAX_GENRE] OF char;
    durasi, tersedia, bioskop_id: integer;
    updatedFilm: POINTER TO Film;
ALGORITMA
    PRINT_HEADER("Menu Edit Film");

    WHILE TRUE DO
        PRINT "Masukkan kode film\t: ";
        READ_LINE(kode_film);

        IF findFilmByKode(kode_film) != NULL AND film.id != findFilmByKode(kode_film)->id THEN
            PRINT_ERROR("Kode film sudah terdaftar.");
            CONTINUE;
        ENDIF

        IF kode_film = "" THEN
            PRINT_ERROR("Kode film tidak boleh kosong.");
            CONTINUE;
        ENDIF

        BREAK;
    ENDWHILE

    PRINT "Masukkan judul film\t: ";
    READ_LINE(judul);

    PRINT "Masukkan genre film\t: ";
    READ_LINE(genre);

    PRINT "Masukkan durasi film (menit)\t: ";
    READ_INTEGER(durasi);

    PRINT "Masukkan status ketersediaan (1 untuk tersedia, 0 untuk tidak)\t: ";
    READ_INTEGER(tersedia);

    PRINT "Masukkan ID bioskop\t: ";
    READ_INTEGER(bioskop_id);

    updatedFilm <- updateFilm(film.id, kode_film, judul, genre, durasi, tersedia, bioskop_id);
    IF updatedFilm = NULL THEN
        PRINT_ERROR("Gagal memperbarui film.");
        RETURN;
    ENDIF

    PRINT_SUCCESS("Berhasil memperbarui film!");
    free(updatedFilm);
END MODUL
```
| Nama Modul           | Find Film by Kode |
|---------------------|--------------------------|
| Deskripsi          | Mencari data film berdasarkan kode film yang diberikan. |
| I.S                | Kode film diberikan. |
| F.S                | Data film ditemukan dan dikembalikan dalam bentuk pointer, atau NULL jika tidak ditemukan. |
| Modul yang Dipanggil | Tidak ada. |
| Modul Pemanggil    | Modul lain yang memerlukan pencarian film berdasarkan kode. |
| Parameter Input/Keluaran | Input: kode_film (string). Output: Pointer ke Film atau NULL. |

```
MODUL findFilmByKode (Input: kode_film: string; Output: film: POINTER TO Film)
DEKLARASI
    file: FILE POINTER;
    film: POINTER TO Film;
ALGORITMA
    file <- fopen(FILM_DATABASE_NAME, "r");
    IF file = NULL THEN
        RETURN NULL;
    ENDIF

    WHILE fscanf(file, FILM_GETTER_FORMAT,
                  &film->id,
                  film->kode_film,
                  film->judul,
                  film->genre,
                  &film->durasi,
                  &film->tersedia,
                  &film->bioskop_id) != EOF DO
        IF strcmp(film->kode_film, kode_film) = 0 THEN
            fclose(file);
            RETURN film;
        ENDIF
    ENDWHILE

    fclose(file);
    RETURN NULL;
END MODUL
```

| Nama Modul           | Create Film |
|---------------------|--------------------------|
| Deskripsi          | Membuat data film baru berdasarkan input pengguna. |
| I.S                | Tidak ada data film baru yang ditambahkan. |
| F.S                | Data film baru berhasil disimpan ke database. |
| Modul yang Dipanggil | setFilmKode, setFilmJudul, setFilmGenre, setFilmDurasi, setFilmTersedia, setFilmBioskopId, getLastAvailableID. |
| Modul Pemanggil    | Modul lain yang memerlukan penambahan data film. |
| Parameter Input/Keluaran | Input: kode_film, judul, genre, durasi, tersedia, bioskop_id. Output: Pointer ke Film baru atau NULL jika gagal. |

```
MODUL createFilm (Input: kode_film: string, judul: string, genre: string, durasi: integer, tersedia: integer, bioskop_id: integer; Output: film: POINTER TO Film)
DEKLARASI
    film: POINTER TO Film;
    file: FILE POINTER;
    id: integer;
ALGORITMA
    film <- malloc(sizeof(Film));
    IF film = NULL THEN
        PRINT("Alokasi memori gagal.");
        RETURN NULL;
    ENDIF

    setFilmKode(film, kode_film);
    setFilmJudul(film, judul);
    setFilmGenre(film, genre);
    setFilmDurasi(film, durasi);
    setFilmTersedia(film, tersedia);
    setFilmBioskopId(film, bioskop_id);

    file <- fopen(FILM_DATABASE_NAME, "a");
    IF file = NULL THEN
        free(film);
        RETURN NULL;
    ENDIF

    id <- getLastAvailableID(FILM_DATABASE_NAME);
    setFilmId(film, id);

    fprintf(file, FILM_SETTER_FORMAT,
            getFilmId(film),
            getFilmKode(film),
            getFilmJudul(film),
            getFilmGenre(film),
            getFilmDurasi(film),
            isFilmTersedia(film),
            getFilmBioskopId(film));

    fclose(file);
    RETURN film;
END MODUL
```

| Nama Modul           | Update Film |
|---------------------|--------------------------|
| Deskripsi          | Memperbarui data film yang ada dengan input baru. |
| I.S                | Data film tersedia di database. |
| F.S                | Data film diperbarui sesuai dengan input baru. |
| Modul yang Dipanggil | setFilmKode, setFilmJudul, setFilmGenre, setFilmDurasi, setFilmTersedia, setFilmBioskopId. |
| Modul Pemanggil    | Modul lain yang memerlukan pembaruan data film. |
| Parameter Input/Keluaran | Input: id, kode_film, judul, genre, durasi, tersedia, bioskop_id. Output: Pointer ke Film yang diperbarui atau NULL jika gagal. |

```
MODUL updateFilm (Input: id: integer, kode_film: string, judul: string, genre: string, durasi: integer, tersedia: integer, bioskop_id: integer; Output: updatedFilm: POINTER TO Film)
DEKLARASI
    updatedFilm: POINTER TO Film;
    fromFile, toFile: FILE POINTER;
    films: array OF Film;
    count, i: integer;
ALGORITMA
    updatedFilm <- malloc(sizeof(Film));
    IF updatedFilm = NULL THEN
        PRINT("Alokasi memori gagal.");
        RETURN NULL;
    ENDIF

    setFilmKode(updatedFilm, kode_film);
    setFilmJudul(updatedFilm, judul);
    setFilmGenre(updatedFilm, genre);
    setFilmDurasi(updatedFilm, durasi);
    setFilmTersedia(updatedFilm, tersedia);
    setFilmBioskopId(updatedFilm, bioskop_id);

    fromFile <- fopen(FILM_DATABASE_NAME, "r");
    IF fromFile = NULL THEN
        free(updatedFilm);
        RETURN NULL;
    ENDIF

    count <- countFilmData();
    IF count = -1 THEN
        fclose(fromFile);
        RETURN NULL;
    ENDIF

    FOR i <- 0 TO count - 1 DO
        IF films[i].id = id THEN
            films[i] <- *updatedFilm;
        ENDIF
    ENDFOR
    fclose(fromFile);

    toFile <- fopen(FILM_DATABASE_NAME, "w");
    IF toFile = NULL THEN
        free(updatedFilm);
        RETURN NULL;
    ENDIF

    FOR i <- 0 TO count - 1 DO
        fprintf(toFile, FILM_SETTER_FORMAT,
                films[i].id,
                films[i].kode_film,
                films[i].judul,
                films[i].genre,
                films[i].durasi,
                films[i].tersedia,
                films[i].bioskop_id);
    ENDFOR
    fclose(toFile);

    RETURN updatedFilm;
END MODUL
```

| Nama Modul           | Delete Film |
|---------------------|--------------------------|
| Deskripsi          | Menghapus data film dari database berdasarkan kode film. |
| I.S                | Data film tersedia di database. |
| F.S                | Data film berhasil dihapus dari database. |
| Modul yang Dipanggil | Tidak ada. |
| Modul Pemanggil    | Modul lain yang memerlukan penghapusan data film. |
| Parameter Input/Keluaran | Input: film (struct Film). Output: Integer (1 jika berhasil, -1 jika gagal). |

```
MODUL deleteFilm (Input: film: Film; Output: result: integer)
DEKLARASI
    fromFile, toFile: FILE POINTER;
    films: array OF Film;
    count, i, j: integer;
ALGORITMA
    fromFile <- fopen(FILM_DATABASE_NAME, "r");
    IF fromFile = NULL THEN
        PRINT("Gagal membuka file.");
        RETURN -1;
    ENDIF

    count <- countFilmData();
    IF count = -1 THEN
        fclose(fromFile);
        RETURN -1;
    ENDIF

    j <- 0;
    FOR i <- 0 TO count - 1 DO
        IF films[i].id != film.id THEN
            films[j] <- films[i];
            j <- j + 1;
        ENDIF
    ENDFOR
    fclose(fromFile);

    toFile <- fopen(FILM_DATABASE_NAME, "w");
    IF toFile = NULL THEN
        RETURN -1;
    ENDIF

    FOR i <- 0 TO j - 1 DO
        fprintf(toFile, FILM_SETTER_FORMAT,
                films[i].id,
                films[i].kode_film,
                films[i].judul,
                films[i].genre,
                films[i].durasi,
                films[i].tersedia,
                films[i].bioskop_id);
    ENDFOR
    fclose(toFile);

    RETURN 1;
END MODUL
```
| Nama Modul           | Count Film Data |
|---------------------|--------------------------|
| Deskripsi          | Menghitung jumlah data film yang ada dalam database. |
| I.S                | Database film tersedia. |
| F.S                | Jumlah data film dihitung dan dikembalikan. |
| Modul yang Dipanggil | Tidak ada. |
| Modul Pemanggil    | Modul lain yang memerlukan informasi jumlah data film. |
| Parameter Input/Keluaran | Input: Tidak ada. Output: Integer (jumlah data film, -1 jika gagal). |

```
MODUL countFilmData ()
DEKLARASI
    file: FILE POINTER;
    film: Film;
    count: integer;
ALGORITMA
    file <- fopen(FILM_DATABASE_NAME, "r");
    IF file = NULL THEN
        PRINT("File gagal dibuka.");
        RETURN -1;
    ENDIF

    count <- 0;
    WHILE fscanf(file, FILM_GETTER_FORMAT,
                 &film.id,
                 &film.bioskop_id,
                 film.kode_film,
                 film.judul,
                 film.genre,
                 &film.durasi,
                 &film.tersedia) != EOF DO
        count <- count + 1;
    ENDWHILE

    fclose(file);
    RETURN count;
END MODUL
```

| Nama Modul           | Load Film |
|---------------------|--------------------------|
| Deskripsi          | Memuat semua data film dari database ke dalam memori. |
| I.S                | Database film tersedia. |
| F.S                | Semua data film dimuat ke dalam array. |
| Modul yang Dipanggil | countFilmData. |
| Modul Pemanggil    | Modul lain yang memerlukan data film. |
| Parameter Input/Keluaran | Input: Pointer ke array film. Output: Integer (jumlah data yang dimuat, -1 jika gagal). |

```
MODUL loadFilm (Output: films: POINTER TO Film; Output: count: integer)
DEKLARASI
    file: FILE POINTER;
    count: integer;
    i: integer;
ALGORITMA
    file <- fopen(FILM_DATABASE_NAME, "r");
    IF file = NULL THEN
        PRINT("File gagal dibuka.");
        RETURN -1;
    ENDIF

    count <- countFilmData();
    films <- malloc(count * sizeof(Film));
    IF films = NULL THEN
        PRINT("Gagal mengalokasi memori.");
        fclose(file);
        RETURN -1;
    ENDIF

    rewind(file);
    FOR i <- 0 TO count - 1 DO
        fscanf(file, FILM_GETTER_FORMAT,
               &films[i].id,
               &films[i].bioskop_id,
               films[i].kode_film,
               films[i].judul,
               films[i].genre,
               &films[i].durasi,
               &films[i].tersedia);
    ENDFOR

    fclose(file);
    RETURN count;
END MODUL
```

| Nama Modul           | Print Film Table |
|---------------------|--------------------------|
| Deskripsi          | Menampilkan data film dalam bentuk tabel pada terminal. |
| I.S                | Data film tersedia di memori. |
| F.S                | Tabel data film ditampilkan di terminal. |
| Modul yang Dipanggil | Tidak ada. |
| Modul Pemanggil    | Modul lain yang membutuhkan tampilan tabel data film. |
| Parameter Input/Keluaran | Input: Array film, jumlah data, halaman, jumlah per halaman, pilihan saat ini. Output: Tidak ada. |

```
MODUL printFilmTable (Input: films: POINTER TO Film, count: integer, page: integer, perPage: integer, selection: integer)
DEKLARASI
    idWidth, kodeWidth, judulWidth, genreWidth, durasiWidth, tersediaWidth, start, end, i: integer;
    tableWidth: integer;
ALGORITMA
    idWidth <- 2; kodeWidth <- 8; judulWidth <- 4;
    genreWidth <- 5; durasiWidth <- 6; tersediaWidth <- 8;
    start <- (page - 1) * perPage;
    end <- start + perPage;
    IF end > count THEN
        end <- count;
    ENDIF

    FOR i <- start TO end - 1 DO
        idWidth <- MAX(idWidth, LENGTH(TO_STRING(films[i].id)));
        kodeWidth <- MAX(kodeWidth, LENGTH(films[i].kode_film));
        judulWidth <- MAX(judulWidth, LENGTH(films[i].judul));
        genreWidth <- MAX(genreWidth, LENGTH(films[i].genre));
    ENDFOR

    tableWidth <- LENGTH(FORMAT("[ * ]| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |",
                               idWidth, "ID",
                               kodeWidth, "Kode Film",
                               judulWidth, "Judul",
                               genreWidth, "Genre",
                               durasiWidth, "Durasi",
                               tersediaWidth, "Tersedia"));

    PRINT_HEADER(tableWidth);
    PRINT_ROW(idWidth, kodeWidth, judulWidth, genreWidth, durasiWidth, tersediaWidth);
    PRINT_DIVIDER(tableWidth);

    FOR i <- start TO end - 1 DO
        IF selection = i + 1 THEN
            PRINT_SELECTED_ROW(films[i]);
        ELSE
            PRINT_ROW(films[i]);
        ENDIF
    ENDFOR

    PRINT_DIVIDER(tableWidth);
    PRINT_PAGE_INFO(page, count, perPage);
END MODUL
```

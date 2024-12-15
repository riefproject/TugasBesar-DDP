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

### db.h

| Nama Modul               | getLastAvailableID                                                                             |
| ------------------------ | ---------------------------------------------------------------------------------------------- |
| Deskripsi                | Mengembalikan ID terakhir yang tersedia dalam database.                                        |
| I.S                      | File database pengguna ada dan dapat diakses.                                                  |
| F.S                      | Mengembalikan nilai ID terakhir + 1 berdasarkan jumlah baris dalam file.                       |
| Modul yang Dipanggil     | Tidak ada                                                                                      |
| Modul Pemanggil          | Fungsi manajemen database lainnya.                                                             |
| Parameter Input/Keluaran | Input: databaseName (string, nama file database). Output: Integer (ID terakhir yang tersedia). |

```
MODUL getLastAvailableID (Input: databaseName: string; Output: result: integer)
DEKLARASI
    count: integer;
    c: char;
    file: FILE POINTER;
ALGORITMA
    count <- 0;
    file <- fopen(databaseName, "r");

    WHILE (c <- fgetc(file)) != EOF DO
        IF c = '\n' THEN
            count <- count + 1;
        ENDIF
    ENDWHILE

    fclose(file);
    RETURN count + 1;
END MODUL
```

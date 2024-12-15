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

### security.h

| Nama Modul               | encrypt                                                                                                     |
| ------------------------ | ----------------------------------------------------------------------------------------------------------- |
| Deskripsi                | Mengenkripsi password menggunakan algoritma SHA-256 dan menghasilkan output hash dalam format heksadesimal. |
| I.S                      | Password string diberikan.                                                                                  |
| F.S                      | Hash password dihasilkan dalam format heksadesimal.                                                         |
| Modul yang Dipanggil     | SHA256 (dari pustaka OpenSSL).                                                                              |
| Modul Pemanggil          | Fungsi manajemen keamanan lainnya.                                                                          |
| Parameter Input/Keluaran | Input: password (string). Output: hashedOutput (string, panjang 64 karakter).                               |

```
MODUL encrypt (Input: password: string; Output: hashedOutput: string)
DEKLARASI
    hash: array [1..SHA256_DIGEST_LENGTH] OF unsigned char;
    i: integer;
ALGORITMA
    SHA256((unsigned char *)password, strlen(password), hash);

    FOR i <- 0 TO SHA256_DIGEST_LENGTH - 1 DO
        sprintf(hashedOutput + (i * 2), "%02x", hash[i]);
    ENDFOR

    hashedOutput[64] <- '\0';
END MODUL
```

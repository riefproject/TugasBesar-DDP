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

### auth.h

| Nama Modul               | authenticateUser                                                            |
| ------------------------ | --------------------------------------------------------------------------- |
| Deskripsi                | Memverifikasi kredensial pengguna dengan mencocokkan username dan password. |
| I.S                      | Username dan password diberikan.                                            |
| F.S                      | Mengembalikan 1 jika autentikasi berhasil, 0 jika gagal.                    |
| Modul yang Dipanggil     | findUserByUsername, encrypt                                                 |
| Modul Pemanggil          | loginUser                                                                   |
| Parameter Input/Keluaran | Input: username (string), password (string). Output: Integer 1 atau 0.      |

```
MODUL authenticateUser (Input: username: string, password: string; Output: result: integer)
DEKLARASI
    user: POINTER TO User;
    hashedPassword: char[65];
ALGORITMA
    user <- findUserByUsername(username);
    IF user = NULL THEN
        PRINT "Username tidak ada";
        RETURN 0;
    ENDIF

    encrypt(password, hashedPassword);
    result <- strcmp(user->password, hashedPassword) = 0;
    free(user);
    RETURN result;
END MODUL
```

| Nama Modul               | registerUser                                                                                     |
| ------------------------ | ------------------------------------------------------------------------------------------------ |
| Deskripsi                | Mendaftarkan pengguna baru dengan validasi data input.                                           |
| I.S                      | Tidak ada pengguna baru dalam sistem.                                                            |
| F.S                      | Pengguna baru terdaftar jika data valid, atau gagal jika ada kesalahan.                          |
| Modul yang Dipanggil     | createUser, findUserByUsername                                                                   |
| Modul Pemanggil          | Menu utama atau fungsi terkait pendaftaran pengguna.                                             |
| Parameter Input/Keluaran | Input: data pengguna baru (username, password, nama, email, notelp). Output: Status pendaftaran. |

```
MODUL registerUser ()
DEKLARASI
    username, password, confirmPassword, name, email, notelp: char;
    user, newUser: POINTER TO User;
ALGORITMA
    WHILE TRUE DO
        PRINT "Masukkan username: ";
        READ username;
        user <- findUserByUsername(username);
        IF user != NULL THEN
            PRINT "Username sudah terdaftar";
            CONTINUE;
        ENDIF
        BREAK;
    ENDWHILE

    PRINT "Masukkan password: ";
    READ password;
    PRINT "Konfirmasi password: ";
    READ confirmPassword;
    IF strcmp(password, confirmPassword) != 0 THEN
        PRINT "Password tidak cocok. Pendaftaran gagal.";
        RETURN;
    ENDIF

    PRINT "Masukkan nama: ";
    READ name;
    PRINT "Masukkan email: ";
    READ email;
    PRINT "Masukkan notelp: ";
    READ notelp;

    newUser <- createUser(username, password, name, email, notelp, CLIENT);
    IF newUser = NULL THEN
        PRINT "Registrasi Gagal.";
        RETURN;
    ENDIF

    PRINT "Registrasi berhasil! Anda dapat login sekarang.";
    free(newUser);
END MODUL
```

| Nama Modul               | loginUser                                                                 |
| ------------------------ | ------------------------------------------------------------------------- |
| Deskripsi                | Melakukan proses login dengan mencocokkan username dan password pengguna. |
| I.S                      | Username dan password diberikan.                                          |
| F.S                      | Login berhasil dan sesi tersimpan, atau login gagal.                      |
| Modul yang Dipanggil     | authenticateUser, findUserByUsername, saveSession                         |
| Modul Pemanggil          | Menu utama atau fungsi login.                                             |
| Parameter Input/Keluaran | Input: username (string), password (string). Output: Integer 1 atau 0.    |

```
MODUL loginUser ()
DEKLARASI
    username: char[MAX_USERNAME];
    password: char[MAX_PASSWORD];
    foundUser: POINTER TO User;
ALGORITMA
    PRINT "Masukkan username: ";
    READ username;
    PRINT "Masukkan password: ";
    READ password;

    IF authenticateUser(username, password) THEN
        foundUser <- findUserByUsername(username);
        IF foundUser != NULL THEN
            saveSession(foundUser);
            free(foundUser);
            PRINT "Login berhasil!";
            RETURN 1;
        ENDIF
    ENDIF

    PRINT "Username atau password salah.";
    RETURN 0;
END MODUL
```

| Nama Modul               | saveSession                                      |
| ------------------------ | ------------------------------------------------ |
| Deskripsi                | Menyimpan informasi sesi pengguna ke dalam file. |
| I.S                      | Sesi pengguna tersedia.                          |
| F.S                      | Sesi pengguna tersimpan ke file "session.bin".   |
| Modul yang Dipanggil     | Tidak ada                                        |
| Modul Pemanggil          | loginUser                                        |
| Parameter Input/Keluaran | Input: user (User struct). Output: Tidak ada.    |

```
MODUL saveSession (Input: user: POINTER TO User)
DEKLARASI
    file: FILE POINTER;
ALGORITMA
    file <- fopen("session.bin", "wb");
    IF file != NULL THEN
        fwrite(user, sizeof(User), 1, file);
        fclose(file);
    ENDIF
END MODUL
```

| Nama Modul               | clearSession                               |
| ------------------------ | ------------------------------------------ |
| Deskripsi                | Menghapus file sesi pengguna untuk logout. |
| I.S                      | File sesi pengguna ada.                    |
| F.S                      | File sesi pengguna dihapus.                |
| Modul yang Dipanggil     | Tidak ada                                  |
| Modul Pemanggil          | Menu logout atau fungsi terkait.           |
| Parameter Input/Keluaran | Tidak ada.                                 |

```
MODUL clearSession ()
ALGORITMA
    remove("session.bin");
END MODUL
```

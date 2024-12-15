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

| Nama Modul               | User Setters dan Getters                                                                                                            |
| ------------------------ | ----------------------------------------------------------------------------------------------------------------------------------- |
| Deskripsi                | Mengatur dan mendapatkan atribut-atribut dari objek User seperti username, password, nama, email, dan no telp.                      |
| I.S                      | Objek User sudah diinisialisasi.                                                                                                    |
| F.S                      | Atribut User berhasil diatur atau diperoleh sesuai permintaan.                                                                      |
| Modul yang Dipanggil     | encrypt (hanya untuk setPassword).                                                                                                  |
| Modul Pemanggil          | Fungsi lain yang memerlukan manipulasi data User.                                                                                   |
| Parameter Input/Keluaran | Input: objek User dan nilai atribut baru (setter) atau objek User (getter). Output: Nilai atribut (getter) atau tidak ada (setter). |

```
MODUL setUsername (Input: user: POINTER TO User, username: string)
ALGORITMA
    strncpy(user->username, username, sizeof(user->username) - 1);
    user->username[sizeof(user->username) - 1] <- '\0';
END MODUL

MODUL setPassword (Input: user: POINTER TO User, password: string)
DEKLARASI
    hashedPassword: char[65];
ALGORITMA
    encrypt(password, hashedPassword);
    strncpy(user->password, hashedPassword, sizeof(user->password) - 1);
    user->password[sizeof(user->password) - 1] <- '\0';
END MODUL

MODUL setName (Input: user: POINTER TO User, name: string)
ALGORITMA
    strncpy(user->name, name, sizeof(user->name) - 1);
    user->name[sizeof(user->name) - 1] <- '\0';
END MODUL

MODUL setEmail (Input: user: POINTER TO User, email: string)
ALGORITMA
    strncpy(user->email, email, sizeof(user->email) - 1);
    user->email[sizeof(user->email) - 1] <- '\0';
END MODUL

MODUL setNoTelp (Input: user: POINTER TO User, notelp: string)
ALGORITMA
    strncpy(user->notelp, notelp, sizeof(user->notelp) - 1);
    user->notelp[sizeof(user->notelp) - 1] <- '\0';
END MODUL

MODUL getUsername (Input: user: POINTER TO User; Output: result: string)
ALGORITMA
    RETURN user->username;
END MODUL

MODUL getPassword (Input: user: POINTER TO User; Output: result: string)
ALGORITMA
    RETURN user->password;
END MODUL

MODUL getName (Input: user: POINTER TO User; Output: result: string)
ALGORITMA
    RETURN user->name;
END MODUL

MODUL getEmail (Input: user: POINTER TO User; Output: result: string)
ALGORITMA
    RETURN user->email;
END MODUL

MODUL getNoTelp (Input: user: POINTER TO User; Output: result: string)
ALGORITMA
    RETURN user->notelp;
END MODUL
```

| Nama Modul               | menuUser                                                                                       |
| ------------------------ | ---------------------------------------------------------------------------------------------- |
| Deskripsi                | Mengelola pengguna dengan menampilkan, menambahkan, memperbarui, atau menghapus data pengguna. |
| I.S                      | Data pengguna tersedia dalam database.                                                         |
| F.S                      | Operasi pada data pengguna selesai dilakukan sesuai pilihan.                                   |
| Modul yang Dipanggil     | loadUser, filterUserByRole, printUserTable, createUserMenu, updateUserMenu, deleteUser         |
| Modul Pemanggil          | Menu utama aplikasi.                                                                           |
| Parameter Input/Keluaran | Tidak ada.                                                                                     |

```
MODUL menuUser ()
DEKLARASI
    users: POINTER TO User;
    count, page, perPage, selection, pointer, command: integer;
ALGORITMA
    count <- loadUser(&users);

    IF getCurrentUser()->role = MANAGER THEN
        filterUserByRole(&users, PETUGAS);
    ELSE IF getCurrentUser()->role = PETUGAS THEN
        filterUserByRole(&users, CLIENT);
    ENDIF

    page <- 1;
    perPage <- 10;
    pointer <- 1;

    WHILE TRUE DO
        system("cls");
        selection <- (page - 1) * perPage + pointer;

        printUserTable(users, count, page, perPage, selection);
        PRINT MENU_OPTIONS;

        command <- getch();
        IF command = NAVIGATION THEN
            HANDLE_NAVIGATION;
        ELSE IF command = 'C' OR command = 'c' THEN
            createUserMenu();
            RELOAD_USERS;
        ELSE IF command = 'U' OR command = 'u' THEN
            updateUserMenu(users[selection - 1]);
            RELOAD_USERS;
        ELSE IF command = 'D' OR command = 'd' THEN
            deleteUser(users[selection - 1]);
            RELOAD_USERS;
        ELSE IF command = 'E' OR command = 'e' THEN
            free(users);
            RETURN;
        ELSE
            PRINT INVALID_COMMAND;
        ENDIF
    ENDWHILE
END MODUL
```

| Nama Modul               | createUserMenu                                         |
| ------------------------ | ------------------------------------------------------ |
| Deskripsi                | Menambahkan pengguna baru ke dalam database.           |
| I.S                      | Tidak ada pengguna baru yang ditambahkan.              |
| F.S                      | Data pengguna baru ditambahkan ke database jika valid. |
| Modul yang Dipanggil     | findUserByUsername, createUser                         |
| Modul Pemanggil          | menuUser                                               |
| Parameter Input/Keluaran | Tidak ada.                                             |

```
MODUL createUserMenu ()
DEKLARASI
    username, password, confirmPassword, name, email, notelp: string;
    role, limitRole: integer;
ALGORITMA
    WHILE TRUE DO
        INPUT_USERNAME;
        IF VALID_USERNAME THEN
            BREAK;
        ENDIF
    ENDWHILE

    WHILE TRUE DO
        INPUT_PASSWORD;
        IF PASSWORDS_MATCH THEN
            BREAK;
        ENDIF
    ENDWHILE

    INPUT_NAME;
    INPUT_EMAIL;
    INPUT_NOTELP;

    SELECT_ROLE;
    User newUser <- createUser(username, password, name, email, notelp, role);
    IF newUser = NULL THEN
        PRINT ADD_USER_FAILED;
        RETURN;
    ENDIF

    PRINT ADD_USER_SUCCESS;
END MODUL
```

| Nama Modul               | updateUserMenu                                  |
| ------------------------ | ----------------------------------------------- |
| Deskripsi                | Memperbarui data pengguna yang ada di database. |
| I.S                      | Data pengguna lama tersedia di database.        |
| F.S                      | Data pengguna diperbarui sesuai input baru.     |
| Modul yang Dipanggil     | findUserByUsername, updateUser                  |
| Modul Pemanggil          | menuUser                                        |
| Parameter Input/Keluaran | Input: user (User struct).                      |

```
MODUL updateUserMenu (Input: user: User)
DEKLARASI
    username, password, confirmPassword, name, email, notelp: string;
ALGORITMA
    WHILE TRUE DO
        INPUT_USERNAME;
        IF VALID_USERNAME THEN
            BREAK;
        ENDIF
    ENDWHILE

    WHILE TRUE DO
        INPUT_PASSWORD;
        IF PASSWORDS_MATCH THEN
            BREAK;
        ENDIF
    ENDWHILE

    INPUT_NAME;
    INPUT_EMAIL;
    INPUT_NOTELP;

    User updatedUser <- updateUser(user.id, username, password, name, email, notelp, user.role);
    IF updatedUser = NULL THEN
        PRINT UPDATE_USER_FAILED;
        RETURN;
    ENDIF

    PRINT UPDATE_USER_SUCCESS;
END MODUL
```

| Nama Modul               | findUserByID                                                             |
| ------------------------ | ------------------------------------------------------------------------ |
| Deskripsi                | Mencari pengguna berdasarkan ID dari database pengguna.                  |
| I.S                      | Database pengguna tersedia.                                              |
| F.S                      | Mengembalikan objek User jika ditemukan, atau NULL jika tidak ditemukan. |
| Modul yang Dipanggil     | Tidak ada.                                                               |
| Modul Pemanggil          | Fungsi lain yang membutuhkan data pengguna berdasarkan ID.               |
| Parameter Input/Keluaran | Input: id (integer). Output: POINTER TO User.                            |

```
MODUL findUserByID (Input: id: integer; Output: result: POINTER TO User)
DEKLARASI
    file: FILE POINTER;
    user: POINTER TO User;
ALGORITMA
    file <- fopen(USER_DATABASE_NAME, "r");
    IF file = NULL THEN
        RETURN NULL;
    ENDIF

    user <- malloc(sizeof(User));
    IF user = NULL THEN
        fclose(file);
        RETURN NULL;
    ENDIF

    WHILE fscanf(file, USER_GETTER_FORMAT, &user->id, user->username, user->password, user->name, user->email, user->notelp, (int *)&user->role) = 7 DO
        IF user->id = id THEN
            fclose(file);
            RETURN user;
        ENDIF
    ENDWHILE

    fclose(file);
    free(user);
    RETURN NULL;
END MODUL
```

| Nama Modul               | findUserByUsername                                                       |
| ------------------------ | ------------------------------------------------------------------------ |
| Deskripsi                | Mencari pengguna berdasarkan username dari database pengguna.            |
| I.S                      | Database pengguna tersedia.                                              |
| F.S                      | Mengembalikan objek User jika ditemukan, atau NULL jika tidak ditemukan. |
| Modul yang Dipanggil     | Tidak ada.                                                               |
| Modul Pemanggil          | Fungsi lain yang membutuhkan data pengguna berdasarkan username.         |
| Parameter Input/Keluaran | Input: username (string). Output: POINTER TO User.                       |

```
MODUL findUserByUsername (Input: username: string; Output: result: POINTER TO User)
DEKLARASI
    file: FILE POINTER;
    user: POINTER TO User;
ALGORITMA
    file <- fopen(USER_DATABASE_NAME, "r");
    IF file = NULL THEN
        RETURN NULL;
    ENDIF

    user <- malloc(sizeof(User));
    IF user = NULL THEN
        fclose(file);
        RETURN NULL;
    ENDIF

    WHILE fscanf(file, USER_GETTER_FORMAT, &user->id, user->username, user->password, user->name, user->email, user->notelp, (int *)&user->role) != EOF DO
        IF strcmp(user->username, username) = 0 THEN
            fclose(file);
            RETURN user;
        ENDIF
    ENDWHILE

    fclose(file);
    free(user);
    RETURN NULL;
END MODUL
```

| Nama Modul               | createUser                                                                                                                         |
| ------------------------ | ---------------------------------------------------------------------------------------------------------------------------------- |
| Deskripsi                | Membuat pengguna baru dan menyimpannya ke database.                                                                                |
| I.S                      | Database pengguna tersedia.                                                                                                        |
| F.S                      | Data pengguna baru ditambahkan ke database.                                                                                        |
| Modul yang Dipanggil     | setUsername, setPassword, setName, setEmail, setNoTelp, getLastAvailableID                                                         |
| Modul Pemanggil          | Fungsi lain yang membutuhkan penambahan data pengguna.                                                                             |
| Parameter Input/Keluaran | Input: username (string), password (string), name (string), email (string), notelp (string), role (Role). Output: POINTER TO User. |

```
MODUL createUser (Input: username: string, password: string, name: string, email: string, notelp: string, role: Role; Output: result: POINTER TO User)
DEKLARASI
    user: POINTER TO User;
    file: FILE POINTER;
    id: integer;
ALGORITMA
    user <- malloc(sizeof(User));
    IF user = NULL THEN
        RETURN NULL;
    ENDIF

    setUsername(user, username);
    setPassword(user, password);
    setName(user, name);
    setEmail(user, email);
    setNoTelp(user, notelp);
    user->role <- role;

    file <- fopen(USER_DATABASE_NAME, "a");
    IF file = NULL THEN
        free(user);
        RETURN NULL;
    ENDIF

    id <- getLastAvailableID(USER_DATABASE_NAME);
    user->id <- id;

    fprintf(file, USER_SETTER_FORMAT, user->id, user->username, user->password, user->name, user->email, user->notelp, user->role);
    fclose(file);
    RETURN user;
END MODUL
```

| Nama Modul               | updateUser                                                                                                                                       |
| ------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------ |
| Deskripsi                | Memperbarui data pengguna yang ada di database.                                                                                                  |
| I.S                      | Data pengguna lama tersedia di database.                                                                                                         |
| F.S                      | Data pengguna diperbarui sesuai input baru.                                                                                                      |
| Modul yang Dipanggil     | setUsername, setPassword, setName, setEmail, setNoTelp                                                                                           |
| Modul Pemanggil          | Fungsi lain yang membutuhkan pembaruan data pengguna.                                                                                            |
| Parameter Input/Keluaran | Input: id (integer), username (string), password (string), name (string), email (string), notelp (string), role (Role). Output: POINTER TO User. |

```
MODUL updateUser (Input: id: integer, username: string, password: string, name: string, email: string, notelp: string, role: Role; Output: result: POINTER TO User)
DEKLARASI
    updatedUser: POINTER TO User;
    fromFile, toFile: FILE POINTER;
    count, i: integer;
    users: array OF User;
ALGORITMA
    updatedUser <- malloc(sizeof(User));
    IF updatedUser = NULL THEN
        RETURN NULL;
    ENDIF

    setUsername(updatedUser, username);
    setPassword(updatedUser, password);
    setName(updatedUser, name);
    setEmail(updatedUser, email);
    setNoTelp(updatedUser, notelp);
    updatedUser->role <- role;

    fromFile <- fopen(USER_DATABASE_NAME, "r");
    IF fromFile = NULL THEN
        free(updatedUser);
        RETURN NULL;
    ENDIF

    count <- countUserData();
    IF count = -1 THEN
        RETURN NULL;
    ENDIF

    FOR i <- 0 TO count - 1 DO
        fscanf(fromFile, USER_GETTER_FORMAT, &users[i].id, users[i].username, users[i].password, users[i].name, users[i].email, users[i].notelp, &users[i].role);
        IF users[i].id = id THEN
            users[i] <- *updatedUser;
        ENDIF
    ENDFOR
    fclose(fromFile);

    toFile <- fopen(USER_DATABASE_NAME, "w");
    FOR i <- 0 TO count - 1 DO
        fprintf(toFile, USER_SETTER_FORMAT, users[i].id, users[i].username, users[i].password, users[i].name, users[i].email, users[i].notelp, users[i].role);
    ENDFOR
    fclose(toFile);

    RETURN updatedUser;
END MODUL
```

| Nama Modul               | deleteUser                                                                 |
| ------------------------ | -------------------------------------------------------------------------- |
| Deskripsi                | Menghapus data pengguna dari database.                                     |
| I.S                      | Data pengguna tersedia di database.                                        |
| F.S                      | Data pengguna dihapus dari database jika konfirmasi berhasil.              |
| Modul yang Dipanggil     | countUserData, showMenu                                                    |
| Modul Pemanggil          | Fungsi lain yang membutuhkan penghapusan data pengguna.                    |
| Parameter Input/Keluaran | Input: user (User struct). Output: Integer 1 jika berhasil, -1 jika gagal. |

```
MODUL deleteUser (Input: user: User; Output: result: integer)
DEKLARASI
    fromFile, toFile: FILE POINTER;
    users: array OF User;
    count, i: integer;
    temp: User;
    head: string;
ALGORITMA
    head <- sprintf("Apakah Anda yakin ingin menghapus data user dengan username '%s'?", user.username);
    menu <- ["Tidak, Batalkan", "Ya, Hapus"];
    selection <- showMenu(menu, 2, head);

    IF selection = 1 THEN
        RETURN 1;
    ENDIF

    fromFile <- fopen(USER_DATABASE_NAME, "r");
    IF fromFile = NULL THEN
        RETURN -1;
    ENDIF

    count <- countUserData();
    IF count = -1 THEN
        RETURN -1;
    ENDIF

    FOR i <- 0 TO count - 1 DO
        fscanf(fromFile, USER_GETTER_FORMAT, &temp.id, temp.username, temp.password, temp.name, temp.email, temp.notelp, &temp.role);
        IF temp.id != user.id THEN
            users[i] <- temp;
        ENDIF
    ENDFOR
    fclose(fromFile);

    toFile <- fopen(USER_DATABASE_NAME, "w");
    FOR i <- 0 TO count - 2 DO
        fprintf(toFile, USER_SETTER_FORMAT, users[i].id, users[i].username, users[i].password, users[i].name, users[i].email, users[i].notelp, users[i].role);
    ENDFOR
    fclose(toFile);

    RETURN 1;
END MODUL
```

| Nama Modul               | countUserData                                                         |
| ------------------------ | --------------------------------------------------------------------- |
| Deskripsi                | Menghitung jumlah pengguna dalam database.                            |
| I.S                      | Database pengguna tersedia.                                           |
| F.S                      | Mengembalikan jumlah record pengguna dalam file database.             |
| Modul yang Dipanggil     | Tidak ada.                                                            |
| Modul Pemanggil          | Fungsi lain yang membutuhkan jumlah pengguna.                         |
| Parameter Input/Keluaran | Input: Tidak ada. Output: Jumlah record (integer) atau -1 jika gagal. |

```
MODUL countUserData (Output: count: integer)
DEKLARASI
    file: FILE POINTER;
    count: integer;
    user: User;
ALGORITMA
    file <- fopen(USER_DATABASE_NAME, "r");
    IF file = NULL THEN
        PRINT "File gagal dibuka.";
        RETURN -1;
    ENDIF

    count <- 0;
    WHILE fscanf(file, USER_GETTER_FORMAT, &user.id, user.username, user.password, user.name, user.email, user.notelp, &user.role) != EOF DO
        count <- count + 1;
    ENDWHILE
    fclose(file);
    RETURN count;
END MODUL
```

| Nama Modul               | loadUser                                                                                  |
| ------------------------ | ----------------------------------------------------------------------------------------- |
| Deskripsi                | Memuat data pengguna dari file database ke dalam array.                                   |
| I.S                      | Database pengguna tersedia.                                                               |
| F.S                      | Data pengguna dimuat ke dalam array.                                                      |
| Modul yang Dipanggil     | countUserData                                                                             |
| Modul Pemanggil          | Fungsi lain yang membutuhkan data pengguna.                                               |
| Parameter Input/Keluaran | Input: users (POINTER TO User ARRAY). Output: Jumlah record (integer) atau -1 jika gagal. |

```
MODUL loadUser (Output: users: POINTER TO User ARRAY; result: integer)
DEKLARASI
    file: FILE POINTER;
    count, i: integer;
ALGORITMA
    file <- fopen(USER_DATABASE_NAME, "r");
    IF file = NULL THEN
        PRINT "File gagal dibuka.";
        RETURN -1;
    ENDIF

    count <- countUserData();

    users <- malloc(count * sizeof(User));
    IF users = NULL THEN
        PRINT "Gagal mengalokasi memori.";
        fclose(file);
        RETURN -1;
    ENDIF

    rewind(file);
    i <- 0;
    WHILE fscanf(file, USER_GETTER_FORMAT, &users[i].id, users[i].username, users[i].password, users[i].name, users[i].email, users[i].notelp, &users[i].role) != EOF DO
        i <- i + 1;
    ENDWHILE
    fclose(file);
    RETURN count;
END MODUL
```

| Nama Modul               | printUserTable                                                                                                         |
| ------------------------ | ---------------------------------------------------------------------------------------------------------------------- |
| Deskripsi                | Menampilkan tabel data pengguna dalam format yang rapi.                                                                |
| I.S                      | Data pengguna tersedia dalam array.                                                                                    |
| F.S                      | Data pengguna ditampilkan dalam format tabel di konsol.                                                                |
| Modul yang Dipanggil     | Tidak ada.                                                                                                             |
| Modul Pemanggil          | Fungsi lain yang membutuhkan tampilan data pengguna.                                                                   |
| Parameter Input/Keluaran | Input: users (User ARRAY), count (integer), page (integer), perPage (integer), selection (integer). Output: Tidak ada. |

```
MODUL printUserTable (Input: users: User ARRAY, count: integer, page: integer, perPage: integer, selection: integer)
DEKLARASI
    idWidth, usernameWidth, nameWidth, emailWidth, notelpWidth, roleWidth, tableWidth, start, end, i: integer;
    roleString: string;
ALGORITMA
    idWidth <- 2;
    usernameWidth <- 8;
    nameWidth <- 4;
    emailWidth <- 5;
    notelpWidth <- 6;
    roleWidth <- 8;

    start <- (page - 1) * perPage;
    end <- start + perPage;
    IF end > count THEN
        end <- count;
    ENDIF

    FOR i <- start TO end - 1 DO
        idWidth <- MAX(idWidth, LENGTH(users[i].id));
        usernameWidth <- MAX(usernameWidth, LENGTH(users[i].username));
        nameWidth <- MAX(nameWidth, LENGTH(users[i].name));
        emailWidth <- MAX(emailWidth, LENGTH(users[i].email));
        notelpWidth <- MAX(notelpWidth, LENGTH(users[i].notelp));
    ENDFOR

    tableWidth <- FORMAT_WIDTH(idWidth, usernameWidth, nameWidth, emailWidth, notelpWidth, roleWidth);
    PRINT HEADER_LINE(tableWidth);
    PRINT HEADER(idWidth, usernameWidth, nameWidth, emailWidth, notelpWidth, roleWidth);
    PRINT HEADER_LINE(tableWidth);

    FOR i <- start TO end - 1 DO
        roleString <- ROLE_TO_STRING(users[i].role);
        IF selection = i + 1 THEN
            PRINT SELECTED_ROW(users[i], idWidth, usernameWidth, nameWidth, emailWidth, notelpWidth, roleWidth, roleString);
        ELSE
            PRINT ROW(users[i], idWidth, usernameWidth, nameWidth, emailWidth, notelpWidth, roleWidth, roleString);
        ENDIF
    ENDFOR

    PRINT HEADER_LINE(tableWidth);
    PRINT PAGE_INFO(page, (count + perPage - 1) / perPage);
END MODUL
```

| Nama Modul               | filterUserByRole                                                                                                              |
| ------------------------ | ----------------------------------------------------------------------------------------------------------------------------- |
| Deskripsi                | Menyaring data pengguna berdasarkan role tertentu.                                                                            |
| I.S                      | Data pengguna tersedia di database.                                                                                           |
| F.S                      | Data pengguna dengan role tertentu dimuat ke dalam array.                                                                     |
| Modul yang Dipanggil     | countUserData                                                                                                                 |
| Modul Pemanggil          | Fungsi lain yang membutuhkan filter data pengguna.                                                                            |
| Parameter Input/Keluaran | Input: users (POINTER TO User ARRAY), role (Role). Output: Jumlah pengguna dengan role tertentu (integer) atau -1 jika gagal. |

```
MODUL filterUserByRole (Input: role: Role; Output: users: POINTER TO User ARRAY; result: integer)
DEKLARASI
    file: FILE POINTER;
    totalCount, validCount, i, j: integer;
    allUsers: POINTER TO User;
ALGORITMA
    file <- fopen(USER_DATABASE_NAME, "r");
    IF file = NULL THEN
        RETURN -1;
    ENDIF

    totalCount <- countUserData();

    allUsers <- malloc(totalCount * sizeof(User));
    IF allUsers = NULL THEN
        fclose(file);
        RETURN -1;
    ENDIF

    validCount <- 0;
    FOR i <- 0 TO totalCount - 1 DO
        fscanf(file, USER_GETTER_FORMAT, &allUsers[i].id, allUsers[i].username, allUsers[i].password, allUsers[i].name, allUsers[i].email, allUsers[i].notelp, &allUsers[i].role);
        IF allUsers[i].role = role THEN
            validCount <- validCount + 1;
        ENDIF
    ENDFOR

    fclose(file);

    users <- malloc(validCount * sizeof(User));
    IF users = NULL THEN
        free(allUsers);
        RETURN -1;
    ENDIF

    j <- 0;
    FOR i <- 0 TO totalCount - 1 DO
        IF allUsers[i].role = role THEN
            users[j] <- allUsers[i];
            j <- j + 1;
        ENDIF
    ENDFOR

    free(allUsers);
    RETURN validCount;
END MODUL
```

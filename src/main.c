#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "db.h"

int main()
{
    // User *user = newUser();

    // User userData = {
    //     "ini adalah username",
    //     "ini adalah password",
    //     "ini adalah nama",
    //     "ini adlaah email",
    //     "ini adalah no telp",
    //     ADMIN,
    // };

    // user->create(userData);

    const char *filename = "db/users.csv"; 
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return 1;  // Return 1 to indicate error
    }

    User user;
    int line_count = 0;

    // Read file using fscanf
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d\n",
                  &user.id,  // Note: no & needed when printing
                  user.username,
                  user.password,
                  user.name,
                  user.email,
                  user.notelp,
                  &user.role) == 7) {
        
        line_count++;
        
        printf("\nUser #%d:\n", line_count);
        printf("ID: %d\n", user.id); 
        printf("Username: %s\n", user.username);
        printf("Password: %s\n", user.password);
        printf("Name: %s\n", user.name);
        printf("Email: %s\n", user.email);
        printf("Phone: %s\n", user.notelp);
        printf("------------------------\n");
    }

    fclose(file);
    return 0;  // Successfully completed

    // User user;
    // int pilihan;

    // while (1)
    // {
    //     tampilkanMenu();
    //     printf("Pilih menu: ");
    //     scanf("%d", &pilihan);
    //     getchar(); // untuk menghapus newline setelah input

    //     switch (pilihan)
    //     {
    //     case 1:
    //         // authAdmin();
    //         break;
    //     case 2:
    //         authUser(&user);
    //         break;
    //     case 3:
    //         addUser();
    //         break;
    //     case 4:
    //         printf("Keluar dari program.\n");
    //         exit(0);
    //     default:
    //         printf("Pilihan tidak valid. Coba lagi.\n");
    //     }
    // }
    // return 0;
}

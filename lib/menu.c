#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "user.h"
#include "auth.h"

// ================================== core ================================== //

MenuConfig getGuestMenu() {
    char *options[] = {
        "Login",
        "Register",
        "Keluar"
    };
    return createMenuConfig(options, 3, "Selamat datang di aplikasi bioskop");
}

MenuConfig getUserMenu(User *user) {
    char *options[] = {
        "Tiket ku",
        "Pesan Tiket",
        "Profil",
        "Logout"
    };
    char message[100];
    sprintf(message, "Hallo, %s", user->name);
    return createMenuConfig(options, 4, message);
}

MenuConfig createMenuConfig(char **options, int count, char *message) {
    MenuConfig config = {options, count, message};
    return config;
}

void handleGuestSelection(int selection, User **currentUser) {
    switch (selection) {
        case 1: loginUser(currentUser); break;
        case 2: registerUser(currentUser); break;
        case 3: exit(0);
    }
}

void handleUserSelection(int selection, User **currentUser) {
    switch (selection) {
        case 1: printf("Tiket ku\n"); break;
        case 2: printf("Pesan Tiket\n"); break;
        case 3: printf("Profil\n"); break;
        case 4: *currentUser = NULL; break;
    }
}

void handleMenu(User **currentUser) {
    char *menu[255];
    MenuConfig config;
    
    if (*currentUser == NULL) {
        config = getGuestMenu();
    } else {
        config = getUserMenu(*currentUser);
    }
    
    setMenu(menu, config.options, config.count);

    int selection = showMenu(menu, config.count, config.message);
    
    if (*currentUser == NULL) {
        handleGuestSelection(selection, currentUser);
    } else {
        handleUserSelection(selection, currentUser);
    }
}

void setMenu(char **menu, char **newMenu, int newMenuSize)
{
    for (int i = 0; i < newMenuSize; i++)
    {
        menu[i] = newMenu[i];
    }
}

int showMenu(char *menu[], int menuLength, char *menuMessage)
{
    int key = 0;
    int selected = 0;

    while (1)
    {
        system("cls");

        printf("%s\n", menuMessage);

        for (int i = 0; i < menuLength; i++)
        {
            if (selected == i)
            {
                printf("-> %s\n", menu[i]);
            }
            else
            {
                printf("   %s\n", menu[i]);
            }
        }

        key = getch();

        if (key == 224)
        {
            key = getch();

            if (key == 72 && selected > 0)
            {
                selected--;
            }
            else if (key == 80 && selected < menuLength - 1)
            {
                selected++;
            }
        }
        else if (key == 13)
        {
            break;
        }
    }

    return selected + 1;
}

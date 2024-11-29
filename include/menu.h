#ifndef MENU_H
#define MENU_H


#include "user.h"

typedef struct
{
    char **options;
    int count;
    char *message;
} MenuConfig;

MenuConfig createMenuConfig(char **options, int count, char *message);

MenuConfig getGuestMenu();
MenuConfig getUserMenu(User *user);

void handleGuestSelection(int selection, User **currentUser);
void handleUserSelection(int selection, User **currentUser);

void handleMenu(User **currentUser);

void setMenu(char **menu, char **newMenu, int newMenuSize);

int showMenu(char *menu[], int menuLength, char *menuMessage);

#endif
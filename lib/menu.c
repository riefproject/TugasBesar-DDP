#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// ================================== core ================================== //

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
        { // Enter
            break;
        }
    }

    return selected + 1;
}

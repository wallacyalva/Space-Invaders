#include <windows.h>
#include <iostream>
#include "./include/player/gameloop.h"
#include "./include/menu.cpp"
int main()
{
    int option = -1;
    do
    {
        option = mainMenu();
        switch (option)
        {
        case 0:
            /* Play Game*/
            GameLoop();
            break;
        case 1:
            /* How to play*/
            break;
        case 2:
            /* Score*/
            break;
        case 3:
            /* About*/
            break;
        default:
            break;
        }
    } while (option != 4);
    return 0;
}
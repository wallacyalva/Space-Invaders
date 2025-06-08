#include <conio.h>
#include <iostream>
#include <string.h>
using namespace std;
void cleanmenu(short int pos)
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 17});
    cout << "Iniciar   \n";
    cout << "Como Jogar   \n";
    cout << "Score      \n";
    cout << "Sobre   \n";
    cout << "Sair   \n";
    cout << "Você pode precionar ESC para sair e ENTER para selecionar;)";
    pos += 17;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, pos});
}
int mainMenu()
{
    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    setlocale(LC_ALL, "pt_BR.UTF-8");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    cout <<
        R"(                                                                  ███████████████████   ██ █ █ ███████ 
███████╗██████╗  █████╗  ██████╗███████╗                          ███████████████████  ██ █ █ ███████   
██╔════╝██╔══██╗██╔══██╗██╔════╝██╔════╝                          ███████████████████ ██ █ █ ████████ 
███████╗██████╔╝███████║██║     █████╗                             ██████████████████████ █ ████████
╚════██║██╔═══╝ ██╔══██║██║     ██╔══╝                              ███████████████████████████████ 
███████║██║     ██║  ██║╚██████╗███████╗                              ███████████████████████████   
╚══════╝╚═╝     ╚═╝  ╚═╝ ╚═════╝╚══════╝                                ███████████████████████  
                                                                           ██████████████████   
██╗███╗   ██╗██╗   ██╗ █████╗ ██████╗ ███████╗██████╗ ███████╗                 █████████      
██║████╗  ██║██║   ██║██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔════╝
██║██╔██╗ ██║██║   ██║███████║██║  ██║█████╗  ██████╔╝███████╗   ██    ██ ███   ██  ██ ██   ███ ████   ██    ██
██║██║╚██╗██║╚██╗ ██╔╝██╔══██║██║  ██║██╔══╝  ██╔══██╗╚════██║   ██    ██ ████  ██  ██  ██  ██  █  ██  ██    ██
██║██║ ╚████║ ╚████╔╝ ██║  ██║██████╔╝███████╗██║  ██║███████║   ██    ██ ██  ████  ██  █████  ███████ ██    ██
╚═╝╚═╝  ╚═══╝  ╚═══╝  ╚═╝  ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝╚══════╝    ██████  ██    ██  ██   ████ ███   ██ ████  ██)"
         << endl;
    int option = 0;
    short int position = 0;

    do
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
        cout << "\n";
        cout << "\n";
        cout << "\n";
        cout << "\n";
        cout << "\n";
        cout << "\n"
             << "\n"
             << "\n"
             << "\n"
             << "\n"
             << "\n"
             << "\n"
             << "\n"
             << "\n"
             << "\n"
             << "\n";
        SetConsoleTitle("Space Invaders - Menu");
        if (option == 0)
        {
            cleanmenu(0);
        }
        switch (position)
        {
        case 0:
            cleanmenu(position);
            cout << "> Iniciar \n";
            break;
        case 1:
            cleanmenu(position);
            cout << "> Como Jogar \n";
            break;
        case 2:
            cleanmenu(position);
            cout << "> Score \n";
            break;
        case 3:
            cleanmenu(position);
            cout << "> Sobre \n";
            break;
        case 4:
            cleanmenu(position);
            cout << "> Sair \n";
            break;
        default:
            break;
        }

        option = getch();
        switch (option)
        {
        case 81:
        case 'q':
            return 2;
        case 72:
        case 'w':
            Beep(1300, 20);
            // Sleep(10); // pequena pausa
            Beep(900, 20);
            // cout<<"Up";
            position <= 0 ? position = 4 : position--;
            break;
        case 80:
        case 's':
            Beep(1300, 20);
            // Sleep(10); // pequena pausa
            Beep(900, 20);
            // cout<<"Down";
            position >= 4 ? position = 0 : position++;
            break;
        case 75:
        case 'a':

            // cout<<"Left";
            break;
        case 77:
        case 'd':
        case 13:
        case 32:
            Beep(100, 10);
            // enter/select option
            switch (position)
            {
            case 0:
                system("cls");
                return 0;
                break;
            case 1:
                // Informações
                return 1;
                break;
            case 2:
                return 2;
                break;
            case 3:
                return 3;
                break;
            case 4:
                return 4;
                break;
            }
            break;
        default:
            cout << option;
            break;
        }
    } while (option != 27);
    return 2;
}

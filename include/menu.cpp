#include <conio.h>
#include <iostream>
#include <string.h>
using namespace std;
void cleanmenu(short int pos,Game &game)
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 17});
    
    for (int i = 0; i < intensMenu; i++){
        cout << game.menu[i] << "         \n";
    }
    
    cout << "Você pode precionar ESC para sair e ENTER para selecionar;)";
    pos += 17;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, pos});
}
int mainMenu(Game &game)
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

        SetConsoleTitle("Space Invaders - Menu");

        cleanmenu(position,game);
        cout << "> " << game.menu[position] <<  "\n";

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
            position <= 0 ? position = 5 : position--;
            break;
        case 80:
        case 's':
            Beep(1300, 20);
            // Sleep(10); // pequena pausa
            Beep(900, 20);
            // cout<<"Down";
            position >= 5 ? position = 0 : position++;
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
            case 5:
                return 5;
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

enum Dificuldade { FACIL = 0, MEDIO = 1, DIFICIL = 2 };

void mostrarOpcoesDificuldade(int selecao) {
    const char *dificuldades[] = {"Fácil", "Médio", "Difícil"};

    COORD pos = {0, 20};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    for (int i = 0; i < 3; i++) {
        if (i == selecao) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Verde
        } else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Branco
        }
        cout << dificuldades[i] << "   ";
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Reset para branco
    cout << "\n\nUse ← → A D para navegar, Enter ou Espaço para confirmar";
}

int escolherDificuldade(int difficulty) {
    system("cls");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 18});
    cout << "Selecione a Dificuldade:\n";

    int selecao = difficulty;
    int tecla;

    mostrarOpcoesDificuldade(selecao);

    do {
        tecla = getch();

        switch (tecla) {
        case 75: // ←
        case 'a':
        case 'A':
            Beep(700, 50);
            selecao = (selecao - 1 + 3) % 3;
            break;
        case 77: // →
        case 'd':
        case 'D':
            Beep(700, 50);
            selecao = (selecao + 1) % 3;
            break;
        case 13: // Enter
        case 32: // Espaço
            Beep(1200, 80);
            return selecao;
        }

        mostrarOpcoesDificuldade(selecao);
    } while (true);
}

void aplicarDificuldade(Game &game) {
    switch (game.difficulty) {
        // Fácil
        case 0:{
            for (int i = 0; i < maxEnemies; i++) {
                if(((i/10) * 10) == i || (1 + ((i/10) * 10)) == i || (3 + ((i/10) * 10)) == i || (5 + ((i/10) * 10)) == i|| (7 + ((i/10) * 10)) == i|| (9 + ((i/10) * 10)) == i || (10 + ((i/10) * 10)) == i){
                    enemiesLive[i].active = false;
                }else{
                    enemiesLive[i].active = true;
                }
            }
            game.player.health = 5; 
        }
        break;
        // Médio
        case 1: {
            game.player.health = 4;
            for (int i = 0; i < maxEnemies; i++) {
                if((1 + ((i/10) * 10)) == i || (4 + ((i/10) * 10)) == i || (7 + ((i/10) * 10)) == i){
                    enemiesLive[i].active = false;
                }else{
                    enemiesLive[i].active = true;
                }
            }
        }    
        break;
        // Difícil
        case 2: {
            game.player.health = 3;
            for (int i = 0; i < maxEnemies; i++) {
                enemiesLive[i].active = true;
            }
        }
        break;   
        default: {
            for (int i = 0; i < maxEnemies; i++) {
                if(((i/10) * 10) == i || (1 + ((i/10) * 10)) == i || (3 + ((i/10) * 10)) == i || (5 + ((i/10) * 10)) == i|| (7 + ((i/10) * 10)) == i|| (9 + ((i/10) * 10)) == i || (10 + ((i/10) * 10)) == i){
                    enemiesLive[i].active = false;
                }else{
                    enemiesLive[i].active = true;
                }
            }
            game.player.health = 5; 
        }
        break;
    }

    game.player.maxhealth = game.player.health;
}
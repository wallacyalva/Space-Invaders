#include<windows.h>
#include<Xinput.h>
#ifndef INPUT_H
#define INPUT_H
#include "../basicStructures/gameElements.h"
using namespace std;

// Adiciona uma tecla à lista de inputs do frame atual, se houver espaço.
// Esta versão é mais segura e eficiente, evitando alocações de memória constantes.
void addInput(Input &input, int key) {
    if (input.count < MAX_INPUTS) {
        input.inputs[input.count] = key;
        input.count++;
    }
}
bool hasKeyboard = false;
bool hasController = false;
void inputGet(Input &input){
input.count = 0; // Reseta os inputs a cada frame
if (GetAsyncKeyState('A') & 0x8000)
{
    hasKeyboard = true;
    addInput(input, 'A');
}
if (GetAsyncKeyState('D') & 0x8000)
{
    hasKeyboard = true;
    addInput(input, 'D');
}
if (GetAsyncKeyState(VK_SPACE) & 0x8000)
{    
    hasKeyboard = true;
    addInput(input, VK_SPACE);
}
if (GetAsyncKeyState(VK_RETURN) & 0x8000)
{
    addInput(input, VK_RETURN);
}
if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
{
    addInput(input, VK_ESCAPE);
}
if (GetAsyncKeyState(VK_LEFT) & 0x8000)
{
    addInput(input, VK_LEFT);
}
if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
{
    addInput(input, VK_RIGHT);
}
if (GetAsyncKeyState('C') & 0x8000)
{
    addInput(input, 'C');
}
if (GetAsyncKeyState('G') & 0x8000)
{
    addInput(input, 'G');

}
if (GetAsyncKeyState('K') & 0x8000)
{
    addInput(input, 'K');
}
if (GetAsyncKeyState('I') & 0x8000)
{
    addInput(input, 'I');
}

/*Controller Support Test*/
XINPUT_STATE controllerState;
int controllerPos = 0;
//verifica se alguém usou teclado como player 1
if (hasKeyboard)
{
    controllerPos = 1;
}

//verificar se controle 0 está conectado
if (XInputGetState(0, &controllerState) == ERROR_SUCCESS)
{
    int inputs[2][3]={{'A','D',VK_SPACE},{VK_LEFT,VK_RIGHT,VK_RETURN}};
    if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT || controllerState.Gamepad.sThumbLX < 0)
    {
        addInput(input, inputs[controllerPos][0]);
    }
    if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT || controllerState.Gamepad.sThumbLX > 0)
    {
        addInput(input, inputs[controllerPos][1]);
    }
    if (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
    {
        addInput(input, inputs[controllerPos][2]);
    }
}
}
#endif
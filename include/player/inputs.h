#include<windows.h>
#include "../basicStructures/gameElements.h"
using namespace std;
void addInput(Input &input, int key) {
    // Cria novo array maior
    int* newInputs = new int[input.count + 1];

    // Copia os valores antigos
    for (int i = 0; i < input.count; i++) {
        newInputs[i] = input.inputs[i];
    }

    // Adiciona nova tecla
    newInputs[input.count] = key;
    input.count++;

    // Libera memória antiga
    delete[] input.inputs;

    // Atualiza ponteiro
    input.inputs = newInputs;
}
void inputGet(Input &input){
input.count = 0;
if (GetAsyncKeyState('A') & 0x8000)
{
    addInput(input, 'A');
}
if (GetAsyncKeyState('D') & 0x8000)
{
    
    addInput(input, 'D');
}
if (GetAsyncKeyState(VK_SPACE) & 0x8000)
{    
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
}
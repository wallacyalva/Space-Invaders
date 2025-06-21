#include <iostream>
#include <windows.h>
#include <XInput.h>
#include <cmath> // Necessário para a função sqrt (raiz quadrada)

// Função para imprimir o estado de cada botão
void print_button_state(const XINPUT_GAMEPAD& gamepad) {
    std::cout << "\n--- Botoes ---\n";
    std::cout << "  DPAD CIMA:    " << ((gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) ? "Pressionado" : "-") << std::endl;
    std::cout << "  DPAD BAIXO:   " << ((gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ? "Pressionado" : "-") << std::endl;
    std::cout << "  DPAD ESQUERDA:" << ((gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ? "Pressionado" : "-") << std::endl;
    std::cout << "  DPAD DIREITA: " << ((gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ? "Pressionado" : "-") << std::endl;
    std::cout << "  START:        " << ((gamepad.wButtons & XINPUT_GAMEPAD_START) ? "Pressionado" : "-") << std::endl;
    std::cout << "  BACK:         " << ((gamepad.wButtons & XINPUT_GAMEPAD_BACK) ? "Pressionado" : "-") << std::endl;
    std::cout << "  L-THUMB:      " << ((gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ? "Pressionado" : "-") << std::endl;
    std::cout << "  R-THUMB:      " << ((gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ? "Pressionado" : "-") << std::endl;
    std::cout << "  L-SHOULDER:   " << ((gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ? "Pressionado" : "-") << std::endl;
    std::cout << "  R-SHOULDER:   " << ((gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? "Pressionado" : "-") << std::endl;
    std::cout << "  A:            " << ((gamepad.wButtons & XINPUT_GAMEPAD_A) ? "Pressionado" : "-") << std::endl;
    std::cout << "  B:            " << ((gamepad.wButtons & XINPUT_GAMEPAD_B) ? "Pressionado" : "-") << std::endl;
    std::cout << "  X:            " << ((gamepad.wButtons & XINPUT_GAMEPAD_X) ? "Pressionado" : "-") << std::endl;
    std::cout << "  Y:            " << ((gamepad.wButtons & XINPUT_GAMEPAD_Y) ? "Pressionado" : "-") << std::endl;
}

// Função para imprimir o estado das entradas analógicas (analógicos e gatilhos)
void print_analog_inputs(const XINPUT_GAMEPAD& gamepad) {
    std::cout << "\n--- Entradas Analogicas ---\n";

    // --- Gatilhos (Triggers) ---
    // Os valores vão de 0 a 255. Normalizamos para 0.0 a 1.0.
    float leftTrigger = (float)gamepad.bLeftTrigger / 255.0f;
    float rightTrigger = (float)gamepad.bRightTrigger / 255.0f;
    std::cout << "  Gatilho Esquerdo: " << leftTrigger << " (Raw: " << (int)gamepad.bLeftTrigger << ")" << std::endl;
    std::cout << "  Gatilho Direito:  " << rightTrigger << " (Raw: " << (int)gamepad.bRightTrigger << ")" << std::endl;

    // --- Analógico Esquerdo (Left Thumbstick) ---
    float LX = gamepad.sThumbLX;
    float LY = gamepad.sThumbLY;

    // Calcula a magnitude do vetor (distância do centro)
    float magnitudeL = sqrt(LX*LX + LY*LY);
    float normalizedLX = 0.0f;
    float normalizedLY = 0.0f;

    // Verifica se a magnitude está fora da zona morta (deadzone)
    if (magnitudeL > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
        // Normaliza o valor para um intervalo de -1.0 a 1.0, considerando a deadzone
        float normalizedMagnitude = (magnitudeL - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
        normalizedLX = (LX / magnitudeL) * normalizedMagnitude;
        normalizedLY = (LY / magnitudeL) * normalizedMagnitude;
    }
    std::cout << "  Analog. Esquerdo (X, Y) Normalizado: (" << normalizedLX << ", " << normalizedLY << ")" << std::endl;

    // --- Analógico Direito (Right Thumbstick) ---
    float RX = gamepad.sThumbRX;
    float RY = gamepad.sThumbRY;
    float magnitudeR = sqrt(RX*RX + RY*RY);
    float normalizedRX = 0.0f;
    float normalizedRY = 0.0f;

    if (magnitudeR > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
        float normalizedMagnitude = (magnitudeR - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) / (32767 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
        normalizedRX = (RX / magnitudeR) * normalizedMagnitude;
        normalizedRY = (RY / magnitudeR) * normalizedMagnitude;
    }
    std::cout << "  Analog. Direito (X, Y) Normalizado:  (" << normalizedRX << ", " << normalizedRY << ")" << std::endl;
}

int main() {
    // Vamos verificar apenas o primeiro controle (índice 0)
    DWORD controllerIndex = 0;
    XINPUT_STATE state;

    std::cout << "Testador de Botoes XInput" << std::endl;
    std::cout << "Conecte um controle de Xbox. Pressione Ctrl+C para sair." << std::endl;
    Sleep(2000); // Pequena pausa para ler a mensagem inicial

    while (true) {
        // Limpa a estrutura de estado antes de usá-la
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        // Pega o estado atual do controle
        DWORD result = XInputGetState(controllerIndex, &state);

        // Limpa a tela do console para uma exibição limpa
        system("cls");

        if (result == ERROR_SUCCESS) {
            // O controle está conectado
            std::cout << "Controle " << controllerIndex + 1 << " conectado!" << std::endl;
            std::cout << "Numero do Pacote: " << state.dwPacketNumber << std::endl;
            
            print_button_state(state.Gamepad);
            print_analog_inputs(state.Gamepad);

        } else {
            // O controle não está conectado
            std::cout << "Controle " << controllerIndex + 1 << " nao esta conectado." << std::endl;
            std::cout << "Por favor, conecte um controle de Xbox e aguarde..." << std::endl;
        }

        // Aguarda um curto período para não sobrecarregar a CPU
        Sleep(100); // Delay de 100ms
    }

    return 0;
}

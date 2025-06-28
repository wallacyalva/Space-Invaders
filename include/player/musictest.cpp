#include <windows.h>
#include <mmsystem.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <fstream>
#include <iostream>
#include <string>

#pragma comment(lib, "winmm.lib")
using namespace std;

void playMidiNote(HMIDIOUT handle, int note, int velocity, int durationMs) {
    DWORD on = 0x90 | (note << 8) | (velocity << 16);
    DWORD off = 0x80 | (note << 8);

    midiOutShortMsg(handle, on);
    std::this_thread::sleep_for(std::chrono::milliseconds(durationMs));
    midiOutShortMsg(handle, off);
}

void playDescending(HMIDIOUT handle, int* scale, int size, int noteDuration = 100) {
    for (int i = size - 1; i >= 0; --i) {
        playMidiNote(handle, scale[i], 100, noteDuration);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

// Música ambiente para menu: lenta, notas espaçadas e suaves
void menuTheme(HMIDIOUT handle, int* scale, int scaleSize, int* rhythm, int rhythmSize) {
    int steps = 6 + rand() % 4;
    for (int i = 0; i < steps; ++i) {
        int note = scale[rand() % scaleSize];
        int vel = 60 + rand() % 30;   // volume mais baixo, suave
        int dur = rhythm[rand() % rhythmSize] + 100;  // notas mais longas
        playMidiNote(handle, note, vel, dur);
        std::this_thread::sleep_for(std::chrono::milliseconds(dur / 2));
    }
}

// Música para combate: ritmo mais rápido, volume alto, mais notas seguidas
void battleTheme(HMIDIOUT handle, int* scale, int scaleSize, int* rhythm, int rhythmSize) {
    int steps = 10 + rand() % 10;
    for (int i = 0; i < steps; ++i) {
        int note = scale[rand() % scaleSize];
        int vel = 90 + rand() % 30;   // volume mais alto
        int dur = rhythm[rand()% rhythmSize];
        playMidiNote(handle, note, vel, dur);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    // playDescending(handle, scale, scaleSize, 80);
}

int main() {
    srand((unsigned int)time(0));
    HMIDIOUT handle;
    int instrumento = 0; // padrão piano

    ifstream inFile("./som");
    if (inFile.is_open()) {
        string line;
        getline(inFile, line);
            int val = stoi(line);
            if (val >= 0 && val <= 127) {
                instrumento = val;
            }
        
        inFile.close();
    }

    if (midiOutOpen(&handle, 0, 0, 0, 0) != MMSYSERR_NOERROR) {
        cerr << "Erro ao abrir dispositivo MIDI.\n";
        return 1;
    }

    midiOutShortMsg(handle, 0xC0 | (instrumento << 8));

    // Escala menor para som retrô/agudo
    int scale[] = {72, 74, 75, 76, 79, 80, 82, 84};
    int rhythmMenu[] = {300, 200, 500};
    int rhythmBattle[] = {320, 380, 240, 300, 450};

    while (true) {
        // Alterna entre menu e combate (exemplo)
        cout << "Tocando tema MENU...\n";
        menuTheme(handle, scale, 8, rhythmMenu, 3);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        cout << "Tocando tema BATALHA...\n";
        battleTheme(handle, scale, 8, rhythmBattle, 5);
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }

    midiOutClose(handle);
    return 0;
}

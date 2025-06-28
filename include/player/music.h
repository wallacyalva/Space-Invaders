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


// Toca uma nota MIDI no canal 0 com o programa 0 (piano)
void playMidiNote(HMIDIOUT handle, int note, int velocity, int durationMs) {
    DWORD on = 0x90 | (note << 8) | (velocity << 16);
    DWORD off = 0x80 | (note << 8);

    midiOutShortMsg(handle, on);
    std::this_thread::sleep_for(std::chrono::milliseconds(durationMs));
    midiOutShortMsg(handle, off);
}

int main() {
    int instrumento = 0;
    ifstream inFile("./som");
    srand(time(0));
    HMIDIOUT handle;
    if (midiOutOpen(&handle, 0, 0, 0, 0) != MMSYSERR_NOERROR) return 1;
    if(inFile.is_open()){
        string line;
        getline(inFile,line);
        instrumento = stoi(line);
        inFile.close();    
    }
    // Programa de som: 0 = piano, 80 = lead synth, 81 = bass synth
    midiOutShortMsg(handle, 0xC0 | (instrumento << 8));

     // Escala de Dó menor (C minor natural): C D Eb F G Ab Bb C (notas mais "épicas")
    int scale[] = {72, 74, 75, 77, 79, 80, 82, 84}; // versão aguda (oitava acima)

    // Ritmo com mais variação dramática
    int rhythm[] = {120, 180, 240, 300, 450};

    while (true) {
        int steps = 8 + rand() % 8;
        for (int i = 0; i < steps; ++i) {
            int note = scale[rand() % 8];
            int vel = 90 + rand() % 30;
            int dur = rhythm[rand() % 4];
            playMidiNote(handle, note, vel, dur);
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }

        // Toque descendente estilo "fim de fase"
        // for (int i = 7; i >= 0; --i) {
        //     playMidiNote(handle, scale[i], 100, 100);
        // }
    }

    midiOutClose(handle);
    return 0;
}

#include <Arduino.h>
#include <pinout.h>
#include <gpio.h>
#include <ChainableLED.h>
#include <speaker.h>
#include "melody.h"
Gpio* gpio = nullptr;
ChainableLED* led = nullptr;
Speaker* speaker = nullptr;
MelodyPlayer* player = nullptr;

// 動作確認用のメロディ(きらきら星)。曲はここを差し替える
const Note testMelody[] = {
    {NOTE_C4, 4}, {NOTE_C4, 4}, {NOTE_G4, 4}, {NOTE_G4, 4},
    {NOTE_A4, 4}, {NOTE_A4, 4}, {NOTE_G4, 8},
    {NOTE_F4, 4}, {NOTE_F4, 4}, {NOTE_E4, 4}, {NOTE_E4, 4},
    {NOTE_D4, 4}, {NOTE_D4, 4}, {NOTE_C4, 8},
    {NOTE_REST, 8},
};

const Note mrsMelody[] = {
    {SI3, 4}, {MI4, 4}, {FA_S4, 4}, {SO_S4, 4},{RA4, 4}, {SI4, 6},   {NOTE_REST, 2},
    {SI4, 4}, {SI4, 4}, {RA4, 4}, {SO_S4, 4},{FA_S4, 4},{MI4, 4},{SO_S4, 6},
    {NOTE_REST, 8},

    {SI3, 4}, {MI4, 4}, {FA_S4, 4}, {SO_S4, 4},{RA4, 4}, {SI4, 6}, 
    {MI4, 2}, {MI4, 2},{NOTE_REST, 2},
    {RA4, 4}, {SO_S4, 4},{MI4, 4},{FA_S4, 4},{RE_S4, 4},{MI4, 6},
    {NOTE_REST, 4},

    {SI3, 4}, {MI4, 4}, {FA_S4, 4}, {SO_S4, 4},{RA4, 4}, {SI4, 6},   {NOTE_REST, 2},
    {MI4, 4},{DO_S5, 4},{SI4, 4},{RA4, 4},{SO_S4, 4},{RA4, 4},{SO_S4, 4},{NOTE_REST, 6},

    {MI4, 6},{NOTE_REST, 2},{MI5, 4},{SI4, 4},{RA4, 4},{SO_S4, 4},{MI4, 6},{NOTE_REST, 2},
    {SI3, 4},{SI3, 4},{SO_S4, 4},{MI4, 4},{FA_S4, 4},{RE_S4, 4},{SO_S4, 6},{NOTE_REST, 2},
 
    {MI4, 6},{NOTE_REST, 2},{MI5, 4},{SI4, 4},{RA4, 4},{SO_S4, 4},{MI4, 6},{NOTE_REST, 2},
    {MI4, 4},{RA4, 4},{SO_S4, 4},{FA_S4, 4},{MI4, 4},{RE_S4, 4},{MI4, 6},

    {NOTE_REST, 8},
};


// 初期化
void setup() {
    Serial.begin(115200);
    Serial.println("===== started =====");
    gpio = new Gpio(Pinout::D13_LED);

    led = new ChainableLED(Pinout::D2,Pinout::D3_PWM,1);
    led->init();

    speaker = new Speaker(Pinout::D6_PWM);

    player = new MelodyPlayer(speaker);
    player->play(mrsMelody, sizeof(mrsMelody) / sizeof(mrsMelody[0]), 185, true);
}

// 点滅用の関数
void Blinking(){
    Serial.println("ON");
    gpio->output(true);
    delay(800);

    Serial.println("OFF");
    gpio->output(false);
    delay(200);
}

// フルカラーLEDの関数
void UpdateLED(){
    Serial.println("Green");
    led->setColorRGB(0,0,255,0);
    delay(800);

    Serial.println("Red");
    led->setColorRGB(0,255,0,0);
    delay(200);
}

// スピーカー関数
void SpeakerUpdate(){
    Serial.println("ON");
    speaker->playTone(100);
    delay(500);

    Serial.println("OFF");
    speaker->stopTone();
    delay(1000);
}



// 更新関数
void loop() {
    //UpdateLED();
    //player->update();
}

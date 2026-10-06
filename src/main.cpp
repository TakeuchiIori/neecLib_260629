#include <Arduino.h>
#include <pinout.h>
#include <gpio.h>
#include <ChainableLED.h>
#include <speaker.h>
Gpio* gpio = nullptr;
ChainableLED* led = nullptr;
Speaker* speaker = nullptr;

// 初期化
void setup() {
    Serial.begin(115200);
    Serial.println("===== started =====");
    gpio = new Gpio(Pinout::D13_LED);

    led = new ChainableLED(Pinout::D2,Pinout::D3_PWM,1);
    led->init();

    speaker = new Speaker(Pinout::D2);
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
    delay(100);

    Serial.println("OFF");
    speaker->stopTone();
    delay(1000);
}



// 更新関数
void loop() {
    SpeakerUpdate();
}

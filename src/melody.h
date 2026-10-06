#pragma once

#include <stdint.h>
#include <speaker.h>
#include "pitches.h"

// 音符1つ分のデータ。ticks は 16分音符いくつ分か
// (16分=1, 8分=2, 4分=4, 付点4分=6, 2分=8, 全音符=16)
struct Note {
    uint16_t freq;   // 周波数(Hz)。NOTE_REST で休符
    uint8_t ticks;   // 長さ
};

class MelodyPlayer {
public:
    MelodyPlayer(Speaker* speaker);
    void play(const Note* notes, uint16_t length, uint16_t bpm, bool loop = false);
    void stop();
    void update();   // loop() から毎回呼ぶ
    bool isPlaying() const;
private:
    Speaker* speaker;       // set by constractor
    const Note* notes;
    uint16_t length;
    uint16_t index;
    uint32_t tickMs;        // 16分音符1つ分の長さ(ms)
    uint32_t noteStart;     // 今の音を鳴らし始めた時刻
    uint32_t noteMs;        // 今の音の長さ(ms)
    bool loop;
    bool playing;
};

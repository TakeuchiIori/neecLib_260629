#include <Arduino.h>
#include "melody.h"

MelodyPlayer::MelodyPlayer(Speaker* speaker)
    : speaker(speaker), notes(nullptr), length(0), index(0), tickMs(0),
      noteStart(0), noteMs(0), loop(false), playing(false) {
}

void MelodyPlayer::play(const Note* notes, uint16_t length, uint16_t bpm, bool loop) {
    if (notes == nullptr || length == 0) return;
    if (bpm == 0) bpm = 120;

    this->notes = notes;
    this->length = length;
    this->loop = loop;
    this->index = 0;
    this->tickMs = 60000UL / bpm / 4;   // 16分音符1つ分
    this->noteStart = millis();
    this->noteMs = 0;                   // 次の update() ですぐ1音目に入る
    this->playing = true;
}

void MelodyPlayer::stop() {
    this->playing = false;
    this->speaker->stopTone();
}

bool MelodyPlayer::isPlaying() const {
    return this->playing;
}

void MelodyPlayer::update() {
    if (!this->playing) return;
    if (millis() - this->noteStart < this->noteMs) return;   // 今の音の途中

    if (this->index >= this->length) {
        if (!this->loop) {
            this->stop();
            return;
        }
        this->index = 0;
    }

    // 前の音の長さ分だけ進めて、処理の遅れが積み重ならないようにする
    this->noteStart += this->noteMs;
    const Note& note = this->notes[this->index++];
    this->noteMs = (uint32_t)note.ticks * this->tickMs;

    if (note.freq == NOTE_REST) {
        this->speaker->stopTone();
        return;
    }

    // 長さの9割だけ鳴らして1割を隙間にする(同じ音が続いても区切れて聞こえる)
    uint32_t onMs = this->noteMs * 9 / 10;
    if (onMs == 0) onMs = 1;   // 0 だと tone() が止まらなくなる
    this->speaker->playTone(note.freq, onMs);
}

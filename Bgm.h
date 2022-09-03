#pragma once

#include <QAudioOutput>
#include <QMediaplayer>
#include <cmath>

class Bgm : QAudioOutput {
    QMediaPlayer* m_player;

    int m_volume;

    void applyVolume();

public:
    Bgm();

    void volumeUp();

    void volumeDown();

    void volumeSet(const int value);

    int getVolume() const;

    void mute();

    void mute(bool mute);
};

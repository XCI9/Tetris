#pragma once

#include <QAudioOutput>
#include <QMediaplayer>
#include <cmath>

class Bgm : QAudioOutput {
    QMediaPlayer* m_player;

public:
    Bgm();

    void volumeUp();

    void volumeDown();

    void mute();
};

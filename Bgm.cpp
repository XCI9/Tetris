#include "Bgm.h"

Bgm::Bgm() :
    m_player{ new QMediaPlayer{} }
{
    m_player->setSource(QUrl::fromLocalFile("bgm.mp3"));
    m_player->setLoops(QMediaPlayer::Infinite);
    m_player->setAudioOutput(this);

    setVolume(1.f);

    m_player->play();
}

void Bgm::volumeUp() {
    //volume ranging from 0 to 100000
    float currentVolume{ std::powf(10, volume() * 5) };

    currentVolume += 5000;
    if (currentVolume > 100000)
        currentVolume = 100000;

    setVolume(std::log10(currentVolume) / 5);
}

void Bgm::volumeDown() {
    //volume ranging from 0 to 100000
    float currentVolume{ std::powf(10, volume() * 5) };

    currentVolume -= 5000;
    if (currentVolume < 0)
        currentVolume = 0;

    setVolume(std::log10(currentVolume) / 5);
}

void Bgm::mute() {
    //flip muted
    setMuted(!isMuted());
}

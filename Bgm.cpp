#include "Bgm.h"

Bgm::Bgm() :
    m_player{ new QMediaPlayer{} },
    m_volume{ 50 }
{
    m_player->setSource(QUrl::fromLocalFile("bgm.mp3"));
    m_player->setLoops(QMediaPlayer::Infinite);
    m_player->setAudioOutput(this);

    applyVolume();

    m_player->play();
}

void Bgm::applyVolume() {
    // volumeSliderValue is in the range [0..100]
    //https://doc.qt.io/qt-6/qaudio.html#convertVolume
    float linearVolume{ QAudio::convertVolume(m_volume / 100.f, QAudio::LogarithmicVolumeScale, QAudio::LinearVolumeScale) };

    setVolume(linearVolume);
}

void Bgm::volumeUp() {
    m_volume += 5;

    if (m_volume > 100)
        m_volume = 100;

    applyVolume();
}

void Bgm::volumeDown() {
    m_volume -= 5;

    if (m_volume < 0)
        m_volume = 0;

    applyVolume();
}

void Bgm::volumeSet(const int value) {
    m_volume = value;

    applyVolume();
}

int Bgm::getVolume() const {
    return m_volume;
}

void Bgm::mute() {
    //flip muted
    setMuted(!isMuted());
}

void Bgm::mute(bool mute) {
    //flip muted
    setMuted(mute);
}

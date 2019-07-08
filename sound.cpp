#include "sound.h"

Sound::Sound(bool b, const QString& s, QObject* parent) : isbgm{b}
{
    sound.setParent(parent);
    sound.setSource(QUrl::fromLocalFile(s));
    if(isbgm)
    {
        sound.setVolume(BGMVolume);
        sound.setLoopCount(QSoundEffect::Infinite);  //循环
    }
}

Sound::~Sound() = default;

void Sound::slotsSetEffectVolume(int v)
{
    effectVolume = static_cast<qreal>(v) / 100.0;
}

void Sound::slotsSetBGMVolume(int v)
{
    BGMVolume = static_cast<qreal>(v) / 100.0;
    if(isbgm)
    {
        if(BGMVolume == 0.0 && sound.isPlaying())
            sound.stop();
        else if(BGMVolume > 0 && sound.isPlaying())
            sound.setVolume(BGMVolume);
        else
            sound.play();
    }
}

void Sound::run()
{
    if(!isbgm)
    {
        sound.setVolume(effectVolume);
        sound.play();                                //播放音效
    } else if(!sound.isPlaying())
        sound.play();                                //播放背景音乐
}

void Sound::slotsChangeBGM(const QString& s)
{
    if(isbgm)
    {
        sound.stop();
        sound.setSource(QUrl::fromLocalFile(tr(":/music/") + s + tr(".wav")));
        sound.play();
    }
}

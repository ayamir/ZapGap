#ifndef SOUND_H
#define SOUND_H

#include <QSoundEffect>
#include <QThread>
#include "constant.h"

class Sound : public QThread           //音乐
{
    Q_OBJECT

public:
    Sound() = delete;
    Sound(bool, const QString&,QObject* parent = nullptr);
    ~Sound();
    static double BGMVolume;          //背景音乐音量
    static double effectVolume;       //游戏音效音量

protected:
    void run();

public slots:
    void slotsSetEffectVolume(int);   //音效音量设置
    void slotsSetBGMVolume(int);      //背景音乐音量设置
    void slotsChangeBGM(const QString&); //背景音乐更改

private:
    bool isbgm;                       //背景音乐标志
    QSoundEffect sound;              //音乐
};

#endif // SOUND_H

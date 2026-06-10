#include "mediaplayer.h"
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>

MediaPlayer::MediaPlayer(){
    audioOutput = new QAudioOutput();
    mediaPlayer = new QMediaPlayer();
    clickSound = new QSoundEffect();
    spreadSound = new QSoundEffect();
    bombSound = new QSoundEffect();
    newSound = new QSoundEffect();
    extendSound = new QSoundEffect();

    audioOutput->setVolume(0.2f);
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl::fromLocalFile("./music/bgm.mp3"));
    mediaPlayer->setLoops(QMediaPlayer::Infinite);

    clickSound->setSource(QUrl::fromLocalFile("./sounds/clicked.wav"));
    clickSound->setVolume(0.01f);
    spreadSound->setSource(QUrl::fromLocalFile("./sounds/spread.wav"));
    spreadSound->setVolume(0.5f);
    bombSound->setSource(QUrl::fromLocalFile("./sounds/bomb.wav"));
    bombSound->setVolume(1.0f);
    newSound->setSource(QUrl::fromLocalFile("./sounds/nextstage.wav"));
    newSound->setVolume(1.0f);
    extendSound->setSource(QUrl::fromLocalFile("./sounds/extend.wav"));
    extendSound->setVolume(1.0f);
}

void MediaPlayer::play(int type){
    switch(type){
        case 0: clickSound->play(); break;
        case 1: spreadSound->play(); break;
        case 2: bombSound->play(); break;
        // case 3: newSound->play(); break;
        case 4: extendSound->play(); break;
    }
}
void MediaPlayer::bgmplay(){
    // mediaPlayer->play();
}
#pragma once
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>


class MediaPlayer{
    public:
        MediaPlayer();
        ~MediaPlayer();
        void play(int type);
        void bgmplay();
    private:
        QSoundEffect *clickSound; // 点击声音
        QSoundEffect *spreadSound; // 扩散声音
        QSoundEffect *bombSound; // 爆炸声音
        QSoundEffect *newSound; // 新关声音
        QSoundEffect *extendSound; // 续命声音
        QMediaPlayer *mediaPlayer; // 背景音乐播放器
        QAudioOutput *audioOutput; // 音频输出设备
};
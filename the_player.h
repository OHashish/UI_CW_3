//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include <vector>
#include <QTimer>

using namespace std;

class ThePlayer : public QMediaPlayer {

Q_OBJECT

private:
    vector<TheButtonInfo>* infos;
    vector<TheButton*>* buttons;
    QTimer* mTimer;
    unsigned long currentVideo = 0;
    int currentOffset = 0;

public:
    ThePlayer() : QMediaPlayer(NULL) {
        setNotifyInterval(5);
        connect (this, SIGNAL (mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT (videoFinish(QMediaPlayer::MediaStatus)));
    }

    // all buttons have been setup, store pointers here
    void setContent(vector<TheButton*>* b, vector<TheButtonInfo>* i);
    void updateButtons();
    void updateButtons(int offset);

private slots:
    void videoFinish (QMediaPlayer::MediaStatus ms);

public slots:
    void nextButtons ();
    void prevButtons ();
    void jumpTo (TheButtonInfo* button);
};

#endif //CW2_THE_PLAYER_H

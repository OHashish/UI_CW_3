//
// Created by twak on 11/11/2019.
//

#include "the_player.h"

using namespace std;

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

// change the image and video for one button every one second
void ThePlayer::videoFinish(QMediaPlayer::MediaStatus ms) {
    if (ms == QMediaPlayer::EndOfMedia) {
        TheButtonInfo* info;
        if (currentVideo+1 >= infos->size()) {
            info = & infos -> at (0);
        } else {
            info = & infos -> at (currentVideo+1);
        }
        jumpTo(info);
    }
}

void ThePlayer::jumpTo (TheButtonInfo* button) {
    currentVideo = button->id;
    setMedia( * button -> url);
    play();
    updateButtons();
}

void ThePlayer::updateButtons() {
    updateButtons(1);
}

void ThePlayer::updateButtons(int offset) {
    for (unsigned long i=0;i<buttons->size();i++) {
        TheButtonInfo* info;
        if (currentVideo+i+offset >= infos->size()) {
            info = & infos -> at (currentVideo+i+offset-infos->size());
        } else {
            info = & infos -> at (currentVideo+i+offset);
        }
        buttons -> at(i) -> init( info );
    }
}

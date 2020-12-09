//
// Created by twak on 11/11/2019.
//

#include "the_player.h"
#include <QtWidgets>

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
    currentOffset = 0;
    setMedia( * button -> url);
    play();
    updateButtons();
}

void ThePlayer::updateButtons() {
    updateButtons(0);
}

void ThePlayer::updateButtons(int offset) {
    for (unsigned long i=0;i<buttons->size();i++) {
        long val = currentVideo+i+offset+1;
        long size = infos->size();
        while (val >= size) {
            val -= size;
        }
        while (val < 0) {
            val += size;
        }
        buttons -> at(i) -> init(& infos -> at (val));
    }
}

void ThePlayer::nextButtons() {
    currentOffset += 1;
    updateButtons(currentOffset);
}

void ThePlayer::prevButtons() {
    currentOffset -= 1;
    updateButtons(currentOffset);
}

void ThePlayer::skipPrev() {
    currentVideo -= 1;
    if (currentVideo == -1) {currentVideo = infos->size() - 1;}
    jumpTo(& infos -> at (currentVideo));
}

void ThePlayer::skipNext() {
    currentVideo += 1;
    if (currentVideo == infos->size()) {currentVideo = 0;}
    jumpTo(& infos -> at (currentVideo));
}


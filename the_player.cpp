//
// Created by twak on 11/11/2019.
//

#include "the_player.h"

using namespace std;

// store buttons and video info in the player
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(& infos -> at(0));
}

// once a video finishes, goto next video
void ThePlayer::videoFinish(QMediaPlayer::MediaStatus ms) {
    if (ms == QMediaPlayer::EndOfMedia) {
        skipNext();
    }
}

// goto a specific video
void ThePlayer::jumpTo (TheButtonInfo* button) {
    currentVideo = button->id;
    setMedia( * button -> url);
    play();
}

// set the buttons to display next 4 videos after the current video
void ThePlayer::updateButtons() {
    updateButtons(currentVideo+1);
}

// display the 4 videos from suggestion
void ThePlayer::updateButtons(long suggestion) {
    long infoSize = infos->size();
    long buttSize = buttons->size();
    while (suggestion >= infoSize) {suggestion -= infoSize;}
    while (suggestion < 0) {suggestion += infoSize;}
    videoSuggestion = suggestion;
    for (long i=0;i<buttSize;i++) {
        if (suggestion+i >= infoSize) {
            buttons -> at(i) -> init(& infos -> at (suggestion+i-infoSize));
        } else {
            buttons -> at(i) -> init(& infos -> at (suggestion+i));
        }
    }
}

// Shift buttons one to the right
void ThePlayer::nextButtons() {
    updateButtons(videoSuggestion+1);
}

// Shift buttons one to the left
void ThePlayer::prevButtons() {
    updateButtons(videoSuggestion-1);
}

// Play the previous video
void ThePlayer::skipPrev() {
    currentVideo -= 1;
    if (currentVideo == -1) {currentVideo = infos->size() - 1;}
    jumpTo(& infos -> at (currentVideo));
}

// Play the next video
void ThePlayer::skipNext() {
    currentVideo += 1;
    if (currentVideo == infos->size()) {currentVideo = 0;}
    jumpTo(& infos -> at (currentVideo));
}

// Used to change the playback speed of the video
void ThePlayer::speedChanged(int index) {
    std::vector<qreal> speeds = {0.25,0.5,1,1.5,2};
    setPlaybackRate(speeds.at(index));
}

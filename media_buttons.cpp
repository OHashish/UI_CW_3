#include "media_buttons.h"

using namespace std;

Media_Buttons::Media_Buttons(QWidget *parent):  QPushButton(parent)//0 = normal but 1 = mute 2 =unmute
{
    resize(QSize(30,30));
    setStyleSheet("background-color:transparent;border:none");
    setIconSize(QSize(25,25));
}

void Media_Buttons::muteClicked() {
    if (muted == false) {
        muted = true;
        emit(setMuted(true));
        setIcon(QIcon(":/unmute.png"));
    } else {
        emit(setMuted(false));
        muted = false;
        setIcon(QIcon(":/mute.png"));
    }
}

void Media_Buttons::playClicked() {
    if (playing == false) {
        playing = true;
        emit(play());
        setIcon(QIcon(":/pause.png"));
    } else {
        playing = false;
        emit(pause());
        setIcon(QIcon(":/play.png"));
    }
}

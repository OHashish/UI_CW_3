#include "scrubber.h"
#include <QString>

using namespace std;

void Scrubber::positionChanged(qint64 time) {
    if (time == 0)
        setValue(0);
    else setValue((time * 2000000000) / duration);
}

void Scrubber::durationChanged(qint64 dur) {
    duration = dur;
    setValue(0);
}

void Scrubber::scrubberChanged(int val) {
    if (pressed) {
        qint64 time = (val * duration) / 2000000000;
        emit(scrubberPos(time));
    }
}

void Scrubber::scrubberPress() {
    pressed = true;
    if (player->state() == 2) {
        wasPaused = true;
    } else {
        wasPaused = false;
    }
    player->pause();
}

void Scrubber::scrubberUnpress() {
    pressed = false;
    if (!wasPaused) {
        player->play();
    }
}

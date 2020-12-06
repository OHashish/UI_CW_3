#ifndef SCRUBBER_H
#define SCRUBBER_H
#include <QSlider>
#include "the_player.h"

using namespace std;

class Scrubber: public QSlider{
    Q_OBJECT

public:
    Scrubber(ThePlayer *p) : QSlider(Qt::Horizontal) {
       player = p;
       setRange(0,2000000000);
    }
private:
    qint64 duration;
    ThePlayer *player;
    bool wasPaused = false;
    bool pressed = false;

public slots:
    void positionChanged(qint64);
    void durationChanged(qint64);
    void scrubberChanged(int);
    void scrubberPress();
    void scrubberUnpress();

signals:
    void scrubberPos(qint64);
};

#endif // SCRUBBER_H

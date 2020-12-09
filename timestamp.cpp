#include "timestamp.h"
#include <QString>

using namespace std;

void Timestamp::positionChanged(qint64 time) {
    int iminutes = time / 60000;
    int iseconds = (time / 1000) % 60;
    int dminutes = duration / 60000;
    int dseconds = (duration / 1000) % 60;
    setText(QString("%1:%2 / %3:%4").arg(iminutes).arg(iseconds,2,10,QLatin1Char('0')).arg(dminutes).arg(dseconds,2,10,QLatin1Char('0')));
}

void Timestamp::durationChanged(qint64 dur) {
    duration = dur;
    emit(positionChanged(0));
}

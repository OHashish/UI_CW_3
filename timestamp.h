#ifndef TIMESTAMP_H
#define TIMESTAMP_H
#include <QLabel>

using namespace std;

class Timestamp: public QLabel{
    Q_OBJECT

public:
    Timestamp() {
        setText("0:00/0:00");
    }
private:
    qint64 duration;

public slots:
    void positionChanged(qint64);
    void durationChanged(qint64);
};

#endif // TIMESTAMP_H

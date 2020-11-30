#ifndef MEDIA_BUTTONS_H
#define MEDIA_BUTTONS_H
#include <QPushButton>

class Media_Buttons: public QPushButton{
    Q_OBJECT
public:
    Media_Buttons(QWidget *parent);
private slots:
    void clicked();
signals:
    void play();
    void pause();
    void stop();
    void setMuted(bool muted);

/*
    void setPosition(qint64 position);
    void setVolume(int volume);

    void setPlaybackRate(qreal rate );
*/
};

#endif // MEDIA_BUTTONS_H

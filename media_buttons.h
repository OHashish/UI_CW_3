#ifndef MEDIA_BUTTONS_H
#define MEDIA_BUTTONS_H
#include <QPushButton>

using namespace std;

class Media_Buttons: public QPushButton{
    Q_OBJECT

public:
    Media_Buttons(QWidget *parent);
private:
    bool muted = false;
    bool playing = true;

private slots:
    void clicked();
public slots:
    void muteClicked();
    void playClicked();

signals:
    void playpause();
    void play();
    void pause();
    void stop();
    void mute();
    void setMuted(bool mute);


/*
    void setPosition(qint64 position);
    void setVolume(int volume);

    void setPlaybackRate(qreal rate );
*/
};

#endif // MEDIA_BUTTONS_H

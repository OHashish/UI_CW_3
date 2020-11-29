#ifndef PLAY_BUTTON_H
#define PLAY_BUTTON_H
#include <QPushButton>
#include <QUrl>

class Play_Button : public QPushButton
{
public:
    Play_Button();
signals:
    void pause();
    void play();
};

#endif // PLAY_BUTTON_H

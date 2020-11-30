#include "media_buttons.h"

Media_Buttons::Media_Buttons(QWidget *parent):  QPushButton(parent)
{
    connect(this, SIGNAL(released()), this, SLOT (clicked() ));
}
void Media_Buttons::clicked() {
    emit play();
    emit pause();
    emit stop();
    emit setMuted(true);
    emit setMuted(false);
}


#include "media_buttons.h"

Media_Buttons::Media_Buttons(QWidget *parent, int muteCheck):  QPushButton(parent)//0 = normal but 1 = mute 2 =unmute
{
    if (muteCheck == 0)
    {
        connect(this, SIGNAL(released()), this, SLOT (clicked() ));
    }
    else if (muteCheck == 1)
    {
        connect(this, SIGNAL(released()), this, SLOT (muteClicked() ));
    }
    else if (muteCheck == 2)
    {
        connect(this, SIGNAL(released()), this, SLOT (unMuteClicked() ));
    }
}
void Media_Buttons::clicked() {
    emit play();
    emit pause();
    emit stop();
}

void Media_Buttons::muteClicked()
{
    emit setMuted(true);
}

void Media_Buttons::unMuteClicked()
{
    emit setMuted(false);
}

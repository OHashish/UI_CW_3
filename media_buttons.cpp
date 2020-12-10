#include "media_buttons.h"
#include "the_player.h"
#include <QDebug>
#include <QtWidgets>
using namespace std;

Media_Buttons::Media_Buttons(QWidget *parent):  QPushButton(parent)//0 = normal but 1 = mute 2 =unmute
{
    resize(QSize(30,30));
    setStyleSheet("background-color:transparent;border:none");
    setIconSize(QSize(25,25));
}

Media_Buttons::Media_Buttons(QWidget *parent , QIcon fallingIcon, QIcon risingIcon): QPushButton(parent), risingIcon(risingIcon), fallingIcon(fallingIcon)
{
    resize(QSize(30,30));
    setStyleSheet("background-color:transparent;border:none");
    setIcon(fallingIcon);
    setIconSize(QSize(25,25));
}

void Media_Buttons::toggle() {
    if (toggled == false) {
        toggled = true;
        emit(toggleRising(true));
        emit(toggleFalling(false));
        emit(toggleRising());
        setIcon(risingIcon);
    } else {
        toggled = false;
        emit(toggleRising(false));
        emit(toggleFalling(true));
        emit(toggleFalling());
        setIcon(fallingIcon);
    }
}

void Media_Buttons::open()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Add Video(s)"));

    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    fileDialog.exec();
    //QUrl* url = new QUrl(fileDialog.selectedUrls()[0]);
//    QIcon* icon = new QIcon(":/unmute.png");
//    m_videos->push_back(TheButtonInfo( url ,icon, num_videos));
    QString f=(fileDialog.selectedUrls()[0]).toString();
    if (f.contains("."))

#if defined(_WIN32)
        if (f.contains(".wmv"))  { // windows
#else
        if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif
            QIcon* icon = new QIcon(":/video_icon.png");//placeholder thumbnail
            QUrl* url = new QUrl(fileDialog.selectedUrls()[0]); // convert the file location to a generic url
            m_videos->push_back(TheButtonInfo( url ,icon, num_videos)); // add to the output list
            num_videos++;
        }
       else{
            QMessageBox::question(
                                NULL,
                                NULL,
                                QString("Video format not supported."),
                                QMessageBox::Ok );

        }
}









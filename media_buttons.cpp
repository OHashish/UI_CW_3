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

void Media_Buttons::muteClicked() {
    if (muted == false) {
        muted = true;
        emit(setMuted(true));
        setIcon(QIcon(":/unmute.png"));
    } else {
        emit(setMuted(false));
        muted = false;
        setIcon(QIcon(":/mute.png"));
    }
}

void Media_Buttons::playClicked() {
    if (playing == false) {
        playing = true;
        emit(play());
        setIcon(QIcon(":/pause.png"));
    } else {
        playing = false;
        emit(pause());
        setIcon(QIcon(":/play.png"));
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
                                QString("Video format not supported"),
                                QMessageBox::Ok );



        }
}









/*
 *
 *    ______
 *   /_  __/___  ____ ___  ___  ____
 *    / / / __ \/ __ `__ \/ _ \/ __ \
 *   / / / /_/ / / / / / /  __/ /_/ /
 *  /_/  \____/_/ /_/ /_/\___/\____/
 *              video for sports enthusiasts...
 *
 *  2811 cw3 : twak
 */

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"
#include "media_buttons.h"
#include "timestamp.h"
#include "scrubber.h"
#include <QSlider>
#include <QLabel>
#include <QDebug>

using namespace std;
int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << Qt::endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder
    vector<TheButtonInfo> videos;
    Media_Buttons *media;

    if (argc == 2)
        videos = media->getInfoIn( string(argv[1]) );

    if (videos.size() == 0) {

        const int result = QMessageBox::question(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! download, unzip, and add command line argument to \"quoted\" file location. Download videos from Tom's OneDrive?"),
                    QMessageBox::Yes |
                    QMessageBox::No );

        switch( result )
        {
        case QMessageBox::Yes:
          QDesktopServices::openUrl(QUrl("https://leeds365-my.sharepoint.com/:u:/g/personal/scstke_leeds_ac_uk/EcGntcL-K3JOiaZF4T_uaA4BHn6USbq2E55kF_BTfdpPag?e=n1qfuN"));
          break;
        default:
            break;
        }
        exit(-1);
    }

    // create the main window and layout
    QWidget window;
    QVBoxLayout *top = new QVBoxLayout();
    window.setLayout(top);
    window.setWindowTitle("Tomeo");
    window.setMinimumSize(800, 680);

    // the widget that will show the video
    QVideoWidget *videoWidget = new QVideoWidget;
    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer();
    player->setVideoOutput(videoWidget);

    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    vector<TheButton*> buttons;
    // the buttons are arranged horizontally
    QHBoxLayout *layout = new QHBoxLayout();
    buttonWidget->setLayout(layout);

    Media_Buttons *back = new Media_Buttons(buttonWidget);
    back->connect(back, SIGNAL(released()),player, SLOT(prevButtons()));
    back->setIcon(QIcon(":/back.png")); //placeholder icon
    layout->addWidget(back);

    // create the four buttons
    for ( int i = 0; i < 4; i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        buttons.push_back(button);
        layout->addWidget(button,1);
        button->init(&videos.at(i));
    }

    Media_Buttons *next = new Media_Buttons(buttonWidget);
    next->connect(next, SIGNAL(released()),player, SLOT(nextButtons()));
    next->setIcon(QIcon(":/play.png"));
    layout->addWidget(next);

    //create buttons
    QWidget *playbackWidget = new QWidget();
    QHBoxLayout *layout2 = new QHBoxLayout();

    Media_Buttons *skipPrev = new Media_Buttons(playbackWidget);
    skipPrev->connect(skipPrev, SIGNAL(released()),player, SLOT(skipPrev()));
    skipPrev->setIcon(QIcon(":/skip_back.png")); //placeholder icon
    skipPrev->setIconSize(QSize(40, 40));
    layout2->addWidget(skipPrev);

    Media_Buttons *pp = new Media_Buttons(playbackWidget, QIcon(":/pause.png"),QIcon(":/play.png"));
    pp->connect(pp, SIGNAL(released()), pp, SLOT(toggle()));
    pp->connect(pp, SIGNAL(toggleFalling()), player, SLOT(play()));
    pp->connect(pp, SIGNAL(toggleRising()), player, SLOT(pause()));
    layout2->addWidget(pp);

    Media_Buttons *stop = new Media_Buttons(playbackWidget);
    stop->connect(stop, SIGNAL(released()),player, SLOT(stop()));
    stop->setIcon(QIcon(":/stop.png"));
    layout2->addWidget(stop);

    Media_Buttons *skipNext = new Media_Buttons(playbackWidget);
    skipNext->connect(skipNext, SIGNAL(released()),player, SLOT(skipNext()));
    skipNext->setIcon(QIcon(":/skip.png")); //placeholder icon
    skipNext->setIconSize(QSize(40, 40));
    layout2->addWidget(skipNext);

    Media_Buttons *mute = new Media_Buttons(playbackWidget, QIcon(":/unmute.png"), QIcon(":/mute.png"));
    mute->connect(mute, SIGNAL(released()), mute, SLOT(toggle()));
    mute->connect(mute, SIGNAL(toggleRising(bool)), player, SLOT(setMuted(bool)));
    layout2->addWidget(mute);


    QSlider *volume = new QSlider(Qt::Horizontal);
    volume->setRange(0, 100);
    volume->connect(volume, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));
    volume->setValue(50);
    volume->setStyleSheet(
                "   QSlider::groove:horizontal {"
                " background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
                "border: 0px solid #424242; "
                "height: 10px; "
                "border-radius: 4px;"
                " }"
                "QSlider::handle:horizontal { "
                "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #840484);"
                "border: 2px solid #840484;"
                "width: 16px; "
                " height: 20px; "
                " line-height: 20px; "
                " margin-top: -5px;"
                " margin-bottom: -5px;"
                "  border-radius: 10px; "
                "  }"
                "QSlider::sub-page:horizontal {background:#840484;}"
                "QSlider::add-page:horizontal {background:#b4b4b4;}"
                );
    layout2->addWidget(volume,2);
    //Duration timestamp
    Timestamp *timestamp = new Timestamp();
    player->connect(player, SIGNAL(positionChanged(qint64)), timestamp, SLOT(positionChanged(qint64)));
    player->connect(player, SIGNAL(durationChanged(qint64)), timestamp, SLOT(durationChanged(qint64)));
    layout2->addWidget(timestamp);

    Scrubber *scrubber = new Scrubber(player);
    player->connect(player, SIGNAL(positionChanged(qint64)), scrubber, SLOT(positionChanged(qint64)));
    player->connect(player, SIGNAL(durationChanged(qint64)), scrubber, SLOT(durationChanged(qint64)));
    scrubber->connect(scrubber, SIGNAL(valueChanged(int)), scrubber, SLOT(scrubberChanged(int)));
    scrubber->connect(scrubber, SIGNAL(sliderPressed()), scrubber, SLOT(scrubberPress()));
    scrubber->connect(scrubber, SIGNAL(sliderReleased()), scrubber, SLOT(scrubberUnpress()));
    scrubber->connect(scrubber, SIGNAL(scrubberPos(qint64)), player, SLOT(setPosition(qint64)));
    scrubber->setStyleSheet(
                "   QSlider::groove:horizontal {"
                " background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
                "border: 0px solid #424242; "
                "height: 10px; "
                "border-radius: 4px;"
                " }"
                "QSlider::handle:horizontal { "
                "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #840484);"
                "border: 2px solid #840484;"
                "width: 16px; "
                " height: 20px; "
                " line-height: 20px; "
                " margin-top: -5px;"
                " margin-bottom: -5px;"
                "  border-radius: 10px; "
                "  }"
                "QSlider::sub-page:horizontal {background:#840484;}"
                "QSlider::add-page:horizontal {background:#b4b4b4;}"
                );
    layout2->addWidget(scrubber,25);

    //fullscreen button
    Media_Buttons *fullscreen = new Media_Buttons(playbackWidget, QIcon(":/fullscreen.png"), QIcon(":/fullscreen.png"));
    fullscreen->connect(fullscreen, SIGNAL(released()), fullscreen, SLOT(toggle()));
    fullscreen->connect(fullscreen, SIGNAL(toggleRising(bool)), buttonWidget, SLOT(setHidden(bool)));
    layout2->addWidget(fullscreen);

    Media_Buttons *openButton = new Media_Buttons(playbackWidget);
    openButton->setIcon(QIcon(":/addVideo.png"));
   openButton->num_videos=videos.size();
    openButton->connect(openButton,SIGNAL(released()), openButton, SLOT(open()));
    layout2->addWidget(openButton);

    Media_Buttons *removeButton = new Media_Buttons(playbackWidget);
    removeButton->setIcon(QIcon(":/removeVideo.png"));
   removeButton->num_videos=videos.size();
    removeButton->connect(removeButton,SIGNAL(released()), player, SLOT(remove_Mode()));
    layout2->addWidget(removeButton);

    fullscreen->connect(fullscreen, SIGNAL(toggleRising(bool)), openButton, SLOT(setHidden(bool)));
    fullscreen->connect(fullscreen, SIGNAL(toggleRising(bool)), removeButton, SLOT(setHidden(bool)));

    playbackWidget->setLayout(layout2);

    // tell the player what buttons and videos are available


    player->setContent(&buttons, & videos);
    //store previous buttons and videos
    openButton->getVid_But(&buttons, & videos);
    openButton->num_videos=videos.size();
    removeButton->getVid_But(&buttons, & videos);
    removeButton->num_videos=videos.size();
    player->setContent(&buttons, & videos);


    // add the video and the buttons to the top level widget
    top->addWidget(videoWidget);
    top->addWidget(playbackWidget);
    top->addWidget(buttonWidget);
    app.setWindowIcon(QIcon(":/logo.png"));
    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}

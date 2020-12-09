#ifndef MEDIA_BUTTONS_H
#define MEDIA_BUTTONS_H
#include <QPushButton>
#include "the_player.h"
#include <QtMultimediaWidgets/QVideoWidget>
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
#include <QDebug>

using namespace std;

class Media_Buttons: public QPushButton{
    Q_OBJECT
private:
    bool muted = false;
    bool playing = true;
    vector<TheButton*>* m_buttons;
    vector<TheButtonInfo>* m_videos;

public:
    Media_Buttons(QWidget *parent);
    // read in videos and thumbnails to this directory
    vector<TheButtonInfo> getInfoIn (string loc) {

        vector<TheButtonInfo> out =  vector<TheButtonInfo>();
        QDir dir(QString::fromStdString(loc) );
        QDirIterator it(dir);
        unsigned long i = 0;
        while (it.hasNext()) { // for all files

            QString f = it.next();

                if (f.contains("."))

    #if defined(_WIN32)
                if (f.contains(".wmv"))  { // windows
    #else
                if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
    #endif

                QString thumb = f.left( f .length() - 4) +".png";
                if (QFile(thumb).exists()) { // if a png thumbnail exists
                    QImageReader *imageReader = new QImageReader(thumb);
                        QImage sprite = imageReader->read(); // read the thumbnail
                        if (!sprite.isNull()) {
                            QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                            QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                            out . push_back(TheButtonInfo( url , ico, i) ); // add to the output list
                            i++;
                        }
                        else
                            qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << Qt::endl;
                }
                else
                    qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << Qt::endl;
            }
        }

        return out;
    }
    size_t num_videos;

    void getVid_But(vector<TheButton*>* b, vector<TheButtonInfo>* i){
        m_buttons=b;
        m_videos=i;
    }

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
private slots:
    void open();

/*
    void setPosition(qint64 position);
    void setVolume(int volume);

    void setPlaybackRate(qreal rate );
*/
};

#endif // MEDIA_BUTTONS_H

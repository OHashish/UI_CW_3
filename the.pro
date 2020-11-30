QT += core gui widgets multimedia multimediawidgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        media_buttons.cpp \
        the_button.cpp \
        the_player.cpp \
        tomeo.cpp \

HEADERS += \
    media_buttons.h \
    the_button.h \
    the_player.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=

RESOURCES += \
    Icons.qrc \
    logo.qrc \
    mute.qrc \
    pause.qrc \
    stop.qrc \
    unmute.qrc

DISTFILES +=


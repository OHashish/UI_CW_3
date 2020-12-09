#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class QAction;
class QMenu;
class QPlainTextEdit;
class QSessionManager;



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    void load_video(const QString &fileName);

private slots:
    void add_video();
    void about();
private:
    QPlainTextEdit *textEdit;
    QString curFile;
};
//! [0]

#endif

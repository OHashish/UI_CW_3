#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QGuiApplication>
#include <QPlainTextEdit>
#include <QTextStream>

MainWindow::MainWindow() : textEdit(new QPlainTextEdit)

{

}
void MainWindow::add_video()
{

        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            load_video(fileName);

}
void MainWindow::load_video(const QString &fileName)
//! [42] //! [43]
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setPlainText(in.readAll());
    QGuiApplication::restoreOverrideCursor();

}
void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
               "write modern GUI applications using Qt, with a menu bar, "
               "toolbars, and a status bar."));
}

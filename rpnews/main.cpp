#include <QApplication>
#include <QLockFile>
#include <QDir>
#include <QMessageBox>
#include <glog/logging.h>
#include "gui/trayiconapp.h"

int main(int argc, char *argv[])
{
    google::InitGoogleLogging("rpnews_log.txt");
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    QLockFile lockFile(QDir::temp().absoluteFilePath("temp.lock"));

    if (!lockFile.tryLock(100))
    {
        QMessageBox message;
        message.setIcon(QMessageBox::Warning);
        message.setText("The application was run.\nYou can run only one instance of the application.");
        message.exec();
        return 1;
    }

    TrayIconApp app;
    return a.exec();
}

#include <QApplication>
#include <QFont>
#include <QFontDatabase>
#include "gui/trayiconapp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    TrayIconApp app;

    return a.exec();
}

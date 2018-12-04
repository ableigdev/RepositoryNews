#include <QApplication>
#include <QFont>
#include <QFontDatabase>
#include "gui/trayiconapp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    if (QFontDatabase::addApplicationFont(":/fonts/fonts/OpenSans-Regular.ttf") != -1)
    {
        QFont font("OpenSans-Regular");
        font.setPointSize(10);
        a.setFont(font);
    }
    TrayIconApp app;

    return a.exec();
}

#ifndef AUTOSTARTAPPLICATION_H
#define AUTOSTARTAPPLICATION_H

#include <QSettings>
#include <QtGlobal>
#include <QString>

namespace helpers
{
    class AutoStartApplication
    {
    public:
        AutoStartApplication();
        ~AutoStartApplication() = default;

        void turnOnAutoStart();
        void turnOffAutoStart();

    private:
    #ifdef WIN32
        QSettings m_Settings;
    #endif
    #ifdef Q_OS_LINUX
        QString m_AutostartPath {};
    #endif
    };
}

#endif // AUTOSTARTAPPLICATION_H

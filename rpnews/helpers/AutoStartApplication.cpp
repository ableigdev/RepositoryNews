#include "AutoStartApplication.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QCoreApplication>

AutoStartApplication::AutoStartApplication()
#ifdef Q_OS_WIN32
    : m_Settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat)
#endif
{

}
void AutoStartApplication::turnOnAutoStart()
{
#ifdef Q_OS_WIN32
    m_Settings.setValue("rpnews", QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
    m_Settings.sync();
#endif
#ifdef Q_OS_LINUX
    // Path to the folder of autostart
    m_AutostartPath = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).at(0) + QLatin1String("/autostart");
    QDir autorunDir(m_AutostartPath);

    if(!autorunDir.exists())
    {
        autorunDir.mkpath(m_AutostartPath);
    }

    QFile autorunFile(m_AutostartPath + QLatin1String("/rpnews.desktop"));

    if(autorunFile.open(QFile::WriteOnly))
    {
        QString autorunContent("[Desktop Entry]\n"
                               "Type=Application\n"
                               "Exec=" + QCoreApplication::applicationFilePath() + "\n"
                               "Hidden=false\n"
                               "NoDisplay=false\n"
                               "X-GNOME-Autostart-enabled=true\n"
                               "Name[en_GB]=rpnews\n"
                               "Name=rpnews\n"
                               "Comment[en_GB]=rpnews\n"
                               "Comment=rpnews\n");
        QTextStream outStream(&autorunFile);
        outStream << autorunContent;
        // Set access rights
        autorunFile.setPermissions(QFileDevice::ExeUser|QFileDevice::ExeOwner|QFileDevice::ExeOther|QFileDevice::ExeGroup|
                               QFileDevice::WriteUser|QFileDevice::ReadUser);
        autorunFile.close();
    }
#endif
}

void AutoStartApplication::turnOffAutoStart()
{
#ifdef Q_OS_WIN32
    m_Settings.remove("rpnews");
#endif
#ifdef Q_OS_LINUX
    m_AutostartPath = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).at(0) + QLatin1String("/autostart");
    QFile autorunFile(m_AutostartPath + QLatin1String("/rpnews.desktop"));

    if(autorunFile.exists())
    {
        autorunFile.remove();
    }
#endif
}

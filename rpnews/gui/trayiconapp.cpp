#include "trayiconapp.h"
#include <QStyle>
#include <QMessageBox>
#include <QApplication>

TrayIconApp::TrayIconApp(QWidget *parent)
    : QMainWindow(parent)
{
    this->setTrayIconActions();
    this->showTrayIcon();
}

void TrayIconApp::showTrayIcon()
{
    m_TrayIcon = new QSystemTrayIcon(this);
    m_TrayIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    m_TrayIcon->setContextMenu(m_TrayIconMenu);
    m_TrayIcon->setToolTip("Tray program was started successfully");

    connect(m_TrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    m_TrayIcon->show();
}

void TrayIconApp::trayActionExecute()
{
    QMessageBox::information(this, "TrayIcon", "Test message");
}

void TrayIconApp::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            this -> trayActionExecute();
            break;
        default:
            break;
    }
}

void TrayIconApp::setTrayIconActions()
{
    // Setting actions...
    m_MinimizeAction = new QAction("Hide", this);
    m_RestoreAction = new QAction("Show", this);
    m_QuitAction = new QAction("Quit", this);

    // Connecting actions to slots...
    connect(m_MinimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    connect(m_RestoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    connect(m_QuitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Setting system tray's icon menu...
    m_TrayIconMenu = new QMenu(this);
    m_TrayIconMenu->addAction(m_MinimizeAction);
    m_TrayIconMenu->addAction(m_RestoreAction);
    m_TrayIconMenu->addAction(m_QuitAction);
}

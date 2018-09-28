#include "trayiconapp.h"
#include <QStyle>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>

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
    m_TrayIcon->setToolTip("rpnews");

    connect(m_TrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    m_TrayIcon->show();
}

void TrayIconApp::trayActionExecute()
{
    QMessageBox::information(this, "TrayIcon", "Test message");
}

void TrayIconApp::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
    {
        m_TrayIconMenu->popup(QCursor::pos());
    }
}

void TrayIconApp::checkedAction(bool value)
{
    qDebug() << "checked: " << value;
}

void TrayIconApp::aboutInformationAction()
{
    qDebug() << "About";
}

void TrayIconApp::setTrayIconActions()
{
    // Setting actions...
    m_AddRepositoryAction = new QAction("Add repository...", this);
    m_ShowAllRepositoriesAction = new QAction("Show All Repositories...", this);
    m_AutoStartAction = new QAction("Autostart", this);
    m_AboutInformationAction = new QAction("Information...");
    m_QuitAction = new QAction("Quit", this);

    m_AutoStartAction->setCheckable(true);

    // Connecting actions to slots...
    //connect(m_MinimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    //connect(m_RestoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    connect(m_AutoStartAction, SIGNAL(toggled(bool)), this, SLOT(checkedAction(bool)));
    connect(m_AboutInformationAction, SIGNAL(triggered()), this, SLOT(aboutInformationAction()));
    connect(m_QuitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Setting system tray's icon menu...
    m_TrayIconMenu = new QMenu(this);
    m_TrayIconMenu->addAction(m_AddRepositoryAction);
    m_TrayIconMenu->addAction(m_ShowAllRepositoriesAction);
    m_TrayIconMenu->addAction(m_AutoStartAction);
    m_TrayIconMenu->addAction(m_AboutInformationAction);
    m_TrayIconMenu->addAction(m_QuitAction);
}

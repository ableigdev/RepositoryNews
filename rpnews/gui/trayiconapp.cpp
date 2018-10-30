#include "trayiconapp.h"
#include <QStyle>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>

TrayIconApp::TrayIconApp(QWidget* parent)
    : QMainWindow(parent),
      m_AddNewRepository(new AddNewRepository),
      m_ShowAllRepositories(new ShowAllRepositories),
      m_PopUpNotifierWindow(new PopUpNotifierWindow)
{
    this->setTrayIconActions();
    this->showTrayIcon();
}

TrayIconApp::~TrayIconApp()
{
    for (size_t i = 0; i < m_Timers.size(); ++i)
    {
        m_Timers[i]->stop();
        QObject::disconnect(m_Connections[i]);
    }
}

void TrayIconApp::showTrayIcon()
{
    m_TrayIcon = std::make_unique<QSystemTrayIcon>(this);
    m_TrayIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    m_TrayIcon->setContextMenu(m_TrayIconMenu.get());
    m_TrayIcon->setToolTip("rpnews");

    connect(m_TrayIcon.get(), SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    m_TrayIcon->show();
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
    value ? m_AutoStartApp.turnOnAutoStart() : m_AutoStartApp.turnOffAutoStart();
}

void TrayIconApp::addNewRepositorySlot()
{
    m_AddNewRepository->exec();
    if (m_AddNewRepository->repositoryIsReady())
    {
        std::shared_ptr<QTimer> timer(new QTimer(this));
        timer->setInterval(m_AddNewRepository->getIntervalTime());
        timer->start();
        m_Repositories.insert({timer->timerId(), m_AddNewRepository->getRepository()});
        m_Connections.push_back(connect(timer.get(), &QTimer::timeout, [=]()
        {
            auto result = m_Repositories[timer->timerId()]->getLastCommit();
            if (!result.empty())
            {
                m_PopUpNotifierWindow->setPopUpText(result.front(), m_Repositories[timer->timerId()]->getRepositoryName());
                m_PopUpNotifierWindow->show();
            }
        }));

        m_Timers.push_back(std::move(timer));
    }
}

void TrayIconApp::aboutInformationAction()
{
    QMessageBox::about(nullptr, "About", "This program check new commits in your repository.");
}

void TrayIconApp::setTrayIconActions()
{
    // Setting actions...
    m_AddRepositoryAction = std::make_unique<QAction>("Add repository...", this);
    m_ShowAllRepositoriesAction = std::make_unique<QAction>("Show All Repositories...", this);
    m_AutoStartAction = std::make_unique<QAction>("Autostart", this);
    m_AboutInformationAction = std::make_unique<QAction>("Information...");
    m_QuitAction = std::make_unique<QAction>("Quit", this);

    m_AutoStartAction->setCheckable(true);

    // Connecting actions to slots...
    connect(m_AddRepositoryAction.get(), SIGNAL(triggered()), this, SLOT(addNewRepositorySlot()));
    connect(m_ShowAllRepositoriesAction.get(), SIGNAL(triggered()), this, SLOT(showAllRepositoriesSlot()));
    connect(m_AutoStartAction.get(), SIGNAL(toggled(bool)), this, SLOT(checkedAction(bool)));
    connect(m_AboutInformationAction.get(), SIGNAL(triggered()), this, SLOT(aboutInformationAction()));
    connect(m_QuitAction.get(), SIGNAL(triggered()), qApp, SLOT(quit()));

    // Setting system tray's icon menu...
    m_TrayIconMenu = std::make_unique<QMenu>(this);
    m_TrayIconMenu->addAction(m_AddRepositoryAction.get());
    m_TrayIconMenu->addAction(m_ShowAllRepositoriesAction.get());
    m_TrayIconMenu->addAction(m_AutoStartAction.get());
    m_TrayIconMenu->addAction(m_AboutInformationAction.get());
    m_TrayIconMenu->addAction(m_QuitAction.get());
}

void TrayIconApp::showAllRepositoriesSlot()
{
    // TODO: Change these methods
//    m_ShowAllRepositories->setTimeInterval(m_TimeIntervals);
//    m_ShowAllRepositories->setRepositories(m_Repositories);
    m_ShowAllRepositories->show();
}


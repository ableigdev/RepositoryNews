#include "trayiconapp.h"
#include <QStyle>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
#include <algorithm>
#include "helpers/CheckExistConfig.h"
#include "helpers/GetNewRepositoryFactory.h"
#include "interfaces/IRepositoryFactory.h"
#include "git_implementation/GitOpenRepositoryStrategyImpl.h"

TrayIconApp::TrayIconApp(QWidget* parent)
    : QMainWindow(parent),
      m_AddNewRepository(new AddNewRepository),
      m_ShowAllRepositories(new ShowAllRepositories),
      m_PopUpNotifierWindow(new PopUpNotifierWindow)
{
    this->setTrayIconActions();
    this->showTrayIcon();
    this->readRepositoriesFromDisk();
    m_AppSettings.value("AutoStartApp").toBool() ? m_AutoStartAction->setChecked(true) : m_AutoStartAction->setChecked(false);
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
    QIcon trayImage(":/images/images/logo.png");
    m_TrayIcon->setIcon(trayImage);
    m_TrayIcon->setContextMenu(m_TrayIconMenu.get());
    m_TrayIcon->setToolTip("rpnews");

    connect(m_TrayIcon.get(), static_cast<void(QSystemTrayIcon::*)(QSystemTrayIcon::ActivationReason)>(&QSystemTrayIcon::activated), this, &TrayIconApp::trayIconActivated);
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
    m_AppSettings.setValue("AutoStartApp", value);
}

void TrayIconApp::addNewRepositorySlot()
{
    m_TrayIcon->hide();
    m_AddNewRepository->exec();
    if (m_AddNewRepository->repositoryIsReady())
    {
        connectRepositoryWithTimer(m_AddNewRepository->getRepository(), m_AddNewRepository->getIntervalTime());
    }
    m_TrayIcon->show();
}

void TrayIconApp::aboutInformationAction()
{
    m_TrayIcon->hide();
    QMessageBox::about(nullptr, "About", "This program check new commits in your repository.");
    m_TrayIcon->show();
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
    connect(m_AddRepositoryAction.get(), &QAction::triggered, this, &TrayIconApp::addNewRepositorySlot);
    connect(m_ShowAllRepositoriesAction.get(), &QAction::triggered, this, &TrayIconApp::showAllRepositoriesSlot);
    connect(m_AutoStartAction.get(), static_cast<void(QAction::*)(bool)>(&QAction::toggled), this, &TrayIconApp::checkedAction);
    connect(m_AboutInformationAction.get(), &QAction::triggered, this, &TrayIconApp::aboutInformationAction);
    connect(m_QuitAction.get(), &QAction::triggered, qApp, &QApplication::quit);

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
    m_TrayIcon->hide();
    std::for_each(m_Timers.begin(), m_Timers.end(), [](auto it){ it->stop(); });
    m_ShowAllRepositories->setTimers(std::move(m_Timers));
    m_ShowAllRepositories->setRepositories(std::move(m_Repositories));
    m_ShowAllRepositories->setConnections(std::move(m_Connections));
    m_ShowAllRepositories->show();
    m_Timers = std::move(m_ShowAllRepositories->getTimers());
    m_Repositories = std::move(m_ShowAllRepositories->getRepositories());
    m_Connections = std::move(m_ShowAllRepositories->getConnections());
    std::for_each(m_Timers.begin(), m_Timers.end(), [](auto it){ it->start(); });
    updateTimersID();
    m_TrayIcon->show();
}

void TrayIconApp::readRepositoriesFromDisk()
{
    auto informAboutRepositories = helpers::CheckExistConfig::check();
    for (const auto& i : informAboutRepositories)
    {
        std::shared_ptr<interfaces::IRepositoryFactory> repositoryFactory(helpers::getNewRepositoryFactory(i.type));
        auto openStrategy(std::make_unique<git_impl::GitOpenRepositoryStrategyImpl>());
        try
        {
            std::shared_ptr<interfaces::IRepository> repository(repositoryFactory->createRepository(i.path, i.user, i.pass, std::move(openStrategy)));
            repository->prepareRepository();
            repository->prepareBranches();
            repository->setCurrentBranch(static_cast<size_t>(i.branchIndex));
            std::chrono::seconds sec { i.timeInterval };
            connectRepositoryWithTimer(std::move(repository), std::move(sec));
        }
        catch (const std::logic_error& e)
        {
            QMessageBox::critical(nullptr, "Error", e.what(), QMessageBox::Critical, QMessageBox::Ok);
        }
    }
}

void TrayIconApp::connectRepositoryWithTimer(std::shared_ptr<interfaces::IRepository>&& repository, std::chrono::seconds&& sec)
{
    std::shared_ptr<QTimer> timer(new QTimer(this));
    timer->setInterval(sec);
    timer->start();
    m_Repositories.emplace_back(std::make_pair(timer->timerId(), repository));
    m_Connections.emplace_back(connect(timer.get(), &QTimer::timeout, [=]()
    {
        auto find = std::find_if(m_Repositories.begin(), m_Repositories.end(), [=](auto it)
        {
            return it.first == timer->timerId();
        });
        auto result = find->second->getLastCommit();
        if (!result.empty())
        {
            m_PopUpNotifierWindow->setPopUpText(result.front(), find->second->getRepositoryName());
            m_PopUpNotifierWindow->show();
        }
    }));

    m_Timers.push_back(std::move(timer));
}

void TrayIconApp::updateTimersID()
{
    for (size_t i = 0; i < m_Repositories.size(); ++i)
    {
        m_Repositories[i].first = m_Timers[i]->timerId();
    }
}

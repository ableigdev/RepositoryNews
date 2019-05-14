#ifndef TRAYWINDOW_H
#define TRAYWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QTimer>
#include <QMetaObject>
#include <QSettings>
#include <memory>
#include <vector>
#include <map>
#include <chrono>
#include "helpers/AutoStartApplication.h"
#include "AddNewRepository.h"
#include "ShowAllRepositories.h"
#include "PopUpNotifierWindow.h"

class TrayIconApp : public QMainWindow
{
    Q_OBJECT
public:
    explicit TrayIconApp(QWidget *parent = nullptr);
    virtual ~TrayIconApp();

private:
    void readRepositoriesFromDisk();
    void connectRepositoryWithTimer(std::shared_ptr<interfaces::IRepository>&& repository, std::chrono::seconds&& sec);
    void updateTimersID();

private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void setTrayIconActions();
    void showTrayIcon();
    void checkedAction(bool value);
    void aboutInformationAction();
    void addNewRepositorySlot();
    void showAllRepositoriesSlot();

private:
    std::unique_ptr<QMenu> m_TrayIconMenu;
    std::unique_ptr<QAction> m_AddRepositoryAction;
    std::unique_ptr<QAction> m_ShowAllRepositoriesAction;
    std::unique_ptr<QAction> m_AutoStartAction;
    std::unique_ptr<QAction> m_AboutInformationAction;
    std::unique_ptr<QAction> m_QuitAction;
    std::unique_ptr<QSystemTrayIcon> m_TrayIcon;

    helpers::AutoStartApplication m_AutoStartApp;
    std::unique_ptr<AddNewRepository> m_AddNewRepository;
    std::unique_ptr<ShowAllRepositories> m_ShowAllRepositories;
    std::unique_ptr<PopUpNotifierWindow> m_PopUpNotifierWindow;
    std::vector<std::shared_ptr<QTimer>> m_Timers;
    std::vector<std::pair<int, std::shared_ptr<interfaces::IRepository>>> m_Repositories;
    std::vector<QMetaObject::Connection> m_Connections;
    QSettings m_AppSettings;
};

#endif // TRAYWINDOW_H

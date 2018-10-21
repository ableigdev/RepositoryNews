#ifndef TRAYWINDOW_H
#define TRAYWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <memory>
#include <vector>
#include <chrono>
#include "rpnews/helpers/AutoStartApplication.h"
#include "AddNewRepository.h"
#include "ShowAllRepositories.h"

class TrayIconApp : public QMainWindow
{
    Q_OBJECT
public:
    explicit TrayIconApp(QWidget *parent = nullptr);

private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void setTrayIconActions();
    void showTrayIcon();
    void checkedAction(bool value);
    void aboutInformationAction();
    void addNewRepositorySlot();
    void showAllRepositoriesSlot();

private:
    QMenu* m_TrayIconMenu;
    QAction* m_AddRepositoryAction;
    QAction* m_ShowAllRepositoriesAction;
    QAction* m_AutoStartAction;
    QAction* m_AboutInformationAction;
    QAction* m_QuitAction;
    QSystemTrayIcon* m_TrayIcon;

    AutoStartApplication m_AutoStartApp;
    std::unique_ptr<AddNewRepository> m_AddNewRepository;
    std::unique_ptr<ShowAllRepositories> m_ShowAllRepositories;
    std::vector<std::shared_ptr<IRepository>> m_Repositories;
    std::vector<std::shared_ptr<std::chrono::seconds>> m_TimeIntervals;
};

#endif // TRAYWINDOW_H

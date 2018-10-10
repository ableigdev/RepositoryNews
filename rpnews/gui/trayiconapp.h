#ifndef TRAYWINDOW_H
#define TRAYWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <memory>
#include "rpnews/helpers/AutoStartApplication.h"
#include "AddNewRepository.h"

class TrayIconApp : public QMainWindow
{
    Q_OBJECT
public:
    explicit TrayIconApp(QWidget *parent = nullptr);

private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayActionExecute();
    void setTrayIconActions();
    void showTrayIcon();
    void checkedAction(bool value);
    void aboutInformationAction();
    void addNewRepositoryAction();

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
};

#endif // TRAYWINDOW_H

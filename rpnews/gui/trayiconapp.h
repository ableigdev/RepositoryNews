#ifndef TRAYWINDOW_H
#define TRAYWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

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

private:
    QMenu* m_TrayIconMenu;
    QAction* m_AddRepositoryAction;
    QAction* m_ShowAllRepositoriesAction;
    QAction* m_AutoStartAction;
    QAction* m_AboutInformationAction;
    QAction* m_QuitAction;
    QSystemTrayIcon* m_TrayIcon;
};

#endif // TRAYWINDOW_H

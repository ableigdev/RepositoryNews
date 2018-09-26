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
    //void changeEvent(QEvent*);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayActionExecute();
    void setTrayIconActions();
    void showTrayIcon();

private:
    QMenu* m_TrayIconMenu;
    QAction* m_MinimizeAction;
    QAction* m_RestoreAction;
    QAction* m_QuitAction;
    QSystemTrayIcon* m_TrayIcon;
};

#endif // TRAYWINDOW_H

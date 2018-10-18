#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QMenu>
#include <QPoint>
#include <QAction>
#include "trayiconapp.h"

class ContextMenu : public QMenu
{
    Q_OBJECT
public:
    explicit ContextMenu(TrayIconApp* parent);
    ~ContextMenu() = default;

    virtual void popup(const QPoint& pos, QAction* action = nullptr);

public slots:
    void changeCharacteristics();

private:
    void leaveEvent(QEvent*);

private:
    TrayIconApp* m_TrayIconApp;
    QMenu* m_Menu;
};

#endif // CONTEXTMENU_H

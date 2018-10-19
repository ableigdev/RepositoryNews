#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QMenu>
#include <QPoint>
#include <QAction>
#include <memory>
#include "trayiconapp.h"

class ContextMenu : public QMenu
{
    Q_OBJECT
public:
    explicit ContextMenu(TrayIconApp* parent);
    ~ContextMenu() = default;

    virtual void popup(const QPoint& pos, QAction* action = nullptr);

public slots:
    void changePropertiesSlot();

private:
    void leaveEvent(QEvent*);

private:
    std::unique_ptr<QMenu> m_Menu;
    TrayIconApp* m_TrayIconApp;
    std::unique_ptr<QAction> m_ChangeProperties;
};

#endif // CONTEXTMENU_H

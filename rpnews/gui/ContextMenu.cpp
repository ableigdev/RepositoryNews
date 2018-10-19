#include "ContextMenu.h"

ContextMenu::ContextMenu(TrayIconApp* parent) :
    m_Menu(new QMenu(parent)),
    m_TrayIconApp(parent)
{
    m_ChangeProperties = std::make_unique<QAction>("Change", this);
    connect(m_ChangeProperties.get(), SIGNAL(triggered()), this, SLOT(changePropertiesSlot()));
    m_Menu->addAction(m_ChangeProperties.get());
}

void ContextMenu::leaveEvent(QEvent* event)
{
    m_Menu->hide();
    event->accept();
}



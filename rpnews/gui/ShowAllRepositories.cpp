#include "ShowAllRepositories.h"
#include "ui_ShowAllRepositories.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>

ShowAllRepositories::ShowAllRepositories(TrayIconApp* parent) :
    QDialog(parent),
    m_UI(new Ui::ShowAllRepositories),
    m_TrayIconApp(parent)
{
    m_UI->setupUi(this);
    this->setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    this->size(),
                    qApp->desktop()->availableGeometry()
                    )
                );
}

ShowAllRepositories::~ShowAllRepositories()
{
    delete m_UI;
}

void ShowAllRepositories::closeEvent(QCloseEvent* event)
{
    event->ignore();
    this->hide();
}

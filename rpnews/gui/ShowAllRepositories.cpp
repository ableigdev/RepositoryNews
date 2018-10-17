#include "ShowAllRepositories.h"
#include "ui_ShowAllRepositories.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>
#include <string>

ShowAllRepositories::ShowAllRepositories(QWidget* parent) :
    QDialog(parent),
    m_UI(new Ui::ShowAllRepositories)
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
    initializeRepositoriesTableWidget();
}

ShowAllRepositories::~ShowAllRepositories()
{
    delete m_UI;
}

void ShowAllRepositories::initializeRepositoriesTableWidget()
{
    m_UI->RepositoriesTableWidget->setColumnCount(3);
    QStringList list;
    list << "Name Of Repository" << "Name of Branch" << "Time Interval (sec)";
    m_UI->RepositoriesTableWidget->setHorizontalHeaderLabels(list);
    m_UI->RepositoriesTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    for (int i = 0; i < m_UI->RepositoriesTableWidget->columnCount(); ++i)
    {
        m_UI->RepositoriesTableWidget->setColumnWidth(i, (m_UI->RepositoriesTableWidget->width() - 10) / 3);
    }
}

void ShowAllRepositories::show()
{
    if (!m_Reposiries.empty())
    {
        fillTheTable();
        QWidget::show();
    }
    else
    {
        QMessageBox::critical(this, "Error", "There are not available repositories!", QMessageBox::Critical, QMessageBox::Ok);
    }
}

void ShowAllRepositories::setRepositories(std::vector<std::shared_ptr<IRepository>> ptr)
{
    m_Reposiries = ptr;
}

void ShowAllRepositories::setTimeInterval(std::chrono::seconds& time)
{
    m_TimeInterval = time;
}

void ShowAllRepositories::fillTheTable()
{
    deleteAllRows();
    for (size_t i = 0; i < m_Reposiries.size(); ++i)
    {
        m_UI->RepositoriesTableWidget->insertRow(static_cast<int>(i));
        m_UI->RepositoriesTableWidget->setItem(static_cast<int>(i), 0, new QTableWidgetItem(m_Reposiries[i]->getRepositoryName().c_str()));
        m_UI->RepositoriesTableWidget->setItem(static_cast<int>(i), 1, new QTableWidgetItem(m_Reposiries[i]->getCurrentBranchName().c_str()));
        m_UI->RepositoriesTableWidget->setItem(static_cast<int>(i), 2, new QTableWidgetItem(std::to_string(m_TimeInterval.count()).c_str()));
    }
}

void ShowAllRepositories::deleteAllRows()
{
    for (int i = 0; i < m_UI->RepositoriesTableWidget->columnCount(); ++i)
    {
        m_UI->RepositoriesTableWidget->removeRow(i);
    }
}

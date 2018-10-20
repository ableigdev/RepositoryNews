#include "ShowAllRepositories.h"
#include "ui_ShowAllRepositories.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>
#include <QComboBox>
#include <string>
#include <chrono>

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
    initializeContextMenu();
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
    m_UI->RepositoriesTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    m_UI->RepositoriesTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (int i = 0; i < m_UI->RepositoriesTableWidget->columnCount(); ++i)
    {
        m_UI->RepositoriesTableWidget->setColumnWidth(i, (m_UI->RepositoriesTableWidget->width() - 10) / 3);
    }

    connect(m_UI->RepositoriesTableWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(closeContextMenuSlot()));
    connect(m_UI->RepositoriesTableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenuSLot(QPoint)));
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

void ShowAllRepositories::setTimeInterval(std::vector<std::chrono::seconds>& time)
{
    m_TimeIntervals = time;
}

void ShowAllRepositories::fillTheTable()
{
    deleteAllRows();
    for (size_t i = 0; i < m_Reposiries.size(); ++i)
    {
        m_UI->RepositoriesTableWidget->insertRow(static_cast<int>(i));
        m_UI->RepositoriesTableWidget->setItem(static_cast<int>(i), 0, new QTableWidgetItem(m_Reposiries[i]->getRepositoryName().c_str()));
        m_UI->RepositoriesTableWidget->setItem(static_cast<int>(i), 1, new QTableWidgetItem(m_Reposiries[i]->getCurrentBranchName().c_str()));
        m_UI->RepositoriesTableWidget->setItem(static_cast<int>(i), 2, new QTableWidgetItem(std::to_string(m_TimeIntervals[i].count()).c_str()));
    }
}

void ShowAllRepositories::deleteAllRows()
{
    for (int i = 0; i < m_UI->RepositoriesTableWidget->columnCount(); ++i)
    {
        m_UI->RepositoriesTableWidget->removeRow(i);
    }
}

void ShowAllRepositories::closeContextMenuSlot()
{
    m_ContextMenu->hide();
}

void ShowAllRepositories::showContextMenuSLot(QPoint position)
{
    m_ContextMenu->popup(m_UI->RepositoriesTableWidget->viewport()->mapToGlobal(position));
}

void ShowAllRepositories::initializeContextMenu()
{
    m_ContextMenu = std::make_unique<QMenu>(this);
    m_ChangeProperties = std::make_unique<QAction>("Change", this);
    m_SaveProperties = std::make_unique<QAction>("Save", this);
    connect(m_ChangeProperties.get(), SIGNAL(triggered()), this, SLOT(changePropertiesSlot()));
    connect(m_SaveProperties.get(), SIGNAL(triggered()), this, SLOT(savePropertiesSlot()));
    m_ContextMenu->addAction(m_ChangeProperties.get());
    m_ContextMenu->addAction(m_SaveProperties.get());
    enabledActions(true);
}

void ShowAllRepositories::changePropertiesSlot()
{
    int index = m_UI->RepositoriesTableWidget->currentIndex().row();
    QComboBox* branchComboBox = new QComboBox();
    QComboBox* timeComboBox = new QComboBox();

    m_Reposiries[static_cast<size_t>(index)]->prepareBranches();
    auto branches = m_Reposiries[static_cast<size_t>(index)]->getBranchName();
    for (const auto& nameOfBranch : branches)
    {
         branchComboBox->addItem(nameOfBranch.c_str());
    }

    timeComboBox->addItem("5 min");
    timeComboBox->addItem("30 min");
    timeComboBox->addItem("1 hour");

    connect(branchComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseBranchSlot(int)));
    connect(timeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseTimeIntervalSlot(int)));

    m_UI->RepositoriesTableWidget->setCellWidget(index, 1, branchComboBox);
    m_UI->RepositoriesTableWidget->setCellWidget(index, 2, timeComboBox);
    enabledActions(false);
    m_UI->RepositoriesTableWidget->update();
}

void ShowAllRepositories::chooseBranchSlot(int index)
{
    m_Reposiries[static_cast<size_t>(m_UI->RepositoriesTableWidget->selectionModel()->currentIndex().row())]->setCurrentBranch(static_cast<size_t>(index));
}

void ShowAllRepositories::chooseTimeIntervalSlot(int index)
{
    // TODO: Improve this part of the code
    std::chrono::seconds sec;
    switch (index)
    {
        case 0:
        {
            std::chrono::minutes min {5};
            sec = min;
            break;
        }
        case 1:
        {
            std::chrono::minutes min {30};
            sec = min;
            break;
        }
        case 2:
        {
            std::chrono::hours hour {1};
            sec = hour;
            break;
        }
        default:
        {
            break;
        }
    }

    m_TimeIntervals[static_cast<size_t>(m_UI->RepositoriesTableWidget->selectionModel()->currentIndex().row())] = sec;
}

void ShowAllRepositories::savePropertiesSlot()
{
    closeEditMode();
    fillTheTable();
    this->update();
}

void ShowAllRepositories::enabledActions(bool flag)
{
    m_ContextMenu->actions().at(0)->setEnabled(flag);
    m_ContextMenu->actions().at(1)->setDisabled(flag);
}

void ShowAllRepositories::closeEditMode()
{
    auto row = m_UI->RepositoriesTableWidget->selectionModel()->currentIndex().row();
    m_UI->RepositoriesTableWidget->removeRow(row);
    m_UI->RepositoriesTableWidget->removeCellWidget(row, 1);
    m_UI->RepositoriesTableWidget->removeCellWidget(row, 2);
    enabledActions(true);
}

void ShowAllRepositories::closeEvent(QCloseEvent* event)
{
    closeEditMode();
    event->accept();
}

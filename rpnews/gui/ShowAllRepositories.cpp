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
#include <algorithm>
#include "rpnews/helpers/SaveConfig.h"
#include "rpnews/helpers/GetTimeInterval.h"
#include "rpnews/helpers/DeleteRepositoryFolder.h"
#include "rpnews/helpers/FillComboBox.h"

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
    QIcon trayImage(":/images/images/logo.png");
    this->setWindowIcon(trayImage);
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

    connect(m_UI->RepositoriesTableWidget, &QTableWidget::clicked, this, &ShowAllRepositories::closeContextMenuSlot);
    connect(m_UI->RepositoriesTableWidget, &QTableWidget::customContextMenuRequested, this, &ShowAllRepositories::showContextMenuSLot);
}

void ShowAllRepositories::show()
{
    if (!m_Repositories.empty())
    {
        fillTheTable();
        QDialog::exec();
    }
    else
    {
        QMessageBox::critical(this, "Error", "There are not available repositories!", QMessageBox::Critical, QMessageBox::Ok);
    }
}

void ShowAllRepositories::setRepositories(std::vector<std::pair<int, std::shared_ptr<IRepository>>>&& repositories)
{
    m_Repositories = std::move(repositories);
}

void ShowAllRepositories::setTimers(std::vector<std::shared_ptr<QTimer>>&& timers)
{
    m_Timers = std::move(timers);
}

void ShowAllRepositories::setConnections(std::vector<QMetaObject::Connection>&& connections)
{
    m_Connections = std::move(connections);
}

std::vector<std::pair<int, std::shared_ptr<IRepository>>>&& ShowAllRepositories::getRepositories()
{
    return std::move(m_Repositories);
}

std::vector<std::shared_ptr<QTimer>>&& ShowAllRepositories::getTimers()
{
    return std::move(m_Timers);
}

std::vector<QMetaObject::Connection>&& ShowAllRepositories::getConnections()
{
    return std::move(m_Connections);
}

void ShowAllRepositories::fillTheTable()
{
    deleteAllRows();
    int counter = 0;
    for (const auto& i : m_Repositories)
    {
        m_UI->RepositoriesTableWidget->insertRow(counter);
        m_UI->RepositoriesTableWidget->setItem(counter, 0, new QTableWidgetItem(i.second->getRepositoryName().c_str()));
        m_UI->RepositoriesTableWidget->setItem(counter, 1, new QTableWidgetItem(i.second->getCurrentBranchName().c_str()));
        m_UI->RepositoriesTableWidget->setItem(counter, 2, new QTableWidgetItem(std::to_string(m_Timers[static_cast<size_t>(counter)]->intervalAsDuration().count() / 1000).c_str()));
        ++counter;
    }
}

void ShowAllRepositories::deleteAllRows()
{
    m_UI->RepositoriesTableWidget->clearContents();
    for (int i = 0; i < m_UI->RepositoriesTableWidget->rowCount(); ++i)
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
    m_ChangeAction = std::make_unique<QAction>("Change", this);
    m_SaveAction = std::make_unique<QAction>("Save", this);
    m_DeleteAction = std::make_unique<QAction>("Delete", this);
    connect(m_ChangeAction.get(), &QAction::triggered, this, &ShowAllRepositories::changePropertiesSlot);
    connect(m_SaveAction.get(), &QAction::triggered, this, &ShowAllRepositories::savePropertiesSlot);
    connect(m_DeleteAction.get(), &QAction::triggered, this, &ShowAllRepositories::deleteRepositorySlot);
    m_ContextMenu->addAction(m_ChangeAction.get());
    m_ContextMenu->addAction(m_SaveAction.get());
    m_ContextMenu->addAction(m_DeleteAction.get());
    enabledActions(true);
}

void ShowAllRepositories::changePropertiesSlot()
{
    int index = m_UI->RepositoriesTableWidget->currentIndex().row();
    auto branchComboBox = new QComboBox();
    auto timeComboBox = new QComboBox();

    m_Repositories[static_cast<size_t>(index)].second->prepareBranches();
    helpers::fillBranchComboBox(m_Repositories[static_cast<size_t>(index)].second->getBranchName(), branchComboBox);
    helpers::fillTimeComboBox(timeComboBox);

    connect(branchComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ShowAllRepositories::chooseBranchSlot);
    connect(timeComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ShowAllRepositories::chooseTimeIntervalSlot);

    m_UI->RepositoriesTableWidget->setCellWidget(index, 1, branchComboBox);
    m_UI->RepositoriesTableWidget->setCellWidget(index, 2, timeComboBox);
    chooseBranchSlot(0);
    chooseTimeIntervalSlot(0);
    enabledActions(false);
    m_UI->RepositoriesTableWidget->update();
}

void ShowAllRepositories::chooseBranchSlot(int index)
{
    m_Repositories[static_cast<size_t>(m_UI->RepositoriesTableWidget->selectionModel()->currentIndex().row())].second->setCurrentBranch(static_cast<size_t>(index));
}

void ShowAllRepositories::chooseTimeIntervalSlot(int index)
{
    m_Timers[static_cast<size_t>(m_UI->RepositoriesTableWidget->selectionModel()->currentIndex().row())]->setInterval(helpers::getTimeInterval(index));
}

void ShowAllRepositories::savePropertiesSlot()
{
    size_t index = static_cast<size_t>(m_UI->RepositoriesTableWidget->selectionModel()->currentIndex().row());
    std::chrono::seconds sec {m_Timers[index]->intervalAsDuration().count() / 1000};

    SaveConfig::saveGUIConfig(m_Repositories[index].second->getRepositoryName(),
                              m_Repositories[index].second->getCurrentBranchName(),
                              m_Repositories[index].second->getCurrentBranchIndex(),
                              sec);
    closeEditMode();
    fillTheTable();
    this->update();
}

void ShowAllRepositories::enabledActions(bool flag)
{
    m_ContextMenu->actions().at(0)->setEnabled(flag);
    m_ContextMenu->actions().at(1)->setDisabled(flag);
    m_ContextMenu->actions().at(2)->setEnabled(flag);
}

void ShowAllRepositories::closeEditMode()
{
    auto row = m_UI->RepositoriesTableWidget->selectionModel()->currentIndex().row();
    m_UI->RepositoriesTableWidget->removeCellWidget(row, 1);
    m_UI->RepositoriesTableWidget->removeCellWidget(row, 2);
    m_UI->RepositoriesTableWidget->removeRow(row);

    enabledActions(true);
}

void ShowAllRepositories::closeEvent(QCloseEvent* event)
{
    enabledActions(true);
    deleteAllRows();
    event->accept();
}

void ShowAllRepositories::deleteRepositorySlot()
{
    size_t index = static_cast<size_t>(m_UI->RepositoriesTableWidget->currentIndex().row());
    auto repositoryName = m_Repositories[index].second->getRepositoryName();
    m_Timers[index]->stop();
    QObject::disconnect(m_Connections[index]);
    m_Timers.erase(std::remove(m_Timers.begin(), m_Timers.end(), m_Timers[index]), m_Timers.end());
    m_Repositories.erase(std::remove(m_Repositories.begin(), m_Repositories.end(), m_Repositories[index]), m_Repositories.end());
    m_Connections.erase(std::remove(m_Connections.begin(), m_Connections.end(), m_Connections[index]), m_Connections.end());
    helpers::deleteRepositoryFolder(std::move(repositoryName));
    fillTheTable();
    this->update();
}

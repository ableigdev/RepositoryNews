#ifndef SHOWALLREPOSITORIES_H
#define SHOWALLREPOSITORIES_H

#include <QDialog>
#include <QPoint>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
#include <QTimer>
#include <QMetaObject>
#include <memory>
#include <vector>
#include <chrono>
#include "interfaces/IRepository.h"

namespace Ui
{
    class ShowAllRepositories;
}

class ShowAllRepositories : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAllRepositories(QWidget* parent = nullptr);
    ~ShowAllRepositories();
    void show();
    void setRepositories(std::vector<std::pair<int, std::shared_ptr<IRepository>>>&& repositories);
    void setTimers(std::vector<std::shared_ptr<QTimer>>&& time);
    void setConnections(std::vector<QMetaObject::Connection>&& connections);

    std::vector<std::pair<int, std::shared_ptr<IRepository>>>&& getRepositories();
    std::vector<std::shared_ptr<QTimer>>&& getTimers();
    std::vector<QMetaObject::Connection>&& getConnections();

private slots:
    void closeContextMenuSlot();
    void showContextMenuSLot(QPoint);
    void changePropertiesSlot();
    void chooseBranchSlot(int index);
    void chooseTimeIntervalSlot(int index);
    void savePropertiesSlot();
    void deleteRepositorySlot();

private:
    void initializeRepositoriesTableWidget();
    void initializeContextMenu();
    void fillTheTable();
    void deleteAllRows();
    void enabledActions(bool flag);
    void closeEditMode();
    void closeEvent(QCloseEvent* event);

private:
    Ui::ShowAllRepositories* m_UI;
    std::vector<std::pair<int, std::shared_ptr<IRepository>>> m_Repositories {};
    std::vector<std::shared_ptr<QTimer>> m_Timers;
    std::vector<QMetaObject::Connection> m_Connections;
    std::unique_ptr<QMenu> m_ContextMenu;
    std::unique_ptr<QAction> m_ChangeAction;
    std::unique_ptr<QAction> m_SaveAction;
    std::unique_ptr<QAction> m_DeleteAction;
};

#endif // SHOWALLREPOSITORIES_H

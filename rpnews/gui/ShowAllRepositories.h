#ifndef SHOWALLREPOSITORIES_H
#define SHOWALLREPOSITORIES_H

#include <QDialog>
#include <QPoint>
#include <QMenu>
#include <QAction>
#include <memory>
#include <vector>
#include <chrono>
#include "rpnews/interfaces/IRepository.h"

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
    void setRepositories(std::vector<std::shared_ptr<IRepository>> ptr);
    void setTimeInterval(std::vector<std::chrono::seconds>& time);

private slots:
    void closeContextMenuSlot();
    void showContextMenuSLot(QPoint);
    void changePropertiesSlot();

private:
    void initializeRepositoriesTableWidget();
    void initializeContextMenu();
    void fillTheTable();
    void deleteAllRows();

private:
    Ui::ShowAllRepositories* m_UI;
    std::vector<std::shared_ptr<IRepository>> m_Reposiries {};
    std::vector<std::chrono::seconds> m_TimeIntervals;
    std::unique_ptr<QMenu> m_ContextMenu;
    std::unique_ptr<QAction> m_ChangeProperties;
};

#endif // SHOWALLREPOSITORIES_H

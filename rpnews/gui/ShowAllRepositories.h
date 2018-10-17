#ifndef SHOWALLREPOSITORIES_H
#define SHOWALLREPOSITORIES_H

#include <QDialog>
#include <QCloseEvent>
#include <QShowEvent>
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

private:
    void initializeRepositoriesTableWidget();
    void fillTheTable();
    void deleteAllRows();

private:
    Ui::ShowAllRepositories* m_UI;
    std::vector<std::shared_ptr<IRepository>> m_Reposiries {};
    std::vector<std::chrono::seconds> m_TimeIntervals;
};

#endif // SHOWALLREPOSITORIES_H

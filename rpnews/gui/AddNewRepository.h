#ifndef ADDNEWREPOSITORY_H
#define ADDNEWREPOSITORY_H

#include <QDialog>
#include <QCloseEvent>
#include <QShowEvent>
#include <memory>
#include <chrono>
#include "interfaces/IRepositoryFactory.h"
#include "interfaces/IRepository.h"

namespace Ui
{
    class AddNewRepository;
}

class AddNewRepository : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewRepository(QWidget* parent = nullptr);
    ~AddNewRepository();
    bool repositoryIsReady() const;
    std::shared_ptr<interfaces::IRepository>&& getRepository();
    std::chrono::seconds getIntervalTime() const;

private slots:
    void on_ComboBox_RepositoryType_activated(int index);
    void on_Button_Connect_clicked();
    void on_ComboBox_BranchName_activated(int index);
    void on_ComboBox_TimeInterval_activated(int index);
    void on_Button_Add_Save_clicked();
    void on_Button_Cancel_clicked();

private:
    void showEvent(QShowEvent* event);
    void initializeComboBoxRepositoryType();
    void initializeComboBoxBranchName();
    void initializeComboBoxTimeInterval();
    void enableElements(bool flag);

private:
    Ui::AddNewRepository* m_UI;
    std::unique_ptr<interfaces::IRepositoryFactory> m_RepositoryFactory;
    std::shared_ptr<interfaces::IRepository> m_Repository;
    std::chrono::seconds m_TimeForSynchronization;
    bool m_RepositoryIsReady = false;

};

#endif // ADDNEWREPOSITORY_H

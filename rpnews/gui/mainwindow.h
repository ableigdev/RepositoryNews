#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <memory>
#include <chrono>
#include "rpnews/interfaces/IRepositoryFactory.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    bool repositoryIsReady() const;
    std::unique_ptr<IRepository> getRepository();

private slots:
    void on_Button_Cancel_clicked();
    void on_Button_Add_Save_clicked();
    void on_ComboBox_TimeInterval_activated(int index);
    void on_ComboBox_BranchName_activated(int index);
    void on_Button_Connect_clicked();
    void on_ComboBox_RepositoryType_activated(int index);

private:
    void closeEvent(QCloseEvent* event);
    void showEvent(QShowEvent* event);
    void initializeComboBoxRepositoryType();
    void deleteRepositoryFolder(const std::string& name);
    void initializeComboBoxBranchName();
    void initializeComboBoxTimeInterval();

private:
    Ui::MainWindow* m_UI;
    std::unique_ptr<IRepositoryFactory> m_RepositoryFactory;
    std::unique_ptr<IRepository> m_Repository;
    std::chrono::seconds m_TimeForSynchronization;
};

#endif // MAINWINDOW_H

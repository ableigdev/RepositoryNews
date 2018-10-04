#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <memory>
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

private slots:
    void on_Button_Connect_clicked();

private slots:
    void on_ComboBox_RepositoryType_activated(int index);

private:
    void closeEvent(QCloseEvent* event);
    void initializeComboBoxRepositoryType();

private:
    Ui::MainWindow* m_UI;
    std::unique_ptr<IRepositoryFactory> m_RepositoryFactory;
};

#endif // MAINWINDOW_H

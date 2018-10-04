#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rpnews/git_implementation/GitRepositoryFactory.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    m_UI(new Ui::MainWindow)
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
    initializeComboBoxRepositoryType();
    on_ComboBox_RepositoryType_activated(0);
}

MainWindow::~MainWindow()
{
    delete m_UI;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (this->isVisible())
    {
        event->ignore();
        this->hide();
    }
}

void MainWindow::initializeComboBoxRepositoryType()
{
    m_UI->ComboBox_RepositoryType->addItem("Git");
}

void MainWindow::on_ComboBox_RepositoryType_activated(int index)
{
    switch (index)
    {
        case 0:
        {
            m_RepositoryFactory = std::make_unique<GitRepositoryFactory>();
            break;
        }
        default:
        {
            break;
        }
    }
}

void MainWindow::on_Button_Connect_clicked()
{
    if (m_UI->Edit_URL->text().isEmpty() || m_UI->Edit_Login->text().isEmpty() || m_UI->Edit_Password->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Input your credentials!", QMessageBox::Ok);
    }
    else
    {

    }
}

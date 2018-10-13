#include "ShowAllRepositories.h"
#include "ui_ShowAllRepositories.h"

ShowAllRepositories::ShowAllRepositories(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowAllRepositories)
{
    ui->setupUi(this);
}

ShowAllRepositories::~ShowAllRepositories()
{
    delete ui;
}

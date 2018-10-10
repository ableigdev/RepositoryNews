#include "AddNewRepository.h"
#include "ui_AddNewRepository.h"

AddNewRepository::AddNewRepository(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewRepository)
{
    ui->setupUi(this);
}

AddNewRepository::~AddNewRepository()
{
    delete ui;
}

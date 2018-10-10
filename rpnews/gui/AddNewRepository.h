#ifndef ADDNEWREPOSITORY_H
#define ADDNEWREPOSITORY_H

#include <QDialog>

namespace Ui {
class AddNewRepository;
}

class AddNewRepository : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewRepository(QWidget *parent = nullptr);
    ~AddNewRepository();

private:
    Ui::AddNewRepository *ui;
};

#endif // ADDNEWREPOSITORY_H

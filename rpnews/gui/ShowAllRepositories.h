#ifndef SHOWALLREPOSITORIES_H
#define SHOWALLREPOSITORIES_H

#include <QDialog>

namespace Ui {
class ShowAllRepositories;
}

class ShowAllRepositories : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAllRepositories(QWidget *parent = nullptr);
    ~ShowAllRepositories();

private:
    Ui::ShowAllRepositories *ui;
};

#endif // SHOWALLREPOSITORIES_H

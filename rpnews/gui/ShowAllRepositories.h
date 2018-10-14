#ifndef SHOWALLREPOSITORIES_H
#define SHOWALLREPOSITORIES_H

#include <QDialog>
#include <QCloseEvent>
#include "trayiconapp.h"

namespace Ui
{
    class ShowAllRepositories;
}

class ShowAllRepositories : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAllRepositories(TrayIconApp* parent = nullptr);
    ~ShowAllRepositories();

private:
    void closeEvent(QCloseEvent* event);

private:
    Ui::ShowAllRepositories* m_UI;
    TrayIconApp* m_TrayIconApp;
};

#endif // SHOWALLREPOSITORIES_H

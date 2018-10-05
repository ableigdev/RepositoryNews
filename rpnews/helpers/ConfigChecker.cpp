#include <stdexcept>
#include <QDir>
#include <QString>
#include "PathChecker.h"

std::string PathChecker::checkAndGetFinalPath(const std::string &nameRepository)
{
    QDir dir;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

    if (!dir.current().exists(".configs"))
    {
        dir.current().mkdir(".configs");
    }

    dir.cd(".configs");
    QString path = dir.currentPath() + "/" + dir.path() + "/" + nameRepository.data();

    if (dir.exists(path))
    {
        throw std::logic_error("The repository '" + nameRepository + "' is exist");
    }

    return path.toStdString();
}
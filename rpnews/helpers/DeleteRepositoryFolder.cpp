#include "DeleteRepositoryFolder.h"
#include <QDir>

void helpers::deleteRepositoryFolder(std::string&& name)
{
    QDir dir;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

    if (dir.current().exists(".configs"))
    {
        dir.cd(".configs");
        dir.cd(name.c_str());
        dir.removeRecursively();
    }
}

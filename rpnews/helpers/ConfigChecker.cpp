#include <stdexcept>
#include <regex>
#include <QDir>
#include <QString>
#include <QDebug>
#include "ConfigChecker.h"

std::string ConfigChecker::checkAndGetFinalPath(const std::string &nameRepository)
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

std::string ConfigChecker::getRepositoryFolderName(const std::string& url)
{
    std::regex regexValue(R"(\/([\w]+)\.[\w]+$)");
    std::cmatch result;
    std::regex_search(url.data(), result, regexValue);
    return result[1].str();
}

std::string ConfigChecker::getRepositoryFolderNameFromPath(const std::string& path)
{
    std::regex regexValue(R"(\/([\w]+)\/.git)");
    std::cmatch result;
    std::regex_search(path.data(), result, regexValue);
    return result[1].str();
}

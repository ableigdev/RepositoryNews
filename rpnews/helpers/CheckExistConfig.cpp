#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QStringList>
#include <regex>
#include <algorithm>
#include <iostream>
#include "CheckExistConfig.h"

std::vector<std::string> CheckExistConfig::check()
{
    std::vector<std::string> result {};
    QDir dir;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

    if (dir.exists(".configs"))
    {
        dir.cd(".configs");
        std::string currentPath = dir.currentPath().toStdString();
        QDirIterator dirIterator(dir, QDirIterator::Subdirectories);
        std::cmatch cm;
        std::regex reg(R"((.*(\.git))\/config)");
        std::string stringData;
        while (dirIterator.hasNext())
        {
            stringData = dirIterator.filePath().toStdString();
            if (std::regex_search(stringData.data(), cm, reg))
            {
                auto str = cm[1].str();
                if (std::find(result.begin(), result.end(), str) == result.end())
                {
                    result.emplace_back(currentPath.append("/").append(str));
                }
            }
            dirIterator.next();
        }
    }
    return result;
}
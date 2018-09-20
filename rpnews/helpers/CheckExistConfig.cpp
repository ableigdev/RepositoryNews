#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QStringList>
#include <regex>
#include <fstream>
#include "CheckExistConfig.h"

std::vector<GetRepositoryInfo> CheckExistConfig::check()
{
    std::vector<GetRepositoryInfo> result {};
    QDir dir;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

    if (dir.exists(".configs"))
    {
        dir.cd(".configs");
        std::string currentPath = dir.currentPath().toStdString();
        QDirIterator dirIterator(dir, QDirIterator::Subdirectories);

        std::cmatch resultOfFindingRepositoryFolder;
        std::cmatch resultOfFindingConfigFile;
        std::regex findRepositoryFolder(R"((.*(\.git)))");
        std::regex findConfigRepository(R"(.*(config_rep))");
        std::string stringData;
        GetRepositoryInfo repositoryInfo {};

        while (dirIterator.hasNext())
        {
            stringData = dirIterator.filePath().toStdString();
            if (std::regex_search(stringData.data(), resultOfFindingRepositoryFolder, findRepositoryFolder))
            {
                repositoryInfo.path = currentPath + "/" + resultOfFindingRepositoryFolder[1].str();
            }

            if (std::regex_search(stringData.data(), resultOfFindingConfigFile, findConfigRepository))
            {
                std::string str(resultOfFindingConfigFile.str());
                std::ifstream inFile(str, std::ios::in);

                inFile >> repositoryInfo.type >> repositoryInfo.user >> repositoryInfo.pass;
            }

            if (!repositoryInfo.path.empty() && repositoryInfo.type != -1 && !repositoryInfo.user.empty() && !repositoryInfo.pass.empty())
            {
                result.emplace_back(repositoryInfo);
                repositoryInfo.path.clear();
                repositoryInfo.type = -1;
                repositoryInfo.user.clear();
                repositoryInfo.pass.clear();
            }
            dirIterator.next();
        }
    }
    return result;
}
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
        std::cmatch resultOfFindingConfigGUIFile;
        std::regex findRepositoryFolder(R"((.*(\.git)))");
        std::regex findConfigRepository(R"(.*(config_rep))");
        std::regex findConfigGUIRepository(R"(.*(config_gui_rep))");
        std::string stringData;
        GetRepositoryInfo repositoryInfo {};

        do
        {
            stringData = dirIterator.filePath().toStdString();
            if (std::regex_search(stringData.data(), resultOfFindingRepositoryFolder, findRepositoryFolder))
            {
                repositoryInfo.path = currentPath + "/" + resultOfFindingRepositoryFolder[1].str();
            }

            if (std::regex_search(stringData.data(), resultOfFindingConfigFile, findConfigRepository))
            {
                std::ifstream inFile(resultOfFindingConfigFile.str(), std::ios::in);
                inFile >> repositoryInfo.type >> repositoryInfo.user >> repositoryInfo.pass;
            }

            if (std::regex_search(stringData.data(), resultOfFindingConfigGUIFile, findConfigGUIRepository))
            {
                std::ifstream inFile(resultOfFindingConfigGUIFile.str(), std::ios::in);
                inFile >> repositoryInfo.branchName >> repositoryInfo.branchIndex >> repositoryInfo.timeInterval;
            }

            if (!repositoryInfo.path.empty() && repositoryInfo.type != -1
                    && !repositoryInfo.user.empty() && !repositoryInfo.pass.empty()
                    && !repositoryInfo.branchName.empty() && repositoryInfo.branchIndex != -1
                    && repositoryInfo.timeInterval != -1)
            {
                result.emplace_back(repositoryInfo);
                repositoryInfo.path.clear();
                repositoryInfo.type = -1;
                repositoryInfo.user.clear();
                repositoryInfo.pass.clear();
                repositoryInfo.branchName.clear();
                repositoryInfo.branchIndex = -1;
                repositoryInfo.timeInterval = -1;
            }
        } while (!dirIterator.next().isEmpty());
    }
    return result;
}

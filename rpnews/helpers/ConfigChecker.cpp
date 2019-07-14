#include <stdexcept>
#include <regex>
#include <filesystem>
#include "ConfigChecker.h"
#include "RepositoryExist.h"

std::string helpers::ConfigChecker::checkAndGetFinalPath(const std::string& nameRepository)
{
    std::string folderName(".configs");
    auto currentPath = std::filesystem::current_path();

    if (!std::filesystem::exists(folderName))
    {
        std::filesystem::create_directory(folderName, currentPath);
    }

    currentPath /= folderName;
    currentPath /= nameRepository;

    if (std::filesystem::exists(currentPath))
    {
        throw RepositoryExist(nameRepository);
    }

    return currentPath.string();
}

std::string helpers::ConfigChecker::getRepositoryFolderName(const std::string& url)
{
    std::regex regexValue(R"(\/([a-zA-Z0-9\._-]+)\.[\w]+$)");
    std::cmatch result;
    std::regex_search(url.data(), result, regexValue);
    return result[1].str();
}

std::string helpers::ConfigChecker::getRepositoryFolderNameFromPath(const std::string& path)
{
    std::regex regexValue(R"(\/([a-zA-Z0-9\._-]+)\/.git$)");
    std::cmatch result;
    std::regex_search(path.data(), result, regexValue);
    return result[1].str();
}

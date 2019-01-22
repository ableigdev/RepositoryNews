#ifndef RPNEWS_PATHCHECKER_H
#define RPNEWS_PATHCHECKER_H

#include <string>

namespace helpers
{
    class ConfigChecker
    {
    public:
        ConfigChecker() = default;
        ~ConfigChecker() = default;
        static std::string checkAndGetFinalPath(const std::string& nameRepository);
        static std::string getRepositoryFolderName(const std::string& url);
        static std::string getRepositoryFolderNameFromPath(const std::string& path);
    };
}

#endif //RPNEWS_PATHCHECKER_H

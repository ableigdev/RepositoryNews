#ifndef RPNEWS_PATHCHECKER_H
#define RPNEWS_PATHCHECKER_H

#include <string>

class ConfigChecker
{
public:
    ConfigChecker() = default;
    ~ConfigChecker() = default;
    static std::string checkAndGetFinalPath(const std::string& nameRepository);
    static std::string getRepositoryFilderName(const std::string& url);
};

#endif //RPNEWS_PATHCHECKER_H

#ifndef RPNEWS_PATHCHECKER_H
#define RPNEWS_PATHCHECKER_H

#include <string>

class PathChecker
{
public:
    PathChecker() = default;
    ~PathChecker() = default;
    static std::string checkAndGetFinalPath(const std::string& nameRepository);
};

#endif //RPNEWS_PATHCHECKER_H

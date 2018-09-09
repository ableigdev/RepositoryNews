#ifndef RPNEWS_CHECKEXISTCONFIG_H
#define RPNEWS_CHECKEXISTCONFIG_H

#include <string>
#include <vector>

class CheckExistConfig
{
public:
    CheckExistConfig() = default;
    ~CheckExistConfig() = default;
    std::vector<std::string> check();
};

#endif //RPNEWS_CHECKEXISTCONFIG_H

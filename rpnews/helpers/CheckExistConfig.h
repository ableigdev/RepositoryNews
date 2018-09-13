#ifndef RPNEWS_CHECKEXISTCONFIG_H
#define RPNEWS_CHECKEXISTCONFIG_H

#include <string>
#include <vector>
#include "rpnews_types.h"

class CheckExistConfig
{
public:
    CheckExistConfig() = default;
    ~CheckExistConfig() = default;
    static std::vector<GetRepositoryInfo> check();
};

#endif //RPNEWS_CHECKEXISTCONFIG_H

#ifndef RPNEWS_SAVECONFIG_H
#define RPNEWS_SAVECONFIG_H

#include <string>
#include "rpnews_types.h"

class SaveConfig
{
public:
    SaveConfig() = default;
    ~SaveConfig() = default;
    void save(const std::string& nameOfTypeRepository, const secure_string& user, const secure_string& pass);
};

#endif //RPNEWS_SAVECONFIG_H

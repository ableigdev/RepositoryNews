#ifndef RPNEWS_SAVECONFIG_H
#define RPNEWS_SAVECONFIG_H

#include <string>
#include "rpnews_types.h"

class SaveConfig
{
public:
    SaveConfig() = default;
    ~SaveConfig() = default;
    static void save(const std::string& path, const TypeRepository& type, const secure_string& user, const secure_string& pass);
};

#endif //RPNEWS_SAVECONFIG_H

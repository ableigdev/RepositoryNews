#ifndef RPNEWS_SAVECONFIG_H
#define RPNEWS_SAVECONFIG_H

#include <string>
#include <chrono>
#include "rpnews_types.h"

class SaveConfig
{
public:
    SaveConfig() = default;
    ~SaveConfig() = default;
    static void save(const std::string& path, const TypeRepository& type, const secure_string& user, const secure_string& pass);
    static void saveGUIConfig(const std::string& nameOfRepository, const std::string& branchName, size_t branchIndex, std::chrono::seconds time);
};

#endif //RPNEWS_SAVECONFIG_H

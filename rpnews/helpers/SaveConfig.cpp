#include <fstream>
#include "SaveConfig.h"

void SaveConfig::save(const std::string& path, const TypeRepository& type, const secure_string& user, const secure_string& pass)
{
    std::ofstream outFile(path + "config_rep", std::ios::out);
    outFile << type << " " << user << " " << pass;
    outFile.close();
}
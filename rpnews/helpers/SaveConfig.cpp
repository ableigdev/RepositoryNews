#include <fstream>
#include "SaveConfig.h"

void SaveConfig::save(const std::string& path, const TypeRepository& type, const secure_string& user, const secure_string& pass)
{
    std::ofstream outFile(path + "config_rep", std::ios::out);
    outFile << type << " " << user << " " << pass;
    outFile.close();
}

void SaveConfig::saveGUIConfig(const std::string& nameOfRepository, const std::string& branchName, size_t branchIndex, std::chrono::seconds time)
{
    std::ofstream outFile(".configs/" + nameOfRepository + "/config_gui_rep", std::ios::out);
    outFile << branchName << " " << branchIndex << " " << time.count();
    outFile.close();
}

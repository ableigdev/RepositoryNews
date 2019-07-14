#include <regex>
#include <fstream>
#include <filesystem>
#include "CheckExistConfig.h"
#include "AESEncryption.h"

std::vector<helpers::GetRepositoryInfo> helpers::CheckExistConfig::check()
{
    std::vector<GetRepositoryInfo> result {};

    if (std::filesystem::exists(".configs"))
    {
        std::string key(AESEncryption::generateKey());
        std::cmatch resultOfFindingRepositoryFolder;
        std::cmatch resultOfFindingConfigFile;
        std::cmatch resultOfFindingConfigGUIFile;
        std::regex findRepositoryFolder(R"((.*(\.git)))");
        std::regex findConfigRepository(R"(.*(config_rep))");
        std::regex findConfigGUIRepository(R"(.*(config_gui_rep))");
        std::string stringData;
        GetRepositoryInfo repositoryInfo {};

        for (auto& currDir : std::filesystem::recursive_directory_iterator(std::filesystem::current_path() / ".configs"))
        {
            stringData = currDir.path().string();
            if (repositoryInfo.path.empty() && std::regex_search(stringData.data(), resultOfFindingRepositoryFolder, findRepositoryFolder))
            {
                repositoryInfo.path = resultOfFindingRepositoryFolder[1].str();
            }

            if (std::regex_search(stringData.data(), resultOfFindingConfigFile, findConfigRepository))
            {
                const short QUANTITY_OF_BYTES = 16;
                std::ifstream inFile(resultOfFindingConfigFile.str(), std::ios::in | std::ios::binary);
                std::string encryptUser(QUANTITY_OF_BYTES, '0');
                std::string encryptPass(QUANTITY_OF_BYTES, '0');
                std::string type(1, '0');
                inFile.read(&type.at(0), 1);
                inFile.seekg(1);
                inFile.read(&encryptUser.at(0), QUANTITY_OF_BYTES);
                inFile.seekg(QUANTITY_OF_BYTES + 1);
                inFile.read(&encryptPass.at(0), QUANTITY_OF_BYTES);
                repositoryInfo.type = std::atoi(type.data());
                repositoryInfo.user = std::move(AESEncryption::decrypt(encryptUser, key));
                repositoryInfo.pass = std::move(AESEncryption::decrypt(encryptPass, key));
                inFile.close();
            }

            if (std::regex_search(stringData.data(), resultOfFindingConfigGUIFile, findConfigGUIRepository))
            {
                std::ifstream inFile(resultOfFindingConfigGUIFile.str(), std::ios::in);
                inFile >> repositoryInfo.branchIndex >> repositoryInfo.timeInterval;
            }

            if (!repositoryInfo.path.empty() && repositoryInfo.type != -1
                    && !repositoryInfo.user.empty() && !repositoryInfo.pass.empty()
                    && repositoryInfo.branchIndex != -1
                    && repositoryInfo.timeInterval != -1)
            {
                result.push_back(repositoryInfo);
                repositoryInfo.path.clear();
                repositoryInfo.type = -1;
                repositoryInfo.user.clear();
                repositoryInfo.pass.clear();
                repositoryInfo.branchIndex = -1;
                repositoryInfo.timeInterval = -1;
            }
        }
    }
    return result;
}

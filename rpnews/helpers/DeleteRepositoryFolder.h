#ifndef DELETEREPOSITORYFOLDER_H
#define DELETEREPOSITORYFOLDER_H

#include <string>
#include <filesystem>

namespace helpers
{
    template <typename StringType>
    void deleteRepositoryFolder(StringType&& name)
    {
        std::string folderName(".configs");
        if (std::filesystem::exists(folderName))
        {
            std::filesystem::remove_all(std::filesystem::current_path() / folderName / (folderName != name ? name : ""));
        }
    }
}

#endif // DELETEREPOSITORYFOLDER_H

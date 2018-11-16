#include "gtest/gtest.h"
#include <QDir>
#include <memory>
#include <stdexcept>

#include "rpnews/interfaces/IRepository.h"
#include "rpnews/interfaces/IRepositoryType.h"
#include "rpnews/interfaces/IRepositoryFactory.h"
#include "rpnews/git_implementation/GitRepositoryTypeImpl.h"
#include "rpnews/git_implementation/GitRepositoryImpl.h"
#include "rpnews/git_implementation/GitRepositoryFactory.h"
#include "rpnews/helpers/rpnews_types.h"
#include "rpnews/helpers/ConfigChecker.h"
#include "rpnews/helpers/RepositoryExist.h"

namespace
{
    void deleteFolder()
    {
        QDir dir;
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        if (dir.exists(".configs"))
        {
            dir.cd(".configs");
            dir.removeRecursively();
        }
    }

    // Enter correct your data, before that you run these tests
    std::string url("https://name@bitbucket.org/name/repository.git"); // Your test repository
    secure_string username("username"); // Your correct username
    secure_string pass("pass"); // Your correct password
}

TEST(ConfigChecker, FolderExists)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    std::unique_ptr<IRepository> rep(ptr->createRepository(url, username, pass, false));
    auto nameOfRepository = rep->getRepositoryName();
    rep.release();
    EXPECT_THROW(ConfigChecker::checkAndGetFinalPath(nameOfRepository), RepositoryExist);
}

TEST(ConfigChecker, FolderIsNotExists)
{
    deleteFolder();
    auto path = ConfigChecker::checkAndGetFinalPath("name");
    EXPECT_TRUE(!path.empty());
}

TEST(ConfigChecker, RepositoryFolderName)
{
    std::string url("https://name@bitbucket.org/name/repository.git");
    EXPECT_EQ(ConfigChecker::getRepositoryFolderName(url), "repository");
}

TEST(ConfigChecker, BadURL)
{
    std::string url("https://name@bitbucket.org/name/repository./git");
    EXPECT_TRUE(ConfigChecker::getRepositoryFolderName(url).empty());
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 

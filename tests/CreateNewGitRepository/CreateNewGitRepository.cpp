#include "gtest/gtest.h"
#include <QDir>
#include <string>
#include <memory>

#include "rpnews/helpers/rpnews_types.h"
#include "rpnews/interfaces/IRepository.h"
#include "rpnews/interfaces/IRepositoryType.h"
#include "rpnews/interfaces/IRepositoryFactory.h"
#include "rpnews/git_implementation/GitRepositoryTypeImpl.h"
#include "rpnews/git_implementation/GitRepositoryImpl.h"
#include "rpnews/git_implementation/GitRepositoryFactory.h"
#include "rpnews/helpers/CheckExistConfig.h"

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

TEST(CreateObject, Valid)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    std::unique_ptr<IRepository> rep(ptr->createRepository(url, username, pass, false));
    EXPECT_TRUE(rep.get() != nullptr);
}

TEST(CreateObject, BadUrl)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    EXPECT_THROW(std::unique_ptr<IRepository> rep(ptr->createRepository("https://name@bitbucket.org/.git", username, pass, false)), std::logic_error);
}

TEST(CreateObject, WrongPassword)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    EXPECT_THROW(std::unique_ptr<IRepository> rep(ptr->createRepository(url, username, "wrong_pass", false)), std::logic_error);
}

TEST(CreateObject, WrongUserName)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    EXPECT_THROW(std::unique_ptr<IRepository> rep(ptr->createRepository(url, "wrong_username", pass, false)), std::logic_error);
}

TEST(MethodsTest, PrepareRepository)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    std::unique_ptr<IRepository> rep(ptr->createRepository(url, username, pass, false));
    EXPECT_NO_THROW(rep->prepareRepository());
}

TEST(MethodsTest, PrepareBranches)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    std::unique_ptr<IRepository> rep(ptr->createRepository(url, username, pass, false));
    rep->prepareRepository();
    EXPECT_NO_THROW((rep->prepareBranches()));
}

TEST(MethodsTest, GetBranchName)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    std::unique_ptr<IRepository> rep(ptr->createRepository(url, username, pass, false));
    rep->prepareRepository();
    rep->prepareBranches();

    EXPECT_TRUE(!rep->getBranchName().empty());
}

TEST(MethodsTest, GetNumberOfBranch)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    std::unique_ptr<IRepository> rep(ptr->createRepository(url, username, pass, false));
    rep->prepareRepository();
    rep->prepareBranches();
    EXPECT_TRUE(rep->getNumberOfBranches() != 0);
}

TEST(MethodsTest, SetCurrentBranchNoThrow)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    std::unique_ptr<IRepository> rep(ptr->createRepository(url, username, pass, false));
    rep->prepareRepository();
    rep->prepareBranches();
    size_t index = rep->getNumberOfBranches();
    EXPECT_TRUE(index != 0);
    EXPECT_NO_THROW(rep->setCurrentBranch(index - 1));
}

TEST(MethodsTest, SetCurrentBranchThrow)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    std::unique_ptr<IRepository> rep(ptr->createRepository(url, username, pass, false));
    rep->prepareRepository();
    rep->prepareBranches();
    size_t index = rep->getNumberOfBranches();
    EXPECT_THROW(rep->setCurrentBranch(index + 1), std::logic_error);
}

TEST(MethodsTest, GetLastCommit)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    std::unique_ptr<IRepository> rep(ptr->createRepository(url, username, pass, false));
    rep->prepareRepository();
    rep->prepareBranches();
    EXPECT_TRUE(!rep->getLastCommit().empty());
}

TEST(OpenRepositoryTest, Valid)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    std::unique_ptr<IRepository> rep(ptr->createRepository(url, username, pass, false));

    EXPECT_TRUE(rep != nullptr);
    rep->saveConfig();
    rep.reset();
    auto result = CheckExistConfig::check();
    EXPECT_NO_THROW(rep.reset(ptr->createRepository(result[0].path, result[0].user, result[0].pass, true)));

    EXPECT_TRUE(rep != nullptr);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
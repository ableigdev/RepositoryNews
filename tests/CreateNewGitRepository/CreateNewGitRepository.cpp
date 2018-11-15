#include "gtest/gtest.h"
#include <QDir>
#include <string>
#include <memory>
#include <fstream>

#include "rpnews/helpers/rpnews_types.h"
#include "rpnews/interfaces/IRepository.h"
#include "rpnews/interfaces/IRepositoryType.h"
#include "rpnews/interfaces/IRepositoryFactory.h"
#include "rpnews/git_implementation/GitRepositoryTypeImpl.h"
#include "rpnews/git_implementation/GitRepositoryImpl.h"
#include "rpnews/git_implementation/GitRepositoryFactory.h"
#include "rpnews/helpers/CheckExistConfig.h"
#include "rpnews/helpers/RepositoryExist.h"
#include "rpnews/helpers/SaveConfig.h"

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

TEST(CreateObject, RepositoryExist)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    std::unique_ptr<IRepository> rep(ptr->createRepository(url, username, pass, false));
    rep->saveConfig();
    EXPECT_THROW(rep.reset(ptr->createRepository(url, username, pass, false)), RepositoryExist);
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
    std::chrono::seconds sec { 30 };
    SaveConfig::saveGUIConfig(rep->getRepositoryName(), rep->getCurrentBranchName(), rep->getCurrentBranchIndex(), sec);
    auto result = CheckExistConfig::check();
    EXPECT_NO_THROW(rep.reset(ptr->createRepository(result.front().path, result.front().user, result.front().pass, true)));
}

TEST(OpenRepositoryTest, WrongPath)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    EXPECT_THROW(std::unique_ptr<IRepository> rep(ptr->createRepository("", username, pass, true)), std::logic_error);
}

TEST(OpenRepositoryTest, WrongUserName)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    std::unique_ptr<IRepository> rep(ptr->createRepository(url, username, pass, false));
    rep->saveConfig();
    std::chrono::seconds sec { 30 };
    SaveConfig::saveGUIConfig(rep->getRepositoryName(), rep->getCurrentBranchName(), rep->getCurrentBranchIndex(), sec);
    auto result = CheckExistConfig::check();
    EXPECT_THROW(std::unique_ptr<IRepository> rep(ptr->createRepository(result.front().path, "wrong_username", result.front().pass, true)), std::logic_error);
}

TEST(OpenRepositoryTest, WrongPassword)
{
    deleteFolder();
    std::unique_ptr<IRepositoryFactory> ptr(new GitRepositoryFactory);
    std::unique_ptr<IRepository> rep(ptr->createRepository(url, username, pass, false));
    rep->saveConfig();
    std::chrono::seconds sec { 30 };
    SaveConfig::saveGUIConfig(rep->getRepositoryName(), rep->getCurrentBranchName(), rep->getCurrentBranchIndex(), sec);
    auto result = CheckExistConfig::check();
    EXPECT_THROW(std::unique_ptr<IRepository> rep(ptr->createRepository(result.front().path, username, "wrong_pass", true)), std::logic_error);
}

TEST(CheckExistConfig, ConfigNotExist)
{
    deleteFolder();
    auto result = CheckExistConfig::check();
    EXPECT_EQ(result.size(), 0);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

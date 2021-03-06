#include "gtest/gtest.h"
#include <QDir>
#include <string>
#include <memory>
#include <fstream>

#include "helpers/rpnews_types.h"
#include "interfaces/IRepository.h"
#include "interfaces/IRepositoryType.h"
#include "interfaces/IRepositoryFactory.h"
#include "git_implementation/GitRepositoryTypeImpl.h"
#include "git_implementation/GitRepositoryImpl.h"
#include "git_implementation/GitRepositoryFactory.h"
#include "git_implementation/GitCreateRepositoryStrategyImpl.h"
#include "git_implementation/GitOpenRepositoryStrategyImpl.h"
#include "helpers/CheckExistConfig.h"
#include "helpers/RepositoryExist.h"
#include "helpers/SaveConfig.h"

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
    helpers::secure_string username("username"); // Your correct username
    helpers::secure_string pass("pass"); // Your correct password
}

TEST(CreateObject, Valid)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, username, pass, std::move(createStrategy)));
    EXPECT_TRUE(rep.get() != nullptr);
}

TEST(CreateObject, BadUrl)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    EXPECT_THROW(std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository("https://name@bitbucket.org/.git", username, pass, std::move(createStrategy))), std::logic_error);
}

TEST(CreateObject, BadStrategy)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    EXPECT_THROW(std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, username, pass, nullptr)), std::logic_error);
}

TEST(CreateObject, WrongPassword)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    EXPECT_THROW(std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, username, "wrong_pass", std::move(createStrategy))), std::logic_error);
}

TEST(CreateObject, WrongUserName)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    EXPECT_THROW(std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, "wrong_username", pass, std::move(createStrategy))), std::logic_error);
}

TEST(CreateObject, RepositoryExist)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, username, pass, std::move(createStrategy)));
    rep->saveConfig();
    createStrategy = std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>();
    EXPECT_THROW(rep = ptr->createRepository(url, username, pass, std::move(createStrategy)), helpers::RepositoryExist);
}

TEST(MethodsTest, PrepareRepository)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, username, pass, std::move(createStrategy)));
    EXPECT_NO_THROW(rep->prepareRepository());
}

TEST(MethodsTest, PrepareBranches)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, username, pass, std::move(createStrategy)));
    rep->prepareRepository();
    EXPECT_NO_THROW((rep->prepareBranches()));
}

TEST(MethodsTest, GetBranchName)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, username, pass, std::move(createStrategy)));
    rep->prepareRepository();
    rep->prepareBranches();

    EXPECT_TRUE(!rep->getBranchName().empty());
}

TEST(MethodsTest, GetNumberOfBranch)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, username, pass, std::move(createStrategy)));
    rep->prepareRepository();
    rep->prepareBranches();
    EXPECT_TRUE(rep->getNumberOfBranches() != 0);
}

TEST(MethodsTest, SetCurrentBranchNoThrow)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, username, pass, std::move(createStrategy)));
    rep->prepareRepository();
    rep->prepareBranches();
    size_t index = rep->getNumberOfBranches();
    EXPECT_TRUE(index != 0);
    EXPECT_NO_THROW(rep->setCurrentBranch(index - 1));
}

TEST(MethodsTest, SetCurrentBranchThrow)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, username, pass, std::move(createStrategy)));
    rep->prepareRepository();
    rep->prepareBranches();
    size_t index = rep->getNumberOfBranches();
    EXPECT_THROW(rep->setCurrentBranch(index + 1), std::logic_error);
}

TEST(MethodsTest, GetLastCommit)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, username, pass, std::move(createStrategy)));
    rep->prepareRepository();
    rep->prepareBranches();
    EXPECT_TRUE(!rep->getLastCommit().empty());
}

TEST(OpenRepositoryTest, Valid)
{
    deleteFolder();

    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, username, pass, std::move(createStrategy)));
    EXPECT_TRUE(rep != nullptr);
    rep->saveConfig();
    std::chrono::seconds sec { 30 };
    helpers::SaveConfig::saveGUIConfig(rep->getRepositoryName(), rep->getCurrentBranchIndex(), sec);
    auto result = helpers::CheckExistConfig::check();
    auto openStrategy(std::make_unique<git_impl::GitOpenRepositoryStrategyImpl>());
    EXPECT_NO_THROW(rep = ptr->createRepository(result.front().path, result.front().user, result.front().pass, std::move(openStrategy)));
}

TEST(OpenRepositoryTest, WrongPath)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto openStrategy(std::make_unique<git_impl::GitOpenRepositoryStrategyImpl>());
    EXPECT_THROW(std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository("", username, pass, std::move(openStrategy))), std::logic_error);
}

TEST(OpenRepositoryTest, WrongUserName)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, username, pass, std::move(createStrategy)));
    rep->saveConfig();
    std::chrono::seconds sec { 30 };
    helpers::SaveConfig::saveGUIConfig(rep->getRepositoryName(), rep->getCurrentBranchIndex(), sec);
    auto result = helpers::CheckExistConfig::check();
    auto openStrategy(std::make_unique<git_impl::GitOpenRepositoryStrategyImpl>());
    EXPECT_THROW(std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(result.front().path, "wrong_username", result.front().pass, std::move(openStrategy))), std::logic_error);
}

TEST(OpenRepositoryTest, WrongPassword)
{
    deleteFolder();
    std::unique_ptr<interfaces::IRepositoryFactory> ptr(new git_impl::GitRepositoryFactory);
    auto createStrategy(std::make_unique<git_impl::GitCreateRepositoryStrategyImpl>());
    std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(url, username, pass, std::move(createStrategy)));
    rep->saveConfig();
    std::chrono::seconds sec { 30 };
    helpers::SaveConfig::saveGUIConfig(rep->getRepositoryName(), rep->getCurrentBranchIndex(), sec);
    auto result = helpers::CheckExistConfig::check();
    auto openStrategy(std::make_unique<git_impl::GitOpenRepositoryStrategyImpl>());
    EXPECT_THROW(std::unique_ptr<interfaces::IRepository> rep(ptr->createRepository(result.front().path, username, "wrong_pass", std::move(openStrategy))), std::logic_error);
}

TEST(CheckExistConfig, ConfigNotExist)
{
    deleteFolder();
    auto result = helpers::CheckExistConfig::check();
    EXPECT_EQ(result.size(), 0);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include "gmock/gmock.h"
#include "rpnews/interfaces/IRepository.h"
#include "rpnews/interfaces/IRepositoryFactory.h"
#include "rpnews/interfaces/IRepositoryType.h"
#include "rpnews/git_implementation/GitRepositoryImpl.h"
#include "rpnews/git_implementation/GitRepositoryFactory.h"
#include "rpnews/git_implementation/GitRepositoryTypeImpl.h"
#include "rpnews/helpers/rpnews_types.h"
#include "rpnews/gui/ShowAllRepositories.h"

#include <QDir>
#include <QApplication>
#include <QTimer>
#include <memory>
#include <chrono>

using namespace testing;

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

class MockGitRepositoryFactory : public IRepositoryFactory
{
public:
    MOCK_METHOD4(createRepository, IRepository*(const std::string& url, const secure_string& user, const secure_string& pass, bool flag));
};

class MockRepository : public IRepository
{
public:
    MOCK_CONST_METHOD0(getBranchName, std::vector<std::string>());
    MOCK_CONST_METHOD0(getNumberOfBranches, size_t());
    MOCK_METHOD1(setCurrentBranch, void(size_t));
    MOCK_CONST_METHOD0(getCurrentBranchIndex, size_t());
    MOCK_CONST_METHOD0(getCurrentBranchName, std::string());
    MOCK_CONST_METHOD0(getRepositoryName, std::string());
    MOCK_METHOD0(getLastCommit, std::vector<commit>());
    MOCK_METHOD0(prepareRepository, void());
    MOCK_METHOD0(prepareBranches, void());
    MOCK_METHOD0(saveConfig, void());
};

TEST(GitRepositoryFactoryTest, CallGitRepositoryImpl)
{
    deleteFolder();
    auto factory = std::make_unique<MockGitRepositoryFactory>();
    EXPECT_CALL(*factory, createRepository(url, username, pass, false)).WillOnce(Return(new GitRepositoryImpl(url, username, pass, false)));
    std::unique_ptr<IRepository> rep(factory->createRepository(url, username, pass, false));
    EXPECT_TRUE(rep.get() != nullptr);
}

TEST(ShowAllRepositoryTest, CallGetRepositoryName)
{
    int i = 1;
    QApplication a(i, nullptr);
    auto repository = std::make_shared<MockRepository>();
    std::vector<std::pair<int, std::shared_ptr<IRepository>>> vector;
    std::shared_ptr<QTimer> timer = std::make_shared<QTimer>();
    std::vector<std::shared_ptr<QTimer>> vector_of_timers;
    std::chrono::seconds sec{ 30 };
    ShowAllRepositories showAllRepositories;

    vector.push_back({ 0, repository });
    timer->setInterval(sec);
    vector_of_timers.push_back(std::move(timer));

    EXPECT_CALL(*repository, getRepositoryName()).Times(AtLeast(1)).WillOnce(Return("test"));
    EXPECT_CALL(*repository, getCurrentBranchName()).Times(AtLeast(1)).WillOnce(Return("master"));
    
    showAllRepositories.setTimers(std::move(vector_of_timers));
    showAllRepositories.setRepositories(std::move(vector));
    showAllRepositories.show();
}

int main(int argc, char** argv) 
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
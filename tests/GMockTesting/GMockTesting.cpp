#include "gmock/gmock.h"
#include "interfaces/IRepository.h"
#include "interfaces/IRepositoryFactory.h"
#include "interfaces/IRepositoryType.h"
#include "git_implementation/GitRepositoryImpl.h"
#include "git_implementation/GitRepositoryFactory.h"
#include "git_implementation/GitRepositoryTypeImpl.h"
#include "helpers/rpnews_types.h"
#include "gui/ShowAllRepositories.h"

#include <QDir>
#include <QApplication>
#include <QTimer>
#include <memory>
#include <chrono>

using namespace testing;

class MockRepository : public interfaces::IRepository
{
public:
    MOCK_CONST_METHOD0(getBranchName, std::vector<std::string>());
    MOCK_CONST_METHOD0(getNumberOfBranches, size_t());
    MOCK_METHOD1(setCurrentBranch, void(size_t));
    MOCK_CONST_METHOD0(getCurrentBranchIndex, size_t());
    MOCK_CONST_METHOD0(getCurrentBranchName, std::string());
    MOCK_CONST_METHOD0(getRepositoryName, std::string());
    MOCK_METHOD0(getLastCommit, std::vector<helpers::commit>());
    MOCK_METHOD0(prepareRepository, void());
    MOCK_METHOD0(prepareBranches, void());
    MOCK_METHOD0(saveConfig, void());
};

TEST(ShowAllRepositoryTest, CallGetRepositoryName)
{
    int i = 1;
    QApplication a(i, nullptr);
    auto repository = std::make_shared<MockRepository>();
    std::vector<std::pair<int, std::shared_ptr<interfaces::IRepository>>> vector;
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

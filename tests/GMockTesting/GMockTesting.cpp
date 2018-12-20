#include "gmock/gmock.h"
#include "rpnews/interfaces/IRepository.h"
#include "rpnews/interfaces/IRepositoryFactory.h"
#include "rpnews/interfaces/IRepositoryType.h"
#include "rpnews/git_implementation/GitRepositoryImpl.h"
#include "rpnews/git_implementation/GitRepositoryFactory.h"
#include "rpnews/git_implementation/GitRepositoryTypeImpl.h"
#include "rpnews/helpers/rpnews_types.h"

#include <QDir>
#include <memory>

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

TEST(GitRepositoryFactoryTest, CallGitRepositoryImpl)
{
    deleteFolder();
    auto factory = std::make_unique<MockGitRepositoryFactory>();
    EXPECT_CALL(*factory, createRepository(url, username, pass, false)).WillOnce(Return(new GitRepositoryImpl(url, username, pass, false)));
    std::unique_ptr<IRepository> rep(factory->createRepository(url, username, pass, false));
    EXPECT_TRUE(rep.get() != nullptr);
}

int main(int argc, char** argv) 
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
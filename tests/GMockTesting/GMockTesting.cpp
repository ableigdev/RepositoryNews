#include "gmock/gmock.h"
#include "rpnews/git_implementation/GitRepositoryImpl.h"
#include "rpnews/git_implementation/GitRepositoryFactory.h"
#include "rpnews/git_implementation/GitRepositoryTypeImpl.h"
#include "rpnews/helpers/rpnews_types.h"

using namespace testing;

class MockGitRepositoryFactory
{
public:
    MOCK_METHOD4(createRepository, IRepository*(const std::string& url, const secure_string& user, const secure_string& pass, bool flag));
};

TEST(GitRepositoryFactoryTest, CallGitRepositoryImpl)
{
    secure_string str;
    MockGitRepositoryFactory factory;
    EXPECT_CALL(factory, createRepository("", str, str, false)).Times(AtLeast(1));
}

int main(int argc, char** argv) 
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
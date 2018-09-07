#include "gtest/gtest.h"
#include <QDir>
#include <string>
#include <memory>

#include "rpnews/IRepository.h"
#include "rpnews/IRepositoryType.h"
#include "rpnews/IRepositoryFactory.h"
#include "rpnews/GitRepositoryTypeImpl.h"
#include "rpnews/GitRepositoryImpl.h"
#include "rpnews/GitRepositoryFactory.h"

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
}

TEST(Test1, Valid)
{
    EXPECT_EQ(1, 1);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
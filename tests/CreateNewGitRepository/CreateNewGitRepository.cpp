#include "gtest/gtest.h"

TEST(Test1, Valid)
{
    EXPECT_EQ(1, 1);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
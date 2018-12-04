#include "gtest/gtest.h"
#include "rpnews/helpers/AESEncryption.h"
#include <QByteArray>

namespace
{
    QByteArray key(QByteArray::fromHex("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"));
    QByteArray plainText(QByteArray::fromHex("00112233445566778899AABBCCDDEEFF"));
    QByteArray expectedResult(QByteArray::fromHex("8EA2B7CA516745BFEAFC49904B496089"));
}


TEST(Encrypt, Valid)
{
    EXPECT_EQ(AESEncryption::encrypt(plainText, key), expectedResult);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 

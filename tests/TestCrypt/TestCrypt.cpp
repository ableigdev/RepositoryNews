#include "gtest/gtest.h"
#include "rpnews/helpers/AESEncryption.h"

namespace
{
    QByteArray key(QByteArray::fromHex("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"));
    QByteArray plainText(QByteArray::fromHex("00112233445566778899AABBCCDDEEFF"));
}

TEST(AESEncrypt, Valid)
{
    auto result = AESEncryption::encrypt(plainText, key);
    EXPECT_EQ(AESEncryption::decrypt(result, key), plainText);
}

TEST(AESEncrypt, Valid2)
{
    std::string key("kasjdfhkl234234");
    std::string text("test");
    auto result = AESEncryption::encrypt(text.data(), key.data());
    EXPECT_EQ(AESEncryption::decrypt(result, key.data()).data(), text);
}

TEST(ASEEncrypt, Invalid)
{
    std::string key("kasjdfhkl234234");
    std::string text("test");
    auto result = AESEncryption::encrypt(text.data(), key.data());
    EXPECT_NE(AESEncryption::decrypt(result, key.substr(0, 4).data()).data(), text);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 

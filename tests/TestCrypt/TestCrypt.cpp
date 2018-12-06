#include "gtest/gtest.h"
#include "rpnews/helpers/AESEncryption.h"
#include <QByteArray>

namespace
{
    QByteArray key(QByteArray::fromHex("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F"));
    QByteArray plainText(QByteArray::fromHex("00112233445566778899AABBCCDDEEFF"));
    QByteArray result(QByteArray::fromHex("8EA2B7CA516745BFEAFC49904B4960899F3B7504926F8BD36E3118E903A4CD4A"));
}

TEST(AESEncrypt, EncryptValid)
{
    std::string key_str(key.begin(), key.end());
    std::string plaitText_str(plainText.begin(), plainText.end());
    std::string expected_result(result.begin(), result.end());
    auto result = AESEncryption::encrypt(plaitText_str, key_str);
    EXPECT_EQ(result, expected_result);
}

TEST(AESEncrypt, DecryptValid)
{
    std::string key_str(key.begin(), key.end());
    std::string plaitText_str(result.begin(), result.end());
    std::string expected_result(plainText.begin(), plainText.end());
    auto result = AESEncryption::decrypt(plaitText_str, key_str);
    EXPECT_EQ(result, expected_result);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 

#include "AESEncryption.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include <vector>

std::string AESEncryption::encrypt(const std::string& data, const std::string& password)
{
    std::vector<CryptoPP::byte> key(password.begin(), password.end());
    std::string result;
    CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption encryption;
    encryption.SetKey(key.data(), key.size());
    CryptoPP::StringSource(data, true, new CryptoPP::StreamTransformationFilter(encryption, new CryptoPP::StringSink(result)));

    return result;
}

std::string AESEncryption::decrypt(const std::string& data, const std::string& password)
{
    std::vector<CryptoPP::byte> key(password.begin(), password.end());
    std::string result;
    CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption decryption;
    decryption.SetKey(key.data(), key.size());
    CryptoPP::StringSource(data, true, new CryptoPP::StreamTransformationFilter(decryption, new CryptoPP::StringSink(result)));
    return result;
}


#ifndef AESENCRYPTION_H
#define AESENCRYPTION_H

#include <string>

class AESEncryption
{
public:
    static std::string decrypt(const std::string& data, const std::string& password);
    static std::string encrypt(const std::string& data, const std::string& password);
    static std::string generateKey();
};

#endif // AESENCRYPTION_H

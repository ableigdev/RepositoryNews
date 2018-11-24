#ifndef AESENCRYPTION_H
#define AESENCRYPTION_H

#include <QBitArray>

class AESEncryption
{
public:
    static QByteArray sha256(const QByteArray& text);
    static QByteArray decrypt(const QByteArray& data, const QByteArray& password);
    static QByteArray encrypt(const QByteArray& data, const QByteArray& password);
};

#endif // AESENCRYPTION_H

#ifndef AESENCRYPTION_H
#define AESENCRYPTION_H

#include <QBitArray>

class AESEncryption
{
public:
    static QByteArray decrypt(const QByteArray& data, const QByteArray& password);
    static QByteArray encrypt(const QByteArray& data, const QByteArray& password);

private:
    static QByteArray sha256(const QByteArray& text);
};

#endif // AESENCRYPTION_H

#ifndef RC4ENCDEC_H
#define RC4ENCDEC_H

#include <QByteArray>

#include <Network/RC4.h>

class RC4EncDec
{
public:
    RC4EncDec(){}
    RC4EncDec(QString iseckey, QString oseckey)
    {
        if (iseckey.length() > 5 && oseckey.length() > 5)
        {
            Dec = new RC4(iseckey);
            Enc = new RC4(oseckey);
        }
    }

    QByteArray Encrypt(QByteArray data)
    {
        if (Enc == NULL)
            return data;
        char out[data.length()];
        Enc->Encrypt(reinterpret_cast<unsigned char*>(data.data()), data.length(), out);
        return QByteArray(out);
    }

    QByteArray Decrypt(QByteArray data)
    {
        if (Dec == NULL)
            return data;
        char out[data.length()];
        Dec->Encrypt(reinterpret_cast<unsigned char*>(data.data()), data.length(), out);
        return QByteArray(out);
    }
private:
    RC4 *Dec;
    RC4 *Enc;
};

#endif // RC4ENCDEC_H

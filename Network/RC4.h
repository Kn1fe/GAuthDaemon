#ifndef RC4_H
#define RC4_H

#include <QObject>
#include <QByteArray>

class RC4
{
public:
    RC4(){}
    RC4(const QString &skey)
    {
        uchar *key = reinterpret_cast<uchar*>(skey.toUtf8().data());
        for (i = 0; i < 256; i++)
            S[i] = i;
        uchar a;
        for (i = 0; i < 256; i++)
        {
            a = (a + key[i % skey.length()] + S[i]);
            std::swap(S[i], S[a]);
        }
    }

    void Encrypt(unsigned char *in, int length, char *out)
    {
        for (int k = 0; k < length; ++k)
        {
            i = (i + 1) % 256;
            j = (j + S[i]) % 256;
            std::swap(S[i], S[j]);
            unsigned char K = (S[i] + S[j]) % 256;
            out[k] = in[k] ^ S[K];
        }
    }

private:
    unsigned char S[256];
    unsigned int i = 0, j = 0;
};

#endif // RC4_H

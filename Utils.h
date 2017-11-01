#ifndef UTILS_H
#define UTILS_H

#include <QTextCodec>
#include <QString>
#include <QDebug>
#include <QDateTime>
#include <Network/Octets.h>
#include <iostream>
#include <arpa/inet.h>

class Utils
{
public:
    static QString toUtf8(Octets octets);
    static QString toASCII(Octets octets);
    static QByteArray toUtf16LE(QByteArray text);
    static Octets fromUtf8(QByteArray text);
    static void print(QString text);
    static QString getIp(int ip);
    static Octets emptyOctets();
    static Octets base64Octets(QString text);
};

#endif // UTILS_H

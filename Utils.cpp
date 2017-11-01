#include "Utils.h"

QString Utils::toUtf8(Octets octets)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    //QTextCodec *codec_utf16le = QTextCodec::codecForName("UTF-16LE");
    return codec->fromUnicode(octets.text).mid(0, octets.lenght);
}

QString Utils::toASCII(Octets octets)
{
    QTextCodec *codec = QTextCodec::codecForName("ISO 8859-1");
    return codec->fromUnicode(octets.text).mid(0, octets.lenght);
}

QByteArray Utils::toUtf16LE(QByteArray text)
{
    QTextCodec *codec_utf8 = QTextCodec::codecForName("UTF-8");
    QTextCodec *codec_utf16le = QTextCodec::codecForName("UTF-16LE");
    return codec_utf16le->fromUnicode(codec_utf8->toUnicode(text)).remove(0, 2);
}

Octets Utils::fromUtf8(QByteArray text)
{
    Octets o;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    o.text = codec->fromUnicode(text.data());
    o.lenght = o.text.length();
    return o;
}

void Utils::print(QString text)
{
    QDateTime date = QDateTime::currentDateTime();
    std::cout << QString("[AuthServer][%1] %2").arg(date.toString("hh:mm:ss")).arg(text).toStdString() << std::endl;
}

QString Utils::getIp(int ip)
{
    struct in_addr addr;
    addr.s_addr = ip;
    return QString(inet_ntoa(addr));
}

Octets Utils::emptyOctets()
{
    Octets o;
    o.text = QByteArray();
    o.lenght = 0;
    return o;
}

Octets Utils::base64Octets(QString text)
{
    Octets o;
    o.text = QByteArray::fromBase64(text.toStdString().c_str());
    o.lenght = o.text.length();
    return o;
}

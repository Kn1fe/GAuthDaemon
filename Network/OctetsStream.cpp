#include "OctetsStream.h"

void OctetsStream::init()
{
    qds = new QDataStream(&data, QIODevice::ReadWrite);
    qds->setByteOrder(QDataStream::LittleEndian);
    qds->setFloatingPointPrecision(QDataStream::SinglePrecision);
}

uint OctetsStream::calcSession()
{
    return session - 2147483648;
}

void OctetsStream::Send(uint opcode)
{
    QByteArray out;
    out.append(OctetsStream::scompact_uint32(opcode));
    out.append(OctetsStream::scompact_uint32(data.length()));
    out.append(data);
    if (socket->isOpen())
        socket->write(out);
}

void OctetsStream::Reset()
{
    data.clear();
    init();
}

uint OctetsStream::uncompact_uint32()
{
    char byte = readByte();
    switch (byte & 0xE0)
    {
    case 0x0E:
        return readInt32();
    case 0xC0:
        qds->device()->seek(qds->device()->pos() - 1);
        return readInt32() & 0x1FFFFFFF;
    case 0x80:
    case 0xA0:
        qds->device()->seek(qds->device()->pos() - 1);
        return readInt16() & 0x3FFF;
    default:
        return byte;
    }
}

uint OctetsStream::readUInt32()
{
    uint value;
    this->operator >>(value);
    return value;
}

int OctetsStream::readInt32()
{
    int value;
    this->operator >>(value);
    return value;
}

short OctetsStream::readInt16()
{
    short value;
    this->operator >>(value);
    return value;
}

char OctetsStream::readByte()
{
    char value;
    this->operator >>(value);
    return value;
}

quint8 OctetsStream::readUByte()
{
    quint8 value;
    this->operator >>(value);
    return value;
}

Octets OctetsStream::readOctet()
{
    Octets value;
    this->operator >>(value);
    return value;
}

void OctetsStream::compact_uint32(const uint &value)
{
    if (value < 127)
        writeByte(value);
    else if (value < 16383)
        writeInt16(value | 0x8000);
}

QByteArray OctetsStream::scompact_uint32(const uint &value)
{
    QByteArray out;
    QDataStream stream(&out, QIODevice::WriteOnly);
    if (value < 127)
        stream << (int8_t)value;
    else if (value < 16383)
        stream << (short)(value | 0x8000);
    return out;
}

void OctetsStream::writeUInt32(const uint &value)
{
    this->operator <<(value);
}

void OctetsStream::writeInt32(const int &value)
{
    this->operator <<(value);
}

void OctetsStream::writeInt16(const short &value)
{
    this->operator <<(value);
}

void OctetsStream::writeByte(const char &value)
{
    this->operator <<(value);
}

void OctetsStream::writeUByte(const quint8 &value)
{
    this->operator <<(value);
}

void OctetsStream::writeOctet(const Octets &value)
{
    this->operator <<(value);
}

OctetsStream &OctetsStream::operator >>(uint &value)
{
    qds->operator >>(value);
    value = qbswap(value);
    return *this;
}

OctetsStream &OctetsStream::operator >>(int &value)
{
    qds->operator >>(value);
    value = qbswap(value);
    return *this;
}

OctetsStream &OctetsStream::operator >>(short &value)
{
    qds->operator >>(value);
    value = qbswap(value);
    return *this;
}

OctetsStream &OctetsStream::operator >>(char &value)
{
    qds->readRawData(&value, 1);
    return *this;
}

OctetsStream &OctetsStream::operator >>(quint8 &value)
{
    qds->operator >>(value);
    return *this;
}

OctetsStream &OctetsStream::operator>>(Octets &value)
{
    uint lenght = uncompact_uint32();
    value.lenght = lenght;
    char data[lenght];
    if (lenght > 1)
        qds->readRawData(data, lenght);
    value.text = QByteArray(data);
    return *this;
}

OctetsStream &OctetsStream::operator <<(uint value)
{
    qds->operator <<(qbswap(value));
    return *this;
}

OctetsStream &OctetsStream::operator <<(int value)
{
    qds->operator <<(qbswap(value));
    return *this;
}

OctetsStream &OctetsStream::operator <<(short value)
{
    qds->operator <<(qbswap(value));
    return *this;
}

OctetsStream &OctetsStream::operator <<(char value)
{
    qds->writeRawData(&value, 1);
    return *this;
}

OctetsStream &OctetsStream::operator <<(quint8 value)
{
    //qds->writeRawData(&value, 1);
    qds->operator <<(value);
    return *this;
}

OctetsStream &OctetsStream::operator <<(Octets value)
{
    compact_uint32(value.lenght);
    if (value.lenght > 1)
        qds->writeRawData(value.text, value.lenght);
    return *this;
}

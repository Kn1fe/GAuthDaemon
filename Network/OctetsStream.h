#ifndef OCTETSSTREAM_H
#define OCTETSSTREAM_H

#include <QObject>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <stdlib.h>
#include <QtEndian>
#include <QTcpSocket>

#include <Network/Octets.h>
#include <Utils.h>

class OctetsStream
{
public:
    OctetsStream() { init(); }
    OctetsStream(QTcpSocket *socket) { socket = socket; init(); }
    OctetsStream(QByteArray data, bool header = true) { setData(data, header); }
    void init();
    void setData(QByteArray data, bool header = true)
    {
        this->data = QByteArray(data);
        init();
        if (header)
        {
            uncompact_uint32();
            uncompact_uint32();
        }
    }
    uint calcSession();
    void Send(uint opcode);
    void Reset();
    virtual void Unmarshal() {}
    virtual void Marshal() {}

    //Read&Write
    uint uncompact_uint32();
    uint readUInt32();
    int readInt32();
    short readInt16();
    char readByte();
    quint8 readUByte();
    Octets readOctet();
    void compact_uint32(const uint &value);
    static QByteArray scompact_uint32(const uint &value);
    void writeUInt32(const uint &value);
    void writeInt32(const int &value);
    void writeInt16(const short &value);
    void writeByte(const char &value);
    void writeUByte(const quint8 &value);
    void writeOctet(const Octets &value);

    //Operator overload
    OctetsStream &operator >>(uint &value);
    OctetsStream &operator >>(int &value);
    OctetsStream &operator >>(short &value);
    OctetsStream &operator >>(char &value);
    OctetsStream &operator >>(quint8 &value);
    OctetsStream &operator >>(Octets &value);
    OctetsStream &operator <<(uint value);
    OctetsStream &operator <<(int value);
    OctetsStream &operator <<(short value);
    OctetsStream &operator <<(char value);
    OctetsStream &operator <<(quint8 value);
    OctetsStream &operator <<(Octets value);

    QTcpSocket *socket;
    uint session;

private:
    QByteArray data;
    QDataStream *qds;
};

#endif // OCTETSSTREAM_H

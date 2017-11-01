#ifndef MATRIXTOKEN_H
#define MATRIXTOKEN_H

#include <QObject>

#include <Utils.h>
#include <Network/OctetsStream.h>
#include <Network/Octets.h>
#include <Database.h>

class MatrixToken : public OctetsStream
{
public:
    MatrixToken() : OctetsStream() {}
    virtual void Unmarshal() override;

    Octets account;
    Octets token;
    int loginip;
    Octets challenge;
};

#endif // MATRIXTOKEN_H

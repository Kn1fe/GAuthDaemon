#ifndef MATRIXPASSWD_H
#define MATRIXPASSWD_H

#include <QObject>
#include <QRegularExpression>

#include <Utils.h>
#include <Network/OctetsStream.h>
#include <Network/Octets.h>
#include <Database.h>
#include <AuthServer.h>

class MatrixPasswd : public OctetsStream
{
public:
    MatrixPasswd() : OctetsStream() {}
    virtual void Unmarshal() override;

    Octets account;
    Octets challenge;
    int loginip;
};

#endif // MATRIXPASSWD_H

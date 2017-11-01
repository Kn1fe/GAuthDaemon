#ifndef GETADDCASHSN_H
#define GETADDCASHSN_H

#include <QObject>

#include <Utils.h>
#include <Network/OctetsStream.h>
#include <AuthServer.h>
#include <Database.h>

class GetAddCashSN : public OctetsStream
{
public:
    GetAddCashSN() : OctetsStream() {}
    virtual void Unmarshal() override;

    int retcode;
    int userid;
    int zoneid;
    int sn;
};

#endif // GETADDCASHSN_H

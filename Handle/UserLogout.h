#ifndef USERLOGOUT_H
#define USERLOGOUT_H

#include <QObject>

#include <Utils.h>
#include <Network/OctetsStream.h>
#include <Network/Octets.h>
#include <Database.h>
#include <AuthServer.h>

class UserLogout : public OctetsStream
{
public:
    UserLogout() : OctetsStream() {}
    virtual void Unmarshal() override;

    int userid;
    uint localsid;
};

#endif // USERLOGOUT_H

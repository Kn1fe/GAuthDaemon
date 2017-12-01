#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <QObject>

#include <Utils.h>
#include <Network/OctetsStream.h>
#include <Network/Octets.h>
#include <Database.h>
#include <AuthServer.h>

class UserLogin : public OctetsStream
{
public:
    UserLogin() : OctetsStream() {}
    virtual void Unmarshal() override;

    int userid;
    unsigned int localsid;
    char blkickuser;
    int freecreatime;
    int loginip;
    Octets account;
    Octets iseckey;
    Octets oseckey;
};

#endif // USERLOGIN_H

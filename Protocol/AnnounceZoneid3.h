#ifndef ANNOUNCEZONEID3_H
#define ANNOUNCEZONEID3_H

#include <QObject>

#include <Utils.h>
#include <Network/OctetsStream.h>
#include <AuthServer.h>
#include <Database.h>

class AnnounceZoneid3 : public OctetsStream
{
public:
    AnnounceZoneid3() : OctetsStream() {}
    virtual void Unmarshal() override;

    int zoneid;
    int aid;
    char blreset;
    int ip1;
    int ip2;
    int ip3;
    int get_au_version;
    int reserved;
};

#endif // ANNOUNCEZONEID3_H

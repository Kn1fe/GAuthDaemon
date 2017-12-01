#ifndef ANNOUNCEZONEID2_H
#define ANNOUNCEZONEID2_H

#include <QObject>

#include <Utils.h>
#include <Network/OctetsStream.h>
#include <AuthServer.h>
#include <Database.h>

class AnnounceZoneid2 : public OctetsStream
{
public:
    AnnounceZoneid2() : OctetsStream() {}
    virtual void Unmarshal() override;

    int zoneid;
    int aid;
    char blreset;
};

#endif // ANNOUNCEZONEID2_H

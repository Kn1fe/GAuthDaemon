#ifndef ANNOUNCEZONEID_H
#define ANNOUNCEZONEID_H

#include <QObject>

#include <Utils.h>
#include <Network/OctetsStream.h>
#include <AuthServer.h>
#include <Database.h>

class AnnounceZoneid : public OctetsStream
{
public:
    AnnounceZoneid() : OctetsStream() {}
    virtual void Unmarshal() override;

    char zoneid;
    char aid;
    char blreset;
};

#endif // ANNOUNCEZONEID_H

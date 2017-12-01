#ifndef GAME2AU_H
#define GAME2AU_H

#include <QObject>

#include <Utils.h>
#include <Network/OctetsStream.h>
#include <AuthServer.h>
#include <Database.h>

class Game2AU : public OctetsStream
{
public:
    Game2AU() : OctetsStream() {}
    virtual void Unmarshal() override;

    int userid;
    int qtype;
    Octets info;
    int reserved;
};

#endif // GAME2AU_H

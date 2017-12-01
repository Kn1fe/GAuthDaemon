#ifndef QUERYUSERPRIVILEGE_H
#define QUERYUSERPRIVILEGE_H

#include <QObject>

#include <Utils.h>
#include <Network/OctetsStream.h>
#include <Database.h>

class QueryUserPrivilege : public OctetsStream
{
public:
    QueryUserPrivilege() : OctetsStream() {}
    virtual void Unmarshal() override;

    int userid;
    char zoneid;
};

#endif // QUERYUSERPRIVILEGE_H

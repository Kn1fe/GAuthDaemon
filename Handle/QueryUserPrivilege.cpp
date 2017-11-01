#include "QueryUserPrivilege.h"

void QueryUserPrivilege::Unmarshal()
{
    this->operator >>(userid);
    this->operator >>(zoneid);
    Database *db = Database::Instance();
    QList<int> priv = db->acquireUserPrivilege(userid, zoneid);
    Reset();
    writeInt32(userid);
    compact_uint32(priv.count());
    foreach (int p, priv)
        writeUByte(p);
    Send(507);
}

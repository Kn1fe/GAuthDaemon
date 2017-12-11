#include "QueryUserPrivilege.h"

void QueryUserPrivilege::Unmarshal()
{
    this->operator >>(userid);
    this->operator >>(zoneid);
    Database *db = Database::Instance();
    QList<int> priv = db->acquireUserPrivilege(userid, zoneid);
    Utils::print(QString("QueryUserPrivilege userid: %1, privilege count: %2")
                 .arg(userid).arg(priv.length()));
    Reset();
    writeInt32(userid);
    compact_uint32(priv.count());
    foreach (int p, priv)
        writeUByte(p);
    Send(507);
}

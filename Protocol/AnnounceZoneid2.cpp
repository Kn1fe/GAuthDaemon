#include "AnnounceZoneid2.h"

void AnnounceZoneid2::Unmarshal()
{
    this->operator >>(zoneid);
    this->operator >>(aid);
    this->operator >>(blreset);
    Utils::print(QString("AnnounceZoneid zoneid: %1, aid: %2, blreset: %3")
                 .arg(zoneid)
                 .arg(aid)
                 .arg(blreset == 0 ? "false" : "true"));
    Utils::print(QString("Set zoneid %1, aid %2").arg(zoneid).arg(aid));
    AuthServer *server = AuthServer::Instance();
    server->Zoneid = zoneid;
    server->Aid = aid;
    Database::Instance()->clearOnlineRecords(zoneid, aid);
}

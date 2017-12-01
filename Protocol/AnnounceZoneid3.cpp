#include "AnnounceZoneid3.h"

void AnnounceZoneid3::Unmarshal()
{
    this->operator >>(zoneid);
    this->operator >>(aid);
    this->operator >>(blreset);
    this->operator >>(ip1);
    this->operator >>(ip2);
    this->operator >>(ip3);
    this->operator >>(get_au_version);
    this->operator >>(reserved);
    Utils::print(QString("AnnounceZoneid zoneid: %1, aid: %2, blreset: %3, "
                 "ip1: %4, ip2: %5, ip3: %6, get_au_version: %7, reserved: %8")
                 .arg(zoneid)
                 .arg(aid)
                 .arg(blreset == 0 ? "false" : "true")
                 .arg(Utils::getIp(ip1))
                 .arg(Utils::getIp(ip2))
                 .arg(Utils::getIp(ip3))
                 .arg(get_au_version)
                 .arg(reserved));
    Utils::print(QString("Set zoneid %1, aid %2").arg(zoneid).arg(aid));
    AuthServer *server = AuthServer::Instance();
    server->Zoneid = zoneid;
    server->Aid = aid;
    Database::Instance()->clearOnlineRecords(zoneid, aid);
}

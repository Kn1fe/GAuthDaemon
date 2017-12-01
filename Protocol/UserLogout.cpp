#include "UserLogout.h"

void UserLogout::Unmarshal()
{
    this->operator >>(session);
    this->operator >>(userid);
    this->operator >>(localsid);
    AuthServer *server = AuthServer::Instance();
    Database *db = Database::Instance();
    int zoneid = server->Zoneid;
    int zonelocalsid = localsid;
    int overwrite = 1;
    db->recordOffline(userid, AuthServer::Instance()->Aid, zoneid, zonelocalsid, overwrite);
    Reset();
    writeUInt32(calcSession());
    if (overwrite == 1)
    {
        writeByte(0);
        Utils::print(QString("UserLogout userid: %1, success logout").arg(userid));
    }
    else
    {
        writeByte(12);
    }
    Send(33);
}

#include "UserLogin.h"

void UserLogin::Unmarshal()
{
    this->operator >>(session);
    this->operator >>(userid);
    this->operator >>(localsid);
    this->operator >>(blkickuser);
    this->operator >>(freecreatime);
    this->operator >>(account);
    this->operator >>(iseckey);
    this->operator >>(oseckey);
    Utils::print(QString("UserLogin userid: %1, localsid: %2, blkickuser: %3, freecreatime: %4")
                 .arg(userid).arg(localsid).arg(blkickuser == 0 ? "false" : "true").arg(freecreatime));
    Database *db = Database::Instance();
    AuthServer *server = AuthServer::Instance();
    int zoneid = server->Zoneid;
    int zonelocalsid = localsid;
    int overwrite = blkickuser;
    db->recordOnline(userid, AuthServer::Instance()->Aid, zoneid, zonelocalsid, overwrite);
    int creatime;
    db->acquireUserCreatime(userid, creatime);
    Reset();
    writeUInt32(calcSession());
    if (server->Zoneid != zoneid || zonelocalsid != localsid)
    {
        writeByte(10);
    }
    else
    {
        if (blkickuser == 1)
        {
            OctetsStream *kick = new OctetsStream();
            kick->socket = socket;
            kick->writeInt32(userid);
            kick->writeUInt32(localsid);
            kick->writeByte(32);
            kick->Send(10);
        }
        writeByte(0);
    }
    writeInt32(0);
    writeInt32(0);
    writeInt32(0);
    QList<int> priv = db->acquireUserPrivilege(userid, zoneid);
    writeByte(priv.count() > 0 ? 1 : 0);
    writeInt32(0);
    writeInt32(0);
    writeInt32(creatime);
    writeInt32(0);
    writeInt32(0);
    Send(15);
}

#include "MatrixPasswd.h"

void MatrixPasswd::Unmarshal()
{
    this->operator >>(session);
    this->operator >>(account);
    this->operator >>(challenge);
    this->operator >>(loginip);
    QString login = Utils::toUtf8(account);
    bool valid = true;
    if (Settings::validator_enabled)
    {
        QRegExp regex(Settings::validator_string);
        valid = login.indexOf(regex) > -1 ? false : true;
    }
    int uid;
    QString passwd;
    if (valid)
    {
        Utils::print(QString("MatrixPasswd account: %1; from ip: %2")
                     .arg(login).arg(Utils::getIp(loginip)));
        Database *db = Database::Instance();
        db->acquireUserPasswd(login, uid, passwd);
    }
    Reset();
    writeUInt32(calcSession());
    if (uid > 0)
    {
        writeInt32(0);
        writeInt32(uid);
        writeInt32(0);
        writeOctet(Utils::base64Octets(passwd));
    }
    else
    {
        writeInt32(2);
        writeInt32(0);
        writeInt32(0);
        writeOctet(Utils::emptyOctets());
    }
    writeOctet(Utils::emptyOctets());
    Send(550);
}

#include "MatrixPasswd.h"

void MatrixPasswd::Unmarshal()
{
    this->operator >>(session);
    this->operator >>(account);
    this->operator >>(challenge);
    this->operator >>(loginip);
    if (AuthServer::Instance()->bruteForceManager(Utils::getIp(loginip)))
        return;
    QString login = Utils::toUtf8(account);
    bool valid = true;
    if (Settings::validator_enabled) {
        QRegExp regex(Settings::validator_string);
        valid = login.indexOf(regex) > -1 ? false : true;
    }
    int uid = 0;
    QString passwd;
    if (valid) {
        Utils::print(QString("MatrixPasswd account: %1, from ip: %2")
                     .arg(login).arg(Utils::getIp(loginip)));
        Database *db = Database::Instance();
        if (login.contains("@") && Settings::byEmail)
            db->acquireUserPasswdbyEmail(login, uid, passwd);
        else if (Settings::byLogin)
            db->acquireUserPasswd(login, uid, passwd);
    } else {
        Utils::print(QString("MatrixPasswd detected bad characters from ip: %1").arg(Utils::getIp(loginip)));
    }
    Reset();
    writeUInt32(calcSession());
    if (uid > 0) {
        writeInt32(0);
        writeInt32(uid);
        writeInt32(0);
        if (Settings::hash_type == 1)
            writeOctet(Utils::base64Octets(passwd));
        else if (Settings::hash_type == 2)
            writeOctet(Utils::fromUtf8(passwd.remove(0, 2).toUtf8()));
    } else {
        writeInt32(2);
        writeInt32(0);
        writeInt32(0);
        writeOctet(Utils::emptyOctets());
    }
    writeOctet(Utils::emptyOctets());
    Send(550);
}

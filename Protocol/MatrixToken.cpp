#include "MatrixToken.h"

void MatrixToken::Unmarshal()
{
    this->operator >>(session);
    this->operator >>(account);
    this->operator >>(token);
    this->operator >>(loginip);
    this->operator >>(challenge);
    if (AuthServer::Instance()->bruteForceManager(Utils::getIp(loginip)))
        return;
    Utils::print(QString("MatrixToken account: %1, from ip: %2")
                 .arg(Utils::toUtf8(account)).arg(Utils::getIp(loginip)));
    Database *db = Database::Instance();
    int uid = 0;
    QString passwd;
    if (Settings::byToken)
        db->acquireUserPasswd(Utils::toUtf8(account), uid, passwd);
    Reset();
    writeUInt32(calcSession());
    if (uid > 0 && Utils::toUtf8(token) == passwd) {
        writeInt32(0);
        writeInt32(uid);
        writeInt32(0);
        writeOctet(Utils::base64Octets(passwd));
    } else {
        writeInt32(28);
        writeInt32(0);
        writeInt32(0);
        writeOctet(Utils::emptyOctets());
    }
    writeOctet(Utils::emptyOctets());
    Send(8070);
}

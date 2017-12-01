#include "GetAddCashSN.h"

void GetAddCashSN::Unmarshal()
{
    this->operator >>(session);
    this->operator >>(retcode);
    this->operator >>(userid);
    this->operator >>(zoneid);
    this->operator >>(sn);
    Utils::print(QString("GetAddCashSN_Re retcode: %1, userid: %2, zoneid: %3, sn: %4")
                 .arg(retcode).arg(userid).arg(zoneid).arg(sn));
    Database *db = Database::Instance();
    QVariantList cash = db->getUseCashNow(userid, zoneid);
    if (cash.length() > 0)
    {
        Reset();
        writeInt32(userid);
        writeInt32(zoneid);
        writeInt32(sn);
        writeInt32(cash[5].toInt());
        Send(515);
        Utils::print(QString("AddCash userid: %1, zoneid: %2, sn: %3, cash: %4")
                     .arg(userid).arg(zoneid).arg(sn).arg(cash[5].toInt()));
        db->addCashLog(userid, zoneid, sn, cash[3].toInt(), cash[4].toInt(), cash[5].toInt(), cash[6].toInt(), cash[7].toDateTime());
    }
}

//this->operator >>(session);
//this->operator >>(retcode);
//this->operator >>(userid);
//this->operator >>(zoneid);
//this->operator >>(sn);
//Utils::print(QString("GetAddCashSN retcode: %1, userid: %2, zoneid: %3, sn: %4")
//             .arg(retcode).arg(userid).arg(zoneid).arg(sn));
//Database *db = Database::Instance();
//if (retcode != 0)
//{
//    if (retcode >= 1 && retcode <= 4)
//        retcode = -1;
//    db->useCash(userid, zoneid, sn, -1, -1, -1, retcode);
//}
//else
//{
//    int status = db->useCash(userid, zoneid, sn, -1, -1, -1, 2);
//    Utils::print(QString::number(status));
//    if (status >= 0)
//    {
//        status = db->useCash(userid, zoneid, sn, -1, -1, -1, 3);
//        Utils::print(QString::number(status));
//        if (status == 0)
//        {
//            QVariantList cash = db->getUseCashNow(userid, zoneid, sn);
//            if (cash.length() > 0)
//            {
//                Reset();
//                writeInt32(userid);
//                writeInt32(zoneid);
//                writeInt32(sn);
//                writeInt32(cash[5].toInt());
//                Send(515);
//                Utils::print(QString("AddCash userid: %1, zoneid: %2, sn: %3, cash: %4")
//                             .arg(userid).arg(zoneid).arg(sn).arg(cash[5].toInt()));
//            }
//        }
//    }
//}

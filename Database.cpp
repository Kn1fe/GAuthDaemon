#include "Database.h"

Database* Database::self = NULL;

void Database::connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(Settings::mysql_host);
    db.setPort(Settings::mysql_port);
    db.setUserName(Settings::mysql_user);
    db.setPassword(Settings::mysql_pass);
    db.setDatabaseName(Settings::mysql_db);
    db.setConnectOptions("MYSQL_OPT_RECONNECT=1;MYSQL_OPT_CONNECT_TIMEOUT=300");
    if (!db.open()) {
        Utils::print(QString("Cant connect to mysql: %1").arg(db.lastError().text()));
        exit(0);
    } else {
        Utils::print("Successfully connected to database");
    }
}

void Database::clearOnlineRecords(const int &zoneid, const int &aid)
{
    QSqlQuery sql(db);
    sql.prepare("CALL clearonlinerecords(?, ?)");
    sql.addBindValue(zoneid);
    sql.addBindValue(aid);
    sql.exec();
}


void Database::acquireUserPasswd(const QString &login, int &uid, QString &passwd)
{
    QSqlQuery sql(db);
    sql.prepare("CALL acquireuserpasswd(?, @out1, @out2)");
    sql.addBindValue(login);
    sql.exec();
    sql.exec("SELECT @out1, @out2");
    if(sql.next()) {
        uid = sql.value(0).toInt();
        passwd = sql.value(1).toString();
    }
}

void Database::acquireUserPasswdbyEmail(const QString &email, int &uid, QString &passwd)
{
    QSqlQuery sql(db);
    sql.prepare("SELECT ID, passwd FROM users WHERE email=?");
    sql.addBindValue(email);
    sql.exec();
    if (sql.next()) {
        uid = sql.value(0).toInt();
        passwd = sql.value(1).toString();
    }
}

void Database::recordOnline(const int &uid, const int &aid, int &zoneid, int &zonelocalid, int &overwrite)
{
    QSqlQuery sql(db);
    sql.prepare("CALL recordonline(?, ?, ?, ?, ?)");
    sql.addBindValue(uid);
    sql.addBindValue(aid);
    sql.addBindValue(zoneid, QSql::InOut);
    sql.addBindValue(zonelocalid, QSql::InOut);
    sql.addBindValue(overwrite, QSql::InOut);
    sql.exec();
    zoneid = sql.boundValue(2).toInt();
    zonelocalid = sql.boundValue(3).toInt();
    overwrite = sql.boundValue(4).toInt();
}

void Database::recordOffline(const int &uid, const int &aid, int &zoneid, int &zonelocalid, int &overwrite)
{
    QSqlQuery sql(db);
    sql.prepare("CALL recordoffline(?, ?, ?, ?, ?)");
    sql.addBindValue(uid);
    sql.addBindValue(aid);
    sql.addBindValue(zoneid, QSql::InOut);
    sql.addBindValue(zonelocalid, QSql::InOut);
    sql.addBindValue(overwrite, QSql::InOut);
    sql.exec();
    zoneid = sql.boundValue(2).toInt();
    zonelocalid = sql.boundValue(3).toInt();
    overwrite = sql.boundValue(4).toInt();
}

void Database::acquireUserCreatime(const int &uid, int &timestamp)
{
    QSqlQuery sql(db);
    sql.prepare("SELECT creatime FROM users WHERE ID=?");
    sql.addBindValue(uid);
    sql.exec();
    if (sql.next()) {
        timestamp = sql.value(0).toDateTime().toTime_t();
    }
}

QList<int> Database::acquireUserPrivilege(const int &userid, const int &zoneid)
{
    QList<int> priv;
    QSqlQuery sql(db);
    sql.prepare("SELECT rid FROM auth WHERE userid=? AND zoneid=?");
    sql.addBindValue(userid);
    sql.addBindValue(zoneid);
    sql.exec();
    while (sql.next())
        priv.append(sql.value(0).toInt());
    return priv;
}

QList<QVariantList> Database::getUseCashNow(const int &status)
{
    QList<QVariantList> cashnow;
    QSqlQuery sql(db);
    sql.prepare("SELECT * FROM usecashnow WHERE status=?");
    sql.addBindValue(status);
    sql.exec();
    QSqlQuery di(db);
    while (sql.next()) {
        cashnow.append(QVariantList() << sql.value(0) << sql.value(1));
        di.exec(QString("UPDATE usecashnow SET status=1 WHERE userid=%1 AND sn=%2")
                .arg(sql.value(0).toString()).arg(sql.value(2).toString()));
    }
    return cashnow;
}

QVariantList Database::getUseCashNow(const int &userid, const int &zoneid)
{
    QVariantList cashnow;
    QSqlQuery sql(db);
    sql.prepare("SELECT * FROM usecashnow WHERE userid=? AND zoneid=? AND status=1");
    sql.addBindValue(userid);
    sql.addBindValue(zoneid);
    sql.exec();
    if (sql.next())
        cashnow << sql.value(0) << sql.value(1) << sql.value(2)
        << sql.value(3) << sql.value(4) << sql.value(5) << sql.value(6) << sql.value(7);
    sql.prepare("DELETE FROM usecashnow WHERE userid=? AND zoneid=? AND status=1");
    sql.addBindValue(userid);
    sql.addBindValue(zoneid);
    sql.exec();
    return cashnow;
}

void Database::addCashLog(const int &userid, const int &zoneid, const int &sn, const int &aid, const int &point, const int &cash, const int &status, const QDateTime &creatime)
{
    QSqlQuery sql(db);
    sql.prepare("INSERT INTO usecashlog VALUES (?, ?, ?, ?, ?, ?, ?, ?, NOW())");
    sql.addBindValue(userid);
    sql.addBindValue(zoneid);
    sql.addBindValue(sn);
    sql.addBindValue(aid);
    sql.addBindValue(point);
    sql.addBindValue(cash);
    sql.addBindValue(status);
    sql.addBindValue(creatime);
    sql.exec();
}

int Database::useCash(const int &userid, const int &zoneid, const int &sn, const int &aid, const int &point, const int &cash, const int &status)
{
    QSqlQuery sql(db);
    sql.prepare("CALL usecash(?, ?, ?, ?, ?, ?, ?, @out1)");
    sql.addBindValue(userid);
    sql.addBindValue(zoneid);
    sql.addBindValue(sn);
    sql.addBindValue(aid);
    sql.addBindValue(point);
    sql.addBindValue(cash);
    sql.addBindValue(status);
    sql.exec();
    sql.exec("SELECT @out1");
    sql.next();
    return sql.value(0).toInt();
}

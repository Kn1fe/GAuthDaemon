#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlError>
#include <iostream>

#include <Settings.h>
#include <Utils.h>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database() { db.close(); }
    void connect();
    void clearOnlineRecords(int zoneid, int aid);
    void acquireUserPasswd(QString login, int &uid, QString &passwd);
    void recordOnline(int uid, int aid, int &zoneid, int &zonelocalid, int &overwrite);
    void recordOffline(int uid, int aid, int &zoneid, int &zonelocalid, int &overwrite);
    void acquireUserCreatime(int uid, int &timestamp);
    QList<int> acquireUserPrivilege(int userid, int zoneid);
    QList<QVariantList> getUseCashNow(int status);
    QVariantList getUseCashNow(int userid, int zoneid);
    void addCashLog(int userid, int zoneid, int sn, int aid, int point, int cash, int status, QDateTime creatime);
    int useCash(int userid, int zoneid, int sn, int aid, int point, int cash, int status);
    static Database *Instance()
    {
        if (!_self) _self = new Database();
        return _self;
    }
    static Database *_self;

private:
    QSqlDatabase db;
};

#endif // DATABASE_H

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
    explicit Database(QObject *parent = nullptr)  : QObject(parent) {}
    ~Database() { db.close(); }
    void connect();
    void clearOnlineRecords(const int &zoneid, const int &aid);
    void acquireUserPasswd(const QString &login, int &uid, QString &passwd);
    void acquireUserPasswdbyEmail(const QString &email, int &uid, QString &passwd);
    void recordOnline(const int &uid, const int &aid, int &zoneid, int &zonelocalid, int &overwrite);
    void recordOffline(const int &uid, const int &aid, int &zoneid, int &zonelocalid, int &overwrite);
    void acquireUserCreatime(const int &uid, int &timestamp);
    QList<int> acquireUserPrivilege(const int &userid, const int &zoneid);
    QList<QVariantList> getUseCashNow(const int &status);
    QVariantList getUseCashNow(const int &userid, const int &zoneid);
    void addCashLog(const int &userid, const int &zoneid, const int &sn, const int &aid, const int &point, const int &cash, const int &status, const QDateTime &creatime);
    int useCash(const int &userid, const int &zoneid, const int &sn, const int &aid, const int &point, const int &cash, const int &status);
    static Database *Instance()
    {
        if (!self)
            self = new Database();
        return self;
    }
    static Database *self;

private:
    QSqlDatabase db;
};

#endif // DATABASE_H

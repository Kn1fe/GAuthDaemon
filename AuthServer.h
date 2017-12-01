#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QHostAddress>
#include <QHash>
#include <QMutex>
#include <QMutexLocker>
#include <QTimer>

#include <Settings.h>
#include <AuthClient.h>
#include <Utils.h>

class AuthServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit AuthServer(QObject *parent = nullptr) : QTcpServer(parent) {}
    void Start();
    bool bruteForceManager(QString ip);
    static AuthServer *Instance()
    {
        if (!self)
            self = new AuthServer();
        return self;
    }
    static AuthServer *self;
    int Zoneid = 0;
    int Aid = 0;

public slots:
    void bruteCleaner();

protected:
    void incomingConnection(qintptr handle);

private:
    QHash<QString, int> challenges;
    QHash<QString, int> blocked;
    QMutex mutex;
    QTimer *bruteTimer;
};

#endif // AUTHSERVER_H

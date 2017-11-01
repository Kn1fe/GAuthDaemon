#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QHostAddress>

#include <Settings.h>
#include <AuthClient.h>
#include <Utils.h>

class AuthServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit AuthServer(QObject *parent = nullptr);
    void Start();
    static AuthServer *Instance()
    {
        if (!_self) _self = new AuthServer();
        return _self;
    }
    static AuthServer *_self;
    int Zoneid = 0;
    int Aid = 0;

protected:
    void incomingConnection(qintptr handle);
};

#endif // AUTHSERVER_H

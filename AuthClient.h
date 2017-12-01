#ifndef AUTHCLIENT_H
#define AUTHCLIENT_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QMetaType>
#include <QMetaObject>
#include <QTimer>

#include <Settings.h>
#include <Network/OctetsStream.h>
#include <Utils.h>
#include <Database.h>

class AuthClient : public QThread
{
    Q_OBJECT
public:
    explicit AuthClient(qintptr socketDescriptor, QObject *parent = nullptr);

signals:

public slots:
    void readyRead();
    void disconnected();
    void goldChecker();

protected:
    void run();

private:
    qintptr socketDescriptor;
    QTcpSocket *socket;
    QTimer *goldTimer;
};

#endif // AUTHCLIENT_H

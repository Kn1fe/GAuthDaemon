#include "AuthServer.h"

AuthServer* AuthServer::self = NULL;

void AuthServer::Start()
{
    AuthServer *server = AuthServer::Instance();
    if (!server->listen(QHostAddress(Settings::auth_host), Settings::auth_port)) {
        Utils::print(QString("Cant start listener, error: %1").arg(server->errorString()));
    }
    if (Settings::antibrut_enabled) {
        bruteTimer = new QTimer();
        bruteTimer->setInterval(Settings::antibrut_interval * 1000);
        connect(bruteTimer, &QTimer::timeout, this, &AuthServer::bruteCleaner, Qt::DirectConnection);
        bruteTimer->start();
    }
}

bool AuthServer::bruteForceManager(QString ip)
{
    if (!Settings::antibrut_enabled)
        return false;
    QMutexLocker lock(&mutex);
    if (blocked.contains(ip))
    {
        if (blocked[ip] + Settings::antibrut_blocktime < QDateTime::currentDateTime().toTime_t()) {
            blocked.remove(ip);
            Utils::print(QString("Ip: %1 has been unblocked").arg(ip));
            return false;
        }
        return true;
    }
    if (challenges.contains(ip)) {
        ++challenges[ip];
    } else {
        challenges.insert(ip, 1);
    }
    if (challenges[ip] > Settings::antibrut_count && !blocked.contains(ip)) {
        blocked.insert(ip, QDateTime::currentDateTime().toTime_t());
        Utils::print(QString("Ip: %1 has been blocked").arg(ip));
        return true;
    }
    return false;
}

void AuthServer::bruteCleaner()
{
    QMutexLocker lock(&mutex);
    challenges.clear();
}

void AuthServer::incomingConnection(qintptr handle)
{
    Utils::print("AuthServer::OnAddSession");
    AuthClient *client = new AuthClient(handle, AuthServer::Instance());
    connect(client, &AuthClient::finished, client, &AuthClient::deleteLater);
    client->start();
}

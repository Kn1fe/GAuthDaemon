#include "AuthServer.h"

AuthServer* AuthServer::_self = NULL;

AuthServer::AuthServer(QObject *parent) : QTcpServer(parent)
{

}

void AuthServer::Start()
{
    AuthServer *server = AuthServer::Instance();
    if (!server->listen(QHostAddress(Settings::auth_host), Settings::auth_port))
    {
        Utils::print(QString("Cant start listener, error: %1").arg(server->errorString()));
    }
}

void AuthServer::incomingConnection(qintptr handle)
{
    Utils::print("AuthServer::OnAddSession");
    AuthClient *client = new AuthClient(handle, AuthServer::Instance());
    connect(client, &AuthClient::finished, client, &AuthClient::deleteLater);
    client->start();
}

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QDir>

#include <Settings.h>
#include <Database.h>
#include <AuthServer.h>
#include <Utils.h>

#include <Handle/AnnounceZoneid.h>
#include <Handle/AnnounceZoneid2.h>
#include <Handle/AnnounceZoneid3.h>
#include <Handle/MatrixPasswd.h>
#include <Handle/UserLogin.h>
#include <Handle/UserLogout.h>
#include <Handle/QueryUserPrivilege.h>
#include <Handle/MatrixToken.h>
#include <Handle/GetAddCashSN.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //Register protocol handle
    qRegisterMetaType<AnnounceZoneid>("505");
    qRegisterMetaType<AnnounceZoneid2>("523");
    qRegisterMetaType<AnnounceZoneid3>("527");
    qRegisterMetaType<MatrixPasswd>("550");
    qRegisterMetaType<UserLogin>("15");
    qRegisterMetaType<UserLogout>("33");
    qRegisterMetaType<QueryUserPrivilege>("506");
    qRegisterMetaType<MatrixToken>("8070");
    qRegisterMetaType<GetAddCashSN>("514");
    qRegisterMetaType<OctetsStream>("516");//AddCash_Re
    qRegisterMetaType<OctetsStream>("8039");//GAME2AU

    Utils::print("GAuthDaemon by Kn1fe-Zone.Ru Team v1.0 alpha");
    Utils::print("Loading gauthd.conf");
    Settings::Init(a.applicationDirPath() + "/gauthd.conf");
    Database::Instance()->connect();
    AuthServer::Instance()->Start();
    return a.exec();
}

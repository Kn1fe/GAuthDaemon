#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QDir>

#include <Settings.h>
#include <Database.h>
#include <AuthServer.h>
#include <Utils.h>

#include <Protocol/AnnounceZoneid.h>
#include <Protocol/AnnounceZoneid2.h>
#include <Protocol/AnnounceZoneid3.h>
#include <Protocol/MatrixPasswd.h>
#include <Protocol/UserLogin.h>
#include <Protocol/UserLogout.h>
#include <Protocol/QueryUserPrivilege.h>
#include <Protocol/MatrixToken.h>
#include <Protocol/GetAddCashSN.h>
#include <Protocol/Game2AU.h>

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
    qRegisterMetaType<Game2AU>("8039");

    Utils::print("GAuthDaemon by Kn1fe-Zone.Ru Team v1.1.2 alpha");
    Utils::print(QString("Build date: %1 at %2").arg(__DATE__).arg(__TIME__));
    Utils::print("Loading gauthd.conf");
    Settings::Init(a.applicationDirPath() + "/gauthd.conf");
    Database::Instance()->connect();
    AuthServer::Instance()->Start();
    return a.exec();
}

#include "Settings.h"

QString Settings::auth_host = "";
int Settings::auth_port = 0;
int Settings::gold_timeout = 0;
bool Settings::byLogin = false;
bool Settings::byEmail = false;
bool Settings::byToken = false;
int Settings::hash_type = 0;
QString Settings::mysql_host = "";
int Settings::mysql_port = 0;
QString Settings::mysql_user = "";
QString Settings::mysql_pass = "";
QString Settings::mysql_db = "";
bool Settings::validator_enabled = false;
QString Settings::validator_string = "";
bool Settings::antibrut_enabled = false;
int Settings::antibrut_count = 0;
int Settings::antibrut_interval = 0;
int Settings::antibrut_blocktime = 0;


void Settings::Init(const QString &file)
{
    QSettings settings(file, QSettings::IniFormat);
    auth_host = settings.value("GAuthServer/host").toString();
    auth_port = settings.value("GAuthServer/port").toInt();
    QString auth_type = settings.value("GAuthServer/allow_auth_type").toString();
    if (auth_type.contains("login"))
        byLogin = true;
    if (auth_type.contains("email"))
        byEmail = true;
    if (auth_type.contains("token"))
        byToken = true;
    gold_timeout = settings.value("GAuthServer/gold_timeout").toInt();
    hash_type = settings.value("GAuthServer/hash_type").toInt();

    mysql_host = settings.value("Mysql/host").toString();
    mysql_port = settings.value("Mysql/port").toInt();
    mysql_user = settings.value("Mysql/user").toString();
    mysql_pass = settings.value("Mysql/pass").toString();
    mysql_db = settings.value("Mysql/db").toString();

    validator_enabled = settings.value("Validator/is_enabled").toBool();
    validator_string = settings.value("Validator/regex").toString();

    antibrut_enabled = settings.value("Antibrut/is_enabled").toBool();
    antibrut_count = settings.value("Antibrut/count").toInt();
    antibrut_interval = settings.value("Antibrut/interval").toInt();
    antibrut_blocktime = settings.value("Antibrut/block_time").toInt();
}

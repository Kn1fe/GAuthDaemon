#include "Settings.h"

QString Settings::auth_host = "";
int Settings::auth_port = 0;
int Settings::gold_timeout = 0;
QString Settings::mysql_host = "";
int Settings::mysql_port = 0;
QString Settings::mysql_user = "";
QString Settings::mysql_pass = "";
QString Settings::mysql_db = "";
QString Settings::iseckey = "";
QString Settings::oseckey = "";
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
    gold_timeout = settings.value("GAuthServer/gold_timeout").toInt();
    iseckey = settings.value("GAuthServer/iseckey").toString();
    oseckey = settings.value("GAuthServer/oseckey").toString();

    mysql_host = settings.value("Mysql/host").toString();
    mysql_port = settings.value("Mysql/port").toInt();
    mysql_user = settings.value("Mysql/user").toString();
    mysql_pass = settings.value("Mysql/pass").toString();
    mysql_db = settings.value("Mysql/db").toString();

    validator_enabled = settings.value("Validator/is_enabled").toBool();
    validator_string = settings.value("Validator/regex").toString();
}

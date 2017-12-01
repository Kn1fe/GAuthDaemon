#ifndef SETTINGS_H
#define SETTINGS_H

#include <QVariant>
#include <QSettings>
#include <QMetaEnum>
#include <QDebug>
#include <QSettings>
#include <QMetaEnum>
#include <QRegExp>
#include <QStringList>

class Settings
{
public:
    static void Init(const QString &file);
    //Settings
    static QString auth_host;
    static int auth_port;
    static int gold_timeout;
    static bool byLogin;
    static bool byEmail;
    static bool byToken;
    static int hash_type;

    static QString mysql_host;
    static int mysql_port;
    static QString mysql_user;
    static QString mysql_pass;
    static QString mysql_db;

    static bool validator_enabled;
    static QString validator_string;

    static bool antibrut_enabled;
    static int antibrut_count;
    static int antibrut_interval;
    static int antibrut_blocktime;
};

#endif // SETTINGS_H

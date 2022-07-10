#include "jooyaapplicationsettings.h"

JooyaApplicationSettings::JooyaApplicationSettings(QObject *parent) : JooyaSettings(parent)
{

}

void JooyaApplicationSettings::setTheme(QString t)
{
    set("theme",t);
}

QString JooyaApplicationSettings::theme()
{
    return get("theme").toString();
}

void JooyaApplicationSettings::setDefaultTheme(QString t)
{
    set("DefaultTheme",t);
}

QString JooyaApplicationSettings::defaultTheme()
{
    return get("DefaultTheme").toString();
}

void JooyaApplicationSettings::setUserInfo(QString info)
{
    set("userInfo",info);
}

QString JooyaApplicationSettings::userInfo()
{
    return get("userInfo").toString();
}

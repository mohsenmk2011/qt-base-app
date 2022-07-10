#include "applicationsettings.h"

ApplicationSettings::ApplicationSettings(QObject *parent) : JooyaSettings(parent)
{

}

QString ApplicationSettings::theme()
{
    return get("theme").toString();
}

void ApplicationSettings::setTheme(QString t)
{
    set("theme",t);
    emit themeChanged();
}

QString ApplicationSettings::userInfo()
{
    return get("userInfo").toString();
}

void ApplicationSettings::setUserInfo(QString t)
{
    set("userInfo",t);
}

bool ApplicationSettings::seenAppIntroducing()
{
    return get("seenAppIntroducing").toBool();
}

void ApplicationSettings::setSeenAppIntroducing(bool seen)
{
    set("seenAppIntroducing",seen);
    void seenAppIntroducingChanged();
}


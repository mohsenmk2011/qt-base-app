#include "applicationversioninfo.h"

QString ApplicationVersionInfo::versionName()
{
    return QString("%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH);
}

QString ApplicationVersionInfo::versionCode()
{
    return QString("%1").arg(VERSION_CODE);
}

QString ApplicationVersionInfo::buildNumber()
{
    return QString::number(VERSION_PATCH);
}

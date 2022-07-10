#include "datetimeutility.h"

DateTimeUtility::DateTimeUtility(QObject *parent)
    : QObject{parent}
{

}

QDateTime DateTimeUtility::toDateTime(QString date)
{
    return QDateTime::fromString(date,"yyyyMMddHHmmss");
}

QString DateTimeUtility::toPersianHourString(QDateTime date)
{
    QLocale locale(QLocale("fa_IR"));
    return locale.toString(date,"HH:mm");
}

QString DateTimeUtility::fromDateTime(QDateTime date)
{
    QLocale locale(QLocale("en_US"));
    return locale.toString(date,"yyyyMMddHHmmss");
}

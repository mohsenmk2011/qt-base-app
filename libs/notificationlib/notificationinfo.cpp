#include "notificationinfo.h"

NotificationInfo::NotificationInfo(QObject *parent) : JooyaSettings(parent)
{

}

QDateTime NotificationInfo::discountViewDate()
{    
    qCritical()<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qCritical()<<"%%%%%%%%%%%%%%%%%%toverfy%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qInfo()<<QDateTime::fromString(get("discountViewDate").toString(),"ddd yyyy/MM/dd HH:MM:ss");
    qInfo()<<get("discountViewDate").toDateTime();
    qCritical()<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qCritical()<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";

    return QDateTime::fromString(get("discountViewDate").toString(),"ddd yyyy/MM/dd HH:MM:ss");
    //return get("discountViewDate").toDateTime();
}

void NotificationInfo::refreshDiscountDateView()
{
    set("discountViewDate",QDateTime::currentDateTime().toString("ddd yyyy/MM/dd HH:MM:ss"));
}

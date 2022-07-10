#ifndef DATETIMEUTILITY_H
#define DATETIMEUTILITY_H

#include <QObject>
#include<QDateTime>
#include<qlocale.h>
class DateTimeUtility : public QObject
{
    Q_OBJECT
public:
    explicit DateTimeUtility(QObject *parent = nullptr);

    QDateTime toDateTime(QString date);
    QString fromDateTime(QDateTime date);
    QString toPersianHourString(QDateTime date);
signals:

};

#endif // DATETIMEUTILITY_H

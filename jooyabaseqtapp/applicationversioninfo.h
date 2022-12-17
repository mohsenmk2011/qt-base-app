#ifndef APPLICATIONVERSIONINFO_H
#define APPLICATIONVERSIONINFO_H

#include <QObject>
#include<version.h>

class ApplicationVersionInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString versionName READ versionName CONSTANT)
    Q_PROPERTY(QString versionCode READ versionCode CONSTANT)
    Q_PROPERTY(QString buildNumber READ buildNumber CONSTANT)
public:
    QString versionName();
    QString versionCode();
    QString buildNumber();
};

#endif // APPLICATIONVERSIONINFO_H

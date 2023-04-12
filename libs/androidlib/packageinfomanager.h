#ifndef PACKAGEINFOMANAGER_H
#define PACKAGEINFOMANAGER_H

#include <QObject>
#include<QDebug>
#include<jooyaandroidcontext.h>
#if defined(Q_OS_ANDROID)
#include<qandroidjniobject.h>
#include<QAndroidJniEnvironment>
#include<QtAndroid>
#include<QtAndroidExtras>
#endif

class PackageInfoManager : public QObject
{
    Q_OBJECT
public:
    explicit PackageInfoManager(QObject *parent = nullptr);
    QString getAppSign();

signals:

};

#endif // PACKAGEINFOMANAGER_H

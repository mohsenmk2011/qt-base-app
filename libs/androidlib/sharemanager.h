#ifndef SHAREMANAGER_H
#define SHAREMANAGER_H

#include <QObject>
#include<QDebug>
#include<QClipboard>
#include<QGuiApplication>

#if defined(Q_OS_ANDROID)
#include<qandroidjniobject.h>
#include<QAndroidJniEnvironment>
#endif
class ShareManager : public QObject
{
    Q_OBJECT
public:
    explicit ShareManager(QObject *parent = nullptr);
    Q_INVOKABLE void share(QString message);
signals:

};

#endif // SHAREMANAGER_H

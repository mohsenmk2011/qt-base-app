#ifndef ANDROIDUTILITY_H
#define ANDROIDUTILITY_H

#include <QObject>
#include<QNetworkInterface>

#if defined (Q_OS_ANDROID)
#include<QtAndroid>
#include<QAndroidJniEnvironment>
#endif
class AndroidUtility : public QObject
{
    Q_OBJECT
public:
    explicit AndroidUtility(QObject *parent = nullptr);
    Q_INVOKABLE void keepScreenOn(bool on);
    QString getMacAddress();

signals:

public slots:
};

#endif // ANDROIDUTILITY_H

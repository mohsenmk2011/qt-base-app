#ifndef JOOYAAPPLICATIONSETTINGS_H
#define JOOYAAPPLICATIONSETTINGS_H

#include <QObject>
#include<jooyasettings.h>

class JooyaApplicationSettings : public JooyaSettings
{
    Q_OBJECT

public:
    explicit JooyaApplicationSettings(QObject *parent = nullptr);

    void setTheme(QString t);
    QString theme();

    void setDefaultTheme(QString t);
    QString defaultTheme();

    void setUserInfo(QString info);
    QString userInfo();

signals:

};

#endif // JOOYAAPPLICATIONSETTINGS_H

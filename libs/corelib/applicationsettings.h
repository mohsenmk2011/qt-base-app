#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
#include<jooyasettings.h>
#include<datetimeutility.h>

class ApplicationSettings : public JooyaSettings
{
    Q_OBJECT
    Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(QString alarmInfo READ alarmInfo WRITE setAlarmInfo NOTIFY alarmInfoChanged)
    Q_PROPERTY(bool seenAppIntroducing READ seenAppIntroducing WRITE setSeenAppIntroducing NOTIFY seenAppIntroducingChanged)
public:
    explicit ApplicationSettings(QObject *parent = nullptr);

    QString alarmInfo();
    void setAlarmInfo(QString ai);

    QString theme();
    void setTheme(QString t);

    QString userInfo();
    void setUserInfo(QString t);

    bool seenAppIntroducing();
    void setSeenAppIntroducing(bool seen);

signals:
    void alarmInfoChanged();
    void themeChanged();
    void seenAppIntroducingChanged();
private:
};

#endif // APPLICATIONSETTINGS_H

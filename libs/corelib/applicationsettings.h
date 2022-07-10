#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
#include<jooyasettings.h>

class ApplicationSettings : public JooyaSettings
{
    Q_OBJECT
    Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(bool seenAppIntroducing READ seenAppIntroducing WRITE setSeenAppIntroducing NOTIFY seenAppIntroducingChanged)
public:
    explicit ApplicationSettings(QObject *parent = nullptr);

    QString theme();
    void setTheme(QString t);

    QString userInfo();
    void setUserInfo(QString t);

    bool seenAppIntroducing();
    void setSeenAppIntroducing(bool seen);

signals:
    void themeChanged();
    void seenAppIntroducingChanged();

};

#endif // APPLICATIONSETTINGS_H

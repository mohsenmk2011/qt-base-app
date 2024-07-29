#ifndef JOOYAAPPLICATION_H
#define JOOYAAPPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include<jooyanetworkengine.h>
#include<materialstylehelper.h>
#include<applicationsettings.h>
#include<QGuiApplication>
#include<applicationinfohelper.h>
#include<applicationalarmsettingshelper.h>
#include<alarmclasses.h>

class JooyaApplication : public JooyaNetworkEngine
{
    Q_OBJECT
public:
    explicit JooyaApplication(QObject *parent = nullptr);
    explicit JooyaApplication(QString organization,QString organizationDomain, QString applicationName);
    void setApplicationName(QString name);
    void setDefaultAlarmSettings(bool hasAlarm, AlarmClasses::AlarmClassesEnum alarmClass, bool hasRepeat, QString notificationContent="");

    static MaterialStyleHelper* m_MaterialStyleHelper;
    static ApplicationAlarmSettingsHelper* m_ApplicationAlarmSettingsHelper;
    static bool m_IsDesignMode;
    static ApplicationInfoHelper* m_AppInfo;
    void processQmlLiveCommandLine(QGuiApplication *app);
    bool isDesignMode();
    void setDefaultTheme(MaterialThemes::MaterialThemesEnum theme, MaterialColors::MaterialColorsEnum primary, MaterialColors::MaterialColorsEnum accent,MaterialColors::MaterialColorsEnum backColor);
signals:

public slots:
};

#endif // JOOYAAPPLICATION_H

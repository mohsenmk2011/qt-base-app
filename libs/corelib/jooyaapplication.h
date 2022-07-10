#ifndef JOOYAAPPLICATION_H
#define JOOYAAPPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include<jooyanetworkengine.h>
#include<materialstylehelper.h>
#include<jooyaapplicationsettings.h>
#include<QGuiApplication>

class JooyaApplication : public JooyaNetworkEngine
{
    Q_OBJECT
public:
    explicit JooyaApplication(QObject *parent = nullptr);
    explicit JooyaApplication(QString organization,QString organizationDomain, QString applicationName);

    static MaterialStyleHelper* m_MaterialStyleHelper;
    static bool m_IsDesignMode;
    void processQmlLiveCommandLine(QGuiApplication *app);
    bool isDesignMode();
    void setDefaultTheme(MaterialThemes::MaterialThemesEnum theme, MaterialColors::MaterialColorsEnum primary, MaterialColors::MaterialColorsEnum accent,MaterialColors::MaterialColorsEnum backColor);
signals:

public slots:
};

#endif // JOOYAAPPLICATION_H

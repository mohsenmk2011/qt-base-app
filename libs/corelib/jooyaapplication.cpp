#include "jooyaapplication.h"

JooyaApplication::JooyaApplication(QObject *parent) : JooyaNetworkEngine(parent)
{
    m_MaterialStyleHelper=new MaterialStyleHelper();
    m_CurrentApplicationHelper = new CurrentApplicationHelper();
    m_ApplicationAlarmSettingsHelper = new ApplicationAlarmSettingsHelper();
    m_ApplicationPageManager = new AppPagesManager();
}

void JooyaApplication::processQmlLiveCommandLine(QGuiApplication *app)
{
    QCommandLineParser parser;
    parser.setApplicationDescription(app->applicationDisplayName());
    parser.addHelpOption();

    QCommandLineOption forceOption(QStringList() << "l" << "live",QCoreApplication::translate("live", "Start live coding mode."));
    parser.addOption(forceOption);
    parser.process(*app);

    JooyaApplication::m_IsDesignMode = parser.isSet(forceOption);
    qCritical()<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@[ DesignMode => "<<m_IsDesignMode<<" ]@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
}

bool JooyaApplication::isDesignMode()
{
    return JooyaApplication::m_IsDesignMode;
}

JooyaApplication::JooyaApplication(QString organization, QString organizationDomain, QString applicationName):JooyaApplication()
{
    QCoreApplication::setOrganizationName(organization);
    QCoreApplication::setOrganizationDomain(organizationDomain);
    QCoreApplication::setApplicationName(applicationName);
    loginInfo()->initialState();
}

void JooyaApplication::setApplicationName(QString name)
{
    m_CurrentApplicationHelper->setName(name);
}

void JooyaApplication::setDefaultAlarmSettings(bool hasAlarm,AlarmClasses::AlarmClassesEnum alarmClass, bool hasRepeat,QString notificationContent)
{
    m_ApplicationAlarmSettingsHelper->setHasAlarm(hasAlarm);
    m_ApplicationAlarmSettingsHelper->setHasRepeat(hasRepeat);
    m_ApplicationAlarmSettingsHelper->setAlarmClass(alarmClass);
    m_ApplicationAlarmSettingsHelper->setNotificationContent(notificationContent);
}

void JooyaApplication::setDefaultTheme(MaterialThemes::MaterialThemesEnum theme,MaterialColors::MaterialColorsEnum primary,MaterialColors::MaterialColorsEnum accent,MaterialColors::MaterialColorsEnum backColor)
{
    ApplicationSettings s;
    if(s.defaultTheme().isNull()||s.defaultTheme().isEmpty()){
        m_MaterialStyleHelper->setTheme(theme);
        m_MaterialStyleHelper->setPrimary(primary);
        m_MaterialStyleHelper->setAccent(accent);
        m_MaterialStyleHelper->setBackgroundColor(backColor);
        s.setDefaultTheme(m_MaterialStyleHelper->toJson());
        s.setTheme(s.defaultTheme());
    }
    qInfo()<<"material style tha was in setings "<<s.theme();
   m_MaterialStyleHelper-> loadFromJson(s.theme());
}

MaterialStyleHelper* JooyaApplication::m_MaterialStyleHelper;//=new MaterialStyleHelper();
ApplicationAlarmSettingsHelper* JooyaApplication::m_ApplicationAlarmSettingsHelper;
AppPagesManager* JooyaApplication::m_ApplicationPageManager;
bool JooyaApplication::m_IsDesignMode=false;

CurrentApplicationHelper* JooyaApplication::m_CurrentApplicationHelper;

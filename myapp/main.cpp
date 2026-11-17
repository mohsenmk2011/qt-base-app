#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QQuickStyle>
#include <QtWebView>
#include<QQuickView>

#include<currentapplicationsettings.h>
#include<currentapplicationpath.h>
#include<version.h>
#include<applicationversioninfo.h>
#include<jooyaapplication.h>

#include<androidlib.h>
#include<corelib.h>
#include<purchasinglib.h>
#include<settingslib.h>
#include<networklib.h>
#include<quicklib.h>
#include<loginlib.h>
#include<googleauth.h>
#include<managerlib.h>
#include<notificationlib.h>
#include<chatlib.h>

#include<jooyafont.h>
#include<jooyanetworkengine.h>
#include<jooyalogger.h>

#include<chatmanager.h>
#include<websockethandler.h>
#include<filewatcher.h>
#include <QCommandLineParser>
#include <QFile>
#include<androidservicemanager.h>
#include<smsmanager.h>

int main(int argc, char *argv[])
{
    JooyaApplication japp("Jooya","www.jooyabash.ir","JooyaQtBaseApplication");
    japp.setApplicationName("اپلیکیشن جویا",false,false);
#if defined(Q_OS_ANDROID)
    // you should create two Android Client id(debug&release) for andorid,that is not used any where,it just register you android app on google
    // Web OAuth client id from Google Cloud Console (audience accepted by the backend).
    // Keep in sync with Authentication:Google:ClientId in the backend appsettings.json
    // web client id has a secret that is will be used in backend
    japp.setGoogleClientId("");
#else
    // this desktop client id and secret is used in google auth class in loginlib
    japp.setGoogleClientId("");
    japp.setGoogleClientSecret("");
#endif
    japp.setDefaultTheme(MaterialThemes::MaterialThemesEnum::Light,MaterialColors::MaterialColorsEnum::Pink,MaterialColors::MaterialColorsEnum::Pink,MaterialColors::MaterialColorsEnum::Pink);
    japp.setDefaultAlarmSettings(true,AlarmClasses::AlarmClassesEnum::AlarmManager,true,"این پیام هشدار اپ جویا است");
    QtWebView::initialize();
    JooyaLogger jl;

    Corelib::registerTypes();
    Androidlib::registerTypes();
    Purchasinglib::registerTypes();
    Settingslib::registerTypes();
    Networklib::registerTypes();
    Quicklib::registerTypes();
    Notificationlib::registerTypes();
    Loginlib::registerTypes();
    Managerlib::registerTypes();
    Chatlib::registerTypes();
    qmlRegisterType<CurrentApplicationSettings>("Jooya",1,0,"CurrentApplicationSettings");
    qmlRegisterType<CurrentApplicationPath>("Jooya",1,0,"CurrentApplicationPath");
    qmlRegisterType<ApplicationVersionInfo>("Jooya",1,0,"ApplicationVersionInfo");
    //00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
    JooyaNetworkEngine jne;

    //TODO: Change this after creating new branch from master branch
    jne.setBaseUrl("https://jooyabash.ir");
    //jne.setBaseUrl("https://localhost:5001");
    //00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
    //TODO: Change this after creating new branch from master branch
    WebSocketHandler::setUrl("wss://jooyabash.ir/ws");
    //    WebSocketHandler::setUrl("ws://localhost:5000/ws");
    //00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
    QGuiApplication app(argc, argv);
    qDebug()<<"^^^^^^^^^[ register Native Methods And BroadcastReceiver(in qt app) ]^^^^^^^^^";

    SmsManager sm;
    sm.registerNativesMethod();

    AndroidDeepLinkManager adm;
    adm.registerNativesMethod();

#if defined(Q_OS_ANDROID)
    GoogleAuth ga;
    ga.registerNativesMethod();
#endif
    qDebug()<<"^^^^^^^^^^^^^^^^^^[ QmlLive live ]^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
    app.setWindowIcon(QIcon(":/images/icon.ico"));

    QString ver=QString("%1.%2,%3.%4").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH).arg(VERSION_BUILD);
    app.setApplicationVersion(ver);

    QQuickStyle::setStyle("Material");
    //QQuickStyle::setStyle("Universal");
    QQmlApplicationEngine engine;
    JooyaApplication::m_ApplicationPageManager->loadQQmlApplicationEngine(&engine);
    //----------------------------------------------------------
#if defined(QT_DEBUG) && !defined(Q_OS_ANDROID)
    const QDir projectDirectory("/home/mohsen/Programming/Projects/jooyaqtquickapplication/myapp");
    JooyaNetworkEngine::m_FileWather=new FileWatcher();
    JooyaNetworkEngine::m_FileWather->addExcludeDirs(QStringList()<<"Other"<<"android");
    JooyaNetworkEngine::m_FileWather->setDirectory(projectDirectory.absolutePath());
    //JooyaNetworkEngine::m_FileWather->writepathcounts();
    //use below line instead above line for qml live be working
    engine.load(QUrl(projectDirectory.absolutePath()+"/main.qml"));
#else
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
#endif

    //------------------------[ AppPagesManager ]-----------------------
    //        AppPagesManager pm;
//add a qml file to mainWinow
//        pm.writeChildrens("mainWindow");
       //pm.setWindow("qrc:/TestItem.qml");
        //pm.writeChildrens("mainWindow");

        //add a main.qml file to mainWinow
//                pm.writeChildrens("mainWindow");
//                pm.setWindow("qrc:/main.qml");
//                pm.writeChildrens("mainWindow");

//        pm.isSameEngine();
        //TODO: SEND URL TO STACKVIEW
        //pm.createChatsPageCom();
        //pm.setParentItem("qrc:/TestItem.qml","ApplicationWindow");
        //pm.setParentItem("qrc:/TestItem.qml","mainWindow");
        //pm.setParentItem("qrc:/TestItem.qml","mainWindow");
       // pm.setParentItem("qrc:/TestItem.qml","mainStackView");
        //////pm.setParentItem("qrc:/pages/chat/ChatsPage.qml","mainStackView");
        //pm.replaceItem("qrc:/pages/chat/ChatsPage.qml","mainStackView");
        //pm.find("mainStackView");
        //pm.writeChildrens("mainStackView");

        //pm.find("chatsPage");
//        pm.writeChildrens("chatsPage");
        if (engine.rootObjects().isEmpty()){
            return -1;
        }
        else {
        }
    //-----------------------------------------------
#if defined(Q_OS_ANDROID)
    QNativeInterface::QAndroidApplication::hideSplashScreen();
#endif
    return app.exec();
}

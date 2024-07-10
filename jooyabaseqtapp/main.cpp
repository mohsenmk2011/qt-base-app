#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QQuickStyle>
#include <QtWebView>
#include<QQuickView>

#include<baseappsettings.h>
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
    japp.setApplicationName("اپلیکیشن جویا");
    japp.setDefaultTheme(MaterialThemes::MaterialThemesEnum::Light,MaterialColors::MaterialColorsEnum::Pink,MaterialColors::MaterialColorsEnum::Pink,MaterialColors::MaterialColorsEnum::Pink);

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
    qmlRegisterType<BaseAppSettings>("Jooya",1,0,"BaseAppSettings");
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
    qDebug()<<"^^^^^^^^^[ register Native Methods And BroadcastReceiver  ]^^^^^^^^^";
    jne.androidService()->registerNativeMethodsAndBroadcastReceiver();

    SmsManager sm;
    sm.registerNativesMethod();

    AndroidDeepLinkManager adm;
    adm.registerNativesMethod();
    qDebug()<<"^^^^^^^^^^^^^^^^^^[ QmlLive live ]^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
    app.setWindowIcon(QIcon(":/images/icon.ico"));

    QString ver=QString("%1.%2,%3.%4").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH).arg(VERSION_BUILD);
    app.setApplicationVersion(ver);

    QQuickStyle::setStyle("Material");
    //QQuickStyle::setStyle("Universal");
    //------------------------[ load main.qml with engin 11111]-----------------------
    //TODO: Change this after creating new branch from master branch
    const QDir projectDirectory("/home/mohsen/QtProjects/qtprojects/rokhshid/jooyabaseqtapp");

    //QmlLive live;
//    FileWatcher* fw= QmlLive::qmlAttachedProperties(nullptr);
//    fw->addExcludeDirs(QStringList()<<"Other"<<"android");
//    fw->setDirectory(projectDirectory.absolutePath());
//    fw->writepathcounts();

//    //japp.processQmlLiveCommandLine(&app);
//    if(japp.isDesignMode()){
//        FileWatcher watcher;
//        QQuickView view;
//        view.setSource(watcher.rootFile());
//        qCritical()<<"watcher.rootFile()"<<watcher.rootFile();
//        view.setWidth(600);
//        view.setHeight(400);
//        view.show();

//        QUrl rootFile=watcher.rootFile();
//        watcher.addCallback([&view, rootFile](){
//            view.engine()->clearComponentCache();
//            view.setSource(rootFile);
//            qDebug()<<"in calll back method";

//        });
//        qCritical()<<"after all";
//    }
//    else{

//        QQmlApplicationEngine engine;
//        AppPagesManager pm;
//        pm.loadQQmlApplicationEngine(&engine);

//        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//        if (engine.rootObjects().isEmpty()){
//            return -1;
//        }
//        else {
//        }
//    }
    //------------------------ORGINAL LOADING-----------------------
    QQmlApplicationEngine engine;

    JooyaNetworkEngine::m_FileWather=new FileWatcher();
    JooyaNetworkEngine::m_FileWather->loadQQmlApplicationEngine(&engine);
    JooyaNetworkEngine::m_FileWather->addExcludeDirs(QStringList()<<"Other"<<"android");
    JooyaNetworkEngine::m_FileWather->setDirectory(projectDirectory.absolutePath());
    JooyaNetworkEngine::m_FileWather->writepathcounts();
    //----------------------------------------------------------
#if defined(QT_DEBUG) && !defined(Q_OS_ANDROID)
        //use below line instead above line for qml live be working
        engine.load(QUrl(projectDirectory.absolutePath()+"/main.qml"));
#else
    {
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    }
#endif

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
        QNativeInterface::QAndroidApplication::hideSplashScreen();

    return app.exec();
}

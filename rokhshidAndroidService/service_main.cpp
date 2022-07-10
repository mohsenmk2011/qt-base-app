#include <QDebug>

#include<androidservicemanager.h>

//#include<notifymanager.h>
//#include<jooyaapplication.h>
//#include<jooyanetworkengine.h>
//#include<jooyalogger.h>
#include<testtimer.h>
#if defined(Q_OS_ANDROID)
#include <QAndroidService>
#endif

int main(int argc, char *argv[])
{

    QString functionColorized=QString("\x1B[47m%{function}\033[0m");
    QString function=QString("%{function}");
    QString lineColorized=QString("\x1B[47;35m%{line}\033[0m");
    QString line=QString("%{line}");
    QString functionLine=QString("[%1(%2)] : ").arg(function).arg(lineColorized);
    QString functionLineColorized=QString("[%1(%2)] : ").arg(functionColorized).arg(lineColorized);

    //=======================
    QString message="%{message}";
    QString redMessage=QString("\x1B[31m%1\033[0m").arg(message);
    QString greenMessage=QString("\x1B[32m%1\033[0m").arg(message);
    QString yellowMessage=QString("\x1B[33m%1\033[0m").arg(message);
    QString blueMessage=QString("\x1B[34m%1\033[0m").arg(message);
    QString magentaMessage=QString("\x1B[35m%1\033[0m").arg(message);
    QString messageColorized=QString("%{if-debug}%1%{endif}%{if-info}%2%{endif}%{if-warning}%3%{endif}%{if-critical}%4%{endif}%{if-fatal}%5%{endif}").arg(blueMessage).arg(greenMessage).arg(yellowMessage).arg(redMessage).arg(magentaMessage);
    //=======================
    //    qSetMessagePattern("[%{function}(%{line})] : %{message}");//Normal
    //    qSetMessagePattern("[\x1B[32m%{function}\033[0m\t(%{line})] : %{message}");//function green
    qSetMessagePattern(QString("%1%2").arg(functionLineColorized).arg(messageColorized));

    qWarning() << "Service starting from a separate .so file";
//    JooyaLogger logger;
//    JooyaApplication japp("Jooya","www.rokhshid.jooyabash.ir","Rokhshid");

//    //00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//    JooyaNetworkEngine jne;
    TestTimer tt;
//    jne.setBaseUrl("https://rokhshid.jooyabash.ir");
//    //jne.setBaseUrl("https://localhost:5001");

//    jne.setIdentityUrl("https://identity.jooyabash.ir");
//    //jne.setIdentityUrl("http://localhost:53963");

//    jne.setClientId("JooyaRokhshidApp");
//    jne.setClientSecret("secret");
//    jne.setApiName("JooyaRokhshidAPI");
//    jne.appendClientScopes(jne.apiName());
//    jne.appendClientScopes("IdentityServerApi");
//    qDebug()<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
//    qDebug()<<jne.clientScopes();
//    qDebug()<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
//    //00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//    WebSocketHandler::setUrl("wss://rokhshid.jooyabash.ir/ws");
//    //    WebSocketHandler::setUrl("ws://localhost:5000/ws");
    //00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
    qInfo() << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qInfo() << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qInfo() << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qInfo() << "%%%%%%%%[ Start Anroid Service main.cpp  ]%%%%%%%%%%%%";
    qInfo() << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qInfo() << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qInfo() << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
#if defined(Q_OS_ANDROID)
    QAndroidService app(argc, argv);
    AndroidServiceManager *qtAndroidService = new AndroidServiceManager(&app);
    qInfo() << "%%%%%%%%[ qtAndroidService->registerNativesOfService();  ]%%%%%%%%%%%%";
    qtAndroidService->registerNativesOfService();
    qInfo() << "%%%%%%%%[ => qtAndroidService->sendMessage(Hi from service);  ]%%%%%%%%%%%%";
//    qtAndroidService->sendToService("CurrentTime/"+QDateTime::currentDateTime().toString("h:m:s ap"));
//    qtAndroidService->registerServiceBroadcastReceiver();
    tt.setAndroidService(qtAndroidService);
    return app.exec();

#endif
}

#include <QDebug>

//#include<notifymanager.h>
//#include<jooyaapplication.h>
//#include<jooyanetworkengine.h>
//#include<jooyalogger.h>
#include<androidservicemanager.h>
#include<testtimer.h>
#include<downloadmanager.h>
#include<jooyaapplication.h>
#include<jooyalogger.h>
#if defined(Q_OS_ANDROID)
#include <QAndroidService>
#endif

int main(int argc, char *argv[])
{
    qInfo() << "$$$$$$$$$[ starting Service  from a separate .so file ]$$$$$$$$$";
    JooyaLogger jl;
    JooyaApplication japp("Jooya","www.rokhshid.jooyabash.ir","Rokhshid");

   //00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
   JooyaNetworkEngine jne;

    jne.setBaseUrl("https://rokhshid.jooyabash.ir");
    //jne.setBaseUrl("https://localhost:5001");

    jne.setIdentityUrl("https://identity.jooyabash.ir");
    //jne.setIdentityUrl("http://localhost:53963");

    jne.setClientId("JooyaRokhshidApp");
    jne.setClientSecret("secret");
    jne.setApiName("JooyaRokhshidAPI");
    jne.appendClientScopes(jne.apiName());
    jne.appendClientScopes("IdentityServerApi");
    qDebug()<<"^^^^^^^^^^^^^^^^^^^< c++ service >^^^^^^^^^^^^^^^^^^^^^^^^^^^";
    qDebug()<<"          "<<jne.clientScopes();
    qDebug()<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
    //00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
    WebSocketHandler::setUrl("wss://rokhshid.jooyabash.ir/ws");
    //    WebSocketHandler::setUrl("ws://localhost:5000/ws");
    //00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

   TestTimer tt;
   DownloadManager dm;
    qInfo() << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qInfo() << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qInfo() << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qInfo() << "%%%%%%%%[ Start Anroid Service main.cpp  ]%%%%%%%%%%%%";
    qInfo() << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qInfo() << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
    qInfo() << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
#if defined(Q_OS_ANDROID)
    QAndroidService app(argc, argv);
    jne.androidService()->setIsInService(true);
    qInfo() << "%%%%%%%%[ qtAndroidService->registerNativesOfService();  ]%%%%%%%%%%%%";
    jne.androidService()->registerNativesOfService();
    qInfo() << "%%%%%%%%[ => qtAndroidService->sendMessage(Hi from service);  ]%%%%%%%%%%%%";
//    qtAndroidService->sendToService("CurrentTime/"+QDateTime::currentDateTime().toString("h:m:s ap"));
    jne.androidService()->registerServiceBroadcastReceiver();
    tt.setAndroidService(jne.androidService());
    return app.exec();

#endif
}

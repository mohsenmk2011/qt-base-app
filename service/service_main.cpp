#include <QDebug>

#include<downloadmanager.h>
#include<jooyaapplication.h>
#include<jooyalogger.h>
#if defined(Q_OS_ANDROID)
#include <QtCore/private/qandroidextras_p.h>

#endif

int main(int argc, char *argv[])
{
    qInfo() << "$$$$$$$$$[ starting Service  from a separate .so file ]$$$$$$$$$";
    JooyaLogger jl;
    //TODO: Change this after creating new branch from master branch
    JooyaApplication japp("Jooya","www.jooyabash.ir","JooyaQtBaseApplication");

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
    return app.exec();
#endif
}

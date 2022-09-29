#include "testtimer.h"

TestTimer::TestTimer(QObject *parent)
    : QObject{parent}
{
    m_Timer.setInterval(1000);
    connect(&m_Timer,&QTimer::timeout,this,&TestTimer::onTimerTimeout);
}

void TestTimer::setAndroidService(AndroidServiceManager *service)
{
    m_Service=service;
    connect(m_Service,&AndroidServiceManager::serviceMessageReceived,this,&TestTimer::onNewMessage);
}

void TestTimer::onNewMessage(QString message)
{
    //m_Service->sendToService("Received in cpp servie");// CurrentTime/"+QDateTime::currentDateTime().toString("h:m:s ap"));
    if(message=="StartTimer"){
        if(!m_Timer.isActive()){
            qInfo()<<"###[ Timer Statred ]###";
            m_Timer.start();
        }
    }
    else if(message=="StopTimer"){
            qInfo()<<"###[ Stop Timer ]###";
            m_Timer.stop();
    }
}

void TestTimer::onTimerTimeout()
{
    qDebug()<<"Send Message From c++ service to java service";
    //m_Service->sendMessage("CurrentTime/"+QDateTime::currentDateTime().toString("h:m:s ap"));
    m_Service->sendToService("CurrentTime/"+QDateTime::currentDateTime().toString("h:m:s ap"),false);
    qDebug()<<"Send Message From c++ service to java service Finished";
}

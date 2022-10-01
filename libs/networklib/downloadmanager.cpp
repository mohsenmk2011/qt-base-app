#include "downloadmanager.h"

DownloadManager::DownloadManager(QObject *parent) : JooyaNetwork(parent)
{
    files={};
    m_CountFailed=0;
    m_CountDownloaded=0;
    m_CountToDownload=0;
    connect(androidService(),&AndroidServiceManager::serviceMessageReceived,this,&DownloadManager::onNewServiceMessage);
    connect(androidService(),&AndroidServiceManager::appMessageReceived,this,&DownloadManager::onNewAppeMessage);
}

QString DownloadManager::downloadCountMessage()
{
    return m_DownloadCountMessage;
}

void DownloadManager::setDownloadCountMessage(QString message)
{
    if(m_DownloadCountMessage!=message){
        m_DownloadCountMessage=message;
        qInfo()<<"=> "<<message;
        emit downloadCountMessageChanged();
    }
}

float DownloadManager::totalRatio()
{
    return m_TotalRatio;
}

void DownloadManager::setTotalRatio(float r)
{
    if(r!=m_TotalRatio){
        m_TotalRatio=r;
        emit totalRatioChanged();
        if(androidService()->isInService()){
            androidService()->sendToService(QString("DownloadManagerTotalRatio,%1").arg(r));
        }
    }
}

void DownloadManager::add(QList<File*> fls)
{
    foreach (File* f,fls) {
        files.append(f);
    }
}

void DownloadManager::add(QString link)
{
#if defined(Q_OS_ANDROID)
    if(androidService()->isInService())
    {
        qInfo()<<"is in service => is adding link("<<link<<")";
        files.append(new File(link));
    }
    else{
        qInfo()<<"is in qt app => send link to service";
        files.append(new File(link));
        androidService()->sendToService("DownloadManagerAddFile,"+link);
    }
#else
    files.append(new File(link));
#endif
}

bool DownloadManager::checkExistance()
{
    foreach (File* f,files) {
        if(!f->exists()){
            return false;
        }
    }
    return true;
}

void DownloadManager::download()
{
#if defined(Q_OS_ANDROID)
    if(androidService()->isInService())
    {
        if(!checkExistance()){
            m_CountDownloaded=0;
            m_CountToDownload=files.count();
            foreach (File* f, files) {
                connect(f,SIGNAL(bytesSentChanged()),this,SLOT(updateRatio()));
                connect(f,SIGNAL(downloadStateChanged()),this,SLOT(updateDownloadCount()));
                f->download();
            }
        }
        else {
            androidService()->sendToService("DownloadManagerFileExists");
        }
    }
    else
    {
        androidService()->sendToService("DownloadManagerStartDownload");
    }
#else
    if(!checkExistance()){
        m_CountDownloaded=0;
        m_CountToDownload=files.count();
        foreach (File* f, files) {
            connect(f,SIGNAL(bytesSentChanged()),this,SLOT(updateRatio()));
            connect(f,SIGNAL(downloadStateChanged()),this,SLOT(updateDownloadCount()));
            f->download();
        }
    }
#endif
}

void DownloadManager::updateRatio()
{
    qint64 totalBytes=0;
    qint64 totalBytesSent=0;
    foreach (File* f, files) {
        totalBytes+=f->bytesTotal();
        totalBytesSent+=f->bytesSent();
    }
    setTotalRatio((float)totalBytesSent/totalBytes);
}

void DownloadManager::updateDownloadCount()
{
    File* f=qobject_cast<File*>(sender());
    if(f->downloadState()==FileDownloadStates::FileDownloadStatesEnum::Succeed||f->downloadState()==FileDownloadStates::FileDownloadStatesEnum::FileExists)
    {
       m_CountDownloaded++;
    }
    else if (f->downloadState()==FileDownloadStates::FileDownloadStatesEnum::Faild) {
        m_CountFailed++;
    }
    refreshDownloadMessage();
    qDebug()<<"m_CountDownloaded="<<m_CountDownloaded;
    qDebug() <<"m_CountFailed="<<m_CountFailed;
    qDebug() <<"files.count()="<<files.count();

    if(m_CountDownloaded+m_CountFailed==files.count()){
        if(androidService()->isInService())
        {
            androidService()->sendToService("DownloadManagerTotalFileDownloaded");
        }
        else{
            emit totalFileDownloaded();
        }
    }
}

void DownloadManager::onNewServiceMessage(QString message)
{
    qCritical()<<"###[(In C++ Service) DownloadManager: message received from app => "<<message<<" ]###";
    if(message.contains("DownloadManagerAddFile"))
    {
        add(message.split(",").at(1));
    }
    else if(message.contains("DownloadManagerStartDownload"))
    {
        download();
    }

}

void DownloadManager::onNewAppeMessage(QString appMessage)
{
    qCritical()<<"###[(In Qt App) DownloadManager: message received from c++ service => "<<appMessage<<" ]###";
    if(appMessage.contains("DownloadManagerFileExists"))
    {
        message()->setContent("این فایل قبلا دانلود شده است");
    }
    else if(appMessage.contains("DownloadManagerTotalRatio"))
    {
        setTotalRatio((appMessage.split(",").at(1).toFloat()));
    }
    else if(appMessage.contains("DownloadManagerTotalFileDownloaded"))
    {
        emit totalFileDownloaded();
    }
}
void DownloadManager::refreshDownloadMessage()
{
    setDownloadCountMessage(QString("در حال دانلود (%1/%2)").arg(m_CountToDownload).arg(m_CountDownloaded));
}

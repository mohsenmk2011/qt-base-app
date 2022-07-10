#include "downloadmanager.h"

DownloadManager::DownloadManager(QObject *parent) : JooyaNetwork(parent)
{
    files={};
    m_CountFailed=0;
    m_CountDownloaded=0;
    m_CountToDownload=0;
}

QString DownloadManager::downloadCountMessage()
{
    return m_DownloadCountMessage;
}

void DownloadManager::setDownloadCountMessage(QString message)
{
    if(m_DownloadCountMessage!=message){
        m_DownloadCountMessage=message;
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
    }
}

void DownloadManager::add(QList<File*> fls)
{
    foreach (File* f,fls) {
        files.append(f);
    }
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
    if(!checkExistance()){
        m_CountDownloaded=0;
        m_CountToDownload=files.count();
        foreach (File* f, files) {
            connect(f,SIGNAL(bytesSentChanged()),this,SLOT(updateRatio()));
            connect(f,SIGNAL(downloadStateChanged()),this,SLOT(updateDownloadCount()));
            f->download();
        }
    }
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
        emit totalFileDownloaded();
    }
}
void DownloadManager::refreshDownloadMessage()
{
    setDownloadCountMessage(QString("در حال دانلود (%1/%2)").arg(m_CountToDownload).arg(m_CountDownloaded));
}

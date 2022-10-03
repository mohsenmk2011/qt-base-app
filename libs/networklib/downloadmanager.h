#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include<jooyanetwork.h>
#include<file.h>
#include<androidservicemanager.h>

class DownloadManager : public JooyaNetwork
{
    Q_OBJECT
    Q_PROPERTY(QString downloadCountMessage READ downloadCountMessage WRITE setDownloadCountMessage NOTIFY downloadCountMessageChanged)
    Q_PROPERTY(float totalRatio READ totalRatio WRITE setTotalRatio NOTIFY totalRatioChanged)
public:
    explicit DownloadManager(QObject *parent = nullptr);

    QString downloadCountMessage();
    void setDownloadCountMessage(QString message);

    float totalRatio();
    void setTotalRatio(float r);

    Q_INVOKABLE void download();
    Q_INVOKABLE void add(QList<File*> fls);
    Q_INVOKABLE void add(QString link);
    Q_INVOKABLE void add(File* file);
    File* findFile(QString link);
    Q_INVOKABLE bool checkExistance();
signals:
    void downloadCountMessageChanged();
    void totalRatioChanged();
    void totalFileDownloaded();
private slots:
    void updateRatio();
    void updateDownloadCount();
    void onSendisDownloadedToAppInstance();

    void onNewServiceMessage(QString message);
    void onNewAppeMessage(QString appMessage);
private:
    QString m_DownloadCountMessage;
    float m_TotalRatio;
    int m_CountToDownload;
    int m_CountDownloaded;
    int m_CountFailed;
    QList<File*> files;
    void refreshDownloadMessage();
};

#endif // DOWNLOADMANAGER_H

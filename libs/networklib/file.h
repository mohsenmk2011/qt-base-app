#ifndef FILE_H
#define FILE_H

#include <QObject>
#include<jooyanetwork.h>
#include<QFile>
#include<QJsonObject>
#include<QDir>
#include<qdebug.h>
#include<applicationpath.h>
#include<filedownloadstates.h>
#include<QUrl>

class File : public JooyaNetwork
{
    Q_OBJECT

    Q_PROPERTY(QString downloadLink READ downloadLink WRITE setDownloadLink NOTIFY downloadLinkChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int fileId READ fileId WRITE setFileId NOTIFY fileIdChanged)

    Q_PROPERTY(qint64 bytesSent READ bytesSent WRITE setBytesSent NOTIFY bytesSentChanged)
    Q_PROPERTY(qint64 bytesTotal READ bytesTotal WRITE setBytesTotal NOTIFY bytesTotalChanged)

    Q_PROPERTY(float upDownRatio READ upDownRatio WRITE setUpDownRatio NOTIFY upDownRatioChanged)
    Q_PROPERTY(QString folderPath READ folderPath WRITE setFolderPath NOTIFY folderPathChanged)
    Q_PROPERTY(QString ext READ ext WRITE setExt NOTIFY extChanged)
    Q_PROPERTY(FileDownloadStates::FileDownloadStatesEnum downloadState READ downloadState WRITE setDownloadState NOTIFY downloadStateChanged)
    Q_PROPERTY(bool isDownloaded READ isDownloaded WRITE setIsDownloaded NOTIFY isDownloadedChanged)

public:
    explicit File(QObject *parent = nullptr);
    File(QString link);
    File(QString link,QString path);
    File(QString link,QString path, QString extension);

    QString downloadLink();
    void setDownloadLink(QString url);

    QUrl url();
    void setUrl(QUrl p);

    QString name();
    void setName(QString n);

    int fileId();
    void setFileId(int id);

    qint64 bytesSent();
    void setBytesSent(qint64 t);

    qint64 bytesTotal();
    void setBytesTotal(qint64 t);

    float upDownRatio();
    void setUpDownRatio(float ratio);

    QString folderPath();
    void setFolderPath(QString folderPath);

    QString ext();
    void setExt(QString ext);

    FileDownloadStates::FileDownloadStatesEnum downloadState();
    void setDownloadState(FileDownloadStates::FileDownloadStatesEnum ds);

    bool isDownloaded();
    void setIsDownloaded(bool isD);

    Q_INVOKABLE bool exists();

    Q_INVOKABLE virtual void download();
    Q_INVOKABLE bool remove();
    bool isVideo(QString ext="");
    bool isAudio(QString ext="");
    bool save(QByteArray textContent);
    bool saveJson(QJsonArray array);
    QByteArray read();
signals:
 void downloadLinkChanged();
 void urlChanged();
 void nameChanged();
 void fileIdChanged();
 void upDownRatioChanged();
 void folderPathChanged();
 void extChanged();
 void bytesSentChanged();
 void bytesTotalChanged();
 void downloadStateChanged();
 void isDownloadedChanged();
private slots:
 void updownLoadingProgress(qint64 bytesSent, qint64 bytesTotal);
 void onDownloadFinishd();
 void refreshPath();

private:
    QString m_DowloadLink;
    QUrl m_Url;
    QString m_Name;
    int m_FileId;
    qint64 m_BytesSent;
    qint64 m_BytesTotal;
    float m_UpDownRatio;
    QString m_FolderPath;
    QString m_Extension;
    FileDownloadStates::FileDownloadStatesEnum m_DownloadState;
    bool m_IsDownloaded;

    void makeSureFolderExsists();
    void initializeFolderPath(QString ext);
};

#endif // FILE_H

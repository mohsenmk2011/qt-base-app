#include "file.h"

File::File(QObject *parent) : JooyaNetwork (parent)
{
    ApplicationPath u;
    setFolderPath(u.filesFolderPath());

    setFileId(0);
    m_IsDownloaded=false;
    m_DownloadState=FileDownloadStates::FileDownloadStatesEnum::NotStarted;
    connect(this,&File::downloadLinkChanged,this,&File::refreshPath);
    connect(this,SIGNAL(imageNameChanged()),this,SLOT(refreshPath()));
    connect(this,SIGNAL(extChanged()),this,SLOT(refreshPath()));
    connect(this,SIGNAL(folderPathChanged()),this,SLOT(refreshPath()));
}

File::File(QString link):File()
{
    setDownloadLink(link);
}

File::File(QString link,QString path):File()
{
    setDownloadLink(link);
    setUrl(path);
}

File::File(QString link, QString path, QString extension):File()
{
    setDownloadLink(link);
    setExt(extension);
    setUrl(path);
}

QString File::downloadLink()
{
    return m_DowloadLink;
}

void File::setDownloadLink(QString link)
{
    if(m_DowloadLink!=link){
        m_DowloadLink=link;
        emit downloadLinkChanged();
        QFileInfo file(link);
        setImageName(file.baseName());
        setExt(file.suffix());
    }
}

QUrl File::url()
{
    return m_Url;
}

void File::setUrl(QUrl p)
{
    if(m_Url!=p){
        m_Url=p;
        emit urlChanged();
        if(QFile::exists(m_Url.path())){
            setDownloadState(FileDownloadStates::FileDownloadStatesEnum::FileExists);
            return;
        }
    }
}

QString File::imageName()
{
    return m_Name;
}

void File::setImageName(QString n)
{
    if(m_Name!=n){
        m_Name=n;
        emit imageNameChanged();
    }
}

int File::fileId()
{
    return m_FileId;
}

void File::setFileId(int id)
{
    if(m_FileId!=id){
        m_FileId=id;
        emit fileIdChanged();
    }
}

qint64 File::bytesSent()
{
    return m_BytesSent;
}

void File::setBytesSent(qint64 t)
{
    if(t!=m_BytesSent){
        m_BytesSent=t;
        emit bytesSentChanged();
    }
}

qint64 File::bytesTotal()
{
    return m_BytesTotal;
}

void File::setBytesTotal(qint64 t)
{
    if(t!=m_BytesTotal){
        m_BytesTotal=t;
        emit bytesTotalChanged();
    }
}

float File::upDownRatio()
{
    return m_UpDownRatio;
}

void File::setUpDownRatio(float ratio)
{
    m_UpDownRatio=ratio;
    emit upDownRatioChanged();
}

QString File::folderPath()
{
    return m_FolderPath;
}

void File::setFolderPath(QString folderPath)
{
    if(folderPath!=m_FolderPath){
        m_FolderPath=folderPath;
        emit folderPathChanged();
        makeSureFolderExsists();
    }
}

QString File::ext()
{
    return m_Extension;
}

void File::setExt(QString ext)
{
    if(m_Extension!=ext){
        m_Extension=ext;
        initializeFolderPath(ext);
        emit extChanged();
    }
}

FileDownloadStates::FileDownloadStatesEnum File::downloadState()
{
    return m_DownloadState;
}

void File::setDownloadState(FileDownloadStates::FileDownloadStatesEnum ds)
{
    if(ds!=m_DownloadState){
        m_DownloadState=ds;
        emit downloadStateChanged();
        setIsDownloaded(ds==FileDownloadStates::FileDownloadStatesEnum::FileExists||ds==FileDownloadStates::FileDownloadStatesEnum::Succeed);
    }
}

bool File::exists()
{
    return QFile::exists((url().path()));
}

QByteArray File::read()
{
    QFile file(url().path());
    if(file.open( QIODevice::ReadOnly|QIODevice::Text))
    {
        QByteArray bytes = file.readAll();
        file.aboutToClose();
        return bytes;
    }
    return QByteArray();
}

bool File::isDownloaded()
{
    return m_IsDownloaded;
}

void File::setIsDownloaded(bool isD)
{
    if(m_IsDownloaded!=isD){
        m_IsDownloaded=isD;
        emit isDownloadedChanged();
    }
}

void File::download()
{
    if(QFile::exists(url().path())){
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::FileExists);
        return;
    }
    qDebug()<<"is going to download => "<<downloadLink();
    if(downloadLink().isNull()||downloadLink().isEmpty()){
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::Faild);
        qWarning()<<"download link was null->return";
        return;
    }
    setDownloadState(FileDownloadStates::FileDownloadStatesEnum::Started);
    QNetworkReply* r=getRequest(downloadLink());
    connect(r,SIGNAL(finished()),this,SLOT(onDownloadFinishd()));
    connect(r,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(updownLoadingProgress(qint64,qint64)));
}

///remove file from disk
bool File::remove()
{
    if(url().isEmpty()){
        return false;
    }
    if(QFile::exists(url().path())){
        QFile file(url().path());
        return file.remove();
    }
    else {
        return false;
    }
}

bool File::isVideo(QString ext)
{
    if(ext=="mp4"){
        return true;
    }
    return false;
}

bool File::isAudio(QString ext)
{
    if(ext=="mp3"||ext=="wav"){
        return true;
    }
    return false;
}

void File::updownLoadingProgress(qint64 bytesSent,qint64 bytesTotal)
{
    setDownloadState(FileDownloadStates::FileDownloadStatesEnum::IsDownloading);
    setBytesSent(bytesSent);
    setBytesTotal(bytesTotal);
    setUpDownRatio((float)bytesSent/bytesTotal);
}

void File::onDownloadFinishd()
{
    QNetworkReply* r=convertToReply(sender());
    qDebug()<<"image download findish";
    if(r->error()==QNetworkReply::NoError)
    {
        qInfo()<<"with no error => url=>"<<url();
        qInfo()<<"NoError=> path=>"<<url().path();
        save(r->readAll());
    }
    else if(isNotFound(r)){
        qCritical()<<"File not found in remote";
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::FileNotFound);
    }
    else {
        qCritical()<<"Error";
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::Faild);
        int HttpCode= getHttpCode(r);
        if(HttpCode==404){
            message()->setContent("فایل یافت نشد");
        }
        else {
            showMessage(r);
        }
    }
    setIsProcssing(false);
}

bool File::saveJson(QJsonArray array){
    QJsonDocument doc(array);
    return save(doc.toJson());
}

bool File::save(QByteArray textContent){
    qDebug()<<"is going to save the file with size=> "<<textContent.count();
    if(url().isEmpty()||!url().isValid()){
        qWarning()<<"path of file was null";
        return false;
    }
    QFile f(url().path());
    if(!f.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate)){
        message()->setContent("فایل ذخیره نشد");
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::ErrorInSaving);
        return false;
    }
    f.write(textContent);
    f.close();
    if(f.exists()) {
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::Succeed);
        emit urlChanged();
        qInfo()<<"file downloaded successfully";
        return true;
    }
    else {
        setDownloadState(FileDownloadStates::FileDownloadStatesEnum::ErrorInSaving);
        return false;
    }
}

void File::refreshPath()
{
    if(folderPath().isNull()||folderPath().isEmpty()){
        return;
    }
    if(imageName().isNull()||imageName().isEmpty()){
        return;
    }
    if(ext().isNull()||ext().isEmpty()){
        return;
    }
    setUrl(QUrl::fromLocalFile(folderPath()+imageName()+"."+ext()));
}

void File::makeSureFolderExsists()
{
    QDir dir(folderPath());

    if(!dir.exists()){
        dir.mkpath(folderPath());
    }
    if(dir.exists()){
    }
    else {
    }
}

void File::initializeFolderPath(QString ext)
{
    ApplicationPath u;
    if(isVideo(ext)){
        setFolderPath(u.videoFolderPath());
    }
    else if (isAudio(ext)) {
        setFolderPath(u.soundFolderPath());
    }
}



#include "jooyanetwork.h"

JooyaNetwork::JooyaNetwork(QObject *parent) :JooyaNetworkEngine(parent)/*, QNetworkAccessManager()*/
{
    currentUrl="";
    //qCritical()<<"Initialize request header(Deleted)";
    //initializeRequestHeader();
    //qCritical()<<"=> Add Token to request";
    addTokenToRequestHeader();
    //qInfo("1- Connecting to-> loginInfo.StateChanged");
    connect(loginInfo(),SIGNAL(stateChanged(LoginStates::LoginStatesEnum)),this,SLOT(addTokenToRequestHeader()));
    connect(&m_NetworkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(currentReplyFinished(QNetworkReply*)));

    QSslConfiguration sslConfiguration = m_Request.sslConfiguration();
    sslConfiguration.setProtocol(QSsl::AnyProtocol);
    sslConfiguration.setPeerVerifyMode(QSslSocket::QueryPeer);
    m_Request.setSslConfiguration(sslConfiguration);
}

void JooyaNetwork::initializeRequestHeader(bool withJsonHeader)
{
    //    qCritical()<<"*** Initialization request header ***";
    m_Request.rawHeaderList().clear();
    if(withJsonHeader){
        m_Request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    }
    else {
        m_Request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    }
}
void JooyaNetwork::addTokenToRequestHeader(){
    //ToDo: agar app daraye login user bashad payyeen anjam shavad
    //qDebug()<<"Sender=>"<<sender();
    //    qCritical()<<"=>Initialization request header";
    initializeRequestHeader();
    if(loginInfo()->isLoggedIn()){
        //        qInfo()<<"*** Is adding Token to Request Header ***";
        QString token=loginInfo()->token();
        QString HeaderName="Authorization";
        QString HeaderValue="Bearer "+token;
        m_Request.setRawHeader(HeaderName.toUtf8(),HeaderValue.toUtf8());
    }
}

QUrl JooyaNetwork::setUrl(QString url, bool useIdentityUrl, bool isFullUrl){
    if(url.isEmpty()||url.isNull()){
        return QUrl();
    }
    if(isFullUrl){
        currentUrl=url;
    }
    else {
        if(url.at(0)=="/"){
            url= url.remove(0,1);
        }
        if(useIdentityUrl){
            currentUrl=identityUrl()+"/"+url;
        }
        else {
            currentUrl=baseUrl()+"/"+url;
        }
    }
    QUrl url2(currentUrl);
    qDebug()<<"currentUrl=>"<<currentUrl;
    m_Request.setUrl(url2);
    return url2;
}

QUrl JooyaNetwork::setFullUrl(QString url){
    //    initializeRequestHeader();
    currentUrl=url;
    QUrl url2(currentUrl);
    m_Request.setUrl(url2);
    return url2;
}

QUrl JooyaNetwork::url()
{
    return currentUrl;
}

QNetworkReply* JooyaNetwork::getRequest(QString url, bool useIdentityUrl, bool isFullUrl)
{
    if(url.isEmpty()||url.isNull()){
        return nullptr;
    }
    setIsProcssing(true);
    setUrl(url,useIdentityUrl,isFullUrl);
    QNetworkReply* r= m_NetworkManager.get(m_Request);
    return r;
}

QNetworkReply* JooyaNetwork::deleteRequest(QString url, bool useIdentityUrl)
{
    setIsProcssing(true);
    setUrl(url,useIdentityUrl);
    QNetworkReply* r= m_NetworkManager.deleteResource(m_Request);
    return r;
}

QNetworkReply* JooyaNetwork::postRequest(QString url, QJsonObject obj, bool useIdentityUrl, bool isFullUrl)
{
    setIsProcssing(true);
    setUrl(url,useIdentityUrl,isFullUrl);
    QNetworkReply* r=m_NetworkManager.post(m_Request,QJsonDocument(obj).toJson());
    return r;
}
QNetworkReply* JooyaNetwork::postRequest(QString url, QUrlQuery query, bool useIdentityUrl, bool isFullUrl)
{
    setIsProcssing(true);
    //برای لاگین باید داده ها رو از طریق بدنه فرستاد
    //در جواب سوال زیر نوشته شده است
    //https://stackoverflow.com/questions/37702013/webapi2-0-owin-token-request-using-json
    initializeRequestHeader(false);
    setUrl(url,useIdentityUrl,isFullUrl);

    QNetworkReply* r= m_NetworkManager.post(m_Request,query.toString(QUrl::FullyEncoded).toUtf8());
    return r;
}
QNetworkReply* JooyaNetwork::putRequest(QString url,QJsonObject obj)
{
    setIsProcssing(true);
    setUrl(url);
    QNetworkReply* r=m_NetworkManager.put(m_Request,QJsonDocument(obj).toJson());
    return r;
}

QString JooyaNetwork::removeQuotationMarks(QString m)
{
    if(m[0]=='"')
    {
        m=m.remove(0,1);
    }
    if(m[m.length()-1]=='"')
    {
        m=m.remove(m.length()-1,1);
    }
    return m;
}

void JooyaNetwork::currentReplyFinished(QNetworkReply* r)
{
    checkCommonErrors(r);
    setIsProcssing(false);
    setDisplayCommonErrorMessage(true);
    setOperationType(OperationTypes::OperationTypesEnum::NoOperation);
    emit requestFinished(r->error()==QNetworkReply::NoError);
}

void JooyaNetwork::showMessage(QObject* obj)
{
    QNetworkReply* reply=qobject_cast<QNetworkReply*>(obj);
    showMessage(reply);
}
int JooyaNetwork::getHttpCode(QNetworkReply *reply)
{
    return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
}

void JooyaNetwork::checkCommonErrors(QNetworkReply* r)
{
    int httpCode= getHttpCode(r);
    qDebug()<<"***[ Reply of => "<<r->url().path()<<"(HTTPStatusCode => "<<httpCode<<") ]***";
    if(isAcceptedResposeCode(httpCode)){
        return;
    }
    qWarning()<<"***[ ErrorString => "<<r->errorString()<<" ]***";
    QString m= "";
    if(httpCode==0&& !r->bytesAvailable())
    {
        m = "اتصال اینترنت را بررسی کنید";
        qDebug()<<"NetworkManager::readReplyMessage =>content="<<message()->content();
        qInfo()<<"faild url=> "<<r->url().path();
        emit connectionError();
    }
    else if(httpCode==405)
    {
        if(r->errorString().contains("Method Not Allowed")){
            m = "چنین متدی تعریف نشده است";
        }
        else{
            m = QString("خطای شماره %1 رخ داد").arg(httpCode);
        }
    }
    else if(httpCode==403)//UnAuthorized
    {
        m = "دسترسی غیر مجاز";
        emit unAuthorizedAccess();
    }
    else if(httpCode==404)
    {
        m = "آدرس یا منبع مورد نظر یافت نشد";
    }
    else if(httpCode==500)
    {
        qCritical()<<"Error ==>> "<<r->readAll();
        m = "خطای سرور";
    }
    else
    {
        m = QString("خطای شماره %1 رخ داد").arg(httpCode);
    }
    if(displayCommonErrorMessage()&&!m.isNull()&&!m.isEmpty())
    {
        message()->setContent(m);
    }
}

bool JooyaNetwork::isAcceptedResposeCode(int code)
{
    //           [ OK ]    [ Bad Request ]
    return code == 200 || code==400 ;
}

void JooyaNetwork::showMessage(QNetworkReply *r)
{
    if(!isAcceptedResposeCode(getHttpCode(r))){
        return;
    }
    if(r->error()== QNetworkReply::NoError)
    {
        showOkMessage(r->readAll());
    }
    else
    {
        qDebug()<<"^^^   BadRequest  ^^^";
        showBadMessage(r->readAll());
    }
}

void JooyaNetwork::showBadMessage(QByteArray replyMessage)
{
    QString messageString =replyMessage;
    qDebug()<<"reply.readAll()=> "<<messageString;
    try
    {
        if(replyMessage.isNull()||replyMessage.isEmpty())
        {
            qWarning()<<"reply.readAll()=> was null";

        }
        else if(messageString.contains("message"))
        {
            QJsonDocument doc=QJsonDocument::fromJson(messageString.toUtf8());
            QJsonObject obj=doc.object();
            QJsonValue value=obj.value("message");
            value.toString();
        }
        else {
            message()->setContent(removeQuotationMarks(replyMessage));
        }
    }
    catch(int d)
    {
    }
}
void JooyaNetwork::showOkMessage(QString replyMessage)
{
    try
    {
        if(replyMessage.isNull()||replyMessage.isEmpty())
        {
            message()->setContent("پیام تهی است");
        }
        else
        {
            message()->setContent(removeQuotationMarks(replyMessage),true);
        }
    }
    catch(int d)
    {
    }
}

QNetworkReply* JooyaNetwork::convertToReply(QObject* obj){
    QNetworkReply* reply=qobject_cast<QNetworkReply*>(obj);
    return reply;
}

bool JooyaNetwork::isNotFound(QNetworkReply* r){
    return r->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()==404;
}

WebSocketHandler* JooyaNetwork::m_WebSocketHandler=new WebSocketHandler();

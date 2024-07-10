#include "jooyanetworkengine.h"

JooyaNetworkEngine::JooyaNetworkEngine(QObject *parent) : QObject(parent)
{
    m_IsProccessing=false;
    m_DisplayCommonErrorMessage = true;
    m_OperationType=OperationTypes::OperationTypesEnum::NoOperation;
    m_OperationMessage="";
}

QJsonObject JooyaNetworkEngine::toJson()
{
    return QJsonObject();
}

void JooyaNetworkEngine::fromJson(QJsonObject json)
{
    Q_UNUSED(json);
}

Message *JooyaNetworkEngine::message(){
    return m_Message;
}

JsonUtility* JooyaNetworkEngine::jsonUtility()
{
    return new JsonUtility();
}

DateTimeUtility *JooyaNetworkEngine::dateTimeUtility()
{
    return new DateTimeUtility();
}

//void JooyaNetworkEngine::setMessage(Message* m){
//    m_Message=m;
//}

UserLoginInfo *JooyaNetworkEngine::loginInfo()
{
    return m_loginInfo;
}

AndroidServiceManager *JooyaNetworkEngine::androidService()
{
    return m_AndroidServiceManager;
}

bool JooyaNetworkEngine::isProcessing()
{
    return m_IsProccessing;
}

void JooyaNetworkEngine::setIsProcssing(bool isProcessing)
{
    m_IsProccessing=isProcessing;
    emit isProcessingChanged(m_IsProccessing);
}

bool JooyaNetworkEngine::displayCommonErrorMessage()
{
    return m_DisplayCommonErrorMessage;
}

void JooyaNetworkEngine::setDisplayCommonErrorMessage(bool show)
{
    m_DisplayCommonErrorMessage = show;
}

QString JooyaNetworkEngine::operationMessage()
{
    return m_OperationMessage;
}

void JooyaNetworkEngine::setOperationMessage(QString message)
{
    if(m_OperationMessage!=message){
        m_OperationMessage=message;
        emit operationMessageChanged();
    }
}

OperationTypes::OperationTypesEnum JooyaNetworkEngine::operationType()
{
    return m_OperationType;
}

void JooyaNetworkEngine::setOperationType(OperationTypes::OperationTypesEnum o)
{
    if(m_OperationType!=o){
        m_OperationType=o;
        emit operationTypeChanged();
    }
}

 QString JooyaNetworkEngine::m_BaseUrl="";
 QString JooyaNetworkEngine::m_IdentityUrl="";
 QString JooyaNetworkEngine::m_ClientId="";
 QString JooyaNetworkEngine::m_ApiName="";
 QString JooyaNetworkEngine::m_ClientSecret="";
 QString JooyaNetworkEngine::m_ClientScopes="openid";

 QString JooyaNetworkEngine::baseUrl()
 {
     return m_BaseUrl;
 }

 void JooyaNetworkEngine::setBaseUrl(QString url)
 {
     m_BaseUrl=url;
 }

 QString JooyaNetworkEngine::identityUrl()
 {
     return m_IdentityUrl;
 }

 void JooyaNetworkEngine::setIdentityUrl(QString url)
 {
     m_IdentityUrl=url;
 }

 QString JooyaNetworkEngine::clientId()
 {
     return m_ClientId;
 }

 void JooyaNetworkEngine::setClientId(QString cId)
 {
     if(m_ClientId!=cId){
         m_ClientId=cId;
     }
 }

 QString JooyaNetworkEngine::clientSecret()
 {
     return m_ClientSecret;
 }

 void JooyaNetworkEngine::setClientSecret(QString secret)
 {
     if(m_ClientSecret!=secret){
         m_ClientSecret=secret;
     }
 }

 QString JooyaNetworkEngine::clientScopes()
 {
     return m_ClientScopes;
 }

 void JooyaNetworkEngine::setClientScopes(QString scope)
 {
     if(m_ClientScopes!=scope){
         m_ClientScopes=scope;
     }
 }

 QString JooyaNetworkEngine::apiName()
 {
     return m_ApiName;
 }

 void JooyaNetworkEngine::setApiName(QString name)
 {
     if(m_ApiName!=name){
         m_ApiName=name;
     }
 }

 void JooyaNetworkEngine::appendClientScopes(QString newScope)
 {
     setClientScopes(newScope+" "+clientScopes());
 }

 UserLoginInfo* JooyaNetworkEngine::m_loginInfo=new UserLoginInfo();

 AndroidServiceManager* JooyaNetworkEngine::m_AndroidServiceManager = new AndroidServiceManager();
 FileWatcher* JooyaNetworkEngine::m_FileWather;//=new FileWatcher();


  bool JooyaNetworkEngine::isNetworkIsAccessible=false;

  Message* JooyaNetworkEngine::m_Message=new Message();

#include "loginmanager.h"

LoginManager::LoginManager(QObject *parent) : JooyaNetwork(parent)
{
    m_SmsManager=new SmsManager();
    connect(m_SmsManager,&SmsManager::newSmsReceived,this,&LoginManager::onNewSmsReceived);
}

void LoginManager::login(QString un,QString pass)
{
    if(un.isNull()||un.isEmpty())
    {
        message()->setContent("نام کاربری را وارد کنید");
        return;
    }
    if(pass.isNull()||pass.isEmpty())
    {
        message()->setContent("کلمه عبور را وارد کنید");
        return;
    }
    setIsProcssing(true);

    QUrlQuery postData;
    postData.addQueryItem("grant_type","password");
    postData.addQueryItem("username",un.trimmed());
    postData.addQueryItem("password",pass);
    postData.addQueryItem("scope",clientScopes());
    postData.addQueryItem("client_id",clientId());
    postData.addQueryItem("client_secret",clientSecret());
    QNetworkReply* reply=postRequest("connect/token",postData,true,false);
    connect(reply,SIGNAL(finished()) ,this,SLOT(loginFinished()));
}

void LoginManager::login(QString code)
{
    if(code.isNull()||code.isEmpty())
    {
        message()->setContent("کد فعالسازی را وارد کنید");
        return;
    }
    setIsProcssing(true);

    QUrlQuery postData;
    postData.addQueryItem("grant_type","hybrid");
//    postData.addQueryItem("code",code);
    postData.addQueryItem("scope",clientScopes());
    postData.addQueryItem("client_id",clientId());
    postData.addQueryItem("client_secret",clientSecret());
    postData.addQueryItem("responsetype","code");

    QNetworkReply* reply=postRequest("connect/authorize",postData,true,false);
    connect(reply,SIGNAL(finished()) ,this,SLOT(loginFinished()));
}

void LoginManager::loginUN(QString un,QString pass,QString captha,QString capthaHash)
{
    qDebug()<<"LoginManager::loginUN(QString un,QString pass)";
    if(un.isNull()||un.isEmpty())
    {
        message()->setContent("نام کاربری را وارد کنید");
        return;
    }
    if(pass.isNull()||pass.isEmpty())
    {
        message()->setContent("کلمه عبور را وارد کنید");
        return;
    }
    else if(captha.isNull()||captha.isEmpty())
    {
        message()->setContent("تصویر امنیتی را وارد کنید");
        return;
    }
    QJsonObject jObj;
    jObj.insert("username",un);
    jObj.insert("password",pass);
    jObj.insert("captha",captha.trimmed());
    jObj.insert("capthaHash",capthaHash);
    QNetworkReply* reply=postRequest("api/User/Login",jObj,true);
    qDebug()<<"url=>"<<identityUrl();
    connect(reply,SIGNAL(finished()) ,this,SLOT(loginFinished()));
}
void LoginManager::loginFinished()
{
    QNetworkReply* reply=qobject_cast<QNetworkReply*>(sender());
    if(reply->error()== QNetworkReply::NoError)
    {
        qInfo()<<"NoError";
        qDebug()<<"=>Read and save Token";
        readAndSaveToken(reply->readAll());
        qCritical()<<"=> Add token to request(Deleted)";
//        addTokenToRequestHeader();
        qDebug()<<"Setting login state to LoggedIn";
        loginInfo()->setState(LoginStates::LoginStatesEnum::LoggedIn);
    }
    else
    {
        qCritical()<<"Error";
        QJsonObject jsonResponse=jsonUtility()->convertToJsonObject(reply);
        QString grantMessage=jsonResponse.value("error_description").toString();
        if(grantMessage=="invalid_username_or_password"){
            message()->setContent("نام کاربری یا کلمه عبور اشتباه است");
        }
        else{
            showMessage(reply);
        }
    }
}

void LoginManager::logout()
{
    qWarning()<<"#########################################";
    qWarning()<<"############# LOGOUT ####################";
    qWarning()<<"#########################################";

    loginInfo()->setToken("");
    qCritical()<<"=>Initialize request header(Deleted)";
//    initializeRequestHeader();
    loginInfo()->setState(LoginStates::LoginStatesEnum::LoggedOut);
}

void LoginManager::signUp(QString un,QString pass,QString passRepeat,QString captha,QString capthaHash)
{
    if(isProcessing()){
        return;
    }
    if(un.isNull()||un.isEmpty())
    {
        message()->setContent("نام کاربری را وارد کنید");
        return;
    }
    if(pass.isNull()||pass.isEmpty())
    {
        message()->setContent("کلمه عبور را وارد کنید");
        return;
    }
    if(passRepeat.isNull()||passRepeat.isEmpty())
    {
        message()->setContent("تکرار کلمه عبور را وارد کنید");
        return;
    }
    if(passRepeat!=pass)
    {
        message()->setContent("کلمه های عبور وارده شده یکسان نیستند");
        return;
    }
    if(captha.isNull()||captha.isEmpty())
    {
        message()->setContent("تصویر امنیتی را وارد کنید");
        return;
    }
    setIsProcssing(true);

    QJsonObject jObj;
    jObj.insert("UserName",un.trimmed());
    jObj.insert("Password",pass);
    jObj.insert("PasswordRepeat",passRepeat);
    jObj.insert("Captha",captha.trimmed());
    jObj.insert("CapthaHash",capthaHash);

    QNetworkReply* reply= postRequest("api/User",jObj,true);
    connect(reply,SIGNAL(finished()) ,this,SLOT(signUpFinished()));
}
void LoginManager::signUpFinished()
{
    QNetworkReply* r=qobject_cast<QNetworkReply*>(sender());
    if(r->error()== QNetworkReply::NoError)
    {
        emit signupSucceed();
    }
    showMessage(r);
}

void LoginManager::signUp(QString phoneNumber,bool hasActivationCode)
{
    if(phoneNumber.isNull()||phoneNumber.isEmpty())
    {
        message()->setContent("شماره تلفن همراه را وارد کنید");
        return;
    }
    qDebug()<<"phoneNumber=>"<<phoneNumber;
    QJsonObject jObj;
    jObj.insert("phoneNumber",phoneNumber);
    jObj.insert("hasActivationCode",hasActivationCode);

    QNetworkReply* reply= postRequest("api/User/SignupPhone",jObj,true);
    connect(reply,SIGNAL(finished()) ,this,SLOT(signUpPhoneFinished()));
}

void LoginManager::signUpPhoneFinished()
{
    QNetworkReply* reply=qobject_cast<QNetworkReply*>(sender());
    if(reply->error()== QNetworkReply::NoError)
    {
        emit signUpPhoneSucceed(readResult(reply->readAll()));
    }
    else
    {
        showMessage(reply);
    }
}

void LoginManager::onNewSmsReceived(const QString &sms)
{
    qInfo()<<"extract activation code from new sms";
    QStringList list= sms.split(" ");
    for (int i = 0; i < list.count(); ++i) {
        if(list.at(i).length()==6){
//            QRegularExpression rx("d(\\d+)");
//            QRegularExpressionMatchIterator ii = rx.globalMatch(list.at(i));
//            while (ii.hasNext()) {
//                QRegularExpressionMatch match = ii.next();
//                QString activationCode = match.captured(1);
//                qInfo()<<i<<"=> "<<list.at(i)<<" <= Matched";
//            }
            int ac=list.at(i).toInt();
            if(ac){
                 qInfo()<<i<<"=> "<<list.at(i)<<" <= Matched";
                 emit activationCodeReceived(list.at(i));
            }
            else{
                qInfo()<<i<<"=> "<<list.at(i)<<" <= Not Matched";
            }
        }
        else{
            qInfo()<<i<<"=> "<<list.at(i);
        }
    }
}

SignupResult* LoginManager::readResult(QByteArray r)
{
    QJsonDocument doc=QJsonDocument::fromJson(r);
    QJsonObject obj=doc.object();
    SignupResult* result=new SignupResult();
    result->setMessage(obj.value("message").toString());
    result->setWaitNextSms(obj.value("waiteTime").toInt());
    result->setPhoneNumber(obj.value("phoneNumber").toString());
    qDebug()<<"waitNext=>"<<result->waitNextSms();
    return result;
}

void LoginManager::activate(QString phoneNumber,QString activationCode)
{
    if(phoneNumber.isNull()||phoneNumber.isEmpty())
    {
        message()->setContent("شماره تلفن خالی است");
        return;
    }
    if(activationCode.isNull()||activationCode.isEmpty())
    {
        message()->setContent("کد فعالسازی را وارد کنید");
        return;
    }
    setIsProcssing(true);
    QJsonObject jObj;
    jObj.insert("phoneNumber",phoneNumber);
    jObj.insert("activationCode",activationCode);

    jObj.insert("clientId",clientId());
    jObj.insert("apiName",apiName());

    qCritical()<<"clientId=> "<<clientId();
    QNetworkReply* reply= postRequest("api/User/Activate",jObj,true);
    connect(reply,SIGNAL(finished()) ,this,SLOT(activateFinished()));
}
void LoginManager::activateFinished(){
    QNetworkReply* reply=convertToReply(sender());
    if(reply->error()== QNetworkReply::NoError)
    {
        readAndSaveToken(reply->readAll());
//        addTokenToRequestHeader();
        loginInfo()->setState(LoginStates::LoginStatesEnum::LoggedIn);
    }
    else
    {
        showMessage(reply);
    }
    setIsProcssing(false);
}
void LoginManager::readAndSaveToken(QByteArray jsonToken)
{
    QJsonObject tokenobj=jsonUtility()->convertToJsonObject(jsonToken);
    QString to= tokenobj.value("access_token").toString();
    //qWarning()<<"save the token=>"<<to;
    loginInfo()->setToken(to);
}

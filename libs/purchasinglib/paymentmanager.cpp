#include "paymentmanager.h"

PaymentManager::PaymentManager(QObject *parent) : JooyaNetwork(parent)
{
    m_IsResultPage=false;
    m_RefId="";
    m_Url="";
    m_LoadProgress=0;
    m_OrderId=0;

    m_PaymentResult=new PaymentResult(false,"در حال دریافت نتیجه تراکنش");
}

void PaymentManager::pay()
{
    if(orderId()<=0){
        message()->setContent("شناسه سفارش معتبر نیست");
        return;
    }
    setIsProcssing(true);
    QNetworkReply* reply=getRequest(QString("api/Order/Pay/%1").arg(orderId()));
    connect(reply,SIGNAL(finished()),this,SLOT(reqPayFinished()));
}

bool PaymentManager::isStartedLoadResultPage()
{
    return m_IsResultPage;
}

void PaymentManager::reqPayFinished(){
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonDocument doc=QJsonDocument::fromJson(r->readAll());
        QJsonObject obj=doc.object();
        m_RefId= obj.value("refId").toString();
        qDebug()<<"RefId="<<m_RefId;
        //TODO: Change this after creating new branch from master branch
        emit payRequestSucceed(true,"https://jooyabash.ir/order/PayFromApp/"+m_RefId);
    }
    else {
        showMessage(r);
        emit payRequestSucceed(false,"");
    }
    setIsProcssing(false);
}

PaymentResult *PaymentManager::paymentResult()
{
    return m_PaymentResult;
}

void PaymentManager::setPaymentResult(PaymentResult *pr)
{
    m_PaymentResult=pr;
    emit paymentResultChanged(pr);
}

QString PaymentManager::url()
{
    return m_Url;
}

void PaymentManager::setUrl(QString url)
{
    if(m_Url!=url){
        m_Url=url;
        QString temp=m_Url.toLower();
        if(temp.contains("jooyabash.ir/order/result"))
        {
            qDebug()<<"====>> Url of result page=> "<<m_Url;
            m_IsResultPage=true;
            emit resultPageStartToLoad();
        }
        else if(temp.contains("bpm.shaparak.ir/pgwchannel/payment.mellat")){
            qDebug()<<"====>> Url Of shaparak=> "<<m_Url;
            m_IsBankPage=true;
        }
        else {
            qDebug()<<"====>> Url Of Other=> "<<m_Url;
            m_IsResultPage=false;
            m_IsBankPage=false;
        }
        emit urlChanged();
    }
}

int PaymentManager::loadProgress()
{
    return m_LoadProgress;
}

void PaymentManager::setLoadProgress(int lp)
{
    if(m_LoadProgress!=lp){
        m_LoadProgress=lp;
        qDebug()<<"LoadProgress="<<lp;

        if(m_IsResultPage&&lp==100){
            qDebug()<<"emit resultPageLoaded();";
            emit resultPageLoaded();
        }
        else if (m_IsBankPage&&lp==100) {
            qDebug()<<"emit bankPageLoaded();";
            emit bankPageLoaded();
        }
        emit loadProgressChanged();
    }
}

int PaymentManager::orderId()
{
    return m_OrderId;
}

void PaymentManager::setOrderId(int oId)
{
    if(m_OrderId!=oId){
        m_OrderId=oId;
        emit orderIdChanged();
    }
}

bool PaymentManager::isPageLoading()
{
    return m_IsPageLoading;
}

void PaymentManager::setIsPageLoading(bool loading)
{
    m_IsPageLoading=loading;
    emit isPageLoadingChanged();

    qDebug()<<"||| setIsPageLoading";
    if(m_IsResultPage&&!loading){
        qDebug()<<"emit resultPageLoaded();";
        emit resultPageLoaded();
    }
    else if (m_IsBankPage&&!loading) {
        qDebug()<<"emit bankPageLoaded();";
        emit bankPageLoaded();
    }

}

void PaymentManager::getResult(){
    qDebug()<<"is getting result";
    setIsProcssing(true);
    QString url=QString("api/Order/Result/%1").arg(orderId());
    qDebug()<<url;
    QNetworkReply* reply=getRequest(url);
    connect(reply,SIGNAL(finished()),this,SLOT(getResultFinished()));
}
void PaymentManager::getResultFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        qDebug()<<"get result finieshd not error";
        PaymentResult* pp= readPaymentResult(r->readAll());
        setPaymentResult(pp);
        emit paymentFinished(pp->paid());
        if(!pp->paid()){
            message()->setContent(pp->message());
        }
    }
    else {
        qDebug()<<"get result finieshd error";
        showMessage(r);
        emit paymentFinished(false);
    }
    setIsProcssing(false);
}

PaymentResult* PaymentManager::readPaymentResult(QString r){
    QJsonDocument doc=QJsonDocument::fromJson(r.toUtf8());
    QJsonObject obj=doc.object();
    PaymentResult* pp=new PaymentResult(obj.value("paid").toBool(),obj.value("trackingCode").toString());
    return pp;
}

void PaymentManager::getTransactions(){
    qDebug()<<"getTransactions";
    setIsProcssing(true);
//    if(isProcessing())
//    {
//        qDebug()<<"=>Stopped IsProcessing";
//        return;
//    }
    qDebug()<<"=>started";
    QString url=QString("api/Order/Transactions/%1").arg(orderId());
    QNetworkReply* reply=getRequest(url);
    connect(reply,SIGNAL(finished()),this,SLOT(reqGetTransactionsFinished()));
}

void PaymentManager::reqGetTransactionsFinished(){
    QNetworkReply* r=convertToReply(sender());
    qDebug()<<"reqGetTransactionsFinished";
    if(r->error()==QNetworkReply::NoError){
        qDebug()<<"=>NoError";

        readTransactions(r->readAll());
    }
    else {
        qDebug()<<"=>Width Error";
        showMessage(r);
    }
    setIsProcssing(false);
}

void PaymentManager::readTransactions(QString r){
    qDebug()<<"Transacs=>>"<<r;
    QJsonDocument doc=QJsonDocument::fromJson(r.toUtf8());
    QJsonArray array= doc.array();
    for (int i = 0; i < array.count(); ++i) {
        QJsonValue val=array.at(i);
        QJsonObject obj=val.toObject();
        m_Transactions.add(new Transaction(obj.value("id").toString(),obj.value("date").toString(),obj.value("resultMessage").toString(),obj.value("shenasehErjaTarakonesh").toString(),obj.value("dargah").toString(),obj.value("creditCardNumber").toString()));
    }
}
TransactionListModel* PaymentManager::transactions(){
    return &m_Transactions;
}

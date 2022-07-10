#ifndef PAYMENTMANAGER_H
#define PAYMENTMANAGER_H

#include <QObject>
#include<jooyanetwork.h>
#include<QNetworkReply>
#include<qjsondocument.h>
#include<qjsonobject.h>
#include<paymentresult.h>
#include<QJsonArray>
#include<transactionlistmodel.h>

class PaymentManager : public JooyaNetwork
{
    Q_OBJECT
    Q_PROPERTY(TransactionListModel* transactions READ transactions CONSTANT)

    Q_PROPERTY(PaymentResult* paymentResult READ paymentResult WRITE setPaymentResult NOTIFY paymentResultChanged)

    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(int loadProgress READ loadProgress WRITE setLoadProgress NOTIFY loadProgressChanged)

    Q_PROPERTY(int orderId READ orderId WRITE setOrderId NOTIFY orderIdChanged)
    Q_PROPERTY(bool isPageLoading READ isPageLoading WRITE setIsPageLoading NOTIFY isPageLoadingChanged)

public:
    explicit PaymentManager(QObject *parent = nullptr);

    Q_INVOKABLE void getResult();
    Q_INVOKABLE void pay();
    Q_INVOKABLE bool isStartedLoadResultPage();

    PaymentResult* paymentResult();
    void setPaymentResult(PaymentResult* pr);

    QString url();
    void setUrl(QString url);

    int loadProgress();
    void setLoadProgress(int lp);

    int orderId();
    void setOrderId(int oId);

    bool isPageLoading();
    void setIsPageLoading(bool loading);

    void readTransactions(QString r);
    Q_INVOKABLE void getTransactions();
    TransactionListModel *transactions();
signals:
    void payRequestSucceed(bool succeed, QString argUrl);
    void paymentResultChanged(PaymentResult* argPaymentResult);

    void urlChanged();
    void loadProgressChanged();

    void resultPageLoaded();
    void resultPageStartToLoad();
    void bankPageLoaded();
    void orderIdChanged();

    void paymentFinished(bool argSucceed);
    void isPageLoadingChanged();

private slots:
    void reqPayFinished();

    void getResultFinished();
    void reqGetTransactionsFinished();
private:
    PaymentResult* m_PaymentResult;
    QString m_RefId;

    QString m_Url;
    bool m_IsResultPage;
    bool m_IsBankPage;
    int m_LoadProgress;
    bool m_IsPageLoading;

    PaymentResult *readPaymentResult(QString r);
    TransactionListModel m_Transactions;
    int m_OrderId;
};

#endif // PAYMENTMANAGER_H

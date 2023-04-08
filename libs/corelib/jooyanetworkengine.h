#ifndef JOOYANETWORKENGINE_H
#define JOOYANETWORKENGINE_H

#include <QObject>
#include<QDebug>
#include<QTimer>
#include<message.h>
#include<QQmlEngine>
#include<userlogininfo.h>
#include<QJsonObject>
#include<operationtypes.h>
#include<filewatcher.h>
#include<jsonutility.h>
#include<datetimeutility.h>
#include<androidservicemanager.h>

class JooyaNetworkEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Message* message READ message CONSTANT)
    Q_PROPERTY(bool isProcessing READ isProcessing WRITE setIsProcssing NOTIFY isProcessingChanged)
    Q_PROPERTY(QString operationMessage READ operationMessage WRITE setOperationMessage NOTIFY operationMessageChanged)

    Q_PROPERTY(UserLoginInfo* loginInfo READ loginInfo CONSTANT)
    Q_PROPERTY(OperationTypes::OperationTypesEnum operationType READ operationType WRITE setOperationType NOTIFY operationTypeChanged)
public:
    explicit JooyaNetworkEngine(QObject *parent = nullptr);

    virtual QJsonObject toJson();
    virtual void fromJson(QJsonObject json);

    Message* message();
//    void setMessage(Message* m);
    static Message* m_Message;

    JsonUtility *jsonUtility();
    DateTimeUtility *dateTimeUtility();

    UserLoginInfo* loginInfo();
    static UserLoginInfo* m_loginInfo;
    static AndroidServiceManager* m_AndroidServiceManager;
    AndroidServiceManager* androidService();
    static FileWatcher* m_FileWather;

    static bool isNetworkIsAccessible;

    bool isProcessing();
    void setIsProcssing(bool isProcessing);

    bool displayCommonErrorMessage();
    void setDisplayCommonErrorMessage(bool show);

    QString operationMessage();
    void setOperationMessage(QString message);

    OperationTypes::OperationTypesEnum operationType();
    void setOperationType(OperationTypes::OperationTypesEnum o);

    QString baseUrl();
    void setBaseUrl(QString url);

    QString identityUrl();
    void setIdentityUrl(QString url);

    QString clientId();
    void setClientId(QString cId);

    QString clientSecret();
    void setClientSecret(QString secret);

    QString clientScopes();
    void setClientScopes(QString scope);

    QString apiName();
    void setApiName(QString name);

    void appendClientScopes(QString newScope);
//    static void initialize(QString newScope);

signals:    
//    void messageChanged();
    void isProcessingChanged(bool isProcessing);
    void operationMessageChanged();
    void operationTypeChanged();
public slots:
private:
    static QString m_BaseUrl;
    static QString m_IdentityUrl;
    static QString m_ClientId;
    static QString m_ClientSecret;
    static QString m_ClientScopes;
    static QString m_ApiName;
    bool m_IsProccessing;
    bool m_DisplayCommonErrorMessage;
    QString m_OperationMessage;
    OperationTypes::OperationTypesEnum m_OperationType;
};

#endif // JOOYANETWORKENGINE_H


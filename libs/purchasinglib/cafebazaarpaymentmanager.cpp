#include "cafebazaarpaymentmanager.h"

CafebazaarPaymentManager *CafebazaarPaymentManager::m_instance = nullptr;

#if defined(Q_OS_ANDROID)
// Forward declaration of the JNI callback registered in registerNativesMethod().
static void staticPurchaseResultReceived(JNIEnv *env, jobject /*thiz*/,
                                         jstring token, jstring sku,
                                         jboolean success, jstring message);
#endif

CafebazaarPaymentManager::CafebazaarPaymentManager(QObject *parent)
    : JooyaNetwork(parent)
{
    m_instance = this;
    m_paymentResult = new PaymentResult(false, "در حال دریافت نتیجه تراکنش");
    m_paymentResult->setParent(this);
}

PaymentResult* CafebazaarPaymentManager::paymentResult()
{
    return m_paymentResult;
}

int CafebazaarPaymentManager::orderId() const
{
    return m_orderId;
}

void CafebazaarPaymentManager::setOrderId(int orderId)
{
    if (m_orderId != orderId)
    {
        m_orderId = orderId;
        emit orderIdChanged();
    }
}

void CafebazaarPaymentManager::registerNativesMethod()
{
#if defined(Q_OS_ANDROID)
    JNINativeMethod methods[] {
        {"sendPurchaseResultToQtApp", "(Ljava/lang/String;Ljava/lang/String;ZLjava/lang/String;)V",
         reinterpret_cast<void *>(staticPurchaseResultReceived)},
    };
    QString className = PackageInfoManager::getPackageName() + "CafeBazaarManager";
    QJniObject javaClass(className.toUtf8());
    QJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
#else
    Q_UNUSED(this);
#endif
}

void CafebazaarPaymentManager::loadSku()
{
    if (m_orderId <= 0)
    {
        emit purchaseFailed("شناسه سفارش معتبر نیست");
        return;
    }
    setIsProcssing(true);
    QNetworkReply* reply = getRequest(QString("api/Order/PayCafebazaar/%1").arg(m_orderId));
    connect(reply, SIGNAL(finished()), this, SLOT(loadSkuFinished()));
}

void CafebazaarPaymentManager::loadSkuFinished()
{
    QNetworkReply* r = convertToReply(sender());
    if (r->error() == QNetworkReply::NoError)
    {
        QJsonDocument doc = QJsonDocument::fromJson(r->readAll());
        QJsonObject obj = doc.object();
        m_sku = obj.value("sku").toString();
        emit skuReceived(m_sku);
    }
    else
    {
        showMessage(r);
        emit purchaseFailed("دریافت اطلاعات محصول از سرور ممکن نشد");
    }
    setIsProcssing(false);
}

void CafebazaarPaymentManager::startPurchase(QString sku)
{
#if defined(Q_OS_ANDROID)
    QString className = PackageInfoManager::getPackageName() + "CafeBazaarManager";
    QJniObject::callStaticMethod<void>(className.toUtf8(),
                                       "startPurchase",
                                       "(Landroid/content/Context;Ljava/lang/String;)V",
                                       QNativeInterface::QAndroidApplication::context(),
                                       QJniObject::fromString(sku).object<jstring>());
#else
    Q_UNUSED(sku);
    emit purchaseFailed("پرداخت کافه بازار فقط روی اندروید قابل استفاده است");
#endif
}

void CafebazaarPaymentManager::verifyPurchase(QString purchaseToken, QString sku)
{
    if (m_orderId <= 0)
    {
        emit purchaseVerified(false, "شناسه سفارش معتبر نیست");
        return;
    }
    setIsProcssing(true);
    QJsonObject obj;
    obj.insert("orderId", m_orderId);
    obj.insert("purchaseToken", purchaseToken);
    obj.insert("productSku", sku.isEmpty() ? m_sku : sku);
    QNetworkReply* reply = postRequest("api/Order/VerifyCafebazaar", obj);
    connect(reply, SIGNAL(finished()), this, SLOT(verifyPurchaseFinished()));
}

void CafebazaarPaymentManager::verifyPurchaseFinished()
{
    QNetworkReply* r = convertToReply(sender());
    if (r->error() == QNetworkReply::NoError)
    {
        QJsonDocument doc = QJsonDocument::fromJson(r->readAll());
        QJsonObject obj = doc.object();
        bool paid = obj.value("paid").toBool();
        QString trackingCode = obj.value("trackingCode").toString();
        QString message = obj.value("message").toString();

        m_paymentResult->setPaid(paid);
        m_paymentResult->setTrackingCode(trackingCode);
        if (!message.isEmpty())
        {
            // keep the friendly message from the server
            QMetaObject::invokeMethod(m_paymentResult, "setMessage", Q_ARG(QString, message));
        }
        emit paymentResultChanged(m_paymentResult);
        emit purchaseVerified(paid, message);
    }
    else
    {
        showMessage(r);
        emit purchaseVerified(false, "تأیید خرید در سرور ممکن نشد");
    }
    setIsProcssing(false);
}

#if defined(Q_OS_ANDROID)
// Registered native callback invoked from CafeBazaarManager.java
// signature: sendPurchaseResultToQtApp(String token, String sku, boolean success, String message)
static void staticPurchaseResultReceived(JNIEnv *env, jobject /*thiz*/,
                                         jstring token, jstring sku,
                                         jboolean success, jstring message)
{
    QString purchaseToken = token ? env->GetStringUTFChars(token, nullptr) : QString();
    QString skuStr = sku ? env->GetStringUTFChars(sku, nullptr) : QString();
    QString msg = message ? env->GetStringUTFChars(message, nullptr) : QString();

    if (CafebazaarPaymentManager::instance() == nullptr)
    {
        qWarning() << "***[ jooya no instance of CafebazaarPaymentManager ]***";
        return;
    }
    if (success)
    {
        emit CafebazaarPaymentManager::instance()->purchaseSucceeded(purchaseToken, skuStr);
        // Validate server-side right away.
        CafebazaarPaymentManager::instance()->verifyPurchase(purchaseToken, skuStr);
    }
    else
    {
        emit CafebazaarPaymentManager::instance()->purchaseFailed(
            msg.isEmpty() ? "پرداخت در کافه بازار ناموفق بود" : msg);
    }
}
#endif

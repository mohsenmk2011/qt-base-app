#include "jooyaandroidcontext.h"

JooyaAndroidContext::JooyaAndroidContext(QObject *parent) : QObject(parent)
{

}

QString JooyaAndroidContext::packageName()
{
#if defined(Q_OS_ANDROID)
    QAndroidJniObject result = QtAndroid::androidContext().callObjectMethod("getPackageName","");
    return result.toString();
#else
    return "";
#endif
}

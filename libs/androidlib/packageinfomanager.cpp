#include "packageinfomanager.h"

PackageInfoManager::PackageInfoManager(QObject *parent)
    : QObject{parent}
{

}

QString PackageInfoManager::getAppSign()
{
    qInfo()<<"is going to get the application sign";
#if defined(Q_OS_ANDROID)
    {
        QJniEnvironment env;
        QJniObject activity = QJniObject::callStaticObjectMethod("org/qtproject/qt/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
        if (activity.isValid())
        {
            QJniObject context = QNativeInterface::QAndroidApplication::context();
            QString className= QString("org/jooya/jooyaqtapplication/PackageinfoManager");


            QJniObject  t= QJniObject::callStaticObjectMethod(className.toStdString().c_str(),"getAppSign","(Landroid/content/Context;)Ljava/lang/String;", context.object<jobject>());

            if (env->ExceptionCheck()) {
                env->ExceptionClear();
            }
            return t.toString();
        }
    }
#elif defined(Q_OS_LINUX)
    {
        qWarning()<<"is not implemented in linux";
    }
#elif defined(Q_OS_WIN32)
    {
        qDebug()<<"";

    }
#endif
    return "";
}

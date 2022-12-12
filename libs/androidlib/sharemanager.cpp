#include "sharemanager.h"

ShareManager::ShareManager(QObject *parent)
    : QObject{parent}
{

}

void ShareManager::share(QString message)
{
    qInfo()<<"share this message=> "<<message;
#if defined(Q_OS_ANDROID)
    {
    QAndroidJniEnvironment _env;
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (_env->ExceptionCheck()) {
        _env->ExceptionClear();
    }
    if (activity.isValid() )
    {
        QAndroidJniObject::callStaticMethod<void>("org/jooya/jooyaqtapplication/ShareManager","share","(Landroid/app/Activity;Ljava/lang/String;)V",activity.object<jobject>(),QAndroidJniObject::fromString(message).object<jstring>());
        if (_env->ExceptionCheck()) {
            _env->ExceptionClear();
        }
    }
    }
#elif defined(Q_OS_LINUX)
    {
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(message);
    }
#elif defined(Q_OS_WIN32)
    {
        qDebug()<<"";

    }
#endif
}

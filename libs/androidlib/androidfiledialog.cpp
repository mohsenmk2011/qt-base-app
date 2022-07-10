#include "androidfiledialog.h"

#if defined(Q_OS_ANDROID)
AndroidFileDialog::AndroidFileDialog(QObject *parent) : QObject(parent)
{
    receiver = new ResultReceiver(this);
}

AndroidFileDialog::~AndroidFileDialog()
{
    delete receiver;
}

bool AndroidFileDialog::provideExistingFileName()
{
    //    QAndroidJniObject ACTION_GET_CONTENT = QAndroidJniObject::fromString("android.intent.action.GET_CONTENT");
    //    QAndroidJniObject intent("android/content/Intent");
    //    if (ACTION_GET_CONTENT.isValid() && intent.isValid()) {
    //        intent.callObjectMethod("setAction", "(Ljava/lang/String;)Landroid/content/Intent;", ACTION_GET_CONTENT.object<jstring>());
    //        intent.callObjectMethod("setType", "(Ljava/lang/String;)Landroid/content/Intent;", QAndroidJniObject::fromString("image/jpeg").object<jstring>());
    //        QtAndroid::startActivity(intent.object<jobject>(), EXISTING_FILE_NAME_REQUEST, receiver);
    //        return true;
    //    } else {
    //        return false;
    //    }

    QAndroidJniObject ACTION_PICK = QAndroidJniObject::getStaticObjectField("android/content/Intent", "ACTION_PICK", "Ljava/lang/String;");
    QAndroidJniObject EXTERNAL_CONTENT_URI = QAndroidJniObject::getStaticObjectField("android/provider/MediaStore$Images$Media", "EXTERNAL_CONTENT_URI", "Landroid/net/Uri;");

    QAndroidJniObject intent=QAndroidJniObject("android/content/Intent", "(Ljava/lang/String;Landroid/net/Uri;)V", ACTION_PICK.object<jstring>(), EXTERNAL_CONTENT_URI.object<jobject>());

    if (ACTION_PICK.isValid() && intent.isValid())
    {
        intent.callObjectMethod("setType", "(Ljava/lang/String;)Landroid/content/Intent;", QAndroidJniObject::fromString("image/*").object<jstring>());
        QtAndroid::startActivity(intent.object<jobject>(), 101, receiver);
        qDebug() << "OK";
    }
    else
    {
        qDebug() << "ERRO";
    }

}

void AndroidFileDialog::emitAccepted(QString result)
{
    emit accepted(result);
}
void AndroidFileDialog::emitRejected()
{
    emit rejected();
}


AndroidFileDialog::ResultReceiver::ResultReceiver(AndroidFileDialog *dialog)
{
    _dialog=dialog;
}

AndroidFileDialog::ResultReceiver::~ResultReceiver()
{

}

void AndroidFileDialog::ResultReceiver::handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data)
{
    jint RESULT_OK = QAndroidJniObject::getStaticField<jint>("android/app/Activity", "RESULT_OK");
    if (receiverRequestCode == 101 && resultCode == RESULT_OK)
    {
        QAndroidJniObject uri = data.callObjectMethod("getData", "()Landroid/net/Uri;");
        QAndroidJniObject dadosAndroid = QAndroidJniObject::getStaticObjectField("android/provider/MediaStore$MediaColumns", "DATA", "Ljava/lang/String;");
        QAndroidJniEnvironment env;
        jobjectArray projecao = (jobjectArray)env->NewObjectArray(1, env->FindClass("java/lang/String"), NULL);
        jobject projacaoDadosAndroid = env->NewStringUTF(dadosAndroid.toString().toStdString().c_str());
        env->SetObjectArrayElement(projecao, 0, projacaoDadosAndroid);
        QAndroidJniObject contentResolver = QtAndroid::androidActivity().callObjectMethod("getContentResolver", "()Landroid/content/ContentResolver;");
        QAndroidJniObject cursor = contentResolver.callObjectMethod("query", "(Landroid/net/Uri;[Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;)Landroid/database/Cursor;", uri.object<jobject>(), projecao, NULL, NULL, NULL);
        jint columnIndex = cursor.callMethod<jint>("getColumnIndex", "(Ljava/lang/String;)I", dadosAndroid.object<jstring>());
        cursor.callMethod<jboolean>("moveToFirst", "()Z");
        QAndroidJniObject resultado = cursor.callObjectMethod("getString", "(I)Ljava/lang/String;", columnIndex);
        QString imagemCaminho = "file://" + resultado.toString();

        _dialog->emitAccepted(imagemCaminho);
    }
    else
    {

        _dialog->emitAccepted("");
        qDebug() << "Caminho errado";
    }
}
//void AndroidFileDialog::ResultReceiver::handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data)
//{
//    jint RESULT_OK = QAndroidJniObject::getStaticField<jint>("android/app/Activity", "RESULT_OK");
//    qDebug()<<"result code="<<resultCode;
//    if (receiverRequestCode == EXISTING_FILE_NAME_REQUEST && resultCode == RESULT_OK) {
//        QAndroidJniObject uri = data.callObjectMethod("getData", "()Landroid/net/Uri;");
//        QString path = uriToPath(uri,data);
//        qDebug()<<"path="<<path;
//        _dialog->emitExistingFileNameReady(path);
//    } else {
//        _dialog->emitExistingFileNameReady(QString());
//    }
//}

QString AndroidFileDialog::ResultReceiver::uriToPath(QAndroidJniObject uri, const QAndroidJniObject &data)
{
    qDebug()<<"I am here frsfwe22222";
    if (uri.toString().startsWith("file:", Qt::CaseInsensitive)) {
        return uri.callObjectMethod("getPath", "()Ljava/lang/String;").toString();
    }
    else {
        qDebug()<<"I am here 2";
        QAndroidJniObject contentResolver = QtAndroid::androidActivity().callObjectMethod("getContentResolver", "()Landroid/content/ContentResolver;");
        QAndroidJniObject cursor = contentResolver.callObjectMethod("query", "(Landroid/net/Uri;[Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;)Landroid/database/Cursor;", uri.object<jobject>(), 0, 0, 0, 0);
        QAndroidJniObject DATA = QAndroidJniObject::fromString("_data");
        jint columnIndex = cursor.callMethod<jint>("getColumnIndexOrThrow", "(Ljava/lang/String;)I", DATA.object<jstring>());
        cursor.callMethod<jboolean>("moveToFirst", "()Z");
        QAndroidJniObject result = cursor.callObjectMethod("getString", "(I)Ljava/lang/String;", columnIndex);
        return result.isValid() ? result.toString() : QString();
    }
}
#else
AndroidFileDialog::AndroidFileDialog(QObject *parent) : QObject(parent)
{
}

bool AndroidFileDialog::provideExistingFileName()
{
    return false;
}
#endif

#ifndef ANDROIDFILEDIALOG_H
#define ANDROIDFILEDIALOG_H

#include <QObject>
#include<qdebug.h>

#if defined(Q_OS_ANDROID)
#include<QAndroidJniObject>
#include<QtAndroid>
#include<QAndroidActivityResultReceiver>
#include<QAndroidJniEnvironment>

class AndroidFileDialog : public QObject
{
    Q_OBJECT
public:
    explicit AndroidFileDialog(QObject *parent = nullptr);
    virtual ~AndroidFileDialog();
    Q_INVOKABLE bool provideExistingFileName();

signals:
    void accepted(QString fileUrl);
    void rejected();
public slots:

private:
    class ResultReceiver:public QAndroidActivityResultReceiver
    {
        AndroidFileDialog *_dialog;

    public:
        ResultReceiver(AndroidFileDialog *dialog);

        virtual ~ResultReceiver();
        void handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data);
        QString uriToPath(QAndroidJniObject uri, const QAndroidJniObject &data);
    };
    static const int EXISTING_FILE_NAME_REQUEST = 1;
    ResultReceiver* receiver;
    void emitAccepted(QString result);
    void emitRejected();
};

#else
class AndroidFileDialog : public QObject
{
    Q_OBJECT
public:
    explicit AndroidFileDialog(QObject *parent = nullptr);
    Q_INVOKABLE bool provideExistingFileName();
signals:
    void accepted(QString fileUrl);
    void rejected();
};
#endif
#endif // ANDROIDFILEDIALOG_H

package org.jooya.jooyaqtapplication;

import java.nio.charset.StandardCharsets;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.os.IBinder;
import android.content.IntentFilter;
import org.qtproject.qt.android.bindings.QtService;
import android.widget.Toast;

import android.graphics.PixelFormat;
import android.graphics.BitmapFactory;
import android.view.Gravity;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.os.Build;
import androidx.core.app.NotificationCompat;

import android.net.Uri;
import android.media.RingtoneManager;
import android.media.Ringtone;

public class DownloadService extends QtService
{
    private static final String TAG = "DownloadService";
    public static final String ACTION_START_ALARM = "START_ALARM";
    private NotificationCompat.Builder downloadNotification;

    @Override
    public void onCreate() {
        super.onCreate();
        Log.i(TAG,"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
        Log.i(TAG,"%%%%%%%%%%%%%[ DownloadService.java Started ]%%%%%%%%%%%%");
        Log.i(TAG,"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
        createDownloadNotification();
        startForeground(1, downloadNotification.build());
    }

    @Override
    public void onDestroy() {
        Log.i(TAG,"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
        Log.i(TAG,"%%%%%%%%%%%%[ DownloadService.java Destroyed ]%%%%%%%%%%%");
        Log.i(TAG,"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
        super.onDestroy();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.i(TAG,"%%%%%%%%%%%%%%%%%%[ DownloadService => Start Command ]%%%%%%%%%%%%%%%%%%");
        int ret = super.onStartCommand(intent, flags, startId);
        if(intent==null){
            Log.i(TAG, "***[ Intent was null => retrun ]***");
            return START_NOT_STICKY;
        }
        String serviceClassName = new String(intent.getByteArrayExtra("ServiceClassName"),StandardCharsets.UTF_8);

        if(!serviceClassName.equals("DownloadService"))
        {
            Log.i(TAG, "***[ the message is not for this service -> return ]***");
            return START_NOT_STICKY;
        }
        /// is this message has been sent from c++ library of service?
        String isInService = new String(intent.getByteArrayExtra("IsInService"),StandardCharsets.UTF_8);
        String m = new String(intent.getByteArrayExtra("MessageFromQt"),StandardCharsets.UTF_8);
        //String m = intent.getStringExtra("MessageFromQt");
        Log.i(TAG, "the message ==>> "+m);

        if(m.equals("StartService"))
        {
            Log.i(TAG, "***[ Service started -> Is Showing Foreground Notification ]***");
            startQtAndroidService(this);
            createDownloadNotification();
        }
        else if(m.equals("StopService"))
        {
            stopQtAndroidService();
            return START_NOT_STICKY;
        }
        if(downloadNotification == null){
            Log.i(TAG, "\\\\\\\\\\\\\\\\\\\\\\\\\\\\|-> notification is null <-|/////////////////////////");
            createDownloadNotification();
        }

        if(isInService.equals("No"))//message contains => "AddFile" || "StartDownload"
        {
            Log.i(TAG, "***[ message is received from qt app => send it to cpp lib of service ]***");
            /// because c++ lib and this class is running in same process you can send by below native method
            /// otherwise you should use sendMessageToCPPService() method that usesed broadcase receiver for commiucation
            DownloadServiceBroadcastUtility.sendToCPPService(m);
            return START_NOT_STICKY;
        }
        Log.i(TAG, "***[ message is received from cpp service => send it to qt app ]***");
        //message contains => "Ratio" || "DownloadMessage" || "TotalFileDownloaded" || "DownloadState"
        Log.i(TAG, "***[ Is goning to send message to qt app ]***");
        sendMessageToQtAPP(m);
        // update download notification
        if(m.contains("Ratio"))
        {
            String[] separated=m.split(",");
            float ratio = Float.parseFloat(separated[2]);

            downloadNotification.setProgress(100,(int)(ratio*100),false);
            downloadNotification.setSilent(true);
            downloadNotification.setOngoing(true);
            //you can use any of two below lines to display
            startForeground(1, downloadNotification.build());
            //JooyaNotificationManager.display(this,downloadNotification);
        }
        else if(m.contains("DownloadMessage"))
        {
            String[] separated=m.split(",");
            Log.i(TAG, "***[ DownloadMessage ==> "+separated[1]+"]***");
            downloadNotification.setContentText(separated[1]);
            downloadNotification.setSilent(true);
            downloadNotification.setOngoing(true);
            startForeground(1, downloadNotification.build());
            //JooyaNotificationManager.display(this,downloadNotification);
        }
        else if(m.contains("TotalFileDownloaded"))
        {
            Log.i(TAG, "***[ Download compeleted so => stop service ]***");
            downloadNotification.setContentText("دانلود به پایان رسید");
            downloadNotification.setSilent(true);
            downloadNotification.setOngoing(false);
            // display result of download in notification
            //JooyaNotificationManager.display(this,downloadNotification);
            stopForeground(true);
            stopQtAndroidService();
        }
        return START_NOT_STICKY;
    }
    //for display notifcation on android 13(api 33) and above should POST_NOTIFICATIONS permission should be granted
    public void createDownloadNotification( ){
        Log.i(TAG, "***[ Is Showing Foreground Notification For Download Manager ]***");
        downloadNotification = JooyaNotificationManager.getNotificationBuilder(this);
        downloadNotification.setContentText("در حال شروع دانلود");
        downloadNotification.setCategory(NotificationCompat.CATEGORY_PROGRESS);
        downloadNotification.setProgress(100,1,false);
        downloadNotification.setSilent(true);
        downloadNotification.setOngoing(true);
        JooyaNotificationManager.display(this,downloadNotification);
        Log.i(TAG, "***[ Foreground Notification For Download Manager Succeed here ]***");
    }
    public void sendMessageToQtAPP(String message){
        Intent sendToUiIntent = new Intent();
        sendToUiIntent.setAction(DownloadAppBroadcastUtility.getActionName(this));
        sendToUiIntent.putExtra("MessageFromQtService", message);
        sendBroadcast(sendToUiIntent);
    }
    public void sendMessageToCPPService(String message){
        Intent sendToUiIntent = new Intent();
        sendToUiIntent.setAction(DownloadServiceBroadcastUtility.getActionName(this));
        sendToUiIntent.putExtra("MessageFromQtApp", message);
        sendBroadcast(sendToUiIntent);
    }
    public static void startQtAndroidService(Context context) {
        context.startService(new Intent(context, DownloadService.class));
    }
    public void stopQtAndroidService() {
        this.stopService(new Intent(this, DownloadService.class));
    }
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}


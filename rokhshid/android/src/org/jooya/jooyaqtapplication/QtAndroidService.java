package org.jooya.rokhshid;

import java.nio.charset.StandardCharsets;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.os.IBinder;
import android.content.IntentFilter;
import org.qtproject.qt5.android.bindings.QtService;
import android.widget.Toast;

//import android.view.WindowManager;
//import android.view.WindowManager.LayoutParams;
//import android.widget.LinearLayout;
//import android.widget.RelativeLayout;
import android.graphics.PixelFormat;
import android.graphics.BitmapFactory;
import android.view.Gravity;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.os.Build;
import androidx.core.app.NotificationCompat;

import android.net.Uri;
import android.media.RingtoneManager;
import android.media.Ringtone;
public class QtAndroidService extends QtService
{
    private static final String TAG = "QtAndroidService";
    private static int ForegroundCount=0;
    private static int backgroundCount=0;
    private static boolean IsDowloadServiceStarted=false;
    private NotificationCompat.Builder downloadNotification;
//    WindowManager windowManager;
//    LinearLayout view;
    private WebView wv;
    private JSInterface jsi;
    @Override
    public void onCreate() {
        super.onCreate();
        jsi=new JSInterface(this);
        System.out.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
        System.out.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
        System.out.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
        System.out.println("%%%%[ Start Anroid Service QtAndroidService.java ]%%%%");
        System.out.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
        System.out.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
        System.out.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
        Toast.makeText(this, "***[ Creating Service ]***", Toast.LENGTH_LONG).show();
        try
        {
            //initializeWebView();
        }
        catch(Exception e)
        {
            System.out.println("Error " + e.getMessage());
        }
    }

    @Override
    public void onDestroy() {
        System.out.println("***[ Destroying Service ]***");
        Toast.makeText(this, "Service stoped by user", Toast.LENGTH_LONG).show();
        super.onDestroy();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.i(TAG, "***[ Start Command ]***");
        int ret = super.onStartCommand(intent, flags, startId);
        if(intent!=null){
            String qtMessage = new String(intent.getByteArrayExtra("MessageFromQt"),StandardCharsets.UTF_8);
//            String qtMessage = intent.getStringExtra("MessageFromQt");
            Log.i(TAG, "the message ==>> "+qtMessage);
            try
            {
                if(qtMessage.equals("StartService"))
                {
                    Toast.makeText(this, "Service started by user", Toast.LENGTH_LONG).show();
                    Log.i(TAG, "***[ Is Showing Foreground Notification ]***");
                    PendingIntent pi=PendingIntent.getActivity(this,0,intent,0);

                    downloadNotification =new NotificationCompat.Builder(this,"org.jooya.rokhshid.RokhshidDownloadForegroundServiceChannel")
                    .setContentTitle("رخشید")
                    .setContentText(qtMessage)
                    .setLargeIcon(BitmapFactory.decodeResource(getResources(), R.drawable.icon))
                    .setSmallIcon(R.drawable.icon)
                    .setContentIntent(pi);
                    startForeground(1, downloadNotification.build());
                }
                else if(qtMessage.equals("StopService"))
                {
                    stopQtAndroidService();
                }
                else if(qtMessage.contains("DownloadManager")||qtMessage.contains("Timer"))
                {
                    Log.i(TAG, "***[ send to download manager ]***");
                    if(qtMessage.contains("TotalRatio")||qtMessage.contains("DownloadMessage")||qtMessage.contains("FileExists")|qtMessage.contains("IsDownloaded")||qtMessage.contains("TotalFileDownloaded")||qtMessage.contains("CurrentTime"))
                    {
                        Log.i(TAG, "***[ Is goning to send message to qt app ]***");
                        sendMessageToQtAPP(qtMessage);
                        if(qtMessage.contains("TotalRatio"))
                        {
                            if(downloadNotification==null){
                                createDownloadNotification(intent);
                            }
                            Log.i(TAG, "***[ qt message => "+qtMessage+"]***");
                            String[] separated=qtMessage.split(",");
                            float ratio = Float.parseFloat(separated[1]);

                            downloadNotification.setProgress(100,(int)(ratio*100),false);
                            startForeground(1, downloadNotification.build());
                        }
                        else if(qtMessage.contains("TotalFileDownloaded"))
                        {
//                            downloadNotification.setContentText("دانلود به پایان رسید");
//                            startForeground(1, downloadNotification.build());
                            stopForeground(true);
                            if(ForegroundCount==0){
                            }
                        }
                        else if(qtMessage.contains("DownloadMessage"))
                        {
                            String[] separated=qtMessage.split(",");
                            Log.i(TAG, "***[ DownloadMessage ==> "+separated[1]+"]***");
                            downloadNotification.setContentText(separated[1]);
                            startForeground(1, downloadNotification.build());
                        }
                        else if(qtMessage.contains("IsDownloaded"))
                        {
                            Log.i(TAG, "***[ IsDownloaded so => stop service ]***");
//                            stopForeground(true);
                        }
                    }
                    else if(qtMessage.contains("AddFile")||qtMessage.contains("StartDownload")||qtMessage.contains("StartTimer")||qtMessage.contains("StopTimer"))
                    {
                        if(qtMessage.contains("AddFile")&&!IsDowloadServiceStarted)
                        {
                            IsDowloadServiceStarted=true;
                            createDownloadNotification(intent);
                        }
                        Log.i(TAG, "***[ Is goning to send message to c++ service ]***");
                        ServiceBroadcastUtility.sendToCPPService(qtMessage);
                    }
                }
                else
                {
                    Toast.makeText(this, "New Message=> "+qtMessage, Toast.LENGTH_LONG).show();
                    sendMessageToQtAPP("Your Message was=> "+qtMessage);
                    //notification.setContentText(qtMessage);
                }
            }
            catch(Exception e)
            {
                System.out.println("all eroeo ldol3 Error => " + e.getMessage());
            }
        }
        return START_NOT_STICKY;
        //return ret;
    }
    public void createDownloadNotification(Intent intent){
        Log.i(TAG, "***[ Is Showing Foreground Notification For Download Manager ]***");
        PendingIntent pi=PendingIntent.getActivity(this,0,intent,0);

        downloadNotification =new NotificationCompat.Builder(this,"org.jooya.rokhshid.RokhshidDownloadForegroundServiceChannel")
        .setContentTitle("رخشید")
        .setOngoing(true)
        .setContentText("در حال دانلود")
        .setLargeIcon(BitmapFactory.decodeResource(getResources(), R.drawable.icon))
        .setSmallIcon(R.drawable.icon)
        .setContentIntent(pi);
        startForeground(1, downloadNotification.build());
    }
    public void sendMessageToQtAPP(String message){
        Intent sendToUiIntent = new Intent();
        sendToUiIntent.setAction(AppBroadcastUtility.BROADCAST_NAME_ACTION1);
        sendToUiIntent.putExtra("MessageFromQt", message);
        Log.i(TAG, "Service sending broadcast");
        sendBroadcast(sendToUiIntent);
    }
    public void sendMessageToCPPService(String message){
        Intent sendToUiIntent = new Intent();
        sendToUiIntent.setAction(ServiceBroadcastUtility.BROADCAST_NAME_ACTION2);
        sendToUiIntent.putExtra("MessageFromQt", message);
        Log.i(TAG, "Service sending broadcast");
        sendBroadcast(sendToUiIntent);
    }
    public static void startQtAndroidService(Context context) {
        context.startService(new Intent(context, QtAndroidService.class));
    }
    public void stopQtAndroidService() {
        this.stopService(new Intent(this, QtAndroidService.class));
    }
    public void initializeWebView(){
        if(wv!=null){
            return;
        }
//        windowManager = (WindowManager) getSystemService(WINDOW_SERVICE);
//        WindowManager.LayoutParams params = new WindowManager.LayoutParams(WindowManager.LayoutParams.WRAP_CONTENT, WindowManager.LayoutParams.WRAP_CONTENT, WindowManager.LayoutParams.TYPE_SYSTEM_OVERLAY, WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE, PixelFormat.TRANSLUCENT);
//        params.gravity = Gravity.TOP | Gravity.LEFT;
//        params.x = 0;
//        params.y = 0;
//        params.width = 0;
//        params.height = 0;

//        view = new LinearLayout(this);
//        view.setLayoutParams(new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.MATCH_PARENT, RelativeLayout.LayoutParams.MATCH_PARENT));

        wv = new WebView(this);
        wv.getSettings().setJavaScriptEnabled(true);
        wv.addJavascriptInterface(jsi, "AndroidApp");
        wv.setWebViewClient(new WebViewClient() {
//            @Override
//            public void onPageStarted(WebView view, String url) {
//               Log.d("WebView", "onPageStarted " + url);
//            }
            @Override
            public void onPageFinished(WebView view, String url) {
               Log.d("WebView", "onPageFinished " + url);
               wv.loadUrl("javascript:var pagehtml=document.documentElement.innerHTML;window.AndroidApp.saveHtmlOfPage(pagehtml);");
            }
//            @Override
//             public void onProgressChanged(WebView view, int progress) {
//                 //Log.d(TAG,progress);
////                if (progress == 100) {
////                }
//             }
         });
//        wv.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT));
//        view.addView(wv);
        wv.loadUrl("http://google.com");

//        windowManager.addView(view, params);
    }
    @Override
    public IBinder onBind(Intent intent) {
        return super.onBind(intent);
    }
}


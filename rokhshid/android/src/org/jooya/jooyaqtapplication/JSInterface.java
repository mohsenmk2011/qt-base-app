package org.jooya.jooyaqtapplication;

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
import android.view.Gravity;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.os.Build;
import androidx.core.app.NotificationCompat;
import android.webkit.JavascriptInterface;

public class JSInterface {

    public Context mContext;
    public JSInterface(Context context){
        mContext=context;
    }
    @JavascriptInterface
    public void saveHtmlOfPage(String value){
        //you will get HAI message in here
        Log.d("JooyaTaminApp", "receiveString mthond");
        Log.i("JavascriptInterface.saveHtmlOfPage",value);
        ServiceBroadcastUtility.sendToCPPService(value);
    }
}

package org.jooya.jooyaqtapplication;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.content.BroadcastReceiver;
import android.content.IntentFilter;
import org.jooya.jooyaqtapplication.R;
import android.content.res.Resources;

public class DownloadServiceBroadcastUtility {
    public static native void sendToCPPService(String message);

    private static final String TAG = "DownloadServiceBroadcastUtility";
    public static String getActionName(Context context) {
        Resources res = context.getResources();
        String packageName = res.getString(R.string.app_package_name);
        return packageName + "." + TAG + ".sendToCPPService";
    }

    public void registerServiceBroadcastReceiver(Context context) {
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(getActionName(context));
        if (android.os.Build.VERSION.SDK_INT >= 33)
        {
            context.registerReceiver(serviceMessageReceiver,intentFilter,Context.RECEIVER_NOT_EXPORTED);
        }
        else
        {
           context.registerReceiver(serviceMessageReceiver, intentFilter);
        }
        Log.i(TAG, "Registered service broadcast receiver");
    }
    public void unregisterServiceBroadcastReceiver(Context context) {
        context.unregisterReceiver(serviceMessageReceiver);
        Log.i(TAG, "un registered service broadcast receiver");
    }

    private BroadcastReceiver serviceMessageReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            Log.i(TAG, "***[ OnReceive BroadcastReceiver ]***");
            if(getActionName(context).equals(intent.getAction())) {
                String qtMessage = intent.getStringExtra("MessageFromQtApp");
                sendToCPPService(qtMessage);
            }
        }
    };
}

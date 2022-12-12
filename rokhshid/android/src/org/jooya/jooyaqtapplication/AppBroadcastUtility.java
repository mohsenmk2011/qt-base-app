package org.jooya.rokhshid;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.content.BroadcastReceiver;
import android.content.IntentFilter;

public class AppBroadcastUtility {

    public static native void sendToQtApp(String message);

    private static final String TAG = "AppBroadcastUtility";
    public static final String BROADCAST_NAME_ACTION1 = "org.jooya.rokhshid.sendToQtApp";

    public void registerServiceBroadcastReceiver(Context context) {
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BROADCAST_NAME_ACTION1);
        context.registerReceiver(serviceMessageReceiver, intentFilter);
        Log.i(TAG, "%%%[ Is registering broadcast receiver ]%%%");
    }

    private BroadcastReceiver serviceMessageReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            Log.i(TAG, "***[ OnReceive BroadcastReceiver ]***");
            if (BROADCAST_NAME_ACTION1.equals(intent.getAction())) {
                String qtMessage = intent.getStringExtra("MessageFromQt");
                sendToQtApp(qtMessage);
            }
        }
    };
}

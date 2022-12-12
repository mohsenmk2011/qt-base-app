package org.jooya.rokhshid;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.content.BroadcastReceiver;
import android.content.IntentFilter;

public class ServiceBroadcastUtility {
    public static native void sendToCPPService(String message);

    private static final String TAG = "ServiceBroadcastUtility";
    public static final String BROADCAST_NAME_ACTION2 = "org.jooya.rokhshid.sendToCPPService";

    public void registerServiceBroadcastReceiver(Context context) {
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BROADCAST_NAME_ACTION2);
        context.registerReceiver(serviceMessageReceiver, intentFilter);
        Log.i(TAG, "Registered broadcast receiver");
    }

    private BroadcastReceiver serviceMessageReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            Log.i(TAG, "***[ OnReceive BroadcastReceiver ]***");
            if(BROADCAST_NAME_ACTION2.equals(intent.getAction())) {
                String qtMessage = intent.getStringExtra("MessageFromQt");
                sendToCPPService(qtMessage);
            }
        }
    };
}

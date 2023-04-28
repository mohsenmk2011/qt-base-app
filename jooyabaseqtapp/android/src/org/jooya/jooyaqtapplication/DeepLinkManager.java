package org.jooya.rokhshid;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.content.BroadcastReceiver;
import android.content.IntentFilter;
import android.widget.Toast;
import java.lang.Object;
import android.telephony.SmsMessage;
import android.os.Bundle;

public class DeepLinkManager {
    public static native void sendToQtApp(String message);
}

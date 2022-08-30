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
import android.os.Vibrator;

public class ReminderBroadcastReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
        if(context == null || intent == null || intent.getAction() == null){
            return;
        }
        if (intent.getAction().equals("alarmRokhshidExercis")) {
            Toast.makeText(context, "Time Up... Now Vibrating !!!",Toast.LENGTH_LONG).show();
            Vibrator vibrator = (Vibrator) context.getSystemService(Context.VIBRATOR_SERVICE);
            vibrator.vibrate(2000);
            NotificationClient.notify(context,"رخشید","زمان انجام تمرینات");
        }
    }
}

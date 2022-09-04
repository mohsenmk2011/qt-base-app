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

    private static final String TAG = "ReminderBroadcastReceiver";
    @Override
    public void onReceive(Context context, Intent intent) {
        Toast.makeText(context, "Alarm trigged now !!!", Toast.LENGTH_SHORT).show();
        Log.i(TAG, "Alarm trigged now !!! ");
        Log.i(TAG, "context is null => "+(context == null) );
        Log.i(TAG, "intent is null => "+(intent == null) );
        Log.i(TAG, "intent.getAction() == null => "+(intent.getAction() == null) );
        if(context == null || intent == null || intent.getAction() == null){
            return;
        }
        if (intent.getAction().equals("Notification")) {
            Vibrator vibrator = (Vibrator) context.getSystemService(Context.VIBRATOR_SERVICE);
            vibrator.vibrate(900);
            NotificationClient.notify(context,"رخشید","زمان انجام تمرینات");
        }
        else if (intent.getAction().equals("Page")) {
            //Display alarm activy page
            Intent alarmIntent = new Intent(context,AlarmActivity.class);
            alarmIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startActivity(alarmIntent);
        }
    }
}

package org.jooya.rokhshid;

import android.content.Context;
import android.content.Intent;
import android.os.Build;
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
        Log.i(TAG, "Alarm trigged now !!! ");
        if(context == null || intent == null){
            return;
        }
        String alarmTime = intent.getStringExtra("time");
        String alarmType = intent.getStringExtra("type");
        Log.i(TAG, "alarmTime=>  "+alarmTime);
        Log.i(TAG, "alarmType=>  "+alarmType);
        if (alarmType.equals("Notification")) {
            Vibrator vibrator = (Vibrator) context.getSystemService(Context.VIBRATOR_SERVICE);
            vibrator.vibrate(900);
            NotificationClient.notify(context,"رخشید","زمان انجام تمرینات");
        }
        else if (alarmType.equals("Page")) {
            //Display alarm activy page
            Intent alarmIntent = new Intent(context,AlarmActivity.class);
            alarmIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            alarmIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
            context.startActivity(alarmIntent);
        }
        if(JooyaAlarmManager.isAlarmUp(context))
        {
            //JooyaAlarmManager.startAlarmWithAlamManager(context,alarmTime,alarmType);
            Log.i(TAG, "Alarm is up !!! ");
        }
        else
        {
            //JooyaAlarmManager.startAlarmWithAlamManager(context,alarmTime,alarmType);
            Log.i(TAG, "Alarm is not up !!! ");
        }
    }
}

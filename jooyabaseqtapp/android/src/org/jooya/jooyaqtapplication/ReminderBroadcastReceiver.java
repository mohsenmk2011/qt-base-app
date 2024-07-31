package org.jooya.jooyaqtapplication;

import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;
import android.os.Build;
import android.util.Log;
import android.content.BroadcastReceiver;
import android.content.IntentFilter;
import android.widget.Toast;
import java.lang.Object;
import android.telephony.SmsMessage;
import android.os.Bundle;
import android.os.Vibrator;
import android.content.res.Resources;
import org.jooya.jooyaqtapplication.R;
import java.util.Calendar;
import android.icu.text.SimpleDateFormat;

public class ReminderBroadcastReceiver extends BroadcastReceiver {

    private static final String TAG = "ReminderBroadcastReceiver";
    public static final String BROADCAST_ACTION_NAME = "org.jooya.jooyaqtquickapplication.JOOYAQTQUICKAPPLICATIONSALARM";
    @Override
    public void onReceive(Context context, Intent intent) {
        Log.i(TAG, "####[ Alarm trigged now :> ]###");
        if(context == null){
            Log.i(TAG, "***[ context is null ]***");
            return;
        }
        if(intent == null){
            Log.i(TAG, "***[ intent is null ]***");
            return;
        }
        if(!BROADCAST_ACTION_NAME.equals(intent.getAction())) {
            return;
        }
        String alarmTime = intent.getStringExtra("time");
        String alarmType = intent.getStringExtra("type");
        String intervalString = intent.getStringExtra("interval");
        int intervalInt = Integer.parseInt(intervalString);
        Log.i(TAG, "alarmTime=>  "+alarmTime);
        Log.i(TAG, "alarmType=>  "+alarmType);
        Log.i(TAG, "application name => "+PackageinfoManager.getApplicationName(context));
        boolean isInterval = intervalInt > 0;
        if (alarmType.equals("Notification")) {
            Vibrator vibrator = (Vibrator) context.getSystemService(Context.VIBRATOR_SERVICE);
            vibrator.vibrate(900);
            //TODO: Change this after creating new branch from master branch
            NotificationClient.notify(context,"اپلیکیشن جویا","زمان انجام تمرینات");
        }
        else if (alarmType.equals("Page")) {
            JooyaNotificationManager.showFullScreenNotification(context,"رخشید","زمان انجام تمرینات");            
        }
        // Reschedule the alarm for the next time
        if (isInterval) {

            Log.i(TAG, "####[ Alarm has interval ]###");
            String[] separated=alarmTime.split(":");
            int hour=Integer.parseInt(separated[0]);
            int minute=Integer.parseInt(separated[1]);

            Calendar dt = Calendar.getInstance();
            dt.set(Calendar.HOUR_OF_DAY, hour);
            dt.set(Calendar.MINUTE, minute);
            dt.set(Calendar.SECOND, 0);
            dt.set(Calendar.MILLISECOND, 0);

            dt.add(Calendar.MINUTE, intervalInt);
            SimpleDateFormat df = new SimpleDateFormat("HH:mm");
            String newTime = df.format(dt.getTime());
            Log.i(TAG, "new alarmTime =>  "+newTime);
            JooyaAlarmManager.setExact(context, newTime, alarmType,intervalString);
        }
    }
}

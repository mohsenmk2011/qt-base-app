package org.jooya.jooyaqtapplication;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.NotificationChannel;
import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;
import android.graphics.Color;
import android.graphics.BitmapFactory;
import org.jooya.jooyaqtapplication.R;
import android.widget.Toast;
import android.util.Log;
import androidx.core.app.NotificationCompat;
import android.os.PowerManager;
import android.net.Uri;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.BroadcastReceiver;
import android.app.AlarmManager;
import android.os.Build;

import android.content.Context;
import androidx.annotation.NonNull;
import androidx.work.Data;
import androidx.work.Worker;
import androidx.work.WorkManager;
import androidx.work.OutOfQuotaPolicy;
import androidx.work.Constraints;
import androidx.work.OneTimeWorkRequest;
import androidx.work.PeriodicWorkRequest;
import androidx.work.NetworkType;
import java.util.concurrent.TimeUnit;
import androidx.work.WorkerParameters;
import java.util.Calendar;
import android.os.Vibrator;

import org.qtproject.qt.android.bindings.QtActivity;
import android.provider.Settings;


public class JooyaAlarmManager
{
    public static native void sendToQtApp(String message);
    public static native void sendToQtService(String message);

    private static final String TAG = "JooyaAlarmManager";    
    private static final int ALARMPENDIGID = 4972563;

    public static void cancelAlarm(Context context) {

        Log.i(TAG, "***[ cancel Alarm ]***");
        AlarmManager alarmManager = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
         Intent intent=new Intent(context,ReminderBroadcastReceiver.class);
         intent.setAction(ReminderBroadcastReceiver.BROADCAST_ACTION_NAME);
         PendingIntent pendingIntent = PendingIntent.getBroadcast(context,ALARMPENDIGID,intent,PendingIntent.FLAG_NO_CREATE | PendingIntent.FLAG_IMMUTABLE);
         alarmManager.cancel(pendingIntent);
         pendingIntent.cancel();
    }
    public static void displayAlarmPage(Context context,String alarmType,String notificationContent)
    {
        Log.i(TAG, "displayAlarmPage");
        Log.i(TAG, "alarmType => "+alarmType);
        Log.i(TAG, "notificationContent => "+notificationContent);
        //alarmType => {Page,Notification}
        if(alarmType.equals("Page"))
        {
            Intent alarmIntent = new Intent(context,AlarmActivity.class);
            alarmIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startActivity(alarmIntent);
        }
        else if(alarmType.equals("Notification"))
        {
            Vibrator vibrator = (Vibrator) context.getSystemService(Context.VIBRATOR_SERVICE);
            vibrator.vibrate(1800);

            NotificationCompat.Builder builder =  JooyaNotificationManager.getNotificationBuilder(context);
            builder.setDefaults(Notification.DEFAULT_SOUND);
            builder.setContentText(notificationContent);
            JooyaNotificationManager.display(context,builder);
        }
    }
    public static boolean isAlarmUp(Context context)
    {
        Intent intent=new Intent(context,ReminderBroadcastReceiver.class);
        intent.setAction(ReminderBroadcastReceiver.BROADCAST_ACTION_NAME);
        boolean alarmUp = (PendingIntent.getBroadcast(context,ALARMPENDIGID,intent,PendingIntent.FLAG_NO_CREATE | PendingIntent.FLAG_IMMUTABLE) != null);
        Log.i(TAG, "***[ Is Alarm Up => " + alarmUp + " ]***");
        return alarmUp;
    }

    public static boolean setExact(Context context,String hm,String alarmType,String interval,String notificationContent)
    {
        Log.i(TAG, "*********[  JooyaAlarmManager.setExact  ]*********");
        Log.i(TAG, "alarm time => "+hm);
        Log.i(TAG, "alarmType => "+alarmType);
        Log.i(TAG, "interval => "+interval);
        //alarmType => {Page,Notification}

        Intent intent=new Intent(context,ReminderBroadcastReceiver.class);
        intent.setAction(ReminderBroadcastReceiver.BROADCAST_ACTION_NAME);
        intent.addFlags(Intent.FLAG_RECEIVER_FOREGROUND);
        intent.putExtra("type",alarmType);
        intent.putExtra("time",hm);
        intent.putExtra("interval",interval);
        intent.putExtra("notificationContent",notificationContent);
        //=====================================================
        PendingIntent pendingIntent;
        int flags = PendingIntent.FLAG_UPDATE_CURRENT;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
            flags |= PendingIntent.FLAG_IMMUTABLE;
        }
        pendingIntent = PendingIntent.getBroadcast(context, ALARMPENDIGID, intent, flags);
        //=====================================================
        String[] separated=hm.split(":");
        int hour=Integer.parseInt(separated[0]);
        int minute=Integer.parseInt(separated[1]);
        Log.i(TAG, "hour => "+hour);
        Log.i(TAG, "minute => "+minute);
        //==========================================
        Calendar now = Calendar.getInstance();
        Calendar dt = Calendar.getInstance();
        dt.set(Calendar.HOUR_OF_DAY, hour);
        dt.set(Calendar.MINUTE, minute);
        dt.set(Calendar.SECOND, 0);
        dt.set(Calendar.MILLISECOND, 0);

        //============================[ find diffrence between two date time ]==================================
         long diffSeconds = (dt.getTimeInMillis() - now.getTimeInMillis())/1000;
        //  // if dt > now so diff is positive => diff = dt   - now
        //  //                                    600 = 11:00 - 10:50
        // Log.i(TAG, "diffSeconds => "+diffSeconds);
        // // if dt < now so diff is negetive => diff = dt    - now
        // //                                    -600 = 11:10 - 11:00
        // so add one day to dt
        if(diffSeconds<0){//time is passed
            dt.add(Calendar.DAY_OF_MONTH, 1);
            diffSeconds = (dt.getTimeInMillis() - now.getTimeInMillis())/1000;
            Log.i(TAG, "is pass so => new diffSeconds is => "+diffSeconds);
        }
        //=========================
        AlarmManager alarmManager = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
        Log.i(TAG, "Build.VERSION.SDK_INT => "+Build.VERSION.SDK_INT);
        Log.i(TAG, "Build.VERSION_CODES.M => "+Build.VERSION_CODES.M);
        Log.i(TAG, "Build.VERSION_CODES.S => "+Build.VERSION_CODES.S);
        Log.i(TAG, "Build.VERSION_CODES.KITKAT => "+Build.VERSION_CODES.KITKAT);
        //====================================================================
        //alarmManager.setInexactRepeating(AlarmManager.RTC_WAKEUP, dt.getTimeInMillis(),AlarmManager.INTERVAL_DAY, pendingIntent);
        //alarmManager.setExactAndAllowWhileIdle(AlarmManager.RTC_WAKEUP, dt.getTimeInMillis(), pendingIntent);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            Log.i(TAG, "is bigger than marshall => Battery Optimizations is Ignored by user in checkBatteryOptimization method");
            alarmManager.setExactAndAllowWhileIdle(AlarmManager.RTC_WAKEUP, dt.getTimeInMillis(), pendingIntent);
        }
        else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            Log.i(TAG, "is higher than kitkat");
            alarmManager.setExact(AlarmManager.RTC_WAKEUP, dt.getTimeInMillis(), pendingIntent);

            // effort to save battery, allow deviation of 15 minutes
            // int windowMillis = 15 * 60 * 1000;
            //alarmManager.setWindow(AlarmManager.RTC_WAKEUP, dt.getTimeInMillis(), windowMillis, pendingIntent);
        }
        else {
            Log.i(TAG, "is lower than kitkat");
            alarmManager.set(AlarmManager.RTC_WAKEUP, dt.getTimeInMillis(), pendingIntent);
        }
        return isAlarmUp(context);
    }    
}

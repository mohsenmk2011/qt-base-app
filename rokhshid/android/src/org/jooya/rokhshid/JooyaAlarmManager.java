package org.jooya.rokhshid;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.NotificationChannel;
import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;
import android.graphics.Color;
import android.graphics.BitmapFactory;
import org.jooya.rokhshid.R;
import org.qtproject.qt5.android.QtNative;
import android.widget.Toast;
import android.util.Log;
import androidx.core.app.NotificationCompat;

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

import org.qtproject.qt5.android.bindings.QtActivity;

public class JooyaAlarmManager
{
    public static native void sendToQtApp(String message);
    public static native void sendToQtService(String message);

    private static final String TAG = "JooyaAlarmManager";
    private static final String ALARMID = "org.jooya.rokhshid.exercisealarm";

    public static void setAlarm(Context context,String hm) {
        Log.i(TAG, "***[ setAlarm ]***");

//        Data data=new Data.Builder()
//                    .putInt("number",10)
//                    .build();
        Constraints con=new Constraints.Builder()
//        .setRequiredNetworkType(NetworkType.CONNECTED)
            .setRequiresDeviceIdle(true)
        .build();

        //==================================for download file=========================================================
//        OneTimeWorkRequest downloadRequest = new OneTimeWorkRequest.Builder(AlarmWorker.class)
//            .setInputData(data)
//            .setConstraints(con)
//            .setInitialDelay(1,TimeUnit.MINUTES)
//              .setId(ALARMID);
//            .build();

//        WorkManager.getInstance(context)
//                         .enqueue(downloadRequest);

         //===========================================================================================
         //split input datetime with ':' input is like 14:00
        String[] separated=hm.split(":");
        int hour=Integer.parseInt(separated[0]);
        int minute=Integer.parseInt(separated[1]);
        Log.i(TAG, "hour => "+hour);
        Log.i(TAG, "minute => "+minute);
       // get datetime now and set input datetime
       Calendar now = Calendar.getInstance();
       Calendar dt = Calendar.getInstance();
       dt.set(Calendar.HOUR_OF_DAY, hour);
       dt.set(Calendar.MINUTE, minute);

       //============================[ find diffrence between two date time ]==================================
       long diffSeconds = (dt.getTimeInMillis() - now.getTimeInMillis())/1000;
        // if dt > now so diff is positive => diff = dt   - now
        //                                    600 = 11:00 - 10:50
       Log.i(TAG, "diffSeconds => "+diffSeconds);
       // if dt < now so diff is negetive => diff = dt    - now
       //                                    -600 = 11:10 - 11:00
       // so add one day to dt
       if(diffSeconds<0){//time is passed
           dt.add(Calendar.DAY_OF_MONTH, 1);
           diffSeconds = (dt.getTimeInMillis() - now.getTimeInMillis())/1000;
           Log.i(TAG, "is pass so => new diffSeconds is => "+diffSeconds);
       }
   //======================================[alarm request]====================================================

           OneTimeWorkRequest alarmRequest = new OneTimeWorkRequest.Builder(AlarmWorker.class)
             //  .setInputData(data) //read time from json file and send as data here
               //.setConstraints(con)
               .setInitialDelay(-diffSeconds,TimeUnit.SECONDS)
                 .addTag(ALARMID)
                 .setExpedited(OutOfQuotaPolicy.RUN_AS_NON_EXPEDITED_WORK_REQUEST)
               .build();

           WorkManager.getInstance(context)
                            .enqueue(alarmRequest);

//        PeriodicWorkRequest alarmRequest=new PeriodicWorkRequest.Builder(AlarmWorker.class,15,TimeUnit.MINUTES)
////                    .setInputData(data)
//                    .addTag(ALARMID)
////                    .setConstraints(con)
//                    .setInitialDelay(-diffSeconds,TimeUnit.SECONDS)
//                    .build();

//        WorkManager.getInstance(context)
//                         .enqueue(alarmRequest);

         //get result of work in here and send to qt application
//         WorkManager.getInstance(context).getWorkInfoByIdLiveData(alarmRequest.getId()).observe(context,
//         new Observer<WorkInfo>(){
//             @Override
//             public void onChanged(WorkInfo workInfo){
//                 Log.i(TAG, "onChaged  => workInfo"+workInfo.getState());
//                 }
//             });

        Log.i(TAG, "***[ Alarm set succeed ]***");
    }

    public static void cancelAlarm(Context context) {

//        PeriodicWorkRequest alarmRequest=new PeriodicWorkRequest.Builder(AlarmWorker.class,1,TimeUnit.DAYS)
//                    .addTag(ALARMID)
//                    .build();

        //WorkManager.getInstance(context).cancelWorkById(alarmRequest.getId());
        WorkManager.getInstance(context).cancelAllWorkByTag(ALARMID);
    }
    public static void displayAlarmPage(Context context,String alarmType)
    {
        //Display alarm activy page

        Log.i(TAG, "displayAlarmPage");
        Log.i(TAG, "alarmType=>"+alarmType);
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
            vibrator.vibrate(900);
            NotificationClient.notify(context,"رخشید","زمان انجام تمرینات");
        }
    }

    public static void startAlarmWithAlamManager(Context context,String hm,String alarmType)
    {
        Log.i(TAG, "JooyaAlarmManager.startAlarmWithAlamManager");
        Log.i(TAG, "alarmType=>"+alarmType);
        //alarmType => {Page,Notification}

        Intent intent=new Intent(context,ReminderBroadcastReceiver.class);
        intent.setAction(alarmType);
        PendingIntent pendingIntent = PendingIntent.getBroadcast(context, 360999, intent, PendingIntent.FLAG_CANCEL_CURRENT);
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

        //============================[ find diffrence between two date time ]==================================
        long diffSeconds = (dt.getTimeInMillis() - now.getTimeInMillis())/1000;
         // if dt > now so diff is positive => diff = dt   - now
         //                                    600 = 11:00 - 10:50
        Log.i(TAG, "diffSeconds => "+diffSeconds);
        // if dt < now so diff is negetive => diff = dt    - now
        //                                    -600 = 11:10 - 11:00
        // so add one day to dt
        if(diffSeconds<0){//time is passed
            dt.add(Calendar.DAY_OF_MONTH, 1);
            diffSeconds = (dt.getTimeInMillis() - now.getTimeInMillis())/1000;
            Log.i(TAG, "is pass so => new diffSeconds is => "+diffSeconds);
        }
        //=========================
        AlarmManager alarmManager = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
        //====================================================================
        //alarmManager.setExactAndAllowWhileIdle(AlarmManager.RTC_WAKEUP, dt.getTimeInMillis(),AlarmManager.INTERVAL_DAY, pendingIntent);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
             alarmManager.setExact(AlarmManager.RTC_WAKEUP, dt.getTimeInMillis(), pendingIntent);

            // effort to save battery, allow deviation of 15 minutes
            int windowMillis = 15 * 60 * 1000;
            //alarmManager.setWindow(AlarmManager.RTC_WAKEUP, dt.getTimeInMillis(), windowMillis, pendingIntent);
        }
        else {
            Log.i(TAG, " ");
            alarmManager.set(AlarmManager.RTC_WAKEUP, dt.getTimeInMillis(), pendingIntent);
        }
        Log.i(TAG, "Build.VERSION.SDK_INT=> "+Build.VERSION.SDK_INT);
    }
}


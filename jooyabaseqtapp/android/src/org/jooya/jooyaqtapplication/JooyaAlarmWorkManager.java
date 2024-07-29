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
import androidx.work.WorkInfo;
import androidx.work.OutOfQuotaPolicy;
import androidx.work.Constraints;
import androidx.work.OneTimeWorkRequest;
import androidx.work.PeriodicWorkRequest;
import androidx.work.NetworkType;
import java.util.concurrent.TimeUnit;
import androidx.work.WorkerParameters;
import java.util.Calendar;
import android.os.Vibrator;
import android.os.Handler;
import android.os.Looper;
import androidx.lifecycle.Observer;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.List;

import org.qtproject.qt.android.bindings.QtActivity;
import android.provider.Settings;


public class JooyaAlarmWorkManager
{
    private static final String TAG = "JooyaAlarmWorkManager";
    //will set alram with workmanager
    public static boolean setAlarm(Context context,String hm,String alarmType,String interval) {
        Log.i(TAG, "***[ is setting Alarm WorkManager ]***");

//        Data data=new Data.Builder()
//                    .putInt("number",10)
//                    .build();
        Constraints con=new Constraints.Builder()
//        .setRequiredNetworkType(NetworkType.CONNECTED)
            .setRequiresDeviceIdle(false)
        .build();
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

           // OneTimeWorkRequest alarmRequest = new OneTimeWorkRequest.Builder(AlarmWorker.class)
           //   //  .setInputData(data) //read time from json file and send as data here
           //     .setConstraints(con)
           //     .setInitialDelay(diffSeconds,TimeUnit.SECONDS)
           //       .addTag(ReminderBroadcastReceiver.BROADCAST_ACTION_NAME)
           //      // .setExpedited(OutOfQuotaPolicy.RUN_AS_NON_EXPEDITED_WORK_REQUEST)
           //     .build();

           // WorkManager.getInstance(context)
           //                  .enqueue(alarmRequest);

       PeriodicWorkRequest alarmRequest=new PeriodicWorkRequest.Builder(AlarmWorker.class,15,TimeUnit.MINUTES)
//                    .setInputData(data)
                    .setConstraints(con)
                   .setInitialDelay(-diffSeconds,TimeUnit.SECONDS)
                   .addTag(ReminderBroadcastReceiver.BROADCAST_ACTION_NAME)
                   .build();

       WorkManager.getInstance(context)
                        .enqueue(alarmRequest);
        return isAlarmUp(context);
    }

    public static boolean cancelAlarm(Context context) {
        Log.i(TAG, "***[ cancel Alarm ]***");
//        PeriodicWorkRequest alarmRequest=new PeriodicWorkRequest.Builder(AlarmWorker.class,1,TimeUnit.DAYS)
//                    .addTag(ReminderBroadcastReceiver.BROADCAST_ACTION_NAME)
//                    .build();

        //WorkManager.getInstance(context).cancelWorkById(alarmRequest.getId());
        Log.i(TAG, "***[ ReminderBroadcastReceiver.BROADCAST_ACTION_NAME => " + ReminderBroadcastReceiver.BROADCAST_ACTION_NAME + " ]***");
        WorkManager.getInstance(context).cancelAllWorkByTag(ReminderBroadcastReceiver.BROADCAST_ACTION_NAME);
        return !isAlarmUp(context);
    }

    public static boolean isAlarmUp(Context context)
    {
        final boolean[] isFinished = {false}; // Use array to modify within the observer
      CountDownLatch latch = new CountDownLatch(1); // Create a latch to wait for the observer

      // Create a handler to post the observer to the main thread
      Handler mainHandler = new Handler(Looper.getMainLooper());

      mainHandler.post(() -> {
          WorkManager.getInstance(context).getWorkInfosByTagLiveData(ReminderBroadcastReceiver.BROADCAST_ACTION_NAME).observeForever(new Observer<List<WorkInfo>>() {
              @Override
              public void onChanged(List<WorkInfo> listOfWorkStatuses) {
                  if (!listOfWorkStatuses.isEmpty()) {
                      WorkInfo workInfo = listOfWorkStatuses.get(0);
                      isFinished[0] = workInfo.getState().isFinished();
                      Log.i(TAG, "***[ Is Alarm Up => " + !isFinished[0] + " ]***");
                  }
                  latch.countDown(); // Countdown the latch after processing
              }
          });
      });

      try {
          latch.await(6, TimeUnit.SECONDS); // Wait for the latch with a timeout
      } catch (InterruptedException e) {
          e.printStackTrace();
      }

      return !isFinished[0];
    }
}


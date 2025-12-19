package org.jooya.jooyaqtapplication;

import androidx.annotation.NonNull;
import androidx.work.Data;
import androidx.work.Worker;
import androidx.work.WorkerParameters;
import android.util.Log;
import android.widget.Toast;
import java.lang.InterruptedException;
import java.lang.Exception;

import android.os.PowerManager;
import android.net.Uri;
import android.media.RingtoneManager;
import android.media.Ringtone;


import android.app.Notification;
import android.app.NotificationManager;
import android.app.NotificationChannel;
import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;
import android.graphics.BitmapFactory;
import org.jooya.jooyaqtapplication.R;
import androidx.core.app.NotificationCompat;


public class AlarmWorker extends Worker {
    private static final String TAG = "AlarmWorker";
    private Context m_Context;
    public AlarmWorker (@NonNull Context context,@NonNull WorkerParameters workerParams){
        super(context,workerParams);
        m_Context=context;
    }
    @NonNull
    @Override
    public Result doWork(){
       Data inputData=getInputData();
       String notificationContent = inputData.getString("notificationContent");
       String alarmType = inputData.getString("alarmType");
       //int number = inputData.getInt(key:"number", defaultValue:-1);
       Log.i(TAG, "alarmType => " + alarmType);
       Log.i(TAG, "notificationContent => " + notificationContent);

//        Toast.makeText(this, "AlarmWorker.doWork()", Toast.LENGTH_LONG).show();
        Log.i(TAG, "***[ Is Showing Alram Notification ]***");
        Log.i(TAG, "m_Context == null => "+(m_Context ==null));

//        PowerManager pm = (PowerManager) m_Context.getSystemService(Context.POWER_SERVICE);
//        PowerManager.WakeLock wl = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, "");
//        wl.acquire();

//        Intent myIntent=new Intent(m_Context,AlarmWorker.class);
//        PendingIntent pi=PendingIntent.getActivity(m_Context,0,myIntent, PendingIntent.FLAG_MUTABLE);

//        Uri soundUri = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
//        Ringtone r = RingtoneManager.getRingtone(m_Context, soundUri);
//        r.play();
        if(alarmType == ""||notificationContent == "")
        {
            NotificationCompat.Builder builder =  JooyaNotificationManager.getNotificationBuilder(m_Context);
            builder.setDefaults(Notification.DEFAULT_SOUND);
            builder.setContentText("alarm type or content is null");
            JooyaNotificationManager.display(m_Context,builder);
        }
        if (alarmType.equals("Notification")) {
            NotificationCompat.Builder builder =  JooyaNotificationManager.getNotificationBuilder(m_Context);
            builder.setDefaults(Notification.DEFAULT_SOUND);
            builder.setContentText(notificationContent);
            JooyaNotificationManager.display(m_Context,builder);
        }
        else if (alarmType.equals("Page")) {
            JooyaNotificationManager.showFullScreenNotification(m_Context,notificationContent);
        }

//        wl.release();
        ///send data as output of worker
//        Data output=new Data.Builder()
//            .putInt("number",18)
//            .build();
//return Result.success(output);

        return Result.success();
    }
}

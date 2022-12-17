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
//        Data inputData=getInputData();
//        String name = inputData.getString("name");
//        int number = inputData.getInt(key:"number", defaultValue:-1);
//        Log.i(TAG, "number=> "+number);

//        Toast.makeText(this, "AlarmWorker.doWork()", Toast.LENGTH_LONG).show();
        Log.i(TAG, "***[ Is Showing Alram Notification ]***");
        Log.i(TAG, "m_Context == null => "+(m_Context ==null));

//        PowerManager pm = (PowerManager) m_Context.getSystemService(Context.POWER_SERVICE);
//        PowerManager.WakeLock wl = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, "");
//        wl.acquire();

//        Intent myIntent=new Intent(m_Context,AlarmWorker.class);
//        PendingIntent pi=PendingIntent.getActivity(m_Context,0,myIntent,0);

//        Uri soundUri = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
//        Ringtone r = RingtoneManager.getRingtone(m_Context, soundUri);
//        r.play();

        Intent alarmIntent = new Intent(m_Context,AlarmActivity.class);
        alarmIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        alarmIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        m_Context.startActivity(alarmIntent);

//        wl.release();
        ///send data as output of worker
//        Data output=new Data.Builder()
//            .putInt("number",18)
//            .build();
//return Result.success(output);

        return Result.success();
    }
}

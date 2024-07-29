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


public class PermissionManager
{

    private static final String TAG = "PermissionManager";
    public static boolean requestIgnoringBatteryOptimizations(Context context)
    {
        Log.i(TAG, "is going to ignore battery optimization?");
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            String packageName = context.getPackageName();
            PowerManager pm = (PowerManager) context.getSystemService(Context.POWER_SERVICE);
            if (pm.isIgnoringBatteryOptimizations(packageName))
            {
               return true;
            }
            Intent intent = new Intent(Settings.ACTION_REQUEST_IGNORE_BATTERY_OPTIMIZATIONS);
            intent.setData(Uri.parse("package:" + packageName));
            if (!(context instanceof Activity)) {
                intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            }
            context.startActivity(intent);
            return false;
        }
        return true;
    }
}


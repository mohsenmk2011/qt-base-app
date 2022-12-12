package org.jooya.jooyaqtapplication;

import android.app.Notification;
import android.app.Application;
import android.os.Build;
import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;
import android.graphics.Color;
import android.graphics.BitmapFactory;
import android.app.NotificationChannel;
import org.jooya.jooyaqtapplication.R;
import org.qtproject.qt5.android.bindings.QtApplication;

public class JooyaApplication extends QtApplication{
    public static final String CHANNEL_ID = "org.jooya.jooyaqtapplication.ForegroundServiceChannel";

    @Override
    public void onCreate() {
        super.onCreate();
        System.out.println("***[ Creating Notification Channel ]***");
        try
        {
            createNotificationChannel();
        }
        catch(Exception e)
        {
            System.out.println("Error " + e.getMessage());
        }
    }
    public void createNotificationChannel(){
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            NotificationChannel notificationChannel = new NotificationChannel(
                CHANNEL_ID,
                "Jooya BimehPardaz Service Channel",
                NotificationManager.IMPORTANCE_DEFAULT
            );
            NotificationManager manager=getSystemService(NotificationManager.class);
            manager.createNotificationChannel(notificationChannel);
        }
    }
}

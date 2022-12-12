package org.jooya.jooyaqtapplication;
import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;
import android.graphics.Color;
import android.graphics.BitmapFactory;
import android.app.NotificationChannel;
import org.jooya.jooyaqtapplication.R;
import org.qtproject.qt5.android.QtNative;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;

public class ShareManager
{
    public static void share(Activity context,String text) {
        Intent sendIntent = new Intent();
        sendIntent.setAction(Intent.ACTION_SEND);
        sendIntent.putExtra(Intent.EXTRA_TEXT, text);
        sendIntent.setType("text/plain");
        context.startActivity(Intent.createChooser(sendIntent, text));
    }
}

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
import org.qtproject.qt.android.bindings.QtActivity;
import androidx.core.app.NotificationCompat;
import android.os.Build;
import android.content.res.Resources;
import android.util.Log;

public class JooyaNotificationManager
{
    private static final String CHANNEL_NAME = "Full Screen Channel";
    private static final String CHANNEL_DESC = "Channel for full-screen notifications";

    public JooyaNotificationManager() {}

    public static String getChannelId(Context context) {
          Resources res = context.getResources();
          String packageName = res.getString(R.string.app_package_name);
          return packageName + ".jooyaqtquickchannelid";
    }

    public static NotificationCompat.Builder getNotificationBuilder(Context context)
    {
        createNotificationChannel(context);
        Intent intent=new Intent(context,MainActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP);
        PendingIntent pi=PendingIntent.getActivity(context,0,intent, PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE);

        NotificationCompat.Builder builder = new NotificationCompat.Builder(context, getChannelId(context))
            .setSmallIcon(R.drawable.icon)
            .setLargeIcon(BitmapFactory.decodeResource(context.getResources(), R.drawable.icon))
            .setContentTitle(PackageinfoManager.getApplicationPersianName(context))
            // .setContentText(message)
            .setPriority(NotificationCompat.PRIORITY_HIGH)
            //.setCategory(NotificationCompat.CATEGORY_MESSAGE)
            .setCategory(NotificationCompat.CATEGORY_EVENT)
            //.setCategory(NotificationCompat.CATEGORY_CALL)
            .setColor(Color.GREEN)
            .setContentIntent(pi)
            //.addAction(R.drawable.notif_icon, "Buy", intent)
            //.addAction(R.drawable.notif_icon, "Product details", intent)
            .setAutoCancel(true);

        return builder;
    }
    public static void display(Context context,NotificationCompat.Builder builder)
    {
        if (builder == null) {
            builder = getNotificationBuilder(context);
        }
        NotificationManager notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        if (notificationManager != null) {
            notificationManager.notify(1, builder.build());
        }
    }
    public static void cancelAll()
    {
        //m_notificationManager = (NotificationManager)m_instance.getSystemService(Context.NOTIFICATION_SERVICE);
        //m_notificationManager.cancel(1);
    }

    public static void createNotificationChannel(Context context) {        
        String CHANNEL_ID = getChannelId(context);
        Log.i("TAG", "%%%[ CHANNEL_ID => "+ CHANNEL_ID);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            NotificationChannel channel = new NotificationChannel(
                    CHANNEL_ID,
                    CHANNEL_NAME,
                    NotificationManager.IMPORTANCE_HIGH
            );
            channel.setDescription(CHANNEL_DESC);
            channel.setLockscreenVisibility(Notification.VISIBILITY_PUBLIC);

            NotificationManager manager = context.getSystemService(NotificationManager.class);
            if (manager != null) {
                manager.createNotificationChannel(channel);
            }
        }
    }
    // doc link: https://developer.android.com/develop/ui/views/notifications/navigation#ExtendedNotification
    public static void showSpecialActivity(Context context,String title, String message) {
       // not implemented
    }
    // doc link:https://developer.android.com/develop/ui/views/notifications/build-notification#urgent-message
    // full screen intent limits : https://source.android.com/docs/core/permissions/fsi-limits
    // will display full screen when screen is lock,otherwise will display notification for user
    public static void showFullScreenNotification(Context context, String message) {
       Intent fullScreenIntent = new Intent(context, AlarmActivity.class);
       PendingIntent fullScreenPendingIntent = PendingIntent.getActivity(
               context,
               0,
               fullScreenIntent,
               PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE
       );

       NotificationCompat.Builder builder = getNotificationBuilder(context);
       builder.setContentText(message);
       builder.setCategory(NotificationCompat.CATEGORY_CALL);
       builder.setFullScreenIntent(fullScreenPendingIntent, true);
       builder.setAutoCancel(true);

       display(context,builder);
   }
}

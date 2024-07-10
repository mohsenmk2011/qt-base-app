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
    public static String CHANNEL_ID = "full_screen_channel_id";
    private static final String CHANNEL_NAME = "Full Screen Channel";
    private static final String CHANNEL_DESC = "Channel for full-screen notifications";

    public JooyaNotificationManager() {}

    public static String getChannelId(Context context) {
          Resources res = context.getResources();
          String packageName = res.getString(R.string.app_package_name);
          return packageName + ".jooyaqtquickchannelid";
    }

    public static void notify(Context context,String title, String message)
    {
        createNotificationChannel(context);
        Intent intent=new Intent(context,QtActivity.class);
        PendingIntent pi=PendingIntent.getActivity(context,0,intent, PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE);

        NotificationCompat.Builder builder = new NotificationCompat.Builder(context, CHANNEL_ID)
            .setSmallIcon(R.drawable.icon)
            .setLargeIcon(BitmapFactory.decodeResource(context.getResources(), R.drawable.icon))
            .setContentTitle(title)
            .setContentText(message)
            .setPriority(NotificationCompat.PRIORITY_HIGH)
            //.setCategory(NotificationCompat.CATEGORY_MESSAGE)
            //.setCategory(NotificationCompat.CATEGORY_EVENT)
            //.setCategory(NotificationCompat.CATEGORY_PROGRESS)
            //.setCategory(NotificationCompat.CATEGORY_CALL)
            .setDefaults(Notification.DEFAULT_SOUND)
            .setColor(Color.GREEN)
            .setContentIntent(pi)
            //.addAction(R.drawable.notif_icon, "Buy", intent)
            //.addAction(R.drawable.notif_icon, "Product details", intent)
            .setAutoCancel(true);

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
        CHANNEL_ID = getChannelId(context);
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
    public static void showFullScreenNotification(Context context,String title, String message) {
       createNotificationChannel(context);

       Intent myAppActivityIntent = new Intent(context, MainActivity.class);
       PendingIntent myAppPI = PendingIntent.getActivity(
               context,
               0,
               myAppActivityIntent,
               PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE
       );

       Intent fullScreenIntent = new Intent(context, AlarmActivity.class);
       PendingIntent fullScreenPendingIntent = PendingIntent.getActivity(
               context,
               0,
               fullScreenIntent,
               PendingIntent.FLAG_UPDATE_CURRENT | PendingIntent.FLAG_IMMUTABLE
       );

       NotificationCompat.Builder builder = new NotificationCompat.Builder(context, CHANNEL_ID)
           .setSmallIcon(R.drawable.icon)
           .setLargeIcon(BitmapFactory.decodeResource(context.getResources(), R.drawable.icon))
           .setContentTitle(title)
           .setContentText(message)
           .setPriority(NotificationCompat.PRIORITY_HIGH)
           //.setCategory(NotificationCompat.CATEGORY_ALARM)
           .setCategory(NotificationCompat.CATEGORY_CALL)
           .setFullScreenIntent(fullScreenPendingIntent, true)
           .setContentIntent(myAppPI)
           .setAutoCancel(true);

       NotificationManager notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
       if (notificationManager != null) {
           notificationManager.notify(1, builder.build());
       }
   }
}

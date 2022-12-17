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
import org.qtproject.qt5.android.bindings.QtActivity;

public class NotificationClient
{
    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;

    public NotificationClient() {}

    public static Notification notify(Context context,String title, String message)
    {
        try {

            Intent intent=new Intent(context,QtActivity.class);
            PendingIntent pi=PendingIntent.getActivity(context,0,intent,0);

            m_notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);

            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
                int importance = NotificationManager.IMPORTANCE_DEFAULT;
                NotificationChannel notificationChannel = new NotificationChannel("QtServiceChannelBimehpardaz", "Qt Service Channel", importance);
                m_notificationManager.createNotificationChannel(notificationChannel);
                m_builder = new Notification.Builder(context, notificationChannel.getId());
            } else {
                m_builder = new Notification.Builder(context);
            }

            m_builder
                    .setSmallIcon(R.drawable.icon)
                    .setLargeIcon(BitmapFactory.decodeResource(context.getResources(), R.drawable.icon))
                    .setContentTitle(title)
                    .setContentText(message)
                    .setDefaults(Notification.DEFAULT_SOUND)
                    .setColor(Color.GREEN)
                    .setContentIntent(pi)
//                    .addAction(R.drawable.notif_icon, "Buy", intent)
//                    .addAction(R.drawable.notif_icon, "Product details", intent)
                    .setAutoCancel(true);
            m_notificationManager.notify(0, m_builder.build());
        } catch (Exception e) {
            e.printStackTrace();
        }
        return m_builder.build();
    }
    public static void cancelAll()
    {
        //m_notificationManager = (NotificationManager)m_instance.getSystemService(Context.NOTIFICATION_SERVICE);
        //m_notificationManager.cancel(1);
    }
}

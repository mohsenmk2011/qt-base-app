package org.jooya.jooyaqtapplication;
import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;
import android.graphics.Color;
import android.graphics.BitmapFactory;
import android.app.NotificationChannel;
import android.os.Bundle;
import android.util.Log;
import org.jooya.jooyaqtapplication.R;
import org.qtproject.qt5.android.bindings.QtActivity;
import android.net.Uri;

public class MainActivity extends QtActivity
{
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.e("jooya", " ================== < onCreate > ================== ");
        handleIntent(getIntent());
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        Log.e("jooya", " ================== < onNewIntent > ================== ");
        handleIntent(intent);
    }

    private void handleIntent(Intent intent)
    {
        if (intent == null)
        {
            return;
        }
        String action = intent.getAction();

        Log.e("jooya", "action => " + action);
        if(action == "android.intent.action.VIEW"){
            Log.e("jooya", " ================== < check deep link > ================== ");
            handleDeepLink(intent);
        }
    }
    private void handleDeepLink(Intent intent)
    {
        Uri data = intent.getData();
        if (data == null) {
            return;
        }
        Log.e("jooya", "link => " + data);
        String id = data.getQueryParameter("id");
        Log.e("jooya", "orderId => " + id);
        // Pass the order id to the Qt Quick application
        // this id will receive in AndroidDeepLinkManager.cpp
        DeepLinkManager.sendToQtApp(id);
    }

}

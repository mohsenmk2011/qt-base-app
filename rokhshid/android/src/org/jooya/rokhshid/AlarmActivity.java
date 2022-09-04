package org.jooya.rokhshid;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.os.Build;
import android.app.Activity;
import android.app.KeyguardManager;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;
import android.view.Window;
import android.widget.ImageView;
import android.util.Log;
import java.lang.Thread;
import java.lang.InterruptedException;

import android.media.MediaPlayer;

public class AlarmActivity extends Activity{
    MediaPlayer mPlayer;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);

        setContentView(R.drawable.alarmlayout);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O_MR1) {
            setShowWhenLocked(true);
            setTurnScreenOn(true);
            KeyguardManager km=(KeyguardManager) getSystemService(this.KEYGUARD_SERVICE);
            km.requestDismissKeyguard(this,null);
        }
        else
        {
            getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON|
                        WindowManager.LayoutParams.FLAG_DISMISS_KEYGUARD|
                        WindowManager.LayoutParams.FLAG_SHOW_WHEN_LOCKED|
                        WindowManager.LayoutParams.FLAG_TURN_SCREEN_ON);
        }
        playWakeupAudio();
    }
    private void playWakeupAudio()
    {
        Log.i("AlarmActivity", "***[ Is palying alarm audio ]***");
        mPlayer = MediaPlayer.create(this, R.raw.alarm);
        mPlayer.start();
        mPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
            public void onCompletion(MediaPlayer mp) {
                if(true){
                    mp.start();
                }
            }
        });
    }
    public void onbtnFinishClick(View v){
        Log.i("AlarmActivity", "***[ Finish buttoon ]***");
        mPlayer.stop();
        finish();
    }
    @Override
    protected void onStop() {
        super.onStop();
        mPlayer.stop();
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        mPlayer.stop();
        mPlayer=null;
    }
}

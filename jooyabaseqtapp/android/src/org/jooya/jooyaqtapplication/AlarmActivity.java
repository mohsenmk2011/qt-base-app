package org.jooya.jooyaqtapplication;

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

import android.media.AudioManager;
import android.media.MediaPlayer;
import java.io.IOException;

import java.util.Timer;
import java.util.TimerTask;

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
            if (km != null) {
                km.requestDismissKeyguard(this, null);
            }
        }
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON|
                WindowManager.LayoutParams.FLAG_DISMISS_KEYGUARD|
                WindowManager.LayoutParams.FLAG_SHOW_WHEN_LOCKED|
                WindowManager.LayoutParams.FLAG_FULLSCREEN|
                WindowManager.LayoutParams.FLAG_TURN_SCREEN_ON);
        Timer timer = new Timer();
        TimerTask t = new TimerTask() {
            @Override
            public void run() {
                finish();
            }
        };
        timer.scheduleAtFixedRate(t,90000,9000);
    }
    @Override
    protected void onStart(){
        super.onStart();
        playWakeupAudio();
    }
    private void playWakeupAudio()
    {
        Log.i("AlarmActivity", "***[ Is palying alarm audio ]***");
        mPlayer = MediaPlayer.create(this, R.raw.alarm);
        AudioManager audioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
        audioManager.setStreamVolume(AudioManager.STREAM_MUSIC, 20, 0);
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

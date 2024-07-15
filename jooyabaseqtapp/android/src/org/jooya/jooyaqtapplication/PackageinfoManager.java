package org.jooya.jooyaqtapplication;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.util.Log;
import java.io.FileInputStream;
import java.security.MessageDigest;
import java.security.DigestInputStream;
import android.util.Base64;
import java.lang.Exception;
import java.io.IOException;
import java.security.NoSuchAlgorithmException;
import java.io.File;
import android.Manifest;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import android.app.Activity;

public class PackageinfoManager {
    private static final int REQUEST_CODE = 123; // You can use any value for the request code

    public static String getAppSign(Context context) {
        try {
            PackageInfo packageInfo = context.getPackageManager().getPackageInfo(context.getPackageName(), PackageManager.GET_SIGNATURES);
            Signature[] signatures = packageInfo.signatures;
            if (signatures != null && signatures.length > 0) {
                Log.i("PackageinfoManager",signatures[0].toCharsString());
                return signatures[0].toCharsString();
            }
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }
        return null;
    }
    public static String getApkHash(Context context,Activity activity) {
        try {
            // ================ Calulation of Hash of Apk file =====================
            String apkPath = context.getPackageCodePath();
            //String apkPath = "/data/app/com.copyprotection.balasplayer-1/base.apk";
            //String apkPath = "/sdcard/0-MyFiles/balas-soft-lock-and.apk";
            //String apkPath = "/sdcard/001/balas-soft-lock-and.apk";
            //String apkPath = "/sdcard/0-MyFiles/balas-soft-lock-and-1.apk";
            Log.e("jooya", " ================== < apkpath > ================== ");
            Log.e("jooya",apkPath);
            File file = new File(apkPath);
            if (file.exists()) {
                Log.e("jooya", " ================== < exists > ================== ");
            } else {
                Log.e("jooya", " ================== < not exists > ================== ");
            }
            Log.e("jooya", " ================== < ======= > ================== ");
            if (ContextCompat.checkSelfPermission(activity, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(activity, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, REQUEST_CODE);
            }
            FileInputStream fileInputStream = new FileInputStream(apkPath);
            MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");
            DigestInputStream digestInputStream = new DigestInputStream(fileInputStream, messageDigest);
            while (digestInputStream.read(new byte[2048]) != -1) {
            }
            digestInputStream.close();
            fileInputStream.close();
            return Base64.encodeToString(messageDigest.digest(), 2);
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return "";
    }
}


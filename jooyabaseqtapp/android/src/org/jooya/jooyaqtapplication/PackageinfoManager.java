package org.jooya.jooyaqtapplication;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.util.Log;

public class PackageinfoManager {

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
}


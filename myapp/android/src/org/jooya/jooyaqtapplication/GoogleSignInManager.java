package org.jooya.rokhshid;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.app.Activity;

/**
 * Google Sign-In bridge for the Qt application.
 *
 * Uses Google Identity Services (play-services-auth GoogleSignIn) to obtain an
 * id_token, then hands it to Qt through the JNI native method
 * GoogleSignInManager.sendIdTokenToQtApp(String) which is registered by
 * GoogleAuth.cpp (libs/loginlib).
 *
 * The web client id must be set here (serverClientId). The backend validates
 * the id_token with Google.Apis.Auth.
 */
public class GoogleSignInManager {

    private static final String TAG = "GoogleSignInManager";

    private static final int RC_SIGN_IN = 9001;

    public static native void sendIdTokenToQtApp(String idToken);
    public static native void sendSignInErrorToQtApp(String message);

    // webClientId => Web OAuth client id from Google Cloud Console (audience accepted by the backend).
    // get client id from google cloude console in client page-> create a client id with type=web and insert it in android app and your backend
    public static void signIn(Context context,String webClientId) {
        Log.i(TAG, "***[ google signing step 3: ]***");
        try {
            if (!(context instanceof Activity)) {
                Log.e(TAG, "context is not an Activity");
                sendSignInErrorToQtApp("no activity");
                return;
            }
            Activity activity = (Activity) context;
            com.google.android.gms.common.GoogleApiAvailability gapi =
                    com.google.android.gms.common.GoogleApiAvailability.getInstance();
            int code = gapi.isGooglePlayServicesAvailable(activity);
            if (code != com.google.android.gms.common.ConnectionResult.SUCCESS) {
                Log.e(TAG, "google play services not available => " + code);
                sendSignInErrorToQtApp("Google Play Services is not available");
                return;
            }
            com.google.android.gms.auth.api.signin.GoogleSignInOptions gso =
                    new com.google.android.gms.auth.api.signin.GoogleSignInOptions.Builder(
                            com.google.android.gms.auth.api.signin.GoogleSignInOptions.DEFAULT_SIGN_IN)
                            .requestIdToken(webClientId)
                            .requestEmail()
                            .build();
            com.google.android.gms.auth.api.signin.GoogleSignInClient client =
                    com.google.android.gms.auth.api.signin.GoogleSignIn.getClient(activity, gso);
            Intent intent = client.getSignInIntent();
            Log.i(TAG, "***[ google signing step 3: start signin activity ]***");
            activity.startActivityForResult(intent, RC_SIGN_IN);
        } catch (Exception e) {
            Log.e(TAG, "***[ google signing step 4: signIn failed => send error to qt application ]***", e);
            sendSignInErrorToQtApp(e.getMessage() == null ? e.toString() : e.getMessage());
        }
    }

    public static void handleSignInResult(int requestCode, int resultCode, Intent data) {
        Log.e(TAG, "***[ google signing step 4: signIn finished ]***");
        if (requestCode != RC_SIGN_IN) {
            return;
        }
        try {
            com.google.android.gms.tasks.Task<com.google.android.gms.auth.api.signin.GoogleSignInAccount> task =
                    com.google.android.gms.auth.api.signin.GoogleSignIn.getSignedInAccountFromIntent(data);
            com.google.android.gms.auth.api.signin.GoogleSignInAccount account = task.getResult(
                    com.google.android.gms.common.api.ApiException.class);
            if (account == null || account.getIdToken() == null) {
                Log.e(TAG, "no id token in sign in result");
                sendSignInErrorToQtApp("id_token دریافت نشد");
                return;
            }
            Log.e(TAG, "google sign in succeed => send id token to qt app");
            Log.i(TAG, "google id token received (length=" + account.getIdToken().length() + ")");
            sendIdTokenToQtApp(account.getIdToken());
        } catch (com.google.android.gms.common.api.ApiException e) {
            Log.e(TAG, "google sign in failed => send statusCode to qt app" + e.getStatusCode(), e);
            sendSignInErrorToQtApp("ورود با گوگل انجام نشد (کد " + e.getStatusCode() + ")");
        } catch (Exception e) {
            Log.e(TAG, "google sign in failed => send error to qt app", e);
            sendSignInErrorToQtApp(e.getMessage() == null ? e.toString() : e.getMessage());
        }
    }
}

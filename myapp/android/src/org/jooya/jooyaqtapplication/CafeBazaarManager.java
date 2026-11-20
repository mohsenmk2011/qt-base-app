package org.jooya.jooyaqtapplication;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.util.Log;

import ir.cafebazaar.purchase.IabHelper;
import ir.cafebazaar.purchase.IabResult;
import ir.cafebazaar.purchase.Purchase;

/**
 * Cafe Bazaar in-app billing bridge for the Qt application.
 *
 * Uses the Cafe Bazaar IAB SDK (ir.cafebazaar.purchase.IabHelper) to start the
 * Bazaar purchase UI and hand the resulting purchase token to Qt through the
 * JNI native method CafeBazaarManager.sendPurchaseResultToQtApp(...) which is
 * registered by CafebazaarPaymentManager.cpp (libs/purchasinglib).
 *
 * The SDK .aar/jar must be placed in myapp/android/libs/ (the gradle build
 * already loads *.jar/*.aar from that folder). Make sure these permissions are
 * in the manifest:
 *   - com.farsitel.bazaar.permission.PAY_THROUGH_BAZAAR
 *   - android.permission.INTERNET
 *
 * The classic Bazaar IAB SDK ("IabHelper") mirrors Google Play Billing v3 and is
 * the most widely used integration for Cafe Bazaar. Newer Bazaar SDKs expose a
 * slightly different API; if your SDK version differs, adjust the calls below.
 */
public class CafeBazaarManager {

    private static final String TAG = "CafeBazaarManager";
    private static final int RC_PURCHASE = 3346;
    private static final String BAZAAR_PACKAGE = "com.farsitel.bazaar";

    private static IabHelper mHelper;

    public static native void sendPurchaseResultToQtApp(String purchaseToken, String sku,
                                                        boolean success, String message);

    /**
     * Starts the Cafe Bazaar purchase UI for the given product SKU.
     * Called from Qt via JNI (CafebazaarPaymentManager.startPurchase).
     */
    public static void startPurchase(Context context, String sku) {
        Log.i(TAG, "***[ cafe bazaar step 1: startPurchase sku=" + sku + " ]***");
        if (!isBazaarInstalled(context)) {
            sendPurchaseResultToQtApp("", sku, false, "کافه بازار روی این دستگاه نصب نیست");
            return;
        }
        if (!(context instanceof Activity)) {
            Log.e(TAG, "context is not an Activity");
            sendPurchaseResultToQtApp("", sku, false, "no activity");
            return;
        }
        try {
            if (mHelper == null) {
                // The classic Bazaar IabHelper does not need a base64 key.
                mHelper = new IabHelper(context);
                mHelper.enableDebugLogging(true);
            }
            final Activity activity = (Activity) context;
            final String skuToBuy = sku;

            mHelper.startSetup(new IabHelper.OnIabSetupFinishedListener() {
                @Override
                public void onIabSetupFinished(IabResult result) {
                    if (!result.isSuccess()) {
                        Log.e(TAG, "***[ cafe bazaar step 2: setup failed ]*** " + result.getMessage());
                        sendPurchaseResultToQtApp("", skuToBuy, false,
                                "راه‌اندازی پرداخت کافه بازار انجام نشد: " + result.getMessage());
                        return;
                    }
                    Log.i(TAG, "***[ cafe bazaar step 2: setup ok, launch purchase flow ]***");
                    mHelper.launchPurchaseFlow(activity, skuToBuy, RC_PURCHASE,
                            new IabHelper.OnIabPurchaseFinishedListener() {
                                @Override
                                public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
                                    if (result.isSuccess() && purchase != null) {
                                        String token = purchase.getToken();
                                        String purchasedSku = purchase.getSku();
                                        Log.i(TAG, "***[ cafe bazaar step 3: purchase succeed ]*** token="
                                                + (token == null ? "" : token));
                                        sendPurchaseResultToQtApp(token, purchasedSku, true,
                                                "خرید با موفقیت انجام شد");
                                    } else {
                                        String msg = result == null ? "خطا" :
                                                (result.getMessage() == null ? "لغو شد" : result.getMessage());
                                        Log.e(TAG, "***[ cafe bazaar step 3: purchase failed ]*** " + msg);
                                        sendPurchaseResultToQtApp("", skuToBuy, false, msg);
                                    }
                                }
                            }, "order"); // payload; can carry an order reference if needed
                }
            });
        } catch (Exception e) {
            Log.e(TAG, "***[ cafe bazaar startPurchase failed ]***", e);
            sendPurchaseResultToQtApp("", sku, false,
                    e.getMessage() == null ? e.toString() : e.getMessage());
        }
    }

    /**
     * Must be forwarded from the Activity's onActivityResult.
     * Called by MainActivity.onActivityResult.
     */
    public static void handleActivityResult(int requestCode, int resultCode, Intent data) {
        Log.i(TAG, "***[ cafe bazaar handleActivityResult ]*** requestCode=" + requestCode);
        if (requestCode == RC_PURCHASE) {
            if (mHelper != null) {
                mHelper.handleActivityResult(requestCode, resultCode, data);
            } else {
                Log.e(TAG, "mHelper is null, cannot handle activity result");
                sendPurchaseResultToQtApp("", "", false, "نتیجه پرداخت دریافت نشد");
            }
        }
    }

    private static boolean isBazaarInstalled(Context context) {
        try {
            context.getPackageManager().getPackageInfo(BAZAAR_PACKAGE, 0);
            return true;
        } catch (PackageManager.NameNotFoundException e) {
            return false;
        }
    }
}


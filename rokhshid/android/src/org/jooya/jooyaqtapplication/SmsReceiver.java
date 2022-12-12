package org.jooya.rokhshid;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.content.BroadcastReceiver;
import android.content.IntentFilter;
import android.widget.Toast;
import java.lang.Object;
import android.telephony.SmsMessage;
import android.os.Bundle;

public class SmsReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        // Get SMS map from Intent
//        if(context == null || intent == null || intent.getAction() == null){
//            return;
//        }
//        if (intent.getAction().equals(Telephony.Sms.Intents.SMS_RECEIVED_ACTION)) {
//            return;
//        }
//        var contentResolver = context.contentResolver;
//        var smsMessages = Telephony.Sms.Intents.geئtMessagesFromIntent(intent);
//        for (int i = 0; i < smsMessages.Count; i++) {
//            Toast.makeText(context, "Message from ${message.displayOriginatingAddress} : body ${message.messageBody}", Toast.LENGTH_SHORT).show();
//            putSmsToDatabase( contentResolver, message);
//        }

        if (intent.getAction().equals("android.provider.Telephony.SMS_RECEIVED")) {
            Bundle mBundle = intent.getExtras();
            SmsMessage[] msg;
            String smsFrom;
            if (mBundle != null) {
                try {
                    Object[] mPdus = (Object[]) mBundle.get("pdus");
                    msg = new SmsMessage[mPdus.length];
//                    Toast.makeText(context, "تعداد پیام / " + mPdus.length, Toast.LENGTH_LONG).show();
                    for (int i = 0; i < mPdus.length; i++) {
                        msg[i] = SmsMessage.createFromPdu((byte[]) mPdus[i]);
                        smsFrom = msg[i].getOriginatingAddress();
                        String smsBody = msg[i].getMessageBody();
//                        Toast.makeText(context, smsBody, Toast.LENGTH_LONG).show();

                        if(smsBody.contains("rokhshid")){
                            SmsManager.sendToQtApp(smsBody);
                         }
                        else{
//                            Toast.makeText(context, "سر شماره / " + smsFrom + " / متن: " + smsBody, Toast.LENGTH_LONG).show();
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }
}

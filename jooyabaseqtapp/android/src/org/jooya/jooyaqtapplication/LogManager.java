package org.jooya.rokhshid;

import android.util.Log;

public class LogManager {

    public static void log(String message) {
            StackTraceElement[] stackTrace = Thread.currentThread().getStackTrace();
            if (stackTrace.length > 3) {
                StackTraceElement element = stackTrace[3];
                String className = element.getClassName();
                String methodName = element.getMethodName();

                // Use className and methodName in your log statement
                String logTag = className + "/" + methodName;

                // Log the message
                Log.d(logTag, message);
            } else {
                // Handle the case where there might not be enough elements in the stack trace
                Log.d("jooya", message);
            }
        }
}

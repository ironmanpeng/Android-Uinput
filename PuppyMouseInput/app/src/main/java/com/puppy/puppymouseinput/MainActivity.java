package com.puppy.puppymouseinput;

import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private Context mContext;
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("uinput-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mContext = this;
        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText("isDeviceOpenSuccess: " + UinputNativeMethods.registerDevice());
        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(mContext,"我被点击了～～～", Toast.LENGTH_SHORT).show();
            }
        });

        tv.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View v) {
                Toast.makeText(mContext,"我被长按了～～～", Toast.LENGTH_SHORT).show();
                return false;
            }
        });

        new Thread(new Runnable() {
            @Override
            public void run() {
//                for(int i = 0; i < 20; i++) {
//                }
                UinputNativeMethods.setPointer(640, 360);
                try {
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                for(int i = 0; i < 20; i++){
                    UinputNativeMethods.handleMouseEvent(UinputNativeMethods.EV_REL,
                            10,-1, 0,0);
                    try {
                        Thread.sleep(15);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                }
                try {
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                for(int i = 0; i < 20; i++){
                    UinputNativeMethods.handleMouseEvent(UinputNativeMethods.EV_REL,
                            -1,-10, 0,0);
                    try {
                        Thread.sleep(15);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                try {
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                for(int i = 0; i < 20; i++){
                    UinputNativeMethods.handleMouseEvent(UinputNativeMethods.EV_REL,
                            -10,-1, 0,0);
                    try {
                        Thread.sleep(15);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                try {
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                for(int i = 0; i < 20; i++){
                    UinputNativeMethods.handleMouseEvent(UinputNativeMethods.EV_REL,
                            -1,10, 0,0);
                    try {
                        Thread.sleep(15);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                try {
                    Thread.sleep(4000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                for(int i=0; i < 300; i++){
                    UinputNativeMethods.handleMouseEvent(UinputNativeMethods.EV_KEY,
                            0,0, UinputNativeMethods.BTN_LEFT,UinputNativeMethods.KEY_DOWN);
                }

                try {
                    Thread.sleep(4000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                for(int i=0; i < 3; i++){
                    UinputNativeMethods.handleMouseEvent(UinputNativeMethods.EV_KEY,
                            0,0, UinputNativeMethods.BTN_LEFT,UinputNativeMethods.KEY_DOWN);
                }

                for(int i=0; i < 3; i++) {
                    UinputNativeMethods.handleMouseEvent(UinputNativeMethods.EV_KEY,
                            0, 0, UinputNativeMethods.BTN_LEFT, UinputNativeMethods.KEY_UP);
                }


                try {
                    Thread.sleep(4000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                for(int i=0; i < 3; i++){
                    UinputNativeMethods.handleMouseEvent(UinputNativeMethods.EV_KEY,
                            0,0, UinputNativeMethods.BTN_RIGHT,UinputNativeMethods.KEY_DOWN);
                }

                for(int i=0; i < 3; i++) {
                    UinputNativeMethods.handleMouseEvent(UinputNativeMethods.EV_KEY,
                            0, 0, UinputNativeMethods.BTN_RIGHT, UinputNativeMethods.KEY_UP);
                }
            }
        }).start();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}

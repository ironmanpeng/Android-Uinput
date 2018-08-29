package com.puppy.puppymouseinput;

public class UinputNativeMethods {
    public static int BTN_LEFT = 0x110;
    public static int BTN_RIGHT = 0x111;
    public static int EV_KEY = 0x01;
    public static int EV_REL = 0x02;
    public static int KEY_DOWN = 1;
    public static int KEY_UP = 0;

    public static native boolean registerDevice();

    public static native boolean unregisterDevice();

    public static native boolean handleMouseEvent(int type, int x, int y, int keycode, int keystaus);

    public static native boolean setPointer(int x, int y);



    //public static native boolean keyDown(int key);

    //public static native boolean keyUp(int key);

    //public static native boolean pointerMove(int x, int y);

    static {
        System.loadLibrary("uinput-lib");
    }
}

package com.github.hirakida;

public class HirakidaJNI {
    static {
        System.loadLibrary("hirakida");
    }

    public native void open();

    public native void close();

    public native String read();

    public native String read2();

    public native void write(String buf);

    public native void write2(String buf);
}

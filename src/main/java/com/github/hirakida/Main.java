package com.github.hirakida;

public final class Main {

    public static void main(String[] args) {
        HirakidaJNI jni = new HirakidaJNI();

        jni.open();
        jni.write("Hello!");

        String buf = jni.read();
        System.out.println(buf);

        jni.write2("Hello!!");

        buf = jni.read2();
        System.out.println(buf);

        jni.close();
    }
}

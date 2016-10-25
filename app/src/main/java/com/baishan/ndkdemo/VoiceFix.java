package com.baishan.ndkdemo;

/**
 * Created by RayYeung on 2016/10/21.
 */

public class VoiceFix {

    public static final int MODE_NORMAL = 1;
    public static final int MODE_LUOLI = 2;
    public static final int MODE_DASHU = 3;
    public static final int MODE_JINGSONG = 4;
    public static final int MODE_GAOGUAI = 5;
    public static final int MODE_KONGLING = 6;

    public static native void fix(String path,int mode);

    static {
        System.loadLibrary("fmod");
        System.loadLibrary("fmodL");
        System.loadLibrary("voiceFix");
    }

}

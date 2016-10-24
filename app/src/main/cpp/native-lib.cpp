#include <jni.h>
#include <android/log.h>
#include <unistd.h>
#include <string>
#include "inc/fmod.hpp"

#define LOGI(FORMAT,...)  __android_log_print(ANDROID_LOG_INFO,"rayyeung",FORMAT,##__VA_ARGS__)
#define LOGE(FORMAT,...)  __android_log_print(ANDROID_LOG_ERROR,"rayyeung",FORMAT,##__VA_ARGS__)

//使用命名空间  相当于java中的包
using namespace FMOD;

#define  MODE_NORMAL  1
#define  MODE_LUOLI  2
#define  MODE_DASHU  3
#define  MODE_JINGSONG  4
#define  MODE_GAOGUAI  5
#define  MODE_KONGLING  6

extern "C"
{
jstring
Java_com_baishan_ndkdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
JNIEXPORT jstring JNICALL
Java_com_baishan_ndkdemo_MainActivity_stringFromJNI2(JNIEnv *env, jobject instance) {

    // TODO

    return env->NewStringUTF("哈哈哈哈");
}
JNIEXPORT void JNICALL
Java_com_baishan_ndkdemo_VoiceFix_fix(JNIEnv *env, jclass type, jstring path_, jint mode) {
    const char *path = env->GetStringUTFChars(path_, 0);

    System *system;
    Sound *sound;
    //任意类型指针
    void *extradriverdata;
    Channel *channel;
    bool isplaying = true;

    try {
        System_Create(&system);
        system->init(32, FMOD_INIT_NORMAL, extradriverdata);
        system->createSound(path, FMOD_DEFAULT, 0, &sound);
        LOGI("路径：%s",path);
        switch (mode){
            //原声
            case MODE_NORMAL:
                //异步操作
                system->playSound(sound, 0, false, &channel);
                break;
        }
    }catch(...) {//...代表捕获所有异常
        LOGE("%s","异常");
        goto end;
    }
    system->update();
    //等待声音播放完成
    while (isplaying){
        channel->isPlaying(&isplaying);
        //休眠1秒
        usleep(1000*1000);
    }
    end:
        LOGI("%s","end");
    system->close();
    system->release();

    env->ReleaseStringUTFChars(path_, path);
}
}
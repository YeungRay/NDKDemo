#include <jni.h>
#include <android/log.h>
#include <unistd.h>
#include <string>
#include "inc/fmod.hpp"

#define LOGI(FORMAT, ...)  __android_log_print(ANDROID_LOG_INFO,"rayyeung",FORMAT,##__VA_ARGS__)
#define LOGE(FORMAT, ...)  __android_log_print(ANDROID_LOG_ERROR,"rayyeung",FORMAT,##__VA_ARGS__)

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

JNIEXPORT void JNICALL
Java_com_baishan_ndkdemo_VoiceFix_fix(JNIEnv *env, jclass type, jstring path_, jint mode) {
    const char *path = env->GetStringUTFChars(path_, 0);

    System *system;
    Sound *sound;
    //任意类型指针
    void *extradriverdata;
    Channel *channel;
    bool isplaying = true;
    DSP *dsp;
    float frequency;
    try {
        System_Create(&system);
        system->init(32, FMOD_INIT_NORMAL, extradriverdata);
        system->createSound(path, FMOD_DEFAULT, 0, &sound);
        LOGI("路径：%s", path);
        switch (mode) {
            //原声
            case MODE_NORMAL:
                //播放是异步的
                system->playSound(sound, 0, false, &channel);
                break;
            case MODE_LUOLI:
                //音效
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //改变音调参数
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2.5);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case MODE_DASHU:
                //音效
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //改变音调参数
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8);
                //并没有播放  update之后才会播放
                system->playSound(sound, 0, false, &channel);
                //对声音的改变 在play之后
                channel->addDSP(0, dsp);
                break;
            case MODE_JINGSONG:

                break;
            case MODE_GAOGUAI:
                system->playSound(sound, 0, false, &channel);
                channel->getFrequency(&frequency);
                frequency = frequency*1.6;
                channel->setFrequency(frequency);
                break;
            case MODE_KONGLING:
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
        }
    } catch (...) {//...代表捕获所有异常
        LOGE("%s", "异常");
        goto end;
    }
    system->update();
    //等待声音播放完成
    while (isplaying) {
        channel->isPlaying(&isplaying);
        //休眠1秒  需引入unix标准库
        usleep(1000 * 1000);
    }
    end:
    LOGI("%s", "end");
    system->close();
    system->release();

    env->ReleaseStringUTFChars(path_, path);
}
}
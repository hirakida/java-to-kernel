#include "com_github_hirakida_HirakidaJNI.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include "hirakida_ioctl.h"

#define DEV_FILE "/dev/hirakida"

int fd = 0;

JNIEXPORT void JNICALL Java_com_github_hirakida_HirakidaJNI_open(JNIEnv *env, jobject obj) {
    if (fd == 0) {
        fd = open(DEV_FILE, O_RDWR);
        if (fd == -1) {
            perror("open");
            exit(1);
        }
    }
}

JNIEXPORT void JNICALL Java_com_github_hirakida_HirakidaJNI_close(JNIEnv *env, jobject obj) {
    if (fd != 0) {
        close(fd);
    }
}

JNIEXPORT jstring JNICALL Java_com_github_hirakida_HirakidaJNI_read(JNIEnv *env, jobject obj) {
    char buf[HIRKIDA_BUF_SIZE];

    if (fd == 0) {
        open(env, obj);
    }

    if (read(fd, buf, sizeof(buf)) == -1) {
        perror("read");
    }

    jstring jbuf = (*env)->NewStringUTF(env, &(buf[0]));
    return jbuf;
}

JNIEXPORT void JNICALL Java_com_github_hirakida_HirakidaJNI_write(JNIEnv * env, jobject obj, jstring jbuf) {
    const char *buf;

    if (fd == 0) {
        open(env, obj);
    }

    buf = (*env)->GetStringUTFChars(env, jbuf, 0);

    if (write(fd, buf, sizeof(buf)) == -1) {
        perror("write");
    }

    (*env)->ReleaseStringUTFChars(env, jbuf, buf);
    return;
}

JNIEXPORT jstring JNICALL Java_com_github_hirakida_HirakidaJNI_read2(JNIEnv *env, jobject obj) {
    struct hirakida_ioctl_data data;
    memset(&data, 0, sizeof(data));

    if (fd == 0) {
        open(env, obj);
    }

    memset(&data, 0, sizeof(data));
    if (ioctl(fd, HIRKIDA_IOR, &data) == -1) {
        printf("errno=%d\n", errno);
        perror("ioctl");
    }

    jstring jbuf = (*env)->NewStringUTF(env, &(data.buf[0]));
    return jbuf;
}

JNIEXPORT void JNICALL Java_com_github_hirakida_HirakidaJNI_write2(JNIEnv *env, jobject obj, jstring jbuf) {
    const char *buf;
    struct hirakida_ioctl_data data;
    memset(&data, 0, sizeof(data));

    if (fd == 0) {
        open(env, obj);
    }

    buf = (*env)->GetStringUTFChars(env, jbuf, 0);

    strncpy(data.buf, buf, strnlen(buf, sizeof(data.buf)));
    if (ioctl(fd, HIRKIDA_IOW, &data) == -1) {
        printf("errno=%d\n", errno);
        perror("ioctl");
    }

    (*env)->ReleaseStringUTFChars(env, jbuf, buf);
    return;
}

/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_github_hirakida_HirakidaJNI */

#ifndef _Included_com_github_hirakida_HirakidaJNI
#define _Included_com_github_hirakida_HirakidaJNI
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_github_hirakida_HirakidaJNI
 * Method:    open
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_github_hirakida_HirakidaJNI_open
  (JNIEnv *, jobject);

/*
 * Class:     com_github_hirakida_HirakidaJNI
 * Method:    close
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_github_hirakida_HirakidaJNI_close
  (JNIEnv *, jobject);

/*
 * Class:     com_github_hirakida_HirakidaJNI
 * Method:    read
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_github_hirakida_HirakidaJNI_read
  (JNIEnv *, jobject);

/*
 * Class:     com_github_hirakida_HirakidaJNI
 * Method:    read2
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_github_hirakida_HirakidaJNI_read2
  (JNIEnv *, jobject);

/*
 * Class:     com_github_hirakida_HirakidaJNI
 * Method:    write
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_github_hirakida_HirakidaJNI_write
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_github_hirakida_HirakidaJNI
 * Method:    write2
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_github_hirakida_HirakidaJNI_write2
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif
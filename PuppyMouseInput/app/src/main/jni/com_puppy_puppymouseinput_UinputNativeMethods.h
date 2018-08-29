/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_puppy_puppymouseinput_UinputNativeMethods */

#ifndef _Included_com_puppy_puppymouseinput_UinputNativeMethods
#define _Included_com_puppy_puppymouseinput_UinputNativeMethods
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_puppy_puppymouseinput_UinputNativeMethods
 * Method:    registerDevice
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_puppy_puppymouseinput_UinputNativeMethods_registerDevice
        (JNIEnv *, jclass);

/*
 * Class:     com_puppy_puppymouseinput_UinputNativeMethods
 * Method:    unregisterDevice
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_puppy_puppymouseinput_UinputNativeMethods_unregisterDevice
        (JNIEnv *, jclass);

/*
 * Class:     com_puppy_puppymouseinput_UinputNativeMethods
 * Method:    handleMouseEvent
 * Signature: (IIIII)Z
 */
JNIEXPORT jboolean JNICALL Java_com_puppy_puppymouseinput_UinputNativeMethods_handleMouseEvent
        (JNIEnv *, jclass, jint, jint, jint, jint, jint);

/*
 * Class:     com_puppy_puppymouseinput_UinputNativeMethods
 * Method:    setPointer
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL Java_com_puppy_puppymouseinput_UinputNativeMethods_setPointer
        (JNIEnv *, jclass, jint, jint);

#ifdef __cplusplus
}
#endif
#endif
/*
 * TrackerController.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: centos
 */

#include "TrackerController.h"
#include <unistd.h>
#include <vector>
#include <string>

using namespace std;


JNIEXPORT jlong JNICALL Java_dk_itu_task_Tracker_createNativeTracker
  (JNIEnv *jenv , jclass, jstring facesFile, jstring eyesFile){

    const char* facesStr = jenv->GetStringUTFChars(facesFile , NULL);
    const char* eyesStr = jenv->GetStringUTFChars(eyesFile , NULL);
    string facesString(facesStr);
    string eyesString(eyesStr);
    jlong result = 0;

    result = (jlong)new Tracker(facesString , eyesStr);

    return result;
}


JNIEXPORT void JNICALL Java_dk_itu_task_Tracker_destroyNativeTracker
  (JNIEnv *, jclass, jlong thiz){

	delete (Tracker*) thiz;
}

JNIEXPORT jboolean JNICALL Java_dk_itu_task_Tracker_initNativeTracker
  (JNIEnv *, jclass, jlong thiz){

	return ((Tracker*)thiz)->init();
}


JNIEXPORT void JNICALL Java_dk_itu_task_Tracker_processNativeTracker
  (JNIEnv *, jclass, jlong thiz, jlong rgba , jlong gray ){

	((Tracker*)thiz)->process((*(Mat*)rgba),(*(Mat*)gray));
}




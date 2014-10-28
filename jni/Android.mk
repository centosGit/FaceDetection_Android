LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

OPENCV_CAMERA_MODULES:=on
OPENCV_INSTALL_MODULES:=on

include /home/centos/libraries/java/OpenCV-2.4.9-android-sdk/sdk/native/jni/OpenCV.mk

LOCAL_MODULE    := tracking
LOCAL_SRC_FILES := TrackerController.cpp Tracker.cpp

include $(BUILD_SHARED_LIBRARY)

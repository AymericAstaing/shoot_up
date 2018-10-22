LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

NDK_PROJECT_PATH = /Users/aymericastaing/Desktop/COCOS_ROOT/android-ndk-r18

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp                                  \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp                   \
                   $(LOCAL_PATH)/../../../Classes/Square.cpp                        \
                   $(LOCAL_PATH)/../../../Classes/Popup.cpp                         \
                   $(LOCAL_PATH)/../../../Classes/Utils.cpp                         \
                   $(LOCAL_PATH)/../../../Classes/GridView.cpp                      \
                   $(LOCAL_PATH)/../../../Classes/ShopScene.cpp                     \
                   $(LOCAL_PATH)/../../../Classes/Bullet.cpp                        \
                   $(LOCAL_PATH)/../../../Classes/Circle.cpp                        \
                   $(LOCAL_PATH)/../../../Classes/UserLocalStore.cpp                \
                   $(LOCAL_PATH)/../../../Classes/Line.cpp                          \
                   $(LOCAL_PATH)/../../../Classes/CustomTableViewCell.cpp           \
                   $(LOCAL_PATH)/../../../Classes/GameScene.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_LDLIBS := -llog

LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

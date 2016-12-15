LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

#traverse all the directory and subdirectory
define walk
  $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef

#traverse Classes Directory
ALLFILES = $(call walk, $(LOCAL_PATH)/../../Classes)

FILE_LIST := hellocpp/main.cpp
FILE_LIST += $(filter %.cpp, $(ALLFILES))
FILE_LIST += $(filter %.cc, $(ALLFILES))
FILE_LIST += $(filter %.c, $(ALLFILES))

FILE_INCLUDES := $(shell find $(LOCAL_PATH)/../../Classes -type d)
FILE_INCLUDES += $(shell find $(LOCAL_PATH)/../../libs/cocos2dx/cocos2dx/platform/third_party/android -type d)

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
                   
LOCAL_C_INCLUDES :=  $(FILE_INCLUDES)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../libs/cocos2dx/extensions/CCArmature/utils

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static box2d_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions) \
$(call import-module,external/Box2D)

ifneq ($(TARGET_SIMULATOR),true)

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= eeprom_tool.c
LOCAL_MODULE := hermes_eeprom_tool
LOCAL_STATIC_LIBRARIES := libcutils libc
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

endif  # TARGET_SIMULATOR != true

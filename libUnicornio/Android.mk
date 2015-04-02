LOCAL_PATH := $(call my-dir)

CURRENT_PATH := $(LOCAL_PATH)

UNICORNIO_PATH := .
UNICORNIO_INCLUDE_PATH := $(UNICORNIO_PATH)/include
UNICORNIO_SOURCE_PATH := $(UNICORNIO_PATH)/src

SDL_PATH := $(UNICORNIO_PATH)/external/SDL2
SDL_IMAGE_PATH := $(UNICORNIO_PATH)/external/SDL2_image
SDL_TTF_PATH := $(UNICORNIO_PATH)/external/SDL2_ttf
SDL_MIXER_PATH := $(UNICORNIO_PATH)/external/SDL2_mixer
#SDL_NET_PATH := $(UNICORNIO_PATH)/external/SDL2_net
WEBP_PATH := $(SDL_IMAGE_PATH)/external/libwebp-0.3.0
MIKMOD_PATH := $(SDL_MIXER_PATH)/external/libmikmod-3.1.12
SMPEG2_PATH := $(SDL_MIXER_PATH)/external/smpeg2-2.0.0

# Enable this if you enabled this libraries inside SDL2_* libraries makefiles
#   Used by SDL2_image
ENABLED_WEBP := false
#   Used by SDL2_mixer
ENABLED_MIKMOD := false
ENABLED_SMPEG2 := false

# Enable these if you want to use prebuilt libraries
USE_PREBUILT_SDL        := false
USE_PREBUILT_SDL_IMAGE  := false
USE_PREBUILT_SDL_TTF    := false
USE_PREBUILT_SDL_MIXER  := false
#USE_PREBUILT_SDL_NET    := false

#--------------------------------
# libSDL2.so
ifeq ($(USE_PREBUILT_SDL), true)
    # Include prebuilt libSDL2.so
    include $(CLEAR_VARS)
    LOCAL_MODULE := SDL2
    LOCAL_SRC_FILES := $(UNICORNIO_PATH)/external/lib/Android/$(TARGET_ARCH_ABI)/libSDL2.so
    LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include
    include $(PREBUILT_SHARED_LIBRARY)
else
    # Build libSDL2.so
    include $(CURRENT_PATH)/$(SDL_PATH)/Android.mk
    LOCAL_PATH := $(CURRENT_PATH)
endif
#--------------------------------

#--------------------------------
# libSDL2_image.so
ifeq ($(USE_PREBUILT_SDL_IMAGE), true)
    # Include prebuilt libSDL2_image.so
    include $(CLEAR_VARS)
    LOCAL_MODULE := SDL2_image
    LOCAL_SRC_FILES := $(UNICORNIO_PATH)/external/lib/Android/$(TARGET_ARCH_ABI)/libSDL2_image.so
    LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(SDL_IMAGE_PATH)
    include $(PREBUILT_SHARED_LIBRARY)
else

    ifeq ($(ENABLED_WEBP), true)
        # Build libwebp.a (needed by SDL_image)
        include $(CURRENT_PATH)/$(WEBP_PATH)/Android.mk
        LOCAL_PATH := $(CURRENT_PATH)
    endif

    # Build libSDL2_image.so
    include $(CURRENT_PATH)/$(SDL_IMAGE_PATH)/Android.mk
    LOCAL_PATH := $(CURRENT_PATH)
endif
#--------------------------------

#--------------------------------
# libSDL2_ttf.so
ifeq ($(USE_PREBUILT_SDL_TTF), true)
    # Include prebuilt libSDL2_ttf.so
    include $(CLEAR_VARS)
    LOCAL_MODULE := SDL2_ttf
    LOCAL_SRC_FILES := $(UNICORNIO_PATH)/external/lib/Android/$(TARGET_ARCH_ABI)/libSDL2_ttf.so
    LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(SDL_TTF_PATH)
    include $(PREBUILT_SHARED_LIBRARY)
else
    # Build libSDL2_ttf.so
    include $(CURRENT_PATH)/$(SDL_TTF_PATH)/Android.mk
    LOCAL_PATH := $(CURRENT_PATH)
endif
#--------------------------------

#--------------------------------
# libSDL2_mixer.so
ifeq ($(USE_PREBUILT_SDL_MIXER), true)
    # Include prebuilt libSDL2_mixer.so
    include $(CLEAR_VARS)
    LOCAL_MODULE := SDL2_mixer
    LOCAL_SRC_FILES := $(UNICORNIO_PATH)/external/lib/Android/$(TARGET_ARCH_ABI)/libSDL2_mixer.so
    LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(SDL_MIXER_PATH)
    include $(PREBUILT_SHARED_LIBRARY)
else
    # Build libSDL2_mixer.so
    include $(CURRENT_PATH)/$(SDL_MIXER_PATH)/Android.mk
    LOCAL_PATH := $(CURRENT_PATH)
endif
#--------------------------------

#--------------------------------
# libSDL2_net.so
#ifeq ($(USE_PREBUILT_SDL_NET), true)
#    # Include prebuilt libSDL2_net.so
#    include $(CLEAR_VARS)
#    LOCAL_MODULE := SDL2_net
#    LOCAL_SRC_FILES := $(UNICORNIO_PATH)/external/lib/Android/$(TARGET_ARCH_ABI)/libSDL2_net.so
#    LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(SDL_NET_PATH)
#    include $(PREBUILT_SHARED_LIBRARY)
#else
#    # Build libSDL2_net.so
#    include $(CURRENT_PATH)/$(SDL_NET_PATH)/Android.mk
#    LOCAL_PATH := $(CURRENT_PATH)
#endif
#--------------------------------

ifeq ($(USE_PREBUILT_SDL_MIXER), true)

    ifeq ($(ENABLED_MIKMOD), true)
        # Include prebuilt libmikmod.so (needed by SDL_mixer)
        include $(CLEAR_VARS)
        LOCAL_MODULE := mikmod
        LOCAL_SRC_FILES := $(UNICORNIO_PATH)/external/lib/Android/$(TARGET_ARCH_ABI)/libmikmod.so
        LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(MIKMOD_PATH)/include
        include $(PREBUILT_SHARED_LIBRARY)
    endif

    ifeq ($(ENABLED_SMPEG2), true)
        # Include prebuilt libsmpeg2.so (needed by SDL_mixer)
        include $(CLEAR_VARS)
        LOCAL_MODULE := smpeg2
        LOCAL_SRC_FILES := $(UNICORNIO_PATH)/external/lib/Android/$(TARGET_ARCH_ABI)/libsmpeg2.so
        LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(SMPEG2_PATH)
        include $(PREBUILT_SHARED_LIBRARY)
    endif

else

    ifeq ($(ENABLED_MIKMOD), true)
        # Build libmikmod.so (needed by SDL_mixer)
        include $(CURRENT_PATH)/$(MIKMOD_PATH)/Android.mk
        LOCAL_PATH := $(CURRENT_PATH)
    endif

    ifeq ($(ENABLED_SMPEG2), true)
        # Build libsmpeg2.so (needed by SDL_mixer)
        include $(CURRENT_PATH)/$(SMPEG2_PATH)/Android.mk
        LOCAL_PATH := $(CURRENT_PATH)
    endif

endif


# Build libUnicornio.so
include $(CLEAR_VARS)
LOCAL_MODULE := Unicornio

LOCAL_SRC_FILES := \
$(patsubst $(LOCAL_PATH)/%, %, $(wildcard $(LOCAL_PATH)/$(UNICORNIO_SOURCE_PATH)/*.cpp)) \
$(patsubst $(LOCAL_PATH)/%, %, $(wildcard $(LOCAL_PATH)/$(UNICORNIO_SOURCE_PATH)/**/*.cpp))

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(UNICORNIO_INCLUDE_PATH) \
$(LOCAL_PATH)/$(UNICORNIO_INCLUDE_PATH)/Colisao \
$(LOCAL_PATH)/$(UNICORNIO_INCLUDE_PATH)/Eventos \
$(LOCAL_PATH)/$(UNICORNIO_INCLUDE_PATH)/Interface \
$(LOCAL_PATH)/$(UNICORNIO_INCLUDE_PATH)/json \
$(LOCAL_PATH)/$(UNICORNIO_INCLUDE_PATH)/Midia \
$(LOCAL_PATH)/$(UNICORNIO_INCLUDE_PATH)/TileMap

LOCAL_CPP_FEATURES += exceptions
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_ttf SDL2_mixer
include $(BUILD_SHARED_LIBRARY)



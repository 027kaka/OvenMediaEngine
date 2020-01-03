LOCAL_PATH := $(call get_local_path)
include $(DEFAULT_VARIABLES)

LOCAL_STATIC_LIBRARIES := \
	webrtc \
	transcoder \
	rtc_signalling \
	ice \
	jsoncpp \
	http_server \
	relay \
	dtls_srtp \
	rtp_rtcp \
	sdp \
	publisher \
	web_console \
	mediarouter \
	application \
	physical_port \
	socket \
	ovcrypto \
	config \
	ovlibrary \
	rtmpprovider \
	publishers \
	segment_stream \
	monitoring \
	jsoncpp \
	sqlite \
	rtsp \
	h264

LOCAL_PREBUILT_LIBRARIES := \
	libpugixml.a

LOCAL_LDFLAGS := -lpthread

ifeq ($(shell echo $${OSTYPE}),linux-musl) 
# For alpine linux
LOCAL_LDFLAGS += -lexecinfo
endif

$(call add_pkg_config,srt)
$(call add_pkg_config,libavformat)
$(call add_pkg_config,libavfilter)
$(call add_pkg_config,libavcodec)
$(call add_pkg_config,libswresample)
$(call add_pkg_config,libswscale)
$(call add_pkg_config,libavutil)
$(call add_pkg_config,openssl)
$(call add_pkg_config,vpx)
$(call add_pkg_config,opus)
$(call add_pkg_config,libsrtp2)

LOCAL_TARGET := OvenMediaEngine

include $(BUILD_EXECUTABLE)

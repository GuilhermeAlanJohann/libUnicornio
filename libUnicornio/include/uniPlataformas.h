#ifndef UNI_UNIPLATAFORMAS_H
#define UNI_UNIPLATAFORMAS_H

/* Windows (x64 and x86) */
#ifdef _WIN32
	#define UNI_PLATAFORMA_WINDOWS 1

#if defined(__WINRT__) && __WINRT__
	#define UNI_PLATAFORMA_WINDOWS_RT 1
#else
	#define UNI_PLATAFORMA_WINDOWS_RT 0
#endif

#ifdef WINAPI_FAMILY

	//	Windows Store App
	#if WINAPI_FAMILY_PARTITION( WINAPI_PARTITION_APP )
		#define UNI_PLATAFORMA_WINDOWS_APP 1
	#endif

	//	UWP App
	#if WINAPI_FAMILY_PARTITION( WINAPI_PARTITION_PC_APP )
		#define UNI_PLATAFORMA_WINDOWS_UNIVERSAL 1
	#endif

	//	Windows Phone 8
	#if WINAPI_FAMILY_PARTITION( WINAPI_PARTITION_PHONE_APP )
		//	windows phone 8 (precisa configurar um projeto para isso)
		#define UNI_PLATAFORMA_WINDOWS_PHONE 1	
	#else
		#define UNI_PLATAFORMA_WINDOWS_PHONE 0	
	#endif

	/*
	#if WINAPI_FAMILY_PARTITION( WINAPI_PARTITION_DESKTOP_APP )
	//	win32 desktop app
	#endif

	#if WINAPI_FAMILY_PARTITION( WINAPI_PARTITION_PHONE_APP )
	//	windows phone 8 (precisa configurar um projeto para isso)
		#define UNI_PLATAFORMA_WINDOWS_PHONE 1	
	#endif

	#if WINAPI_FAMILY_PARTITION( WINAPI_PARTITION_TV_TITLE )
	//	xbox one XDK (funciona? precisa sdk?)
	#endif

	#if WINAPI_FAMILY_PARTITION( WINAPI_PARTITION_APP_TITLE )
	//	xbox one ADK (funciona? precisa sdk?)
	#endif
	*/
	#else
		#define UNI_PLATAFORMA_WINDOWS_RT 0
		#define UNI_PLATAFORMA_WINDOWS_APP 0
		#define UNI_PLATAFORMA_WINDOWS_UNIVERSAL 0
		#define UNI_PLATAFORMA_WINDOWS_PHONE 0
	#endif
#else
	#define UNI_PLATAFORMA_WINDOWS 0
	#define UNI_PLATAFORMA_WINDOWS_RT 0
	#define UNI_PLATAFORMA_WINDOWS_APP 0
	#define UNI_PLATAFORMA_WINDOWS_UNIVERSAL 0
	#define UNI_PLATAFORMA_WINDOWS_PHONE 0
#endif

/* Unix */
#ifdef __unix__
	#define UNI_PLATAFORMA_UNIX 1
#else
	#define UNI_PLATAFORMA_UNIX 0
#endif

/* Linux */
#ifdef __linux__
	#define UNI_PLATAFORMA_LINUX 1
#else
	#define UNI_PLATAFORMA_LINUX 0
#endif

/* Android */
#if defined(ANDROID) || defined(__ANDROID__)
	#define UNI_PLATAFORMA_ANDROID 1
#else
	#define UNI_PLATAFORMA_ANDROID 0
#endif

/* Apple OSX and iOS (Darwin) */
#if defined(__APPLE__) && defined(__MACH__)

	#include <TargetConditionals.h>

	/* iOS in Xcode simulator */
    #if TARGET_IPHONE_SIMULATOR == 1
		#define UNI_PLATAFORMA_IOS_SIMULADOR 1
		#define UNI_PLATAFORMA_IOS 1
		#define UNI_PLATAFORMA_MAC 0
    	
	/* iOS on iPhone, iPad, etc. */ 
    #elif TARGET_OS_IPHONE == 1
		#define UNI_PLATAFORMA_IOS_SIMULADOR 0
		#define UNI_PLATAFORMA_IOS 1
		#define UNI_PLATAFORMA_MAC 0
    	   
	/* Mac */
    #elif TARGET_OS_MAC == 1
		#define UNI_PLATAFORMA_IOS_SIMULADOR 0
		#define UNI_PLATAFORMA_IOS 0
		#define UNI_PLATAFORMA_MAC 1
	#endif
#else
	#define UNI_PLATAFORMA_IOS_SIMULADOR 0
	#define UNI_PLATAFORMA_IOS 0
	#define UNI_PLATAFORMA_MAC 0
#endif

#if UNI_PLATAFORMA_ANDROID || UNI_PLATAFORMA_IOS || UNI_PLATAFORMA_WINDOWS_PHONE
	#define UNI_PLATAFORMA_MOVEL 1
#else
	#define UNI_PLATAFORMA_MOVEL 0
#endif

#endif
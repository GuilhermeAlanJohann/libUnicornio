#ifndef UNI_UNIPLATAFORMAS_H
#define UNI_UNIPLATAFORMAS_H

/* Windows (x64 and x86) */
#ifdef _WIN32
	#define UNI_PLATAFORMA_WINDOWS 1
#else
	#define UNI_PLATAFORMA_WINDOWS 0
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
#ifdef ANDROID
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

#if UNI_PLATAFORMA_ANDROID || UNI_PLATAFORMA_IOS
	#define UNI_PLATAFORMA_MOVEL 1
#else
	#define UNI_PLATAFORMA_MOVEL 0
#endif

#endif
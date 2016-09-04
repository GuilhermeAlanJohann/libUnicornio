#ifndef UNI_API

#ifdef UNICORNIO_SHARED
	#ifdef UNICORNIO_EXPORT
		#define UNI_API __declspec(dllexport)
	#else
		#define UNI_API __declspec(dllimport)
	#endif
#else
	#define UNICORNIO_STATIC
	#define UNI_API
#endif

#endif
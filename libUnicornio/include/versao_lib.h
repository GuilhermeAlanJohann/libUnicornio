#ifndef UNI_VERSAO_LIB_H
#define UNI_VERSAO_LIB_H
// libUnicornio: Cabecalho para configuracao automatica das bibliotecas no Visual Studio

#if _MSC_VER >= 1800
// Visual C++ 2013 ou mais recente
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_ttf.h"
	#include "SDL_mixer.h"	

	#ifndef _DEBUG
		#pragma message("RELEASE UNICORNIO: added libs: sdl2.lib sdl2main.lib sdl2_image.lib sdl2_ttf.lib sdl2_mixer.lib")
		#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2.lib")
		#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2main.lib")
		#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2_image.lib")
		#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2_ttf.lib")
		#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2_mixer.lib")
		#pragma comment(lib, "..//..//libUnicornio//lib//MSVS_2013//libUnicornio.lib")
	#else
		#pragma message("DEBUG UNICORNIO: added libs: sdl2.lib sdl2main.lib sdl2_image.lib sdl2_ttf.lib sdl2_mixer.lib")
		#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2.lib")
		#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2main.lib")
		#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2_image.lib")
		#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2_ttf.lib")
		#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2_mixer.lib")
		#pragma comment(lib, "..//..//libUnicornio//lib//MSVS_2013//libUnicornio_d.lib")
	#endif	
#else
	#if _MSC_VER >= 1700
	// Visual C++ 2012 ou mais recente
		#include "SDL.h"
		#include "SDL_image.h"
		#include "SDL_ttf.h"
		#include "SDL_mixer.h"	

		#ifndef _DEBUG
			#pragma message("RELEASE UNICORNIO: added libs: sdl2.lib sdl2main.lib sdl2_image.lib sdl2_ttf.lib sdl2_mixer.lib")
			#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2.lib")
			#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2main.lib")
			#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2_image.lib")
			#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2_ttf.lib")
			#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2_mixer.lib")
			#pragma comment(lib, "..//..//libUnicornio//lib//MSVS_2012//libUnicornio.lib")
		#else
			#pragma message("DEBUG UNICORNIO: added libs: sdl2.lib sdl2main.lib sdl2_image.lib sdl2_ttf.lib sdl2_mixer.lib")
			#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2.lib")
			#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2main.lib")
			#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2_image.lib")
			#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2_ttf.lib")
			#pragma comment(lib, "..//..//libUnicornio//SDL2//lib//x86//sdl2_mixer.lib")
			#pragma comment(lib, "..//..//libUnicornio//lib//MSVS_2012//libUnicornio_d.lib")
		#endif
	#endif
#endif

#endif
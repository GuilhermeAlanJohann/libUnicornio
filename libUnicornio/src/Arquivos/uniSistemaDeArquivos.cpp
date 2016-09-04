#include "uniSistemaDeArquivos.h"

string uniGetCaminhoPreferencias()
{
	string caminho;

#if UNI_PLATAFORMA_ANDROID
	caminho = string(SDL_AndroidGetExternalStoragePath());

#elif UNI_PLATAFORMA_IOS
	NSFileManager *filemgr;
	NSArray *dirPaths;
	NSString *libsDir;
	NSString *prefsDir;

	filemgr = [NSFileManager defaultManager];
	dirPaths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
	libsDir = [dirPaths objectAtIndex : 0];
	prefsDir = [docsDir stringByAppendingPathComponent : @"Preferences"];

	BOOL isDir;
	if ([fileManager fileExistsAtPath : prefsPath isDirectory : &isDir] && isDir) 
	{
		//	Diretório já existe
	}
	else
	{
		//	Cria o diretório para as preferências
		if ([filemgr createDirectoryAtPath : prefsDir attributes : nil] == NO)
		{
			// Erro ao criar diretório para as preferências
			return "";
		}
	}

	caminho = string([prefsDir UTF8String]);

	[filemgr release];

#elif UNI_PLATAFORMA_WINDOWS_RT
	caminho = SDL_WinRTGetFSPathUTF8(SDL_WINRT_PATH_LOCAL_FOLDER);

#else
	caminho = "./";
#endif

	return caminho;
}

/*string uniGetCaminhoDocumentos()
{
	string caminho;

#if UNI_PLATAFORMA_ANDROID
	caminho = string(SDL_AndroidGetExternalStoragePath());

#elif UNI_PLATAFORMA_IOS
	NSArray *dirPaths;
	NSString *docsDir;

	dirPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	docsDir = [dirPaths objectAtIndex : 0];
	
	caminho = string([docsDir UTF8String]);

#elif UNI_PLATAFORMA_WINDOWS_RT
	caminho = SDL_WinRTGetFSPathUTF8(SDL_WINRT_PATH_LOCAL_FOLDER);

#else
	caminho = "./";
#endif

	return caminho;
}*/


string uniGetNomeEExtencaoDoArquivo(const string& caminho)
{
	for (int i = caminho.size() - 1; i >= 0; --i)
	{
		if (caminho[i] == '/' || caminho[i] == '\\')
		{
			std::string nome = caminho.substr(i + 1);
			return nome;
		}
	}

	return caminho;
}

string uniGetExtencaoDoArquivo(const string& caminho)
{
	for (int i = caminho.size() - 1; i >= 0; --i)
	{
		if (caminho[i] == '.')
		{
			std::string ext = caminho.substr(i + 1);
			return ext;
		}
		else if (caminho[i] == '/' || caminho[i] == '\\')
		{
			return "";
		}
	}

	return "";
}
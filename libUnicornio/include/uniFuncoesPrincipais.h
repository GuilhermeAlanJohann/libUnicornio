#ifndef UNI_FUNCOESPRINCIPAIS_H
#define UNI_FUNCOESPRINCIPAIS_H

#include "uniPlataformas.h"
#include <string>
using namespace std;

#ifndef UNI_CALL_CONV
	#if UNI_PLATAFORMA_WINDOWS
		#define UNI_CALL_CONV _cdecl
	#else
		#define UNI_CALL_CONV
	#endif
#endif

struct UniVersao
{
	int maior;
	int menor;
	int patch;
};

bool UNI_CALL_CONV uniInicializar(int largura_janela, int altura_janela, bool tela_cheia = false, string titulo_janela = "libUnicornio");
void UNI_CALL_CONV uniFinalizar();
bool UNI_CALL_CONV uniEstaInicializada();

void UNI_CALL_CONV uniIniciarFrame(bool limitarFPS = true);
void UNI_CALL_CONV uniTerminarFrame(bool limpar_janela = true);

void UNI_CALL_CONV uniDormir(int milisec);
UniVersao UNI_CALL_CONV uniGetVersao();

#endif
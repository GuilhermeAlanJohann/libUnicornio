#ifndef UNI_FUNCOESPRINCIPAIS_H
#define UNI_FUNCOESPRINCIPAIS_H

#include "uniAPI.h"
#include "uniPlataformas.h"
#include <string>

using namespace std;

struct UNI_API UniVersao
{
	int maior;
	int menor;
	int patch;
};

bool UNI_API uniInicializar(int largura_janela, int altura_janela, bool tela_cheia = false, string titulo_janela = "libUnicornio", int flags_sdl_window = 0);
void UNI_API uniFinalizar();
bool UNI_API uniEstaInicializada();
	 
void UNI_API uniIniciarFrame(bool limitarFPS = true);
void UNI_API uniTerminarFrame(bool limpar_janela = true);
	 
void UNI_API uniDormir(int milisec);
UniVersao UNI_API uniGetVersao();

#endif
#ifndef UNI_FONTE_H
#define UNI_FONTE_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

using namespace std;

class Fonte
{
private:
	TTF_Font *font;
	string caminhoArquivo;
	int tamanho;

public:
	Fonte();
	~Fonte();

	bool carregar(string arquivo,int tamanho = 16);
	bool carregarMem(unsigned char mem[], int tamanho_mem, int tamanho = 16);

	int getTamanho();

	string getCaminhoDoArquivo();
	Fonte clonar();

	TTF_Font* getTTF_Font();
};

#endif
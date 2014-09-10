#ifndef UNI_FONTE_H
#define UNI_FONTE_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

using namespace std;

enum EstiloFonte
{
	FONTE_ESTILO_NORMAL = TTF_STYLE_NORMAL,
	FONTE_ESTILO_NEGRITO = TTF_STYLE_BOLD,
	FONTE_ESTILO_ITALICO = TTF_STYLE_ITALIC,
	FONTE_ESTILO_SUBLINHADO = TTF_STYLE_UNDERLINE,
	FONTE_ESTILO_RISCADO_AO_MEIO = TTF_STYLE_STRIKETHROUGH
};

class Fonte
{
private:
	TTF_Font *font;
	string caminhoArquivo;
	int tamanho;

	EstiloFonte estilo;

public:
	Fonte();
	~Fonte();

	bool carregar(string arquivo, int tamanho = 16, EstiloFonte estilo = FONTE_ESTILO_NORMAL);
	bool carregarMem(unsigned char mem[], int tamanho_mem, int tamanho = 16, EstiloFonte estilo = FONTE_ESTILO_NORMAL);
	void descarregar();
	bool estaCarregado();

	int getTamanho();
	EstiloFonte getEstilo();
	TTF_Font* getTTF_Font();
	string getCaminhoDoArquivo();

	void setEstilo(EstiloFonte estilo);

	Fonte clonar();
};

#endif
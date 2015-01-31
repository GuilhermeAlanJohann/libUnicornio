#ifndef UNI_FONTE_H
#define UNI_FONTE_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <map>

using namespace std;

enum TipoEstiloFonte
{
	FONTE_ESTILO_NORMAL = TTF_STYLE_NORMAL,
	FONTE_ESTILO_NEGRITO = TTF_STYLE_BOLD,
	FONTE_ESTILO_ITALICO = TTF_STYLE_ITALIC,
	FONTE_ESTILO_SUBLINHADO = TTF_STYLE_UNDERLINE,
	FONTE_ESTILO_RISCADO_AO_MEIO = TTF_STYLE_STRIKETHROUGH
};

struct Glifo
{
public:
	Glifo()
	{
		sdl_tex = NULL;
		caractere = 0;
		avanco = 0;
		larg = 0;
		alt = 0;
		alt_abaixo_da_base = 0;
		alt_acima_da_base = 0;
	}

	SDL_Texture *sdl_tex;
	Uint16 caractere;
	int avanco;
	int larg;
	int alt;
	int alt_abaixo_da_base;
	int alt_acima_da_base;
};

class Fonte
{
public:
	Fonte();
	~Fonte();

	bool carregar(string arquivo, int tamanho = 16, int estilo = FONTE_ESTILO_NORMAL);
	bool carregarMem(unsigned char mem[], int tamanho_mem, int tamanho = 16, int estilo = FONTE_ESTILO_NORMAL);
	void descarregar();
	bool estaCarregada();

	void preCarregarGlifos(string caracteres);
	void preCarregarGlifos(wstring caracteres);
	void preCarregarGlifos(Uint16 inicio, Uint16 fim);
	void preCarregarGlifo(Uint16 caractere);

	bool eMonoespacada();

	Glifo *getGlifo(Uint16 caractere);
	int getNumGlifosUsados();

	int getLarguraMaxDosGlifos();
	int getAlturaMaxDosGlifos();
	int getAlturaMaxDosGlifosAcimaDaBase();
	int getAlturaMaxDosGlifosAbaixoDaBase();

	int getTamanho();
	int getEstilo();

	TTF_Font *getTTF_Font();
	string getCaminhoDoArquivo();
	Fonte clonar();

private:
	bool criarGlifo(Uint16 ch, Glifo *&glifo);
	bool criarGlifoNulo();
	bool criarTexturaParaGlifo(int ch, SDL_Texture *&tex);

	bool carregada;
	bool carregada_da_memoria;

	std::map<Uint16, Glifo*> mapa_glifos;
	TTF_Font *font;

	int estilo;

	int largura_max_glifo;
	int altura_max_glifo;
	int altura_max_acima_da_base;
	int altura_max_abaixo_da_base;
	bool monoespacada;

	string caminho_arquivo;
};

#endif
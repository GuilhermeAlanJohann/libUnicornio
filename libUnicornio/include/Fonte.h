#ifndef UNI_FONTE_H
#define UNI_FONTE_H

#include <string>
#include <vector>
#include "EnumQualidadeEscala.h"
#include "Retangulo.h"
#include "Vetor2D.h"
#include "Cor.h"
#include "SDL_ttf.h"

using namespace std;


enum EnumEstiloFonte
{
	FONTE_ESTILO_NORMAL = TTF_STYLE_NORMAL,
	FONTE_ESTILO_NEGRITO = TTF_STYLE_BOLD,
	FONTE_ESTILO_ITALICO = TTF_STYLE_ITALIC,
	FONTE_ESTILO_SUBLINHADO = TTF_STYLE_UNDERLINE,
	FONTE_ESTILO_RISCADO_AO_MEIO = TTF_STYLE_STRIKETHROUGH
};

class Glifo: public Retangulo
{
public:
	Glifo() :caractere(0), avanco(0), alturaAcimaDaBase(0)
	{};

	Uint16 caractere;
	Uint16 avanco;
	Sint16 dx;
	Sint16 alturaAcimaDaBase;
};

class Fonte
{
public:
	Fonte();
	~Fonte();

	bool carregar(const string& arquivo, int tamanho = 16, int estilo = FONTE_ESTILO_NORMAL, Uint16 primeiro_glifo = 0, Uint16 ultimo_glifo = 255, EnumQualidadeEscala qualidade_escala = QUALIDADE_ESCALA_BAIXA);
	bool carregar(const string& arquivo, const wstring& caracteres, int num_glifos_x, int num_glifos_y, EnumQualidadeEscala qualidade_escala = QUALIDADE_ESCALA_BAIXA);
	bool carregar(const string& arquivo, const string& caracteres, int num_glifos_x, int num_glifos_y, EnumQualidadeEscala qualidade_escala = QUALIDADE_ESCALA_BAIXA);
	bool descarregar();
	bool estaCarregada();
	bool eMonoespacada();
	bool eTrueType();
	bool eBitmap();

	Glifo* getGlifo(Uint16 charactere);
	Glifo* getGlifoPeloIndice(Uint16 indice);
	Glifo* getGlifoNulo();

	int getNumGlifosX();
	int getNumGlifosY();
	int getNumGlifos();
	int getLarguraGlifos();
	int getAlturaGlifos();
	int getTamanho();
	int getAscent();
	int getEstilo();
	int getQualidadeEscala();
	
	SDL_Texture* getSDL_Texture();
	string getCaminhoDoArquivo();
	Fonte clonar();

	void setCaracteres(const string& caracteres, bool unsigned_char = true);
	void setCaracteres(const wstring& caracteres);

	void desenharGlifo(Uint16 caractere, const Retangulo& destino, const Cor& cor);
	void desenharGlifo(Uint16 caractere, int x_esq, int y_cima, int x_texto, int y_texto, float rot_texto, const Vetor2D& escala_texto, SDL_RendererFlip flip_mode, const Cor& cor);
	void desenharGlifo(Glifo* glifo, int x_esq, int y_cima, int x_texto, int y_texto, float rot_texto, const Vetor2D& escala_texto, SDL_RendererFlip flip_mode, const Cor& cor);
	
protected:
	bool carregarTrueType(const string& arquivo, int tamanho, int estilo, Uint16 primeiro_glifo, Uint16 ultimo_glifo, EnumQualidadeEscala qualidade_escala);
	bool carregarBitmap(const string& arquivo, const wstring& caracteres, int num_glifos_x, int num_glifos_y, EnumQualidadeEscala qualidade_escala);
	bool criarTexturaTrueType(TTF_Font* ttf_font, int tamanho, Uint16 primeiro_glifo, Uint16 ultimo_glifo, EnumQualidadeEscala qualidade_escala);
	bool criarTexturaBitmap(const string& arquivo, EnumQualidadeEscala qualidade_escala);

	bool carregada;
	bool ttf;

	SDL_Texture* sdl_texture;
	Uint8 qualidadeEscala;
	vector<Glifo> glifos;
	Glifo glifoNulo;

	int estilo;

	Uint16 numGlifosX;	
	Uint16 numGlifosY;	
	Uint16 larguraGlifos;
	Uint16 alturaGlifos;
	Uint16 ascent;
	bool monoespacada;

	string caminhoArquivo;
};

#endif
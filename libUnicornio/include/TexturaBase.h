#ifndef UNI_TEXTURABASE_H
#define UNI_TEXTURABASE_H

#include "uniAPI.h"
#include "SDL_image.h"
#include "Cor.h"
#include "Quad.h"
#include "Vetor2D.h"
#include "EnumQualidadeEscala.h"
#include <string>

using namespace std;

enum UNI_API EnumTipoTextura
{
	TEXTURA_ESTATICA	 = SDL_TEXTUREACCESS_STATIC,
	TEXTURA_DE_STREAMING = SDL_TEXTUREACCESS_STREAMING,
	TEXTURA_ALVO		 = SDL_TEXTUREACCESS_TARGET
};

enum UNI_API EnumInverterDesenho
{
	NAO_INVERTER = SDL_FLIP_NONE,
	INVERTER_X = SDL_FLIP_HORIZONTAL,
	INVERTER_Y = SDL_FLIP_VERTICAL,
	INVERTER_XY = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL
};

class UNI_API TexturaBase
{
public:
	TexturaBase();
	TexturaBase(const TexturaBase& t);
	virtual ~TexturaBase();

	TexturaBase& operator=(const TexturaBase& t);
	bool operator==(const TexturaBase& t);
	bool operator==(const TexturaBase& t) const;
	bool operator!=(const TexturaBase& t);
	bool operator!=(const TexturaBase& t) const;

	virtual bool destruir() = 0;
	bool estaCriada();

	int getTipo();

	int getLargura();
	int getAltura();
	Uint8 getQualidadeDeEscala();

	SDL_Texture* getSDL_Texture();

	void obterTamanho(int& larg, int& alt);

	bool desenhar(int x, int y, float rot = 0.0f, float ancora_x = 0.5f, float ancora_y = 0.5f, float escala_x = 1.0f, float escala_y = 1.0f, Cor cor = Cor(255, 255, 255, 255), EnumInverterDesenho inverter = NAO_INVERTER);
	bool desenhar(int x, int y, float rot, const Vetor2D ancora = Vetor2D(0.5f, 0.5f), const Vetor2D& escala = Vetor2D(1.0f, 1.0f), Cor cor = Cor(255, 255, 255, 255), EnumInverterDesenho inverter = NAO_INVERTER);
	bool desenhar(const Quad& retangulo, int x, int y, float rot = 0.0f, float ancora_x = 0.5f, float ancora_y = 0.5f, float escala_x = 1.0f, float escala_y = 1.0f, Cor cor = Cor(255, 255, 255, 255), EnumInverterDesenho inverter = NAO_INVERTER);
	bool desenhar(const Quad& retangulo, int x, int y, float rot, const Vetor2D ancora = Vetor2D(0.5f, 0.5f), const Vetor2D& escala = Vetor2D(1.0f, 1.0f), Cor cor = Cor(255, 255, 255, 255), EnumInverterDesenho inverter = NAO_INVERTER);
	bool desenhar(const Quad& retangulo, const Quad& destino, Cor cor = Cor(255, 255, 255, 255));

protected:
	bool _criar(int largura, int altura, int qualidade_escala, EnumTipoTextura tipo);
	bool _criarDoArquivo(const string& arquivo, int qualidade_escala);
	bool _destruir();

	SDL_Texture* sdl_texture;
	Sint16 largura;
	Sint16 altura;
	bool criada;
	Uint8 qualidadeEscala;
};

#endif
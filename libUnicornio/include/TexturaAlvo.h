#ifndef UNI_TEXTURAALVO_H
#define UNI_TEXTURAALVO_H

#include "uniAPI.h"
#include "TexturaBase.h"

class UNI_API TexturaAlvo: public TexturaBase
{
public:
	TexturaAlvo();
	TexturaAlvo(const TexturaAlvo& t);
	~TexturaAlvo();

	TexturaAlvo& operator=(const TexturaAlvo& t);

	bool criar(int largura, int altura, int qualidade_escala = QUALIDADE_ESCALA_BAIXA);
	bool destruir();

	bool ativar();
	bool desativar();
	bool estaAtiva();

	bool limpar(const Cor& cor);
	bool limpar(int r = 0, int g = 0, int b = 0, int a = 0);

private:
	SDL_Texture* alvoAnterior;
};

#endif
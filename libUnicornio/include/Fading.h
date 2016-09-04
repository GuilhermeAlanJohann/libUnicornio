#ifndef UNI_FADE_H
#define UNI_FADE_H

#include "uniAPI.h"
#include "Cor.h"

class UNI_API Fading
{
public:
	Fading();
	~Fading();

	void atualizar();
	void atualizar(double dt);
	void desenhar();

	void cancelar();

	void iniciarFadeIn();
	void iniciarFadeOut();
	void terminarFadeIn();
	void terminarFadeOut();

	bool estaExecutando();
	bool estaExecutandoFadeIn();
	bool estaExecutandoFadeOut();

	bool terminou();
	bool terminouFadeIn();
	bool terminouFadeOut();

	void setTerminouFadeIn(bool b);
	void setTerminouFadeOut(bool b);

	Cor getCor();
	Cor getCorAtual();
	void obterCor(Uint8& r, Uint8& g, Uint8& b, Uint8& a);
	void obterCorAtual(Uint8& r, Uint8& g, Uint8& b, Uint8& a);
	void setCor(Cor c);
	void setCor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	double getDuracao();
	void setDuracao(double t);

protected:
	Cor cor;

	double tempo;
	double duracao;

	bool executandoFadeIn;
	bool executandoFadeOut;
	bool _terminouFadeIn;
	bool _terminouFadeOut;
};

#endif
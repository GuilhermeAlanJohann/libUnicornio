#ifndef UNI_SPRITE_H
#define UNI_SPRITE_H

#include "SpriteSheet.h"
//#include "libUnicornio.h"

class Sprite
{
private:
	SpriteSheet* sheet;
	int frame_atual;
	int anim_atual;
	float tempo_anim;
	float vel_anim;
	float escala_x;
	float escala_y;
	SDL_Rect clip;
	float ancora_x;
	float ancora_y;
	SDL_RendererFlip flip_mode;
	bool animacao_ao_contrario;
	bool pause;
	SDL_Color cor;
	bool terminou_anim;
	

public:
	Sprite();
	Sprite(const Sprite& cp);
	~Sprite();

	Sprite& operator=(const Sprite &r);
	bool operator==(const Sprite &r);
	bool operator!=(const Sprite &r);

	float getAncoraX();
	float getAncoraY();
	float getEscalaX();
	float getEscalaY();
	int	getLargura();			//	escalado
	int getAltura();			//	escalado
	int	getLarguraOriginal();	//	não escalado
	int getAlturaOriginal();	//	não escalado
	int getAnimacaoAtual();
	int getFrameAtual();
	bool getPause();
	bool getInverterX();
	bool getInverterY();
	int getCorVermelho();
	int getCorVerde();
	int getCorAzul();
	int getCorAlpha();
	SpriteSheet* getSpriteSheet();

	void obterAncora(float &x, float &y);
	void obterEscala(float &sx, float& sy);
	void obterTamanho(int &w, int &h);			//	escalado
	void obterTamanhoOriginal(int &w, int &h);	//	não escalado
	void obterCor(int &vermelho, int &verde, int &azul);
	void obterCor(int &vermelho, int &verde, int &azul, int &alpha);

	bool terminouAnimacao();

	void setAncora(float x, float y);
	void setEscala(float sx, float sy);
	void setAnimacao(int anim, bool recomecar = false);
	void setFrame(int frame);
	void setPause(bool p);
	void setVelocidadeAnimacao(float vel);
	void setInverterX(bool b);
	void setInverterY(bool b);
	void setCor(int vermelho = 255, int verde = 255, int azul = 255, int alpha = 255);
	void setCorVermelho(int vermelho);
	void setCorVerde(int verde);
	void setCorAzul(int azul);
	void setCorAlpha(int alpha);
	void setAnimacaoAoContrario(bool b);
	void setSpriteSheet(string nome);
	void setSpriteSheet(SpriteSheet* sheet);

	void recomecarAnimacao();
	void avancarAnimacao();
	void avancarAnimacao(float dt);
	bool desenhar(int x, int y, float rot = 0);
};

#endif
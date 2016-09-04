#ifndef UNI_BOTAOSPRITE_H
#define UNI_BOTAOSPRITE_H

#include "uniAPI.h"
#include "Sprite.h"

enum UNI_API EstadoBotaoSprite
{
	BOTAOSPRITE_NORMAL,
	BOTAOSPRITE_COM_MOUSE_EM_CIMA,
	BOTAOSPRITE_ABAIXADO,
	NUMERO_DE_ESTADOS_BOTAOSPRITE
};

class UNI_API BotaoSprite
{
public:
	BotaoSprite();
	~BotaoSprite();

	bool setSpriteSheet(SpriteSheet *spritesheet);
	bool setSpriteSheet(string spritesheet);

	void atualizar();
	void atualizar(double dt);
	void desenhar();

	bool estaClicado();
	bool estaComMouseEmCima();
	bool estaAbaixado();
	bool mudouEstado();
	bool mouseEntrouEmCima();
	bool mouseSaiuDeCima();

	Vetor2D getPos();
	float getX();
	float getY();

	EstadoBotaoSprite getEstado();
	Sprite *getSprite();

	int getAnimacaoDoEstado(EstadoBotaoSprite estado);
	int getAnimacaoDoEstadoNormal();
	int getAnimacaoDoEstadoComMouseEmCima();
	int getAnimacaoDoEstadoAbaixado();

	int getBotaoMouse();

	void obterPos(float &x, float &y);

	void setPos(Vetor2D pos);
	void setPos(float x, float y);
	void setX(float x);
	void setY(float y);

	void setEstado(EstadoBotaoSprite estado);

	void setAnimacaoDoEstado(EstadoBotaoSprite estado, int anim);
	void setAnimacaoDoEstadoNormal(int anim);
	void setAnimacaoDoEstadoComMouseEmCima(int anim);
	void setAnimacaoDoEstadoAbaixado(int anim);
	
	void setBotaoMouse(int botao);

private:
	void atualizarEstadoMouse();
	void atualizarEstadoToque();
	bool estaDentroDoRetangulo(int x, int y);

	Vetor2D pos;
	bool clicado;
	bool mudou;
	bool mouse_entrou;
	bool mouse_saiu;

	Sprite spr;
	EstadoBotaoSprite estado;
	int anims[NUMERO_DE_ESTADOS_BOTAOSPRITE];

	int botao_mouse;
};

#endif
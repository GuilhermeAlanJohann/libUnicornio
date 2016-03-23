#pragma once
#include "libUnicornio.h"

class Agente : public MaquinaDeEstados
{
public:
	Agente();
	~Agente();

	void inicializar();
	bool finalizar();		//	Reimplementação do método virtual

	void atualizar();		//	Reimplementação do método virtual
	void desenhar();

	Sprite* getSprite();
	Vetor2D getPos();
	float getRot();

	void setPos(Vetor2D p);
	void setRot(float r);

private:
	Sprite spr;
	Vetor2D pos;
	float rot;
};


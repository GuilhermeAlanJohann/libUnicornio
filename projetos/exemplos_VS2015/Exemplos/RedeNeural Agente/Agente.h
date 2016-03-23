#pragma once

#include "libUnicornio.h"
#include "RedeNeural.h"
#include <list>

class Comida;
class Ambiente;

struct Sensor
{
	Sensor() {};
	~Sensor() {};

	Comida* comida;
	Vetor2D dist;
	float comprimento;
};

class Agente
{
public:
	Agente();
	~Agente();

	void inicializar(Ambiente* ambiente);
	void atualizar();
	void desenhar();

	Vetor2D getPos();
	float getRot();
	Sprite& getSprite();
	RedeNeural* getRede();

	void setTreinando(bool b);
	bool getTreinando();

	void setDesenharSensores(bool b);
	bool getDesenharSensores();

private:
	void atualizarSensores();
	void desenharSensores();

	Sprite spr;
	Vetor2D pos;
	Vetor2D dir;
	float rot;
	float vel;
	float velRot;

	//	Rede neural estática para treinar a mesma rede em todos os agentes
	static RedeNeural rede;	

	list<Sensor> sensores;
	Ambiente* ambiente;
	int numSensores;

	bool treinando;
	bool _desenharSensores;
	Vetor2D dirIdeal;
};


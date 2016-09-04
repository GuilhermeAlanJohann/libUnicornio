#ifndef UNI_TRAVESSIAASTAR_H
#define UNI_TRAVESSIAASTAR_H

#include "uniAPI.h"
#include "AStar.h"

class UNI_API TravessiaAStar
{
public:
	TravessiaAStar();
	~TravessiaAStar();

	void avancar();
	void avancar(float dt);

	void reiniciar();
	void interromper();
	void continuar();

	float getVelocidade();
	float getTempo();
	float getDuracao();
	Vetor2D getDeslocamento();
	Vetor2D getPos();
	Vetor2D getDirecao();

	bool estaParado();
	bool estaInterrompendo();
	bool interrompeu();
	bool terminou();
	bool caminhoEstaVazio();

	void setVelocidade(float velocidade);
	void setTempo(float tempo);
	void setDeslocamento(float desloc_x, float desloc_y);
	void setDeslocamento(Vetor2D desloc);
	void setCaminho(const vector<NodoAStar>& caminho, bool reiniciar = true);
	void setPos(Vetor2D pos);
	void setDirecao(Vetor2D dir);

private:
	inline void limitarTempo();

	float vel;
	float tempo;
	Vetor2D deslocamento;
	Vetor2D pos;
	Vetor2D dir;
	vector<NodoAStar> caminho;
	bool interrompendo;
	bool _interrompeu;
	bool _terminou;
	int nodo_final;	//	usado somente quando a travessia eh interrompida
};

#endif
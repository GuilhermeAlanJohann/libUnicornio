#include "TravessiaAStar.h"
#include "Global.h"


TravessiaAStar::TravessiaAStar()
{
	vel = 1.0f;
	tempo = 0.0f;
	deslocamento.set(0.5f, 0.5f);
	pos = deslocamento;
	dir.set(0.0f, 0.0f);
	interrompendo = false;
	_interrompeu = false;
	_terminou = false;
	nodo_final = -1;
}

TravessiaAStar::~TravessiaAStar()
{
}

void TravessiaAStar::avancar()
{
	avancar(gTempo.getDeltaTempo());
}

void TravessiaAStar::avancar(float dt)
{
	if (estaParado())
		return;

	//	avanca o tempo e limita
	tempo += dt;
	limitarTempo();

	//	calc nodos
	int nodo_ant = tempo * vel;
	int nodo_prox = nodo_ant + 1;

	//	chegou no final (terminou)
	if(nodo_prox > caminho.size() - 1)
	{
		pos = caminho[nodo_ant].pos + deslocamento;
		dir.set(0.0f, 0.0f);
		_terminou = true;
		interrompendo = false;
		return;
	}
	//	esta interrompendo
	else if (interrompendo)
	{
		if (nodo_prox > nodo_final)
		{
			pos = caminho[nodo_ant].pos + deslocamento;
			dir.set(0.0f, 0.0f);
			_interrompeu = true;
			interrompendo = false;
			return;
		}
	}
	//	calc pos e dir
	float t = tempo - (nodo_ant / vel);
	pos = caminho[nodo_ant].pos + (caminho[nodo_prox].posRelativa * t * vel) + deslocamento;
	dir = caminho[nodo_prox].posRelativa;
}

void TravessiaAStar::reiniciar()
{
	tempo = 0.0f;
	interrompendo = false;
	_interrompeu = false;
	_terminou = false;

	if (caminho.empty())
	{
		pos = deslocamento;
		dir.set(0.0f, 0.0f);
	}
	else
	{
		pos = caminho[0].pos + deslocamento;

		if(caminho.size() > 1)
			dir = caminho[1].posRelativa;
		else
			dir.set(0.0f, 0.0f);
	}
}

void TravessiaAStar::interromper()
{
	if (!estaParado())
	{
		interrompendo = true;
		nodo_final = 1 + (tempo * vel);
	}
}

void TravessiaAStar::continuar()
{
	interrompendo = false;
	_interrompeu = false;
}

float TravessiaAStar::getVelocidade()
{
	return vel;
}

float TravessiaAStar::getTempo()
{
	return tempo;
}

float TravessiaAStar::getDuracao()
{
	return caminho.size() / vel;
}

Vetor2D TravessiaAStar::getDeslocamento()
{
	return deslocamento;
}

Vetor2D TravessiaAStar::getPos()
{
	return pos;
}

Vetor2D TravessiaAStar::getDirecao()
{
	return dir;
}

bool TravessiaAStar::estaParado()
{
	return _interrompeu || _terminou || caminho.empty();
}

bool TravessiaAStar::estaInterrompendo()
{
	return interrompendo;
}

bool TravessiaAStar::interrompeu()
{
	return _interrompeu;
}

bool TravessiaAStar::terminou()
{
	return _terminou;
}

bool TravessiaAStar::caminhoEstaVazio()
{
	return caminho.empty();
}

void TravessiaAStar::setVelocidade(float velocidade)
{
	vel = velocidade;
}

void TravessiaAStar::setTempo(float tempo)
{
	this->tempo = tempo;
	limitarTempo();
}

void TravessiaAStar::setDeslocamento(float desloc_x, float desloc_y)
{
	setDeslocamento(Vetor2D(desloc_x, desloc_y));
}

void TravessiaAStar::setDeslocamento(Vetor2D desloc)
{
	deslocamento = desloc;
}

void TravessiaAStar::setCaminho(const vector<NodoAStar>& caminho, bool reiniciar_)
{
	this->caminho = caminho;
	if (reiniciar_)
	{
		reiniciar();
	}
	else if (caminho.empty())
	{
		pos = deslocamento;
		dir.set(0.0f, 0.0f);
	}
	else
	{
		pos = deslocamento + caminho[0].pos;

		if (caminho.size() > 1)
			dir = caminho[1].posRelativa;
		else
			dir.set(0.0f, 0.0f);
	}
}

void TravessiaAStar::setPos(Vetor2D pos)
{
	this->pos = pos;
}

void TravessiaAStar::setDirecao(Vetor2D dir)
{
	this->dir = dir;
}

void TravessiaAStar::limitarTempo()
{
	float tempoMax = caminho.size() / vel;
	if (tempo > tempoMax)
		tempo = tempoMax;
	else if (tempo < 0)
		tempo = 0;
}
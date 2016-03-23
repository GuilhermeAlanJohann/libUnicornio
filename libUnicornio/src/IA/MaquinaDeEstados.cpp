#include "MaquinaDeEstados.h"
#include "Estado.h"
#include "Global.h"


MaquinaDeEstados::MaquinaDeEstados()
{
	proxEstado = 0;
	estadoAtual = 0;
	trocandoEstado = false;
	inicializada = false;
}

MaquinaDeEstados::~MaquinaDeEstados()
{
}

bool MaquinaDeEstados::inicializar(Estado* estado)
{
	if (estaInicializada())
	{
		gDebug.erro("Impossivel inicializar MaquinaDeEstados, pois ela já está inicializada.", this);
		return false;
	}
	
	if (!estado)
	{
		gDebug.erro("Impossivel inicializar MaquinaDeEstados, com estado nulo.", this);
		return false;
	}

	estado->setMaquinaDeEstados(this);
	estadoAtual = estado;
	estado->entrar();
	trocandoEstado = false;
	proxEstado = 0;

	aoInicializar();

	inicializada = true;
	return true;
}

bool MaquinaDeEstados::finalizar()
{
	if (!estaInicializada())
	{
		gDebug.erro("Impossivel finalizar MaquinaDeEstados, pois ela não está inicializada.", this);
		return false;
	}

	aoFinalizar();

	if (proxEstado)
	{
		delete proxEstado;
		proxEstado = 0;
	}

	if (estadoAtual)
	{
		estadoAtual->sair();
		delete estadoAtual;
		estadoAtual = 0;
	}

	trocandoEstado = false;
	inicializada = false;
	return true;
}

void MaquinaDeEstados::aoInicializar()
{}

void MaquinaDeEstados::aoFinalizar()
{}

void MaquinaDeEstados::atualizar(float dt)
{
	if (!estaInicializada())
		return;

	while (trocandoEstado)
	{
		trocandoEstado = false;
		estadoAtual->sair();
		delete estadoAtual;
		estadoAtual = proxEstado;
		proxEstado = 0;
		estadoAtual->entrar();
	}

	estadoAtual->atualizar(dt);
}

void MaquinaDeEstados::trocarEstado(Estado* proxEstado)
{
	if (!proxEstado)
		return;

	if (this->proxEstado)
		delete this->proxEstado;

	proxEstado->setMaquinaDeEstados(this);
	this->proxEstado = proxEstado;
	trocandoEstado = true;
}

void MaquinaDeEstados::atualizar()
{
	atualizar(gTempo.getDeltaTempo());
}

bool MaquinaDeEstados::estaInicializada()
{
	return inicializada;
}
#include "MaquinaDeEstadosComPilha.h"
#include "Estado.h"
#include "Global.h"

MaquinaDeEstadosComPilha::MaquinaDeEstadosComPilha()
{
	empilhandoEstado = false;
	desempilhandoEstado = false;
}

MaquinaDeEstadosComPilha::~MaquinaDeEstadosComPilha()
{}

bool MaquinaDeEstadosComPilha::inicializar(Estado* estado)
{
	if (!MaquinaDeEstados::inicializar(estado))
		return false;

	pilhaDeEstados.push(estado);
	empilhandoEstado = false;
	desempilhandoEstado = false;
	return true;
}

bool MaquinaDeEstadosComPilha::finalizar()
{
	estadoAtual = 0;

	if (!MaquinaDeEstados::finalizar())
		return false;

	while (!pilhaDeEstados.empty())
	{
		Estado* e = pilhaDeEstados.top();
		e->sair();
		delete e;
		pilhaDeEstados.pop();
	}

	empilhandoEstado = false;
	desempilhandoEstado = false;
	return true;
}

void MaquinaDeEstadosComPilha::atualizar(float dt)
{
	if (!estaInicializada())
		return;

	Estado *estado;

	if (pilhaDeEstados.empty())
	{
		if(!proxEstado)
			return;

		trocandoEstado = false;
		empilhandoEstado = false;
		desempilhandoEstado = false;

		pilhaDeEstados.push(proxEstado);
		proxEstado = 0;
		estado = pilhaDeEstados.top();
		estado->entrar();
	}
	else
		estado = pilhaDeEstados.top();

	while (trocandoEstado)
	{
		trocandoEstado = false;
		
		if (empilhandoEstado)
		{
			empilhandoEstado = false;
			estado->sair();

			pilhaDeEstados.push(proxEstado);
			proxEstado = 0;

			estado = pilhaDeEstados.top();
			estado->entrar();
		}
		else if (desempilhandoEstado)
		{
			estado->sair();
			delete estado;
			pilhaDeEstados.pop();

			desempilhandoEstado = false;

			if (pilhaDeEstados.empty())
				return;

			estado = pilhaDeEstados.top();
			estado->entrar();
		}
		else
		{
			estado->sair();
			delete estado;
			pilhaDeEstados.pop();

			pilhaDeEstados.push(proxEstado);
			proxEstado = 0;
			estado = pilhaDeEstados.top();
			estado->entrar();
		}
	}

	estado->atualizar(dt);
}

void MaquinaDeEstadosComPilha::atualizar()
{
	atualizar(gTempo.getDeltaTempo());
}

void MaquinaDeEstadosComPilha::trocarEstado(Estado* proxEstado)
{
	MaquinaDeEstados::trocarEstado(proxEstado);
	empilhandoEstado = false;
	desempilhandoEstado = false;
}

void MaquinaDeEstadosComPilha::empilharEstado(Estado *estado)
{
	if (!estado)
		return;

	if (this->proxEstado)
		delete this->proxEstado;

	proxEstado = estado;
	proxEstado->setMaquinaDeEstados(this);

	trocandoEstado = true;
	empilhandoEstado = true;
	desempilhandoEstado = false;
}

void MaquinaDeEstadosComPilha::desempilharEstado()
{
	if(proxEstado)
	{
		delete proxEstado;
		proxEstado = 0;
	}

	trocandoEstado = true;
	empilhandoEstado = false;
	desempilhandoEstado = true;
}

bool MaquinaDeEstadosComPilha::temEstados()
{
	return !pilhaDeEstados.empty();
}
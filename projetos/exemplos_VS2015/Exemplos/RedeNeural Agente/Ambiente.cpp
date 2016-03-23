#include "Ambiente.h"



Ambiente::Ambiente()
{
}


Ambiente::~Ambiente()
{
}

void Ambiente::inicializar()
{
	//	Inicializar a semente do rand
	uniRandSetSemente(time_t(NULL));

	//	Inicializar as comidas com posição aleatória
	for (unsigned int i = 0; i < NUM_COMIDAS; ++i)
	{
		Comida c;
		//	Fazer o rand entre dois vetores nos dá uma posição aleatória na area formada pelos dois vetores
		c.pos = uniRandEntre(Vetor2D(0, 0), Vetor2D(gJanela.getLargura(), gJanela.getAltura()));
		c.spr.setSpriteSheet("branco");
		c.spr.setCor(0, 255, 0);
		c.indice = i;
		comidas.push_back(c);
	}

	//	Inicialiar os agentes com posição aleatória
	for (unsigned int i = 0; i < NUM_AGENTES; ++i)
	{
		agentes.push_back(Agente());
		//	Passamos o ponteiro para o ambiente, pois o agente
		//	precisa conhecer o ambiente para saber o que fazer.
		agentes[i].inicializar(this);
	}
}

void Ambiente::finalizar()
{
	comidas.clear();
	agentes.clear();
}

void Ambiente::atualizar()
{
	//	Atualizar input
	if (gTeclado.pressionou[TECLA_ENTER])
	{
		for (unsigned int i = 0; i < NUM_AGENTES; ++i)
			agentes[i].setTreinando(!agentes[i].getTreinando());
	}

	if (gTeclado.pressionou[TECLA_D])
	{
		for (unsigned int i = 0; i < NUM_AGENTES; ++i)
			agentes[i].setDesenharSensores(!agentes[i].getDesenharSensores());
	}

	if (gTeclado.pressionou[TECLA_S])
	{
		//	Como a rede neural é estatica, ou seja, a mesma para todos os agentes, 
		//	basta salvar a primeira.
		if(UNI_PLATAFORMA_MOVEL)
			agentes[0].getRede()->salvarPesos(uniGetCaminhoPreferencias() + "rede neural.pesos_agente.txt");
		else
			agentes[0].getRede()->salvarPesos("assets/rede neural/pesos_agente.txt");
	}

	if (gTeclado.pressionou[TECLA_C])
	{
		//	Como a rede neural é estatica, ou seja, a mesma para todos os agentes, 
		//	basta carregar a primeira.
		if (UNI_PLATAFORMA_MOVEL)
			agentes[0].getRede()->carregarPesos(uniGetCaminhoPreferencias() + "rede neural.pesos_agente.txt");
		else
			agentes[0].getRede()->carregarPesos("assets/rede neural/pesos_agente.txt");
	}

	gDebug.depurar("treinando", agentes[0].getTreinando());
	gDebug.depurar("desenhandoSensores", agentes[0].getDesenharSensores());

	//	Atualizar agentes
	for (unsigned int i = 0; i < NUM_AGENTES; ++i)
		agentes[i].atualizar();

	//	Atualizar colisoes
	atualizarColisoes();
}

void Ambiente::desenhar()
{
	//	Desenhar comidas
	for (unsigned int i = 0; i < NUM_COMIDAS; ++i)
		comidas[i].spr.desenhar(comidas[i].pos.x, comidas[i].pos.y);

	//	Desenhar Agentes
	for (unsigned int i = 0; i < NUM_AGENTES; ++i)
		agentes[i].desenhar();
}

void Ambiente::atualizarColisoes()
{
	for (int i = 0; i < NUM_COMIDAS; ++i)
	{
		Vetor2D posC = comidas[i].pos;
		for (int j = 0; j < NUM_AGENTES; ++j)
		{
			Vetor2D posA = agentes[j].getPos();
			float rotA = agentes[j].getRot();

			if (uniTestarColisaoSpriteComSprite(agentes[j].getSprite(), posA.x, posA.y, rotA, comidas[i].spr, posC.x, posC.y, 0))
			{
				sortearPosComida(i);
			}
		}
	}
}

void Ambiente::sortearPosComida(int indice)
{
	do
	{
		comidas[indice].pos = uniRandEntre(Vetor2D(0, 0), Vetor2D(gJanela.getLargura(), gJanela.getAltura()));

	}	//	mantêm o loop enquanto a comida está colidindo com algum agente 
	while (comidaColidiuComAlgumAgente(indice));
}

Comida& Ambiente::getComida(int indice)
{
	return comidas[indice];
}

bool Ambiente::comidaColidiuComAlgumAgente(int indice)
{
	for (int j = 0; j < NUM_AGENTES; ++j)
	{
		if (uniTestarColisaoCirculoComCirculo(comidas[indice].pos.x, comidas[indice].pos.y, 50, agentes[j].getPos().x, agentes[j].getPos().y, 50))
			return true;
	}
	return false;
}